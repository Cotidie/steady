package json

import (
	"encoding/json"
	"fmt"
)

// #############################################################################
// JSON Marshal Test
// Conclusion: Inherited method can only access to the composited struct.
// #############################################################################
type ResponseNoComposition struct {
	status Status
	Data   InjectData `json:"data"`
}

func TestNoTagMarshaling() {
	injectData := InjectData{"1.1", "Injection"}
	status := Status{"This is Status", 1}

	response := ResponseNoComposition{status, injectData}
	jsonResp, err := json.MarshalIndent(response, "", " ")
	if err != nil {
		fmt.Printf("Error Happened!! %v\n", err)
		return
	}

	fmt.Printf("JSON Response: %s\n", string(jsonResp))
}
