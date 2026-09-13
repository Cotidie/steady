package com.example.calculator

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Button
import kotlinx.android.synthetic.main.activity_main.*
import java.lang.NumberFormatException

class MainActivity : AppCompatActivity() {
    // FSM으로 개선 가능
    var operand1: Double? = null
    var operand2: Double? = null
    var operator: String? = null
    var temp: String? = null       // 피연산자 할당 전 임시저장할 곳

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }

    fun onDigit(view: View) {
        val txt = (view as Button).text.toString()
        // 0이 처음으로 입력되어서는 안 된다.
        if (txt.equals("0") && isFirstDigit()) return

        if (temp == null) temp = txt
        else temp += txt
        txtResult.append(txt)
    }

    fun onOperator(view: View) {
        // 연산자는 하나만 허용한다.
        if (!this.operator.isNullOrEmpty()) return
        // 연산자부터 입력되어서는 안 된다.
        if (operand1 == null && temp == null) return
        // 현재까지 입력된 값이 실수로 변환 가능해야 한다.
        if (!isParsableToDouble(temp)) return

        val btn = view as Button
        this.operator = btn.text.toString()
        this.operand1 = temp?.toDouble(); temp = null

        txtResult.append(this.operator)
    }

    // 음수 기호인지 먼저 판단해야 한다.
    fun onMinus(view: View) {
        // 피연산자를 처음 입력하는 경우에만 음수기호이다.
        if (!isFirstDigit()) return onOperator(view)

        // 이제 temp는 null이다.
        val btn: Button = view as Button
        temp = btn.text.toString()
        txtResult.append(btn.text)
    }

    fun onDot(view: View) {
        // 소수점은 하나만 있어야 한다.
        if (temp != null && temp!!.contains(".")) return

        val dot: String = (view as Button).text.toString()
        if (temp == null) temp = dot
        else temp += dot

        txtResult.append(dot)
    }

    fun onEqual(view: View) {
        // 계산할 모든 요소가 갖추어져야 한다.
        if (operand1 == null || operator == null || temp == null) return
        // 입력한 숫자가 실수로 변환 가능해야 한다.
        if (!isParsableToDouble(temp)) return

        // 값 계산 및 결과창에 표시
        operand2 = temp?.toDouble()
        val calculated = calculate() ?: return
        var toPrint: String = calculated.toString()
        // 정수이면 소수점 이하를 없앤다.
        if (Math.floor(calculated) == calculated)
            toPrint = calculated.toInt().toString()
        txtResult.text = toPrint


        // 다음 계산 준비
        clear()
        temp = toPrint
    }

    fun onClear(view: View) {
        clear()
        txtResult.text = ""
    }

    private fun calculate(): Double? {
        when (operator) {
            "+" -> return operand2?.let { operand1?.plus(it) }
            "-" -> return operand2?.let { operand1?.minus(it) }
            "/" -> return operand2?.let { operand1?.div(it) }
            "*" -> return operand2?.let { operand1?.times(it) }
        }

        return null
    }

    private fun isParsableToDouble(str: String?): Boolean {
        if (str == null) return false

        try {
            str.toDouble()
            return true
        } catch (e: NumberFormatException) {
            return false
        }
    }

    private fun isFirstDigit(): Boolean {
        // 피연산자1 입력단계
        if (operand1 == null && temp == null) return true
        // 피연산자2 입력단계
        if (operator != null && operand2 == null && temp == null) return true

        return false
    }

    private fun clear() {
        operand1 = null; operand2 = null
        operator = null; temp = null
    }
}