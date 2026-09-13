package com.example.quizapp

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import com.example.quizapp.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {
    lateinit var viewBinding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        // 뷰 바인딩
        viewBinding = ActivityMainBinding.inflate(layoutInflater)

        // 기능 설정
        val btnStart = viewBinding.btnStart
        btnStart.setOnClickListener {
            startQuiz()
        }

        setContentView(viewBinding.root)
    }

    private fun startQuiz() {
        val etName = viewBinding.etName
        if (etName.text.isNullOrEmpty()) {
            Toast.makeText(this,
                "Please enter your name", Toast.LENGTH_SHORT)
                .show()
        } else {
            // 현재 -> QuizApp Activity
            val intent = Intent(this, QuizQuestionsActivity::class.java)
            startActivity(intent)
            finish() // 현재 Activity 종료
        }
    }
}