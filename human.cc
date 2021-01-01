#include "human.h"

Human::Human(): Player{} // calls superclass constructor
{}

void Human::play(Card * c)
{

	std::vector<Card *>::iterator n = hand.begin(); // sets iterator
        for(unsigned i = 0; i < hand.size(); i++) // runs through hand
        {

                if (c == hand[i]) // if passed pointer is equal to the current element in hand
                {

                        hand.erase(n); // erase the current iterator

                }
                ++n; // increment iterator

        }

}

void Human::discard(Card * c)
{

	std::vector<Card *>::iterator n = hand.begin(); // sets iterator
        for(unsigned i = 0; i < hand.size(); i++) // runs through hand
        {

                if (c == hand[i]) // if passed pointer is equal to the current element in hand
                {

			disc.emplace_back(*n); // add pointer to back of discard
                        hand.erase(n); // erase the current iterator

                }
                ++n; // increment iterator

	}

}

bool Human::isHuman() // returns true as Human is human
{

	return true;

}
