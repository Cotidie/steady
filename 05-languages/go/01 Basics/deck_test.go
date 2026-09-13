package main

import (
	"os"
	"testing"
)

func TestNewDeck(t *testing.T) {
	d := newDeck()

	if len(d) != 16 {
		t.Errorf("Expected deck lengh of 16, but got %d", len(d))
	}

	if d[0] != "Ace of Spades" {
		t.Errorf("The first card must be Ace of Spaces, but got %v", d[0])
	}

	if d[len(d)-1] != "Four of Clovas" {
		t.Errorf("The last card must be Four of Clovas, but got %v", d[len(d)-1])
	}
}

func TestSaveToDeckAndNewDeckTestFromFile(t *testing.T) {
	filename := "newDeck_decktesting"
	d := newDeck()
	err := d.saveToFile(filename)

	if err != nil {
		t.Errorf("Save to file failed: %v", err)
	}

	lodadedDeck := newDeckFromFile(filename)
	if len(lodadedDeck) != 16 {
		t.Errorf("Loaded deck should be size of 16, but got %v", len(lodadedDeck))
	}

	os.Remove(filename + ".json")
}
