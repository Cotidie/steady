package com.example.quizapp

import android.util.Log

// 모든 Activity에서 이용할 클래스 (Object => Singleton)
// 데이터 클래스 Question을 이용한다.
object Constants {
    val flags = mapOf<String, Int>(
        "Argentina" to R.drawable.ic_flag_of_argentina,
        "Austrailia" to R.drawable.ic_flag_of_australia,
        "Belgium" to R.drawable.ic_flag_of_belgium,
        "Brazil" to R.drawable.ic_flag_of_brazil,
        "denmark" to R.drawable.ic_flag_of_denmark,
        "Fiji" to R.drawable.ic_flag_of_fiji,
        "Germany" to R.drawable.ic_flag_of_germany,
        "India" to R.drawable.ic_flag_of_germany,
        "Kuwait" to R.drawable.ic_flag_of_kuwait,
        "New Zealand" to R.drawable.ic_flag_of_new_zealand
    )

    fun getQeustions(n: Int): ArrayList<Question> {
        fun getOptions(answer: String): List<String> {
            val options = ArrayList<String>()
            val incorrectAnswers = flags.keys
                .minus(answer)
                .shuffled()
                .subList(0, 3)

            options.add(answer)
            options.addAll(incorrectAnswers)

            return options.shuffled()
        }
        assert(n <= flags.size) {"퀴즈 개수는 국기 개수 이하여야 합니다."}

        val questionString = "What country does this belong to?"
        val questions = ArrayList<Question>()
        val answers = flags.keys.shuffled()

        for (i in 1..n) {
            val correctAnswer = answers.get(i-1)
            val options = getOptions(correctAnswer)
            val answerIndex = options.indexOf(correctAnswer)

            questions.add(Question(
                i, questionString,
                flags.get(correctAnswer)!!,
                options.get(0), options.get(1),
                options.get(2), options.get(3),
                answerIndex
            ))
        }

        return questions
    }
}