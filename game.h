#ifndef GAME_H_
#define GAME_H_
#include "player.h"
#include <vector>
#include <random>
#include <memory>
#include <algorithm>
#include <iostream>
#include <chrono>

class Game
{

	std::vector<std::unique_ptr<Card>> deck; // holds deck of cards
	std::vector<std::vector<Card *>> field; // holds current field of play
	public:
	Game(); // constructor for Game
	int shuffle(std::vector<std::shared_ptr<Player>> players, int g); // shuffles deck
	bool checkValid(Card * c); // checks if a card can be played
	void play(Card * c); // plays card
	void cards(bool ascii); // prints out cards on field
	void printDeck(bool ascii); // prints out deck
	bool checkWin(std::vector<std::shared_ptr<Player>> players, bool ascii); // checks if a player has won

};

#endif
