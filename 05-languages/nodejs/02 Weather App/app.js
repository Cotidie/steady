import chalk from 'chalk'
import * as openApi from './lib/open-api.js'

const city = process.argv[2]
if (!city) {
    console.log(`Please provide a geocode or a city name`)
    process.exit(1)
}

openApi.requestGeology(city, (error, { latitude, longitude } = {}) => {
    if (error) return console.log(error)

    openApi.requestWeather(latitude, longitude, (error, forecast = '') => {
        if (error) return console.log(error)

        console.log(chalk.inverse(`${city}'s Weather`))
        console.log(forecast)
    })
})