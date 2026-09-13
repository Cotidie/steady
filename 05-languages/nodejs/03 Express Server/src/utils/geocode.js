import request from 'postman-request'

const host = "https://api.mapbox.com/geocoding/v5/mapbox.places/"
const apiKey = "pk.eyJ1IjoiY290aWRpZSIsImEiOiJjbDNiNHhzZzMwODRtM3BydW11eXMzdjU3In0.AqLK3FOMRB9qel8tNtvwqA"

export function requestGeology(location, callback) {
    const url = `${host}${location}.json?access_token=${apiKey}&limit=1`
    const options = {
        url,
        json: true
    }

    request(options, (error, response, body) => {
        if (error) {
            callback("인터넷 연결에 이상이 있습니다.", {})
            return
        }
        if (!body.features.length) {
            callback("적절한 주소를 찾을 수 없습니다. 다시 입력해주세요.", {})
            return
        }

        console.log(body)

        const coordinate = body.features[0].center
        const latitude = coordinate[1]
        const longitude = coordinate[0]
        const location = body.features[0].text

        callback(undefined, {latitude, longitude, location})
    })
}
