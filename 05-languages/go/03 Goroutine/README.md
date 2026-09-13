# Concurrency

## Goroutine
![Imgur](https://i.imgur.com/sFSWnpZ.jpg)
```go
func requestPing(url string) {}

// Create a new goroutine
go requestPing("http://google.com")
```
Golang runs by goroutines on top of threads. Goroutines take a function as a unit of execution and put it in the **Global Run Queue**. Then **Go scheduler** checks which thread is available and move a function to a **Local Run Queue** associated with a thread.
- Parent goroutine can cancel child goroutines. 
- Goroutines are cooperative, meaning that only certain points will it reschedule. (Making new goroutine...etc.)


## Channel
![Channel](https://media.geeksforgeeks.org/wp-content/uploads/20190731140438/Untitled-Diagram46.jpg)
**Channels** are only way to communicate between goroutines. Channels can be used to check all other goroutines are finished before ending the main goroutine.
- Waiting for a channel blocks the routine
- Use function literal for continuos goroutine calls

```go
channel := make(chan string)

// Send the value 'five' to the channel
channel <- "five"
// Wait for a value from the channel in 2 identical ways
for {
    myValue <- channel
    //...
}
for myValue := channel {
    // myValue should be passed as a parameter
    // otherwise myValue is locked by function literal's reference and won't change by channel
    go func(value string) {
        //...
    }(myValue)
}
```