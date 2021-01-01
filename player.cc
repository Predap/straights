#include "player.h"

Player::Player()
{

	score = 0; // sets score to 0

}

void Player::setHand(std::vector <Card *> h) // sets hand to the passed vector
{

	hand = h;

}

std::vector<Card *> Player::getHand() // returns hand
{

	return hand;

}

std::vector<Card *> Player::getDiscard() // returns discard
{

	return disc;

}

int Player::getScore() // returns score
{

	return score;

}

void Player::addScore(int n) // adds n to score
{

	score += n;

}

bool Player::isHuman() // returns false as to whether player is human
{

	return false;

}

Card * Player::choose(std::vector<Card *> lp) // chooses card to play
{

	if (lp.size() > 0)
	{

		return lp[0]; // plays first legal play if there is one

	}
	else
	{

		return hand[0]; // if no legal plays, choose first card in hand

	}

}

void Player::clearDisc() // clears discard at end of rounds
{

	disc.clear();

}

void Player::play(Card * c) // plays card; this should not happen in player
{

	std::cerr << "Error!" << std::endl; // prints error

}

void Player::discard(Card * c) // discards card; this should not happen in player
{

	std::cerr << "Error!" << std::endl; // prints error

}
