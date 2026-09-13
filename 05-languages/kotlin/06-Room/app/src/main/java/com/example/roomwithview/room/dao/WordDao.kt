package com.example.roomwithview.room.dao

import androidx.room.Dao
import androidx.room.Insert
import androidx.room.OnConflictStrategy
import androidx.room.Query
import com.example.roomwithview.room.entity.Word
import com.example.roomwithview.room.entity.WordInsert
import kotlinx.coroutines.flow.Flow

@Dao
interface WordDao {
    @Query("SELECT * FROM table_word ORDER BY word ASC")
    fun getAlphabetizedWords() : Flow<List<Word>>

    @Insert(entity=Word::class, onConflict = OnConflictStrategy.IGNORE)
    suspend fun insert(word: WordInsert)

    @Query("DELETE FROM table_word")
    suspend fun deleteAll()
}