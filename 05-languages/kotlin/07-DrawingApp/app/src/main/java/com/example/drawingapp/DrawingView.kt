package com.example.drawingapp

import android.content.Context
import android.graphics.*
import android.util.AttributeSet
import android.view.MotionEvent
import android.view.View

class DrawingView(context: Context, attrs: AttributeSet) : View(context, attrs) {
    private var mDrawPath: CustomPath? = null
    private var mCanvasBitmap: Bitmap? = null
    private var mDrawPaint: Paint? = null
    private var mCanvasPaint: Paint? = null
    private var mBrushSize: Float = 0F
    // View가 그려질 화면과 그 색상
    private var canvas: Canvas? = null
    private var color = Color.BLACK
    // 그려진 Path를 저장할 곳
    private val mPaths = ArrayList<CustomPath>()

    // Primary Constructor 이후에 실행
    init {
        setupDrawing()
    }

    private fun setupDrawing() {
        mDrawPath = CustomPath(color, mBrushSize)
        mDrawPaint = Paint()
        mDrawPaint!!.color = color
        mDrawPaint!!.style = Paint.Style.STROKE
        mDrawPaint!!.strokeJoin = Paint.Join.BEVEL
        mDrawPaint!!.strokeCap = Paint.Cap.ROUND
        mCanvasPaint = Paint(Paint.DITHER_FLAG)
        mBrushSize = 20F
    }

    // Path에 색상과 굵기 추가
    inner class CustomPath(
        var color: Int,
        var brushThickness: Float
    ) : Path()

    // 액티비티 시작 시 함께 실행
    override fun onSizeChanged(w: Int, h: Int, oldw: Int, oldh: Int) {
        super.onSizeChanged(w, h, oldw, oldh)

        mCanvasBitmap = Bitmap.createBitmap(w, h, Bitmap.Config.ARGB_8888)
        canvas = Canvas(mCanvasBitmap!!)
    }


    override fun onDraw(canvas: Canvas?) {
        super.onDraw(canvas)
        // 초기화하지 않으면 Path는 계속 덧씌워진다 => 메모리 낭비
        canvas?.drawBitmap(mCanvasBitmap!!, 0f, 0f, mCanvasPaint)

        for (path in mPaths) {
            mDrawPaint!!.strokeWidth = path.brushThickness
            mDrawPaint!!.color = path.color
            canvas?.drawPath(path, mDrawPaint!!)
        }

        if (!mDrawPath!!.isEmpty) {
            mDrawPaint!!.strokeWidth = mDrawPath!!.brushThickness
            mDrawPaint!!.color = Color.GREEN
            canvas?.drawPath(mDrawPath!!, mDrawPaint!!)
        }
    }

    // 약 1픽셀 단위로 수없이 호출된다.
    override fun onTouchEvent(event: MotionEvent?): Boolean {
        val touchX = event?.x
        val touchY = event?.y

        when(event?.action) {
            MotionEvent.ACTION_DOWN -> {
                mDrawPath!!.color = color
                mDrawPath!!.brushThickness = mBrushSize

                // moveTo 설정 등을 초기화
                mDrawPath!!.reset()
                // lineTo의 시작점 제공
                mDrawPath!!.moveTo(touchX!!, touchY!!)
            }
            MotionEvent.ACTION_UP -> {
                // 선 초기화
                // 아래 invalidate()에서 초기화되면서 화면에서 사라짐
                mPaths.add(mDrawPath!!)
                mDrawPath = CustomPath(color, mBrushSize)
            }
            MotionEvent.ACTION_MOVE -> {
                mDrawPath!!.lineTo(touchX!!, touchY!!)
            }
            else -> return false
        }
        // onDraw() 호출
        invalidate()

        return true
    }
}