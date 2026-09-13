import request from 'postman-request'

const host = "http://api.weatherstack.com/"
const apiKey = "d87a77a5ad6342ad9ea5ff3696d70c65"

export function requestWeather(latitude, longitude, location, callback) {
    const query = `query=${latitude},${longitude}`
    const url = host + "current?access_key=" + apiKey + "&" + query
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
        const temperature = currentWeather.temperature
        const feelsLike = currentWeather.feelslike
    
        callback(
            undefined,
            `${location} is ${weatherState} throughout a day. Temperture is ${temperature} degrees, and it feels like ${feelsLike} degrees.`
        )
    })
}