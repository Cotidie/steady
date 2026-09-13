import fs from 'fs'
import chalk from 'chalk'

export function addNote(title, body) {
    const notes = loadNotes()
    const duplicates = notes.filter((note) => note.title === title)

    debugger

    if (duplicates.length !== 0) {
        console.log("Note title is duplicated!")
        return
    }

    notes.push({
        title: title,
        body: body       
    })

    saveNotes(notes)
    console.log(printSuccess("Note added!"))
}

export function getNotes() {
    return loadNotes()
}

export function removeNotes(title) {
    const notes = loadNotes()
    const removed = notes.filter(note => note.title !== title)

    if (notes.length === removed.length) {
        console.log(printFailure("No such title is found:"), title)
        return
    } 

    saveNotes(removed)
    console.log(printSuccess("Successfully removed:"), title)
}

export function readNote(title) {
    const found = getNote(title)

    if (!found) {
        console.log(printFailure("No such title:"), title)
        return
    }

    console.log("======", chalk.inverse(found.title), "======")
    console.log(found.body)
}

function saveNotes(notes) {
    const notesJSON = JSON.stringify(notes)
    fs.writeFileSync('../notes/notes.json', notesJSON)
}

function loadNotes() {
    try {
        const buffer = fs.readFileSync('../notes/notes.json')
        const JSONstring = buffer.toString()
        const notes = JSON.parse(JSONstring)

        return notes
    } catch (e) {
        return []
    }
}

function getNote(title) {
    const notes = loadNotes()
    return notes.find((note) => note.title === title)
}

function printFailure(msg) {
    return chalk.bgRed.white.bold(msg)
}

function printSuccess(msg) {
    return chalk.bgGreen.white.bold(msg)
}