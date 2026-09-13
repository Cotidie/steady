package main

import (
	"fmt"
	"net/http"
	"time"
)

func getUrls() map[string]string {
	urls := make(map[string]string)
	urls["Google"] = "http://google.com"
	urls["Facebook"] = "http://facebook.com"
	urls["Stackoverflow"] = "http://stackoverflow.com"
	urls["Golang"] = "http://golang.org"

	return urls
}

func checkUrl(link string, c chan string) {
	_, error := http.Get(link)
	if error != nil {
		fmt.Println("Error:", error)
		c <- "Unable to connect to the link"
		return
	}

	fmt.Printf("%v is Up!\n", link)
	c <- link
}

func main() {
	urls := getUrls()
	channel := make(chan string)

	for _, url := range urls {
		go checkUrl(url, channel)
	}

	// Blocking Channel: wait for a value to be sent
	for link := range channel {
		// this way, time between goroutine calls are equal to 500ms
		go checkUrl(link, channel)
		time.Sleep(500 * time.Millisecond)
	}
}
