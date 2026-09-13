import request from 'postman-request'
import { config } from './config.js'

const apiKey = "access_key=" + config.weatherStack.apiKey
const query = "query=Busan"
const url = config.weatherStack.endpoint + "current?" + apiKey + "&" + query


export function requestCurrentWeather() {
    request(url, (error, response, body) => {
        const json = JSON.parse(body)
        const weatherInfo = json.current
        console.log(weatherInfo)
    })
}

