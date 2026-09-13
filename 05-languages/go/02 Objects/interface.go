package main

import "fmt"

type Bot interface {
	Introducer
	getBotVersion() float64
}

type Introducer interface {
	introduce() string
}

type EnglishBot struct{}
type SpanishBot struct{}

func printGreeting(b Introducer) {
	fmt.Println(b.introduce())
}

func (EnglishBot) introduce() string {
	return "Hi, I'm an English bot"
}

func (EnglishBot) getBotVersion() float64 {
	return 0.01
}

func (SpanishBot) introduce() string {
	return "Hi, I'm a Spanish bot"
}

func (SpanishBot) getBotVersion() float64 {
	return 0.02
}

func testInterfaces() {
	engBot := EnglishBot{}
	spaBot := SpanishBot{}

	printGreeting(engBot)
	printGreeting(spaBot)
}
