# Weather App
![Weather App 스크린샷](https://user-images.githubusercontent.com/51331195/169198609-c68077b2-243b-43ca-816e-6e60a3db466d.png)

 지역, 도시 또는 국가명을 인자로 입력하면 현재 날씨와 온도, 체감 온도를 알려주는 앱. 다음과 같은 기능을 구현해야 한다.
- Open API를 활용해 필요한 정보를 불러온다.
  - 지역, 도시, 국가명으로부터 위도와 경도를 알아낸다. (MapBox)
  - 위도와 경도로부터 날씨 정보를 불러온다. (Weather Stack)
- API 통신과 관련된 오류 처리를 해야 한다
  - (Low): 인터넷과 연결되지 않은 경우
  - (Middle): 잘못된 쿼리 인자 등 서버 측 오류
- 통신 결과를 활용하기 위해 콜백함수를 이용한다.
  - 가독성을 위해 Object Property Shorthand, Destructure를 이용한다.
   
## 목차
- [Event Loop](#event-loop)
- [HTTP Request](#http-request)
  - [Standard Library(http, https)](#standard-libraryhttp-https)
  - [NPM Library(postman-request)](#npm-librarypostman-request)
- [Callback](#callback)
- [ES6 Features](#es6-features)
  - [Object Property Shorthands](#object-property-shorthands)
  - [Object Desctructing](#object-desctructing)
- [Open API](#open-api)
  - [Weather Stack](#weather-stack)
  - [Mapbox](#mapbox)
  
## 배운점
### Event Loop
![Event Loop](https://i.imgur.com/zCgCjYs.png)
Node.js는 기본적으로 싱글 스레드이며 병렬적으로 처리되지 않는다. 싱글 스레드 위에서 병렬 처리를 위해 Node.js는 Call Stack과 구분되는 Node API, Event Loop를 둔다. 프로그램은 이 모든 영역이 비어 있어야 종료된다.
* **Node API**: C++ 라이브러리를 활용하는 멀티 스레드 영역
  * 시간을 재거나 I/O 작업 등이 이루어진다.
  * 작업이 끝나면 콜백 함수가 Event Loop로 전달된다. 
* **Event Loop**: Call Stack이 비워지면 도착한 순서대로 콜백 함수를 실행한다.
```js
console.log('Starting')

// Basic Async Function
setTimeout(() => {
    console.log('After 2 seconds')
}, 2000)
setTimeout(() => {
    console.log('After 0 seconds')
}, 0)

console.log('Stopping')

// 실행결과
Starting
Stopping
After 0 seconds
After 2 seconds
```

### HTTP Request
#### Standard Library(http, https)
```js
// 프로토콜에 따라 다른 STL을 사용한다.
import https from 'https'
import http from 'http'

const options = {
  host: 'www.random.org',
  path: '/integers/?num=1&min=1&max=1',
  port: '1337',  // 서버측 1337번 포트와 소켓 형성
  method: 'POST'
}

// HTTP 요청에 대한 응답을 처리할 콜백함수
const callback(response) {
  let buffer = ''

  // 패킷을 받을 때마다 buffer에 담는다. 
  // chunk는 buffer이다.
  response.on('data', (chunk) => {
    buffer = buffer + chunk.toString()
  })

  // 모든 패킷을 수신한 경우
  // 온전한 JSON으로 옮긴다.
  response.on('end', () => {
    const json = JSON.parse(buffer)
  })
}

// Error Handling
https.on('error', (error) => {
  ...
})

// HTTP Requester 빌드
const req = https.request(options, callback)

// req.write(string)으로 body에 데이터를 추가해나간다.
// 모든 데이터를 추가했으면 end()로 request를 날린다.
req.write('Hello!')
req.end()
```
Node.js가 제공하는 http, https 라이브러리를 활용한다. 이 라이브러리는 패킷 단위로 받아 통신의 끝 시점에 이를 개발자가 파싱해야 한다. 

#### NPM Library(postman-request)
```js
import requst from 'postman-request'

const options = {
  url: url,            // 요청 보낼 URL
  json: boolean        // body를 JSON으로 파싱 및 Header에 Content-type: application/json 추가
}

requenst(options, (error, response, body) => {
  // Error Handling: error와 response는 둘 중 하나가 undefined이다.
  if (error) {
    console.log("인터넷 연결에 이상이 있습니다.")
    return
  }
  if (body.error) {
    console.log("서버 요청 중 오류가 발생했습니다.")
    return
  }

  const json = body
  ...
})
```
[postman-request](https://www.npmjs.com/package/postman-request) 라이브러리를 이용하면 간편하게 요청을 보낼 수 있다. 

### Callback
```js
// callback은 (error, data) => {} 의 형식을 취한다.
export function requestGeology(location, callback) {
  request(options, (error, response, body) => {
    if (error) {
        callback("인터넷 연결에 이상이 있습니다.", undefined)
        return
    }
    callback(undefined, body.data)
  )
}
```
Async 함수의 결과를 활용하고자 한다면 콜백함수를 전달해야 한다. 이때 자료형이 정해져 있지 않으므로 주석이나 API 문서를 남길 필요가 있다.

### ES6 Features
#### Object Property Shorthands
```js
// 속성명과 변수명이 같으면 다음과 같이 축약할 수 있다.
const name = 'Jason'
const age = 10

// 아래는 {name: 'Jason', age: 10}과 같다.
const obj = {name, age}
```

#### Object Desctructing
```js
const product = {
    name: 'ref',
    price: 1000,
    stock: 1.2
}

// 속성과 동일한 이름의 변수에 값이 들어간다.
const {price, stock} = product
// 다른 이름으로 정의할 경우
// 존재하지 않는 속성에 대해서 기본값을 지정할 수 있다.
const {price: pPrice, stock: pStock, rating=5} = product
// 이는 함수의 가독성을 개선하는 데에 이용할 수 있다.
function releaseMovie(date, { title, desc }) {
  ...
}
```


### Open API
#### [Weather Stack](https://weatherstack.com/)
위도와 경도 또는 지역/도시 명을 토대로 상세한 날씨 정보를 알려주는 서비스.

#### [Mapbox](https://docs.mapbox.com/api/search/geocoding/)
위도와 경도 <-> 지역/도시명 사이 변환해주는 서비스.
