# Quiz App

# 배운점
* **ViewModel LifeCycle**: 생성과 소멸만을 주기로 갖고, Activity/Fragment가 소멸할 때 함께 소멸한다.
  * ViewModelProvider: Activity/Fragment와 생명주기 연계
  * ViewModelFactory: ViewModel의 생성자에 인자 전달
```kotlin
class GameViewModel: ViewModel() {
    init {
        Log.d("디버그: 초기화", "GameViewModel Initiated.")
    }

    override fun onCleared() {
        super.onCleared()
        Log.d("디버그: 종료", "GameViewModel Cleared")
    }
}
```
* **ViewModelProvider**: 소유 UI(Activity/Fragment)와 class 형식을 인자로 넘겨 인스턴스를 받는다. 소유 UI가 완전히 소멸되면 ViewModel도 소멸된다. (회전 등 재시작 제외)
```kotlin
private lateinit var viewModel: GameViewModel
...
viewModel = ViewModelProvider(this).get(GameViewModel::class.java)
```
* **ViewModelFactory**: 아래와 같은 템플릿으로 작성하여 ViewModel의 생성자에 인자를 넘긴다.
```kotlin
// Factory 정의
class ScoreViewModelFactory (private val <인자값>) : ViewModelProvider.Factory {
    override fun <T : ViewModel?> create(modelClass: Class<T>): T {
        if (modelClass.isAssignableFrom(ScoreViewModel::class.java)) {
            return ScoreViewModel(<인자값>) as T
        }
        throw IllegalArgumentException("Unknown ViewModel class")
    }
}

// Fragment, Activity에서 이용
private lateinit var viewModel: ScoreViewModel
private lateinit var viewModelFactory: ScoreViewModelFactory
...
viewModelFactory = ScoreViewModelFactory(<인자값>)
viewModel = ViewModelProvider(this, viewModelFactory)
        .get(ScoreViewModel::class.java)
```
* **LiveData**: LiveData에 Observer를 달아 데이터변경마다 콜백함수를 호출하도록 한다. 이때 Fragment와 Fragment's View의 사소한 차이로 인해 두 제약은 반드시 지켜야 한다.
  * onCreateView()에서 Observe한다.
  * viewLifeCycleOwner를 인자로 전달한다.  
  * backing property로 캡슐화한다. (외부에는 Non-Mutable)
```Kotlin
// LiveData 정의
class GameViewModel : ViewModel() {
    // The current word
    val _word = MutableLiveData<String>()
    // The current score
    val _score = MutableLiveData<Int>()
    val word: LiveData<String>
        get() = _word
    val score: LiveData<Int>
        get() = _score
    ...
}

// Fragment에서 이용
viewModel.score.observe(viewLifecycleOwner, Observer { newScore ->
    binding.scoreText.text = newScore.toString()
})
```


# 이슈
