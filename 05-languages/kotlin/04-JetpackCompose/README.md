## 학습자료
* [공식 튜토리얼](https://developer.android.com/jetpack/compose/tutorial)
* [API 문서 - material](https://developer.android.com/reference/kotlin/androidx/compose/material/package-summary#surface)
* [Notion 정리본 by Finn](https://flower-dove-ecc.notion.site/Jetpack-Compose-4425de2e58d14d479f03db53c92705ef)
* [Github 업로드](https://github.com/Cotidie/STEADY/tree/main/Kotlin)


## 배운점
 * **Modifier**: padding, clickable, clip, weight, size  
 * **Recomposition**
: State가 변경되면 해당 Composable이 다시 실행된다. 이때 remember 객체에 의해 이전과 다르게 렌더링되므로 나머지 종속변수들은 val을 사용해도 된다.
 * **Persisting State**
: remember는 Activity 생명주기 내에서 그 값을 유지한다. 화면회전, 다크모드 변경 등에 의해 Activity가 재시작되면 값이 사라지므로 대신 rememberSaveable을 위임받아야 한다.
 * **테마변경**(ui.theme > Color.kt, Theme.kt)
: 색상 팔레트는 Color에 주어진 상수값을 활용해 Theme에서 정의한다. 이를 이용하면 테마를 자유롭게 변경할 수 있다.
 * **Animation**
: animate<T>AsState는 해당 타입을 가진 State이다. 이 State를 활용하면 AnimateSpec에 전달된 설정에 따라 State를 서서히 변화시켜 Recomposition을 진행한다.
```
// spring: 애니메이션 종료 시점에 값 바운싱
// dampingRatio: 바운싱 정도
// stiffness: 바운싱 속도
val extraPadding by animateDpAsState(
    targetValue = if (isExpanded) 48.dp else 0.dp,
    animationSpec = spring(
        dampingRatio = Spring.DampingRatioHighBouncy,
        stiffness = Spring.StiffnessHigh
    )
)
// 48.dp -> 0.dp에서 음수가 될 수 있으므로 최소값 처리!
.padding(bottom = extraPadding.coerceAtLeast(0.dp))
```

* **Scrolling**
: LazyColumn, LazyRow와 함께 사용하고, 스크롤 위치는 rememberLazyListState 객체를 활용한다. LazyColumn/LazyRow는 코루틴으로 동작하는데, 수동으로 조작할 경우 코루틴이 종료된다. 이를 방지하기 위해 같은 CoroutineScope(IO, Main 등)에서 조작해야 한다. 

```
val scrollState = rememberLazyListState()
// LazyColumn이 동작하는 코루틴
val coroutineScope = rememberCoroutineScope()

Button(
    onClick = {
        coroutineScope.launch {
            scrollState.scrollToItem(items.size-1)
        }
    },
) {...}

LazyColumn(state = scrollState) {
    items(items) { item ->
        ...
    }
}
``` 
* **Custom Layout**
: 개발자가 직접 Composable의 위치를 지정할 때 이용한다. Composable은 트리 구조로 파싱되어 항상 부모와 최소/최대 사이즈를 지정하는 Constraint 속성을 지닌다. 렌더링되는 과정은 다음과 같다.
  1. @Composable -> Element(=Measureable)로 파싱된다.
  2. Measureable은 Constraint에 따라 크기를 계산한다.
    * 자식 Measureable을 재귀적으로 먼저 계산한다.
    * 계산결과 Placeable로 변환된다.  
  3. Placeable은 자식들과 자기 자신을 화면에 배치한다.
    * [Alignment Line](https://developer.android.com/jetpack/compose/layouts/alignment-lines) 값들을 토대로 정렬, 배치된다.
    * Alignment Line은 Horizontal, Vertical 두 요소로 구성됨

```
// firstBaselineToTop: 원하는 baseline 위치
fun Modifier.firstBaselineToTop(
    firstBaselineToTop: Dp
) = Modifier.layout { measurable, constraints ->
    // 제약 사항에 따라 위치를 결정한다. (본래 표시될 위치)
    val placeable = measurable.measure(constraints)

    // FirstBaseLine은 Text의 고유 Alignment Line이다.
    // 존재하지 않으면 Text가 아닌 것이다.
    check(placeable[FirstBaseline] != AlignmentLine.Unspecified)
    val firstBaseline = placeable[FirstBaseline]

    // 원하는 위치와 본래 표시될 위치의 차이
    val placeableY = firstBaselineToTop.roundToPx() - firstBaseline
    val height = placeable.height + placeableY
    layout(placeable.width, height) {
        // 부모 요소 내에서의 해당 좌표에 표시)
        // 가로세로 크기는 위 layout에 명시되어 있다.
        placeable.placeRelative(0, placeableY)
    }
}

Text("Hi there!", Modifier.firstBaselineToTop(32.dp))
```

* **Custom Layout(Group)**
: 다수의 Composable에 대해 Custom Layout을 적용한다. 이를 이용하면 원하는 기능을 갖춘 Column, Row 등을 구현할 수 있다.
```
// 기본 구조
// measurables를 순회하며 개별적으로 적용
@Composable
fun CustomLayout(
    modifier: Modifier = Modifier,
    // custom layout attributes 
    content: @Composable () -> Unit
) {
    Layout(
        modifier = modifier,
        content = content
    ) { measurables, constraints ->
        // measure and position children given constraints logic here
    }
}
```
* **modifier.height(IntrinsicSize.Min)**
: Row, Column 등이 Composable에 fillHeight(), fillWidth()를 적용할 때, Height는 부모 Constraint의 maxHeight가 된다. 그러나 measure를 끝낸 이후에 적용하면 Height/Width는 계산된 수치가 된다. 이렇게 maxHeight, maxWidth를 자식의 constraint를 따르게 하고자 IntrinsicSize.Min/Max를 이용한다.
  * [Intrinsic 적용 전](https://trello.com/1/cards/61c90f134842ff139e7d2ac2/attachments/61cab603cdb4b41777383795/download/d61f179394ded825.png)
  * [Intrinsic 적용 후](https://developer.android.com/codelabs/jetpack-compose-layouts/img/835f0b8c9f07cd9.png)



## QnA
 * Text의 일부분만 폰트, 색상을 적용하는 방법
    => Row, Column으로 감싸고 여러 Text로 쪼갠다
 * Surface의 역할
    => [When should I use Android Jetpack Compose Surface composable?](https://stackoverflow.com/questions/65918835/when-should-i-use-android-jetpack-compose-surface-composable#:~:text=android%20android%2Djetpack%20android%2Djetpack,might%20be%20done%20using%20modifiers.)  
 * by 키워드의 람다식에 전달되는 내용
   => 오버라이드하여 메소드 재정의 ([코틀린 공식문서](https://kotlinlang.org/docs/delegation.html#overriding-a-member-of-an-interface-implemented-by-delegation))
 * Composable에서 primitive 대신 remember를 사용하는 이유
```kotlin
// 단순 boolean으로 하지 않는 이유는?
var isExpanded by remember { mutableStateOf(false) }
```
    => Composable은 하나의 객체를 소유할 수 있고, remember는 바로 이 역할을 한다. Composable은 함수이기 때문에 UI를 구성하면서 멤버를 명시할 수 없다.
 * 스크롤바 표시하는 방법

## 기타 링크
  * [코틀린 by 키워드](https://velog.io/@haero_kim/Kotlin-by-%ED%82%A4%EC%9B%8C%EB%93%9C%EC%9D%98-%EC%97%AD%ED%95%A0-%EC%95%8C%EC%95%84%EB%B3%B4%EA%B8%B0)
  * [Compose Alignment Lines](https://developer.android.com/jetpack/compose/layouts/alignment-lines)
