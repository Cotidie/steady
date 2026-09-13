package json

import (
	"encoding/json"
	"fmt"
)

// #############################################################################
// JSON Unmarhsal Test
// Conclusion: []byte is unmarshalled into []byte form even it's JSON format.
// #############################################################################
type Response struct {
	Status
	Data []byte `json:"data"`
}

type Status struct {
	Msg  string `json:"msg"`
	Code int    `json:"code"`
}

type InjectData struct {
	Version string `json:"version"`
	Name    string `json:"name"`
}

func TestJSONUnmarshal() {
	injectData := InjectData{"1.1", "Injection"}
	rawData, _ := json.MarshalIndent(injectData, "", " ")

	status := Status{"This is Status", 1}
	response := Response{status, rawData}

	jsonResp, err := json.MarshalIndent(response, "", " ")
	if err != nil {
		fmt.Printf("Error happened!! %v\n", err)
		return
	}

	var unmarshaled Response
	err = json.Unmarshal(jsonResp, &unmarshaled)
	if err != nil {
		fmt.Printf("Error in unmarshal: %v\n", err)
		return
	}

	fmt.Printf("Successful Unmarshaling: %+v\n", unmarshaled)
}
