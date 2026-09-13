package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/url"
	"runtime"

	"wonseok/go/playground/lib"
)

// Defer keyword works in function scope.
func deferTiming() {
	if true {
		defer fmt.Println("Defer executed!")
	}
	fmt.Println("if statement ended")
}

// Conclusion: it needs double slash(//) to parse Host. Otherwise Host will be empty
// Example: localhost/some/path => Host: "", Path: "localhost/some/path"
func urlParsing() {
	endpoint := "localhost/some/path"
	url, err := url.Parse(endpoint)
	if err != nil {
		log.Panicf("Filed to parse URL: %v\n", err)
	}

	fmt.Printf("Host: %s\n Path: %s\n", url.Host, url.Path)
}

// Get caller function's name and pacakge
func GetCallerPackage() {
	pc, _, _, ok := runtime.Caller(1)
	if !ok {
		log.Println("Couldn't get caller infomation")
		return
	}

	funcName := runtime.FuncForPC(pc).Name()
	log.Printf("Caller info: %v\n", funcName)
}

// #############################################################################
// Method Overriding Test
// Conclusion: Inherited method can only access to the composited struct.
// #############################################################################
type Serializable interface {
	JSON() []byte
}

type Base struct {
	Name string `json:"name"`
}

type SubBase struct {
	Base
	Email string `json:"email"`
}

func (b *Base) JSON() []byte {
	serialized, err := json.MarshalIndent(b, "", "\t")
	if err != nil {
		log.Panicf("Error! %v\n", err)
	}

	return serialized
}

func main() {
	lib.CanURLParseEmptyStringWithoutError()
}
