package com.example.quizapp

import android.graphics.Color
import android.graphics.Typeface
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.TextView
import androidx.core.content.ContextCompat
import com.example.quizapp.databinding.ActivityQuizQuestionsBinding

class QuizQuestionsActivity : AppCompatActivity(), View.OnClickListener {
    lateinit var binding: ActivityQuizQuestionsBinding
    private val questionList = Constants.getQeustions(5)
    private val tvOptions = ArrayList<TextView>()
    private var currentStage: Int = 0
    private var selectedIndex: Int = -1


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityQuizQuestionsBinding.inflate(layoutInflater)

        initializeUI()
        setQuestion(currentStage)
        setContentView(binding.root)
    }

    private fun initializeUI() {
        binding.progressBar.max = questionList.size
        tvOptions.add(binding.tvOptionOne)
        tvOptions.add(binding.tvOptionTwo)
        tvOptions.add(binding.tvOptionThree)
        tvOptions.add(binding.tvOptionFour)

        for (i in 0 until tvOptions.size) {
            tvOptions.get(i).setOnClickListener {
                selectedOptionView(i)
            }
        }
        binding.btnSubmit.setOnClickListener {
            if (selectedIndex > 0) {
                answerView()
                selectedIndex = -1
            } else {
                currentStage++
                setQuestion(currentStage)
            }
        }
    }

    // idx번 퀴즈를 설정한다,
    private fun setQuestion(idx: Int) {
        val question = questionList.get(idx)
        binding.ivFlag.setImageResource(question.image)
        binding.progressBar.progress = idx+1
        binding.tvProgress.setText("${idx+1}/${binding.progressBar.max}")
        binding.tvQuestion.setText(question.question)
        binding.tvOptionOne.setText(question.optionOne)
        binding.tvOptionTwo.setText(question.optionTwo)
        binding.tvOptionThree.setText(question.optionThree)
        binding.tvOptionFour.setText(question.optionFour)

        defaultOptionsView()

        if (idx == questionList.size-1) {
            binding.btnSubmit.text = "FINISH"
        } else {
            binding.btnSubmit.text = "SUBMIT"
        }
    }

    // 옵션 TextView를 기본 스타일로 설정
    private fun defaultOptionsView() {
        for (option in tvOptions) {
            option.setTextColor(
                ContextCompat.getColor(
                    this, R.color.grey_dark
                )
            )
            option.background = ContextCompat.getDrawable(
                this, R.drawable.default_option_border_bg
            )
            option.typeface = Typeface.DEFAULT
        }
    }

    private fun selectedOptionView(selected: Int) {
        val selectedOption = tvOptions.get(selected)
        // 기본 버튼 스타일 초기화
        defaultOptionsView()
        // 선택 옵션 스타일 바꾸기
        selectedOption.setTextColor(Color.BLACK)
        selectedOption.background = ContextCompat.getDrawable(
            this, R.drawable.selected_option_border_bg
        )
        selectedOption.setTypeface(
            selectedOption.typeface,
            Typeface.BOLD
        )

        this.selectedIndex = selected
    }

    private fun answerView() {
        val question = questionList.get(currentStage)
        val selectedOption = tvOptions.get(selectedIndex)
        val answerOption = tvOptions.get(question.correctAnswer)

        answerOption.background = ContextCompat.getDrawable(
            this, R.drawable.correct_answer_border_bg
        )
        if (selectedIndex != question.correctAnswer) {
            selectedOption.background = ContextCompat.getDrawable(
                this, R.drawable.wrong_answer_border_bg
            )
            selectedOption.setTextColor(Color.GRAY)
        }
        binding.btnSubmit.setText("Go Next")
    }

    override fun onClick(v: View?) {
        Log.d("Activity Clicked: ", "Clicked!")
    }
}