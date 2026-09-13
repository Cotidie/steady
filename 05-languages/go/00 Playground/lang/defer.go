package lang

import "fmt"

// #############################################################################
// Defer evaluation test
// Conclusion: If it's two-fold, it works as lazy-evaluation.
// #############################################################################

var printFunc func()

func callPrintFunc() {
	printFunc()
}

func setDifferentPrintFunc() {
	printFunc = func() {
		fmt.Println("This is assigned later.")
	}
}

func DeferEvaluationTiming() {
	printFunc = func() {
		fmt.Println("this is assigned First")
	}
	defer callPrintFunc()

	setDifferentPrintFunc()
}
