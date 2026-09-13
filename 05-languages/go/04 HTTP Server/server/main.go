package main

import (
	"fmt"
	"sync"
)

const (
	testPort = "8120"
)

func main() {
	wg := sync.WaitGroup{}
	fakeServer := FakeServer{}
	fakeServer.Run(testPort)

	fmt.Println("End of main function")
}
