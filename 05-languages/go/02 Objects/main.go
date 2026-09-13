package main

import (
	"fmt"
	"reflect"
)

type person struct {
	firstName   string
	lastName    string
	contactInfo // = contactInfo contactInfo
}

type contactInfo struct {
	email   string
	zipCode int
}

func printStruct() {
	alex := person{
		firstName: "Alex",
		lastName:  "Anderson",
		contactInfo: contactInfo{
			email:   "daily142857@gmail.com",
			zipCode: 94061,
		},
	}

	fmt.Printf("%+v", alex)
}

func printMap() {
	colors := make(map[string]int)
	colors["red"] = 1
	colors["green"] = 2
	colors["white"] = 3

	for color, value := range colors {
		fmt.Println(color, ":", value)
	}
}

func typeCheck(obj interface{}) {
	// Method 1: using reflect.TypeOf()
	myType := reflect.TypeOf(obj)
	fmt.Println(myType)

	// Method 2: using .(type) syntax ->
	switch objType := obj.(type) {
	case int:
		println("it's int")
	default:
		// raises an error if it doesn't match with the .(type)
		println("Int?:", objType.(int))
		println("String?:", objType.(string))
	}
}

func main() {
	myInt := 32

	typeCheck(myInt)
	// getGoogleHTMLandLog()
}
