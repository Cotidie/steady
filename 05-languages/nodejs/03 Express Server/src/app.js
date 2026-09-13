import express from 'express'
import path from 'path'
import hbs from 'hbs'
import { forecastWeahter } from './utils/forecast.js'

const app = express()
const port = process.env.PORT || 3000     // 개발용 포트

const dirname = path.resolve()
const staticPath = path.join(dirname, 'static')
const viewsPath = path.join(dirname, 'templates', 'views')
const partialsPath = path.join(dirname, 'templates', 'partials')

app.set('view engine', 'hbs')
app.set('views', viewsPath)
hbs.registerPartials(partialsPath)

app.use('/static', express.static(staticPath))

app.get('', (req, res, next) => {
    res.render('index', {
        title: "Weather!",
        name: "WSJ"
    })
})

app.get('/about', (req, res) => {
    res.render('about', {
        title: "About Me",
        name: "WSJ"
    })
})

app.get('/help', (req, res) => {
    res.render('help', {
        title: 'Help',
        name: "WSJ",
        helpText: 'How can I help you?'
    })
})

app.get('/weather', (req, res) => {
    const address = req.query.address
    if (!address) {
        return res.send({
            errorMessage: "Address query should be passed!"
        })
    }

    forecastWeahter(address, (error, forecast) => {
        if (error) {
            return res.send({ error })
        }
        
        return res.send({ forecast })
    })
})

app.get('/help/(.*)', (req, res) => {
    res.status(404).send("Help page not found")
})

app.get('(.*)', (req, res) => {
    res.render('404', {
        title: 'Page Not Found',
        name: "WSJ",
        errorMessage: "페이지를 찾을 수 없습니다."
    })
})

app.listen(port, function() {
    console.log(path.resolve())
})