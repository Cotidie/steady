console.log("Client-Side js is loaded.")

const host = 'http://localhost'
const port = 3000
const endpoint = 'weather'

const form = document.querySelector('form')
const input = document.querySelector('input')
const resultText = document.querySelector('#forecast')

form.addEventListener('submit', (event) => {
    // 페이지 새로고침을 막는다
    event.preventDefault()

    const address = input.value
    const query = `address=${address}`
    const url = `/${endpoint}?${query}`
    fetch(url).then((response) => {
        response.json().then((data) => {
            if (data.error) {
                forecast.textContent = data.error
            } else {
                forecast.textContent = data.forecast
            }
        })
    })
})