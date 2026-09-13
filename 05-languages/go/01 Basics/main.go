package main

func createHand(d deck) (deck, deck) {
	return deal(d, 2)
}

func saveDeck(hand deck, reamining deck) {
	hand.saveToFile("hand")
	reamining.saveToFile("remainingDeck")
}

func shuffleTest() {
	cards := newDeckFromFile("remainingDeck.json")
	cards.shuffle()

	cards.print()
}

func introduceMyself() {
	greetings.sayHello()
}

func main() {
	introduceMyself()
}
