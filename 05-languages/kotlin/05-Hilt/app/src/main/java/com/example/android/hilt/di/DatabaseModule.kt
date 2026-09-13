package com.example.android.hilt.di

import android.content.Context
import android.util.Log
import androidx.room.Room
import com.example.android.hilt.data.AppDatabase
import com.example.android.hilt.data.LogDao
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.android.components.ActivityComponent
import dagger.hilt.android.qualifiers.ActivityContext
import dagger.hilt.android.qualifiers.ApplicationContext
import dagger.hilt.android.scopes.ActivityScoped
import dagger.hilt.components.SingletonComponent
import javax.inject.Singleton

@InstallIn(ActivityComponent::class)
@Module
class DatabaseModule {
    @Provides
    fun provideLogDao(database: AppDatabase): LogDao {
        Log.d("디버그", "AppDatabase Created")
        return database.logDao()
    }

    @Provides
    @ActivityScoped
    fun provideDatabase(@ActivityContext appContext: Context): AppDatabase {
        return Room.databaseBuilder(
            appContext,
            AppDatabase::class.java,
            "logging.db"
        ).build()
    }
}