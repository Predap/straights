#include "computer.h"

Computer::Computer(int ai): Player{} // calls superclass constructor, sets ai level
{

	a = ai;

}

Computer::Computer(Player p, int ai) // sets fields to those of p
{

	score = p.getScore();
	hand = p.getHand();
	disc = p.getDiscard();	
	a = ai;

}

Card * Computer::choose(std::vector<Card *> lp) // chooses card to play
{

	if (a == 0) // if ai level is 0
	{

		if (lp.size() > 0) // if there is a legal play
		{

			return lp[0]; // return first legal play

		}
		return hand[0]; // if no legal plays, return first card in hand

	}
	else if (a == 1) // if ai level is 1
	{

		if (lp.size() > 0) // if there is a legal play
		{

			int choice = 0; // set highest value to 0
			Card * ret = lp[0]; // sets highest pointer to first legal play
			Card * n = lp[0]; // sets current pointer to check to first legal play
			for (unsigned i = 0; i < lp.size(); i++) // loops through legal plays
			{

				n = lp[i]; // sets pointer to check to for loop variable
				if (n->getIntNum() > choice) // if current card is higher than the highest number
				{

					choice = n->getIntNum(); // set highest number to current number
					ret = n; // set value of card pointer to current pointer

				}

			}
			if (choice == 7) // run through again if choice is 7, as 7s should be played last
			{

				int twochoice = 0; // set highest non-seven value to 0
				Card * tworet = lp[0];
				for (unsigned i = 0; i < lp.size(); i++) // loops through legal plays, loop works same as above EXCEPT:
				{

					n = lp[i];
					if (n->getIntNum() > twochoice && n->getIntNum() != 7) // if number is 7, do not include
					{

						twochoice = n->getIntNum();
						tworet = n;

					}

				}
				if (twochoice != choice) // if there is another legal play, choose that play
				{

					return tworet; // returns play

				}

			}
			return ret; // returns choice

		}
		else // if no legal plays
		{

			int choice = 14; // sets lowest number to 14
			Card * ret = hand[0]; // sets current highset pointer to first card in hand
			Card * n = hand[0]; // sets current pointer to check
			for (unsigned i = 0; i < hand.size(); i++) // loops through hand
			{

				n = hand[i]; // sets current pointer to check
				if (n->getIntNum() < choice) // if number is less than the lowest number
				{

					choice = n->getIntNum(); // set lowest number
					ret = n; // set pointer to lowest number

				}

			}
			return ret; //return card to discard

		}

	}
	return hand[0]; // return first card in hand

}

void Computer::play(Card * c) // plays card
{

	std::vector<Card *>::iterator n = hand.begin(); // sets iterator to hand
	for(unsigned i = 0; i < hand.size(); ++i) // loops through hand
        {

                if (c == hand[i]) // if card pointer is equal to card in hand
                {
			
                        hand.erase(n); // erase iterator

                }
		++n; // increment iterator

        }

}

void Computer::discard(Card * c) // discards card
{

	for (unsigned i = 0; i < hand.size(); ++i) // loops through hand
	{

		if (hand[i] == c) // if card pointer is equal to card in hand
		{

			hand.erase(hand.begin() + i); // erase iterator

		}

	}
	disc.emplace_back(c); // puts pointer in discard

}

bool Computer::isHuman() // checks if computer is human
{

	return false; // Computers are, sadly, not human. :(

}
