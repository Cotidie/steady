# Objects

## Struct
* if no value is assigned, the field will be initiated with its zero value
* plus(+) sign in %+v shows field names with values.
* embedding a struct into another is possible as a syntatic sugar
* Use a pointer to pass by reference
```go
// Defining a struct
type person struct {
    name string
    contact            // = contact contact
}
type contact struct {
    phone string
    email string
}

// Declaring a struct
me := {
    name: "Wonseok",
    contact: contact{
        phone: "010-4797-1428",
        email: "daily142857@gmail.com"
    }
}
me.contact.phone = "669-338-6638"

// normal form
mePointer := &me
mePointer.updateName("Finn")
// pointer shortcut
me.updateName("Finn")

// to actually change the value, receiver should be a pointer
func (p *person) updateName(newName string) {
    (*person).name = newName
}
```
## Map
```go
// Initializing a map
color := map[string][int] {
    "red": 1,
    "green": 2,
    "blue": 3,
}
// Just declaring an empty map
colors := make(map[string]string)
var colors map[string]string

// Write and Read
colors["red"] = 1
colors["red"]       // = colors.red

// Delete an entry
delete(colors, "red")

// Iterating: replace with _ if not want to use that variable
for key, value := range colors {
    // key, value
}
```
## Interface
 To implement an interface, all needs to be done is to implement right signitures of interface members. Those types are called *honorary members*
  - Compiler simply seeks signitures of an interface in a type
  - Interfaces can have another interface.
```go
// Defining an interface
type Bot interface {
    Introducer          // interfaces can be folded
    getVersion() float64
}

type Introducer interface {
    introduce(string) string
}

type EnglishBot struct{}

// EnglishBot is now an honorary member of the interface 'Introducer'
func (EnglishBot) introduce(prefix string) string {
    return ...
}

// EnglishBot is now a member of both 'Introducer' and 'Bot'
func (EnglishBot) getVersion() float64 {
    return 0.1
}
```

## Type Check
```interface{}``` represents anonymous type for all object. Later the type can be checked by ```.(type)``` syntx.
- ```reflect.```
- ```.(type)``` can only be used for switch statement
- ```.(<type>)``` raises an error if the \<type\> doens't match 
```go
func typeCheck(obj interface{}) {
    objType := reflect.TypeOf(obj)

    switch x := obj.(type) {
    case int:
        ...
    }
}
```

## HTTP Package
| https://pkg.go.dev/net/http

Golang's HTTP package has [io.ReadCloser](https://pkg.go.dev/io#ReadCloser) type as its body, which implements Reader and Closer
  -  Reader gets ```[]byte``` as avcontainer, and put data
  -  Writer takes ```[]byte``` as input, and pass to a destination (stdOut, file...etc.)
```go
Response
    - Status        string
    - StatusCode    int
    - Header        Header
    - Body          io.ReadCloser
        - Reader
            - Read([]byte) (int, error)
        - Closer
            - Close()      (error)

resp, err := http.Get("http://google.com")
// 1. Directly reads from response body
buffer := make([]byte, 32 * 1024)
resp.Body.Read(buffer)
fmt.Println(string(buffer))

// 2. Use a Writer to hide buffer
io.Copy(os.Stdout, resp.Body)

// 3. Use a custum writer
type LogWriter struct{}

func (LogWriter) Write(bs []byte) (int, error) {
    fmt.Println(string(bs))
	return len(bs), nil
}

lw := LogWriter{}
io.Copy(lw, resp.Body)
```

Q. How to track which type is implementing which interface?
    => You should look at documents and find whether it satisfies.