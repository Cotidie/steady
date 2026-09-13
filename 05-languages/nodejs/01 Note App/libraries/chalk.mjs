import chalk from 'chalk'

function printSuccess(msg) {
    return chalk.green.bgWhite.bold.inverse(msg)
}

var msg = printSuccess("Success!!")
console.log(msg)