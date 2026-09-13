# Note App
![nodejs note app](https://user-images.githubusercontent.com/51331195/168443997-715fa1fa-1868-488d-9f60-39d9f5c4ade2.png)  
제목(title)과 본문(body)를 같는 메모를 notes.json에 저장하고 불러오는 앱. 다음과 같은 명령어를 제공한다.
* **add**: --title, --body 옵션을 받아 notes.json에 저장한다.
    * 동일한 title이 있으면 오류 메시지를 출력한다.
* **list**: notes.json에 저장중인 메모를 모두 불러와 출력한다.
* **read**: --title 옵션을 받아 제목(styled)과 본문을 출력한다.
    * 찾는 title이 없으면 오류 메시지를 출력한다.
* **remove**: --title 옵션을 받아 제목과 일치하는 메모를 notes.json에서 삭제한다.
    * 찾는 title이 없으면 오류 메시지를 출력한다.

## 목차
- [Note App](#note-app)
  - [목차](#목차)
  - [배운점](#배운점)
    - [**require**](#require)
    - [**import/export**](#importexport)
    - [**NPM**](#npm)
    - [**Array**](#array)
    - [**Arrow Function**](#arrow-function)
    - [**I/O**](#io)
      - [File System](#file-system)
      - [Command Line](#command-line)
      - [JSON Read/Write](#json-readwrite)
    - [**Debug**](#debug)
    - [**Third Party Packages**](#third-party-packages)
  - [오류](#오류)
    - [**import 오류**](#import-오류)
    - [**Powershell 보안 오류**](#powershell-보안-오류)
    - [**import, require 동시 사용**](#import-require-동시-사용)

## 배운점
### **require**
기본 모듈의 사용법은 [공식 문서](https://nodejs.org/docs/latest-v17.x/api/)에서 확인 가능하다.
```js
// test.js
// 기본 라이브러리는 모듈명으로 import한다.
// require 순간에 모듈이 실행된다.
const fs = require('fs')

const name = "myName"
const add = function (a, b) { return a + b } // 함수도 export 가능

// require(module)의 반환값을 설정
// exports는 최상위 객체로, Object를 담는다.
module.exports = {
    name: name,
    add: add
}

// 다른 파일에서 사용
const test = require('test.js')
test.name          // myName
test.add(1, 2)     // 3
```
### **import/export**
Node.js 13.2 버전부터 지원하는 ES 기능. 파일은 .mjs 확장자여야 하며, 외부로 export하고자 하는 함수, 변수 앞에 export 키워드를 붙인다.
* package.json에 ```type: "module"```을 추가한 경우 .js도 가능
```js
// test.mjs
export add(a, b) { return a + b }
export const PI = 3.141592

// 다른 파일
import { add, PI } from './test.mjs'
import * as test from './test.mjs'
```

### **NPM**
Node.js Package Manager. 터미널을 통해 설치하고 패키지 간 종속성을 관리한다.
* 패키지 저장소: [https://www.npmjs.com/](https://www.npmjs.com/)
```js
> npm init
// 패키지 설치 및 삭제 (-g: 전역 패키지)
> npm install <package name>@version
> npm install <package name>@version -g
> npm uninstall <package name>
> npm uninstall <package name> -g

// 전역 패키지 설치는 되도록 피해야 한다.
// 대신 dev Dependency로 설치하고, script로 실행한다.
> npm install <package name>@version --save-dev
// package.json
{
    ...
    "script": {
        "dev": "nodemon app.js -e js, hbs"
    },
    "devDependencies": {
        ...
    }
}
> npm run dev

// 종속성 설치 (package.json)
> npm install 
```

### **Array**
* forEach: 배열의 각 원소를 순회한다. ```const notes = ["a", "b", "c"]```에 대하여,
```js
for (const note of notes) { // async friendly
    ...
}
for (const [index, value] of notes.entries()) { // indexedForEach
    ...
}
notes.forEach((element, index) => { // not async friendly
    ...
})
```
* filter: 조건에 맞는 요소만을 필터링하여 새로운 배열로 반환한다.
```js
const filtered = notes.filter(function(note) {
    return note !== "b"
}) // ["a", "c"]
```
* find: filter와 다르게 조건을 만족하는 하나를 찾아 반환한다. 없을 경우 undefined를 반환한다.
```js
const found = notes.find((note) => note == "b")
const notFound = notes.find((note) => note == "$")
console.log(found) // b
console.log(notFound) // undefined
```

### **Arrow Function**
: Arrow Function은 람다와 같은 개념이나, this가 메소드의 위치에 바인드되지 않고 메소드를 사용하는 곳에 바인드되는 특징이 있다. this의 위치에 따라 기존 function 문법을 적절히 섞어 사용한다.
```js
const event = {
    title: "Birthday Party",
    people: ["Andrew", "Tom", "Lily"],
    printInfo() {
        // event를 가리키는 this를 사용할 것이므로 function 구문을 사용한다.
        console.log("The event is", this.title)

        // function 구문을 사용할 때, forEach의 this는 global obejct이다.
        // 또는 2번째 매개변수에 전달한 객체가 this가 된다.
        this.people.forEach(function(name, index) {
            console.log("Person:", this.people[index])
        }, this)

        // Arrow Function을 호출하는 곳은 printInfo()이므로 이 scope의 this가 바인드된다.
        this.people.forEach((name, index) => {
            console.log("Arrow Function:", this.people[index])
        })
    }
}
```

### **I/O**
#### File System
```js
const fs = require('fs')

// 파일쓰기 : fs.writeFile
fs.writeFileSync(fileName, data);  // 파일 쓰기
fs.appendFileSync(fileName, data); // 내용 추가하기
```

#### Command Line
```js
> node app.js WSJ

// app.js
console.log(process.argv)

// 출력 결과
[node 실행파일경로, 현재파일 경로, <CLI 입력값, ...>]
```

#### JSON Read/Write
```js
import fs from 'fs'

// Read: Binary Buffer -> String -> JSON
const buffer = fs.readFileSync('1-json.json')
const data = buffer.toString()
const json = JSON.parse(data)
console.log(json)

// Write: Object -> JSON String
fs.writeFileSync('2-json.json', JSON.stringify(json))s
```

### **Debug**
![nodejs Debugger](https://user-images.githubusercontent.com/51331195/168444350-0c6aebe0-da02-432c-8506-e03d6317ccfa.png)
Node.js 전용 debugger를 사용하며, ```node ~~```대신에  ```node inspect ~~```으로 프로세스를 실행하여 디버거를 부착한다. 디버거는 Chrome의 chrome://inspect/에서 확인할 수 있으며, 코드 중 ```debugger``` 줄을 넣어 Breakpoint를 설정한다.

### **Third Party Packages**
[**Validator**](https://www.npmjs.com/package/validator): 이메일, 전화번호 등 여러 양식을 검사해주는 패키지
```js
> npm install validator
import validator from 'validator';
```

[**chalk**](https://www.npmjs.com/package/chalk): 로그 메시지에 색상을 입히는 패키지. 로그 메시지에 대해서 Chaining으로 여러 스타일링이 가능하다.
```js
// Modifier, Color, Background로 스타일링 가능
// - Modifier: bold, dim, reset, italic, underline, inverse, strikethrough...
// - Color: green, blue, black, gray ...
// - Background: bgGreen, bgBlue, bgBlack ...
import chalk from 'chalk'
const successMsg = chalk.white.bgGreen.bold("Success!!")
console.log(successMsg)
```

[**nodemon**](https://www.npmjs.com/package/nodemon): 실행한 .js/.mjs 파일의 변경 마다 자동으로 재시작하도록 하는 패키지. .js/.mjs 실행 시 node 대신 nodemon으로 실행한다.

[**Yargs**](https://www.npmjs.com/package/yargs): CLI 입력과 그 옵션 값에 대해 손쉽게 파싱해주는 패키지. .mjs(Module, ES)를 지원하지 않으므로 require를 사용해야 한다.
```js
> node input.js add --title="aaa"

// input.js
const yargs = require('yargs')
// process.argv 대신 yargs.argv
console.log(yargs.argv)  // { _: [ 'remove' ], title: 'aaa', '$0': 'input.js' }
// 명령어 추가
yargs.command({
    command: "add",
    describe: "Add a new note",
    // Options Builder
    builder: {
        title: {
            describe: "Set a note's title",
            demandOption: true,
            type: 'string'
        }
    },
    // The first argument is always argv
    handler: function(argv) {
        console.log("Adding a new note! (" + argv['title'] + ")")
    }
})

// yargs 사용 명시
yargs.parse()
```

## 오류
### **import 오류**
 최상위 js 파일이 아닌, 모듈 또는 폴더 내 js 파일에서 ```import``` 문을 사용할 경우 다음과 같은 오류를 출력한다.  
| ```Cannot use import statement outside a module```
=> package.json에 다음과 같이 type 속성을 추가하거나 파일 확장자 명을 mjs로 바꾸어야 한다. mjs는 해당 파일이 node.js에서 사용할 ES 모듈임을 명시한다.
```js
// package.json
{
  "type": "module"
}
```

### **Powershell 보안 오류**
Windows Powershell이 제3자 스크립트 실행을 제한하는 문제. Powershell을 관리자의 권한으로 실행하여 ```Set-ExecutionPolicy Unrestricted```를 입력하여 외부 스크립트를 실행 가능하도록 한다.

### **import, require 동시 사용**
.mjs 확장자 또는 ```type: "module"```이 명시된 경우 require을 사용할 수 없던 문제. 다음 두 줄을 파일에 추가하여 import와 require을 동시에 사용할 수 있다.
```js
import { createRequire } from "module";
const require = createRequire(import.meta.url);
```
