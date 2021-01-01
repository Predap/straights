#ifndef HUMAN_H_
#define HUMAN_H_
#include "player.h"
#include "game.h"
#include <iostream>

class Human : public Player { // subclass of player

	public:
	Human(); // constructor
	void play(Card * c = nullptr); // plays card
        void discard(Card * c = nullptr); // discards card
	bool isHuman(); // checks if player is human

};

#endif
