package com.example.android.hilt.di

import com.example.android.hilt.data.Counter
import com.example.android.hilt.data.ICounter
import dagger.Binds
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.android.components.ActivityComponent
import dagger.hilt.android.scopes.ActivityScoped
import dagger.hilt.android.scopes.FragmentScoped
import dagger.hilt.components.SingletonComponent
import javax.inject.Singleton

@InstallIn(SingletonComponent::class)
@Module
class CounterModule {

    @Provides
    fun provideCounter() : Counter {
        return Counter()
    }
}