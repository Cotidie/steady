package com.example.jetpacklayout

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.Image
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.lazy.rememberLazyListState
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Favorite
import androidx.compose.runtime.Composable
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.layout.AlignmentLine
import androidx.compose.ui.layout.FirstBaseline
import androidx.compose.ui.layout.Layout
import androidx.compose.ui.layout.layout
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.Dp
import androidx.compose.ui.unit.dp
import coil.compose.rememberImagePainter
import com.example.jetpacklayout.ui.theme.JetpackLayoutTheme
import kotlinx.coroutines.launch

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            JetpackLayoutTheme {
                DefaultPreview()
            }
        }
    }
}

@Composable
fun PhotographerCard(name: String) {
    Row (modifier = Modifier
        .padding(all = 8.dp)
        .clip(shape = RoundedCornerShape(4.dp))
        .clickable { }
        .padding(all = 16.dp)
    ) {
        Surface(
            color = MaterialTheme.colors.onSurface.copy(alpha = 0.2f),
            shape = CircleShape,
            modifier = Modifier.size(50.dp)
        ) {

        }

        Column(modifier = Modifier.padding(start=8.dp)) {
            Text(name, fontWeight = FontWeight.Bold)
            Text("3 minutes ago")
        }
    }
}

@Composable
fun SimpleList() {
    val scrollState = rememberLazyListState()
    val items = List(1000) {"Item $it"}
    val coroutineScope = rememberCoroutineScope()

    Column(modifier = Modifier.fillMaxWidth()) {
        Row {
            Button(
                onClick = {
                    coroutineScope.launch {
                        scrollState.scrollToItem(0)
                    }
                },
                modifier = Modifier.weight(1f)
            ) {
                Text("Top")
            }
            Button(
                onClick = {
                    coroutineScope.launch {
                        scrollState.scrollToItem(items.size-1)
                    }
                },
                modifier = Modifier.weight(1f)
            ) {
                Text("Bottom")
            }
        }
        LazyColumn(state = scrollState) {
            items(items) { item ->
                ImageItem(item)
            }
        }
    }


}

@Composable
fun ImageItem(text: String) {
    Row {
        Image(
            painter = rememberImagePainter(
                data = "https://developer.android.com/images/brand/Android_Robot.png"
            ),
            contentDescription = null,
            modifier = Modifier.size(40.dp)
        )

        Spacer(Modifier.width(5.dp))

        Text(text)
    }
}

@Composable
fun ScaffoldScreen() {
    Scaffold(
        topBar = {
            TopAppBar(
                title = {
                    Text(text = "JetpackLayout", style = MaterialTheme.typography.h4)
                },
                actions = {
                    IconButton(onClick = { /*TODO*/ }) {
                        Icon(
                            imageVector = Icons.Filled.Favorite,
                            contentDescription = "즐겨찾기")
                    }
                }
            )
        },
        bottomBar = {
            BottomNavigation {
                BottomNavigationItem(
                    icon = {Icon(Icons.Filled.Favorite, null)},
                    label = {Text("Practice")},
                    onClick = {},
                    selected = false
                )
                BottomNavigationItem(
                    icon = {Icon(Icons.Filled.Favorite, null)},
                    label = {Text("Practice")},
                    onClick = {},
                    selected = false
                )
            }
        }
    ) { innerPadding ->
        PhotographerCard(name = "Andrew")
    }
}

// firstBaselineToTop: 원하는 baseline 위치
fun Modifier.firstBaselineToTop(
    firstBaselineToTop: Dp
) = layout { measurable, constraints ->
    // Measure the composable
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

@Preview(showBackground = true)
@Composable
fun DefaultPreview() {
    JetpackLayoutTheme {
        Text("Hi there!", Modifier.firstBaselineToTop(70.dp))
    }
}