import request from 'postman-request'
import chalk from 'chalk'
import { config } from './config.js'

export function requestWeather(latitude, longitude, callback) {
    const apiKey = "access_key=" + config.weatherStack.apiKey
    const query = `query=${latitude},${longitude}`
    const url = config.weatherStack.endpoint + "current?" + apiKey + "&" + query
    const options = {
        url,
        json: true
    }
    
    request(options, (error, response, body) => {
        if (error) {
            callback(`인터넷이 연결되지 않았습니다.`, undefined)
            return
        }
        if (body.error) {
            callback(`서버 처리 중 실패했습니다.`, undefined)
            return
        }

        const currentWeather = body.current
        const weatherState = currentWeather.weather_descriptions[0]
        const temperature = chalk.bgYellowBright(currentWeather.temperature)
        const feelsLike = chalk.bgGreenBright(currentWeather.feelslike)
    
        callback(
            undefined,
            `${weatherState} throughout a day. Temperture is ${temperature} degrees, and it feels like ${feelsLike} degrees.`
        )
    })
}

export function requestGeology(location, callback) {
    const endpoint = config.mapBox.endpoint
    const apiKey = config.mapBox.apiKey
    const url = `${endpoint}${location}.json?access_token=${apiKey}&limit=1`
    const options = {
        url,
        json: true
    }

    request(options, (error, response, body) => {
        if (error) {
            callback("인터넷 연결에 이상이 있습니다.", undefined)
            return
        }
        if (!body.features.length) {
            callback("서버 요청 중 오류가 발생했습니다.", undefined)
            return
        }
        const coordinate = body.features[0].center
        const latitude = coordinate[1]
        const longitude = coordinate[0]

        callback(undefined, {latitude, longitude})
    })
}
