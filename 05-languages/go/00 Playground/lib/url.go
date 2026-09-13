package lib

import (
	"fmt"
	"net/url"
)

// #############################################################################
// URL Parsing Empty String Test
// Conclusion: It parses without an error if empty string is given.
// #############################################################################

func CanURLParseEmptyStringWithoutError() {
	_, err := url.Parse("")
	if err != nil {
		fmt.Printf("Parse failed: %v\n", err)
		return
	}

	fmt.Println("Parse Success.")
}
