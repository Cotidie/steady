package com.example.android.hilt.data

import android.util.Log
import dagger.hilt.android.scopes.ActivityScoped
import javax.inject.Inject
import javax.inject.Singleton


class Counter @Inject constructor(){
    private var value = 0

    fun increase() {
        value += 1
    }

    fun decrease() {
        value -= 1
    }

    fun show() {
        Log.d("카운터값", value.toString())
    }
}