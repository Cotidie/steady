package com.example.roomwithview

import android.app.Application
import com.example.roomwithview.room.database.WordDatabase
import com.example.roomwithview.room.repository.WordRepository
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.SupervisorJob

class WordApplication : Application() {
    val applicationScope = CoroutineScope(SupervisorJob())

    val database by lazy { WordDatabase.getDatabase(this, applicationScope) }
    val repository by lazy { WordRepository(database.wordDao()) }

}