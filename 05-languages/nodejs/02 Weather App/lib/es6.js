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

console.log(pPrice, pStock, rating)