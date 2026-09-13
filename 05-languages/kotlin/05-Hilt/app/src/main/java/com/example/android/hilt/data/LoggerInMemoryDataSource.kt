package com.example.android.hilt.data

import dagger.hilt.android.scopes.ActivityScoped
import java.util.*
import javax.inject.Inject

// 액티비티 단위에서 동작한다.
@ActivityScoped
class LoggerInMemoryDataSource @Inject constructor(
): LoggerDataSource {

    private val logs = LinkedList<Log>()

    override fun addLog(msg: String) {
        logs.addFirst(Log(msg, System.currentTimeMillis()))
    }

    override fun getAllLogs(callBack: (List<Log>) -> Unit) {
        callBack(logs)
    }

    override fun removeLogs() {
        logs.clear()
    }
}