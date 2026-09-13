package com.example.android.hilt.data

// 앱 사용 동안의 로그 (Application 스코프)
interface LoggerDataSource {
    fun addLog(msg: String)
    fun getAllLogs(callBack: (List<Log>) -> Unit)
    fun removeLogs()
}