# Quiz App

# 배운점
* **View Drawing**: View 요소를 직접 화면에 그리는 방법. Canvas > Bitmap > Path, Paint의 계층구조로 렌더링한다.
```kotlin
// View를 상속받은 클래스

// 액티비티 시작 시 함께 실행
override fun onSizeChanged(w: Int, h: Int, oldw: Int, oldh: Int) {
    super.onSizeChanged(w, h, oldw, oldh)

    mCanvasBitmap = Bitmap.createBitmap(w, h, Bitmap.Config.ARGB_8888)
    canvas = Canvas(mCanvasBitmap!!)
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

override fun onDraw(canvas: Canvas?) {
    super.onDraw(canvas)
    // 초기화하지 않으면 Path는 계속 덧씌워진다 => 메모리 낭비
    canvas?.drawBitmap(mCanvasBitmap!!, 0f, 0f, mCanvasPaint)

    if (!mDrawPath!!.isEmpty) {
        mDrawPaint!!.strokeWidth = mDrawPath!!.brushThickness
        mDrawPaint!!.color = Color.GREEN
        canvas?.drawPath(mDrawPath!!, mDrawPaint!!)
    }
}
```


# 이슈
