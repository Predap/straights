#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "card.h"

class Player
{

	protected: // score, hand, and discard are all protected so subclasses can access
	int score;
	std::vector<Card *> hand;
	std::vector<Card *> disc;
	Player(); // constructor for player
	public:
	void setHand(std::vector <Card *> h); // sets hand to passed vector
	std::vector<Card *> getHand(); // returns hand
	int getScore(); // returns score
	virtual bool isHuman(); // checks if player is human
	void addScore(int n); // adds n to score
	std::vector<Card *> getDiscard(); // returns discard pile
	virtual Card * choose(std::vector<Card *> c); // chooses a card to play based upon the passed vector
	void clearDisc(); // clears the discard pile
	virtual void play(Card * c = nullptr); // plays card pointer passed
	virtual void discard(Card * c = nullptr); // discards card pointer passed

};

#endif
