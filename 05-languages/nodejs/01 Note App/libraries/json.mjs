import fs from 'fs'

// Read: Binary Buffer -> String -> JSON
const buffer = fs.readFileSync('1-json.json')
const data = buffer.toString()
const json = JSON.parse(data)
console.log(json)

// Write: Object -> JSON String
fs.writeFileSync('2-json.json', JSON.stringify(json))