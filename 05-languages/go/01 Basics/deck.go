package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"math/rand"
	"os"
	"time"
)

type deck []string

func newDeck() deck {
	cards := deck{}

	cardSuits := []string{"Spades", "Diamonds", "Hearts", "Clovas"}
	cardValues := []string{"Ace", "Two", "Three", "Four"}

	for _, suit := range cardSuits {
		for _, value := range cardValues {
			newCard := fmt.Sprintf("%s of %s", value, suit)
			cards = append(cards, newCard)
		}
	}

	return cards
}

func newDeckFromFile(filename string) deck {
	filename = filename + ".json"
	bs, err := ioutil.ReadFile(filename)
	if err != nil {
		fmt.Println("Error:", err)
		os.Exit(1)
	}

	var cardsString []string
	errJson := json.Unmarshal(bs, &cardsString)
	if err != nil {
		fmt.Println("Error:", errJson)
		os.Exit(1)
	}

	return deck(cardsString)
}

func (d deck) print() {
	for i, card := range d {
		fmt.Println(i, card)
	}
}

func deal(d deck, handSize int) (deck, deck) {
	return d[:handSize], d[handSize:]
}

func (d deck) toStringSlice() []string {
	return d
}

func (d deck) toJson() []byte {
	result, _ := json.Marshal(d.toStringSlice())

	return result
}

func (d deck) toJsonString() string {
	return string(d.toJson())
}

func (d deck) saveToFile(filename string) error {
	filename = filename + ".json"
	return ioutil.WriteFile(filename, d.toJson(), 0666)
}

func (d deck) shuffle() {
	now := time.Now().UnixNano()
	source := rand.NewSource(now)
	r := rand.New(source)

	for i := range d {
		randomIndex := r.Intn(len(d))
		d[i], d[randomIndex] = d[randomIndex], d[i]
	}
}
