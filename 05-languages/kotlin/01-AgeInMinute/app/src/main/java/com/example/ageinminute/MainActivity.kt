package com.example.ageinminute

import android.app.DatePickerDialog
import android.os.Build
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Toast
import androidx.annotation.RequiresApi
import kotlinx.android.synthetic.main.activity_main.*
import java.text.SimpleDateFormat
import java.time.LocalDate
import java.util.*

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        btn_select_date.setOnClickListener { view ->
            clickDatePicker(view)
        }
    }

    fun clickDatePicker(view: View) {
        val myCalendar = Calendar.getInstance()
        val year = myCalendar.get(Calendar.YEAR)
        val month = myCalendar.get(Calendar.MONTH)
        val day = myCalendar.get(Calendar.DAY_OF_MONTH)

        // 날짜선택창
        val dpd = DatePickerDialog(this,
            DatePickerDialog.OnDateSetListener { view, year, month, dayOfMonth ->
                val sdf = SimpleDateFormat("dd/MM/yyyy", Locale.KOREA)
                val selectedTime = sdf.parse("$dayOfMonth/${month+1}/$year")!!.time
                val currentDate = sdf.format(System.currentTimeMillis()); debugByToast(currentDate)
                val currentTime = sdf.parse(currentDate)!!.time

                val daysBetween = (currentTime - selectedTime) / (1000*60*60*24)

                age_in_day.setText(daysBetween.toString())
            }, year, month, day)

        // 최대 선택가능 날짜를 하루 전으로 설정
        dpd.datePicker.maxDate = Date().time - (1000*60*60*24)
        dpd.show()
    }

    fun debugByToast(str: String) {
        Toast.makeText(this, str, Toast.LENGTH_SHORT).show()
    }
}