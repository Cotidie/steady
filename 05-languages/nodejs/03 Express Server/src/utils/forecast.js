import * as geocode from './geocode.js'
import * as weather from './weather.js'

export function forecastWeahter(location, callback) {
    if (!location) {
        callback('No Location is given', undefined)
        return
    }

    geocode.requestGeology(location, (error, { latitude, longitude, location }) => {
        if (error) {
            callback(error, undefined)
            return
        }

        weather.requestWeather(latitude, longitude, location, (error, forecast) => {
            if (error) {
                callback(error, undefined)
                return
            }

            callback(undefined, forecast)
        })
    })
}