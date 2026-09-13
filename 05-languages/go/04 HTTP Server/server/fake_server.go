package main

import (
	"fmt"
	"net"
	"net/http"
)

type Server interface {
	Close()
	Run() error
	Port() int
}

type FakeServer struct {
	listner      net.Listener
	receivedData []byte
}

func (fs FakeServer) GetData() []byte {
	return fs.receivedData
}

func (fs *FakeServer) Close() {
	_ = fs.listner.Close()
}

func (fs FakeServer) Port() int {
	return fs.listner.Addr().(*net.TCPAddr).Port
}

func (fs *FakeServer) Run() error {
	var err error = nil
	if fs.listner == nil {
		err = fs.createListener()
	}
	if err != nil {
		return err
	}

	http.HandleFunc("/post/data", fs.postData)

	go func() {
		http.Serve(fs.listner, nil)
	}()

	return nil
}

func (fs *FakeServer) createListener() error {
	listener, err := net.Listen("tcp", ":0")
	if err != nil {
		return err
	}
	fs.listner = listener

	return nil
}

// -----------------------------------------------------------------------------------------------------------------
// Server Endpoints
// -----------------------------------------------------------------------------------------------------------------

func (fs *FakeServer) postData(rw http.ResponseWriter, req *http.Request) {
	body := []byte{}
	req.Body.Read(body)

	fmt.Printf("Received Data: %v\n", body)
	fs.receivedData = append(fs.receivedData, body...)
}
