import * as noteCommand from '../notes/command.mjs'
import { createRequire } from "module";
const require = createRequire(import.meta.url);

const yargs = require('yargs')

// Customize yargs version, help document
yargs.version('1.1.0')

// 명령어 추가
yargs.command({
    command: "add",
    describe: "Add a new note",
    builder: {
        title: {
            describe: "Set a note's title",
            demandOption: true,
            type: 'string'
        },
        body: {
            describe: "Set a note's body",
            demandOption: false,
            type: 'string'
        }
    },
    handler: (argv) => {
        noteCommand.addNote(argv.title, argv.body)
    }
})

yargs.command({
    command: 'remove',
    describe: "Remove a note",
    builder: {
        title: {
            describe: "A title to be removed",
            demandOption: true,
            type: 'string'
        }
    },
    handler(argv) {
        noteCommand.removeNotes(argv.title)
    }
})

yargs.command({
    command: 'list',
    describe: "List notes",
    handler() {
        const notes = noteCommand.getNotes()
        console.log("======== Notes ========")
        for (const note of notes) {
            console.log(note)
        }
    }
})

yargs.command({
    command: 'read',
    describe: "Read a note",
    build: {
        title: {
            describe: "A title of note to read",
            demandOption: true,
            type: 'string'
        }
    },
    handler: function(argv) {
        noteCommand.readNote(argv.title)
    }
})

yargs.parse()