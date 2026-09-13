# Web Server
![webserver](https://i.imgur.com/uY5EKbT.gif)

동적 템플릿을 이용하여 웹 페이지를 렌더링하는 서버. 이전에 제작한 일기예보를 활용하여 입력한 주소지의 날씨를 알려준다.
* index, about, help 페이지를 갖는다.
  * localhost:3000/: index 페이지
  * localhost:3000/about: about 페이지
  * localhost:3000/help: help 페이지
  * 네비게이션 메뉴를 갖는 header와 작성자를 표지하는 footer의 partial을 이용한다.
  * 유효하지 않은 주소로 접근할 시 404 페이지를 반환한다.
* index 페이지의 input에 도시명을 입력할 시 현재 날씨를 알려준다.
  * 오류일 경우 오류 메시지를 표시한다.
  * 정상일 경우 다음 형식으로 표시한다.
    * ```${location} is ${weatherState} throughout a day. Temperture is ${temperature} degrees, and it feels like ${feelsLike} degrees.```

## 목차
- [Web Server](#web-server)
  - [목차](#목차)
  - [배운점](#배운점)
    - [Absolute Path](#absolute-path)
    - [Express.js](#expressjs)
      - [Middle-Ware](#middle-ware)
      - [Routing](#routing)
      - [Static files](#static-files)
      - [Dynamic Templates](#dynamic-templates)
    - [NPM package](#npm-package)
      - [hbs](#hbs)
    - [Heroku Deployment](#heroku-deployment)
  - [오류](#오류)
    - [__dirname undefined](#__dirname-undefined)

## 배운점
### Absolute Path
```js
import path from 'path'

// node가 실행된 절대경로를 반환한다.
const dirname = path.resolve()
// <루트경로>/src/hello/a.js
const somePath = path.join(dirname, "src", "hello", "a.js")
```
path는 디렉토리 경로를 파싱하는 STL로, 경로명을 이어붙일 때에 유용하다.

### Express.js
[Express.js](https://expressjs.com/en/starter/installing.html)는 API 구축을 간편하게 하는 서버 프레임워크이다. 서버 사이드 렌더링, 서버-클라이언트 구조, 웹/모바일 등 다양하게 활용할 수 있으며 간결한 인터페이스를 제공한다.
| 메소드 | 설명 |
| ------ | ---- |
| app/router.use(path, callback)  | 모든 METHOD에 대해 실행할 Application/Router 레벨 미들웨어를 등록 |
| app/router.METHOD(path, callback) | 특정 HTTP 메소드에 대해 실행할 Application/Router 레벨 미들웨어를 등록 |
| app.set(name, value) | 서버 동작 중 사용할 전역 변수를 담는다. 일부 단어는 특수한 용도로 쓰이는 키워드이며 [여기](http://expressjs.com/en/5x/api.html#app.settings.table)서 확인 가능 |
| app.get(name) | app.set()에서 설정한 변수 값을 불러온다 |
| response.render(view, data) | /views 폴더의 뷰 엔진(hbs 등) 템플릿을 HTML로 렌더링하여 반환한다. |

#### Middle-Ware
![mw](https://media.geeksforgeeks.org/wp-content/uploads/20211007175759/MiddlewareChaining.png)  
Middle-Ware 함수는 Express.js의 핵심 중 하나로, request, response 및 다음 middle-ware 함수에 대한 접근 권한을 갖는 콜백 함수를 말한다. 라우터의 콜백 함수 또한 middle-ware 함수이며, Application 레벨과 Router 레벨로 구분하여 등록한다.
* middle-ware 함수는 등록된 순서대로 실행된다. (Queue)
* application 레벨의 middle-ware는 반드시 next()를 실행해야 한다.
  * next()는 **큐**에서 다음 middle-ware 함수를 실행한다.
  * 실행하지 않을 경우 request는 끝나지 않고, 클라이언트는 계속 대기한다.
  * next('router')를 통해 middle-ware 실행을 종료할 수 있다.
* router 레벨의 middle-ware는 next()를 실행하지 않아도 된다.
  * next() 호출이 없으면 그곳에서 middle-ware 실행이 끝난다.
  * next() 호출이 있으면 **큐**에서 다음 middle-ware 함수를 실행한다. (application 레벨)
```js
const route = express.Router()

// 실행되어야 하나, next('router')에 의하여 실행되지 않는다.
route.get('/middle', (req, res, next) => {
    console.log("라우터 레벨 /middle 미들웨어")
    res.send("끝!")
})

// 첫 번째로 실행된다.
app.get('/middle', (req, res, next) => {
    console.log("앱 레벨 /middle 미들웨어")
    next()
})

// 두 번째로 실행된다.
app.use('/', (req, res, next) => {
    console.log("전역 Middle ware 함수")
    res.send("전역 middle-ware에서 종료")
    next('router')
})

app.use('/', route)

// 출력결과
"앱 레벨 /middle 미들웨어"
"전역 Middle ware 함수"
```


#### Routing
```js
import express from 'express'

const app = express()
const port = 3000

// app.<method>로 라우팅 설정
app.get('/path',(req, res) => {
    // query는 req.query로 접근한다 (object)
    const query = req.query
    res.send(<Response Body>)
})

// Error Handler: 404 page
// 위쪽에 정의된 모든 경로와 매칭되지 않을 경우 라우팅되므로
// 항상 마지막에 정의되어야 하며, 와일드카드는 소괄호로 감싸준다.
app.get('/help/(.*)', (req, res) => {
    res.status(404).send("Help page not found")
})

app.get('(.*)', (req, res) => {
    res.send('404: File Not Found')
})

app.listen(port, () => {
    // 앱 구동 직후 실행할 콜백
})
```
* res.send는 HTML 문자열 또는 Object(JSON)을 인자로 받는다.

#### Static files
```js
import express from 'express'
import path from 'path'

const app = express()
const dirname = path.resolve()
const staticPath = path.join(dirname, 'public')
const staticServe = express.static(staticPath)

// 이제 localhost:3000/static은 public 폴더를 가리킨다.
app.use('/static', staticServe)

// html 등에서 절대경로로 활용할 수 있다
<link rel="stylesheet" href="/static/style.css"/>
```

#### Dynamic Templates
```js
// partialPath/footer.hbs
<footer>Created by {{name}}</footer>

// viewsPath/about.hbs
<html>
    ...
    <p>My name is {{name}}</p>
    // partial은 {{>}}에 입력한다.
    {{>footer}}
    ...
</html>

// .js
import hbs from 'hbs'

app.set('view engine', 'hbs')
app.set('views', viewsPath)
hbs.registerPartials(partialsPath)

router.get('/about', (req, res, next) => {
    res.render('about', {
        name: 'Aqua'
    })
})
```
hbs 등 뷰 엔진을 이용해 동적 HTML 템플릿을 이용한다. 컴포넌트 역할을 하는 Partial과 템플릿 역할을 하는 View로 구분된다. Partial이 필요로 하는 변수명은 해당 partial에 숨겨져 있는 점은 불편하다.
* **app.set('views', path)**: 템플릿을 찾을 폴더의 경로를 설정한다.
* **app.render(view, variables)**: 렌더링할 뷰 엔진 파일과 내부의 변수를 설정한다.
* **hbs.registerPartials(partialsPath)**: 컴포넌트 역할을 할 partial들이 위치한 경로를 설정한다.

### NPM package
#### hbs
* 패키지 주소: [hbs](https://www.npmjs.com/package/hbs)
express.js를 위한 view 엔진. Dynamic HTML Template을 지원한다.

### Heroku Deployment
1. **스크립트 설정**: ```npm run start```, heroku에서 진입점을 설정한다.
```js
// package.json
{
  ...
  "scripts": {
    "start": <앱 구동 경로>,
  },
  ...
}
```
2. **port 번호 설정**: heroku 서버에서 사용할 port 번호를 설정한다. 포트 번호는 실행마다 달라질 수 있다. 
```js
//app.js
const port = process.env.PORT || 3000
app.listen(port, function() {
    // 구동 직후 실행할 스크립트
})
```
3. **heroku 연동**: heroku에 생성된 앱은 전용 git remote에 저장되고, CI/CD에 의해 배포된다. 이 저장소를 로컬로 옮긴다.
  * package.json에 종속성이 모두 명시되어 있어야 한다.
```js
// package.json이 위치한 루트폴더에서 실행
> git init
> heroku git:remote -a <existing app>
> git remote
heroku
> git add .
> git commit -m "..."
> git push heroku master
<빌드 진행>
```
## 오류
### __dirname undefined
* **문제**: 전역 변수로 제공되던 __dirname, __filename이 더이상 존재하지 않는 문제
* **원인**: ES6에서는 __dirname, __filename이 path 라이브러리로 대체되었다.
* **해결**
```js
import path from 'path'
const dirname = path.resolve()
```
