package com.example.roomwithview

import android.util.Log
import androidx.lifecycle.*
import com.example.roomwithview.room.entity.Word
import com.example.roomwithview.room.entity.WordInsert
import com.example.roomwithview.room.repository.WordRepository
import kotlinx.coroutines.launch

class WordViewModel(val repository: WordRepository) : ViewModel() {
    // Flow를 LiveData로 변환
    val allWords: LiveData<List<Word>> = repository.allWords.asLiveData()

    // Main 쓰레드에서 word 넣기
    // repository는 Room이나 Retrofit을 이용하므로 Main-Safe이다.
    fun insert(word: WordInsert) = viewModelScope.launch {
        repository.insert(word)
    }
}

class WordViewModelFactory(private val repository: WordRepository): ViewModelProvider.Factory {
    override fun <T : ViewModel> create(modelClass: Class<T>): T {
        if (modelClass.isAssignableFrom(WordViewModel::class.java)) {
            @Suppress("UNCHECKED_CAST")
            return WordViewModel(repository) as T
        }
        throw IllegalArgumentException("Unknown ViewModel class")
    }
}