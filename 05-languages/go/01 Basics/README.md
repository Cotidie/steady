# Cards
From the deck of 52 cards, the program provides those functions: create a deck, print, shuffle, deal, save and load deck. 'deal' command creates a 'hand' of cards.
- **deal(deck, int)**: pick n number of cards from a deck
  - **return**: a hand of cards and a remaining deck
- **shuffle()**: randomize the order of the current deck
  - Go doesn't shuffle a slice
- **saveToFile()**: saves a list of cards to a file on the local machine
  - it should use JSON format
- **readFromFile()**: reads JSON file into deck type.

## Table of Contents
- [Basics](#basics)
  - [Package](#package)
  - [Import](#import)
  - [Variables](#variables)
  - [Functions](#functions)
  - [Slice and Loop](#slice-and-loop)
  - [Class](#class)
- [Errors](#errors)
  - [Unnamed Name](#unnamed-name)
- [Testing](#testing)
- [Standard Packages](#standard-packages)
  - [io/ioutil](#ioioutil)
  - [strings](#strings)
  - [encoding/json](#encodingjson)
  - [math/rand](#mathrand)
  - [os](#os)

## Basics
```go
package main

// use linebreaks to import multiple packages
import (
    "fmt"
    "strings"
)

func main() {
    fmt.Println("Hello, world!")
}
```
### Module
Golang's module equals to a workspace or a library. go.mod file contains the **module name**, **go version** and **dependencies**.
- ```go mod init <module>```: Creates a module that can be imported. The best practice is to have module name as approchable url.
```go
module github.com/cotidie/cards

go 1.18

// dependencies
require (
	github.com/golang/mock v1.6.0
	github.com/google/uuid v1.3.0
	...
)
```
- ```go mod tidy```: 
### Package
 Package refers to a workspace or a project. 
* **Executable**: Generate a .exe file we can run, by 'go build command'
    * package name must be **'main'**
    * must have 'main' function
* **Reusable**: Packages used as dependencies.
    * anything but name 'main' is a reusable package.
  
| Q. How to test reusable packages

### Import
| Standard Packages: https://pkg.go.dev/std

import standard or reusable packages. The root path is where the main package is located at.

| Q. absolute and relative import?

### Variables
Go is referred to a static typed language. The variable name is followed by its type declaration.  
  * **value types**: bool, string, int, float64, struct
  * **Reference types**: slice, map, channel, pointer, function
  * types can be inferred from its declaration
  * global variables can be declared, but cannot be initialized
  
```go
var name type = value
card := value  // type inferrence

// can be assigned later
var deckSize int
deckSize = 52
```

### Functions
- Arguments are basically passed by value
- Functions can have multiple returns
```go
func main() {
    card := newCard()
    fmt.Println(card)
}

// function with multiple returns
func deal(d deck, size int) (deck, deck) {
    return deck[:size], deck[size:]
}
```

### Slice and Loop
Go provides slices as a default array type.
* **Slice**: an array can grow and shrink (ref. vector in c++)
* ```range``` keyword gets an index and an iterator from an iterable
```go
func main() {
    cards := []type{"a", "b", "c"}
    cards = append(cards, "d")

    // if index is not in use, replace it with '_'
    for i, card := range cards {
        fmt.Println(i, card)
    }

    // slice: [start:end)
    sliced := cards[0:2] // = cards[:2]
}
```

### Class
- receivers are also passed by value by default
```go
// Declare a new type deck
type deck []string

// Receiver: d is an instance of the type deck
func (d deck) print() {
    for i, card := range deck {
        fmt.PrintlnI(i, card)
    }
}
```


## Errors
### Unnamed Name
* Cause: a go file in the same package wasn't imported
* Solution: initialize go modules first
```go
go mod init
go mod tidy
```

## Testing
: To make a test file, create a go file ending with **'_test.go'** and test methods starting with **'Test'**. Then run the test with ```go test``` command.
  - Each test methods should accept [*testing.T](https://pkg.go.dev/testing#T) as a testing handler
  - at the end of the test, any files created during test should be cleaned ()
```bash
go test deck_test.go
```



## Standard Packages
### io/ioutil
| https://pkg.go.dev/io/ioutil
- [WriteFile(filename string, data []byte, perm FileMode))](https://pkg.go.dev/io/ioutil#WriteFile)
  - Filemode follows Linux permission form, which is 3 bits(rwx) for 3 user groups (0666 for read, write permissions for all three)
  - Save path follows current working directory
- [ReadFile(filename string)](https://pkg.go.dev/io/ioutil#ReadFile)
  - if error occurs, error != nil

### strings
- [Join(a []string,sep string)](https://pkg.go.dev/strings#Join)
- [Split(s, sep string)](https://pkg.go.dev/strings#Split)

### encoding/json
- [Marhsal(v any)](https://pkg.go.dev/encoding/json#Marshal): Converts any type that implements MarshalJSON or TextMarshaler into JSON bytes. use [MarshalIndent(...)](https://pkg.go.dev/encoding/json#MarshalIndent) if needs prettier form.

### math/rand
: Before call any random functions, the seed must be changed. For this purpose, use NewSource() and New(source Source)
- [NewSource(seed int64)](https://pkg.go.dev/math/rand#NewSource): create a new seed. **time.Now().UnitNano()** is recommended.
- [New(source Source)](https://pkg.go.dev/math/rand#New)
- [Intn(n int)](https://pkg.go.dev/math/rand#Intn): returns a random int between [0, n)

### os
- [Exit(code int)](https://pkg.go.dev/os#Exit): Completely finishes the program with exit code
- [Remove(name string)](https://pkg.go.dev/os#Remove)