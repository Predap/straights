#include "game.h"

Game::Game()
{

	for (int i = 0; i < 52; i++) // runs through deck
	{

		char c; // holds character for card
		int t = (i % 13) + 1; // holds number for card
		if (i < 13) // if card is club, sets c to C
		{

			c = 'C';

		}
		else if (i < 26) // if card is diamond, sets c to D
		{

			c = 'D';

		}
		else if (i < 39) // if card is heart, sets c to H
		{

			c = 'H';

		}
		else // if card is spade, sets c to S
		{

			c = 'S';

		}
		std::unique_ptr<Card> p = std::make_unique<Card>(t, c); // creates card
		deck.emplace_back(std::move(p)); // puts card on deck

	}
	for (int i = 0; i < 4; i++) // for each suit, add vector on field
	{

		std::vector<Card *> cv;
		field.emplace_back(cv);

	}

}

int Game::shuffle(std::vector<std::shared_ptr<Player>> players, int g) // shuffles deck
{

	if (g == 0) // if no seed given
	{

		g = std::chrono::system_clock::now().time_since_epoch().count(); // set seed randomly

	}
	int start = 0; // holds player with 7S
	std::shuffle(deck.begin(), deck.end(), std::default_random_engine(g)); // shuffles deck using seed
	for (int i = 0; i < 4; i++) // loops through each player
	{

		std::vector<Card *> hand;
		for (int j = 0; j < 13; j++) //loops through each card in hand
		{

			if ((deck[i*13+j]).get()->getIntNum() == 7 && (deck[i*13+j]).get()->getSuit() == 'S') // if the card's 7S, set start
			{

				start = i;

			}
			hand.emplace_back((deck[i*13+j].get())); // put card on hand

		}
		(players[i].get())->setHand(hand); // set the player's hand

	}
	return start; // return player with 7S

}

bool Game::checkValid(Card * c) // checks if a play is valid
{

	char suit = c->getSuit(); // gets suit of card
	int num = c->getIntNum(); // gets number of card
	if (field[3].empty() && (num != 7 || suit != 'S')) // if there are no spades and the card isn't 7S
	{

		return false; // not valid

	}
	else if (field[3].empty()) // if there are no spades and the card is 7S
	{

		return true; // valid

	}
	if (suit == 'C') // for clubs
	{

		if(num == 7 ||(!(field[0].empty()) && (num + 1 == field[0][0]->getIntNum() || num - 1 == field[0][field[0].size()-1]->getIntNum()))) // if the card is a seven or is adjacent to a card on the field
		{

			return true; // valid

		}
		else
		{

			return false; // not valid

		}

	}	
	if (suit == 'D') // for diamonds
        {

                if(num == 7 ||(!(field[1].empty()) && (num + 1 == field[1][0]->getIntNum() || num - 1 == field[1][field[1].size()-1]->getIntNum()))) // same as for clubs
                {

                        return true;

                }
                else
                {

                        return false;

                }

        }
	if (suit == 'H') // for hearts
        {

                if(num == 7 ||(!(field[2].empty()) && (num + 1 == field[2][0]->getIntNum() || num - 1 == field[2][field[2].size()-1]->getIntNum()))) // same as for clubs
                {

                        return true;

                }
                else
                {

                        return false;

                }

        }
	if (suit == 'S') // for spades
        {

                if(num == 7 ||(!(field[3].empty()) && (num + 1 == field[3][0]->getIntNum() || num - 1 == field[3][field[3].size()-1]->getIntNum()))) // same as for clubs
                {

                        return true;

                }
                else
                {

                        return false;

                }

        }
	return false; // if nothing is chosen, return false as failsafe

}

void Game::play(Card * c) // plays card
{

	if (checkValid(c)) // if the card's valid
	{

		char suit = c->getSuit();
		int num = c->getIntNum();
		int nSu = 0; // holds suit index
		if (suit == 'D')
		{

			nSu = 1;

		}
		else if (suit == 'H')
		{

			nSu = 2;

		}
		else if (suit == 'S')
		{

			nSu = 3;

		}
		if (num == 7)
		{

			field[nSu].emplace_back(c); // if card is 7, put in vector

		}
		else if (num < field[nSu][0]->getIntNum()) // if card is less than lowest
		{

			field[nSu].emplace(field[nSu].begin(), c); // put at beginning

		}
		else // if card is greater than highest
		{

			field[nSu].emplace_back(c); // put at end
	
		}

	}

}

void Game::cards(bool ascii) // prints out cards
{

	if (!ascii) // without bonus
	{

		std::cout << "Cards on the table:" << std::endl;
		std::cout << "Clubs:";
		for (auto n: field[0])
		{

			std::cout << " " << (*n).getNum() << (*n).getSuit(); // loops through clubs

		}
		std::cout << std::endl;
		std::cout << "Diamonds:";
		for (auto n: field[1])
		{

			std::cout << " " << (*n).getNum() << (*n).getSuit(); // loops through diamonds
	
		}
		std::cout << std::endl;
		std::cout << "Hearts:";
		for (auto n: field[2])
		{

			std::cout << " " << (*n).getNum() << (*n).getSuit(); // loops through hearts

		}
		std::cout << std::endl;
		std::cout << "Spades:";
		for (auto n: field[3])
		{

			std::cout << " " << (*n).getNum() << (*n).getSuit(); // loops through spades

		}
		std::cout << std::endl;

	}
	else // if better UI enabled
	{

		for (int i = 0; i < 4; i++) // runs through suits
		{

			if (i == 0) // prints Clubs header
			{

				std::cout << "                                      ====CLUBS====" << std::endl;

			}
			else if (i == 1) // prints Diamonds header
			{

				std::cout << "                                     ====DIAMONDS====" << std::endl;

			}
			else if (i == 2) // prints Hearts header
			{

				std::cout << "                                      ====HEARTS====" << std::endl;

			}
			else if (i == 3) // prints Spades header
			{

				std::cout << "                                      ====SPADES====" << std::endl;

			}
			if (field[i].size() > 0) // if there are cards in the current suit on the field
			{

				int low = (field[i][0])->getIntNum(); // find the lowest number
				int l = field[i].size(); // find size
				for (int j = 1; j < low; j++) // for cards that aren't there, print spaces
				{

					std::cout << "       ";

				}
				for (int j = low; j < l + low; j++) // top border for existing cards
				{

					std::cout << "------ ";

				}
				std::cout << std::endl;
				for (int j = 1; j < low; j++) // more spaces
				{

					std::cout << "       ";

				}
				for (int j = low; j < l + low; j++) // put card info & border
				{

					std::cout << "| " << (field[i][j-low])->getNum() << (field[i][j-low])->getSuit() << " | ";

				}
				std::cout << std::endl;
				for (int j = 1; j < low; j++) // even more spaces
				{

					std::cout << "       ";

				}
				for (int j = low; j < l + low; j++) // put borders
				{

					std::cout << "|    | ";

				}
				std::cout << std::endl;
				for (int j = 1; j < low; j++) // last batch of spaces (probably)
                                {

                                        std::cout << "       ";

                                }
                                for (int j = low; j < l + low; j++) // bottom border
                                {

                                        std::cout << "------ ";

                                }
				std::cout << std::endl << std::endl;

			}
			else // if no cards, put a bunch of newlines
			{

				std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;

			}


		}

	}

}

bool Game::checkWin(std::vector<std::shared_ptr<Player>> players, bool ascii) // checks if a player has won
{

	bool win = false; // checks if someone's won
	int scores = 0; // holds current score
	int highScore = 0; // holds highest score to check
	int lowScore = 0; // holds lowest score to check
	for(int i = 1; i <= 4; i++) // runs through players
	{

		std::cout << "Player" << i << "'s discards:" << std::endl;
		std::vector <Card *> discard = (players[i-1]).get()->getDiscard();
		if (!ascii) // if no UI enhancement
		{

			for(auto n: discard) // runs through discarded cards
			{

				std::cout << " " << (*n).getNum() << (*n).getSuit(); // prints card
				scores += (*n).getIntNum(); // adds card to score

			}

		}
		else // for enhanced UI
		{

                        int l = discard.size(); // get the size of the discard pile
                        for (int j = 0; j < l; j++) // print the tops of cards
                        {

                        	std::cout << "------ ";

                        }
                        std::cout << std::endl;
                        for (int j = 0; j < l; j++) // print the info and add to the score
                        {

                               std::cout << "| " << discard[j]->getNum() << discard[j]->getSuit() << " | ";
			       scores += discard[j]->getIntNum();

                        }
                        std::cout << std::endl;
                        for (int j = 0; j < l; j++) // print bottom middle of cards
                        {

                               std::cout << "|    | ";

                        }
                        std::cout << std::endl;
                        for (int j = 0; j < l; j++) // print bottom of cards
                        {

                               std::cout << "------ ";

                        }
                        std::cout << std::endl;

		}
		std::cout << std::endl;
		(players[i-1]).get()->addScore(scores); // add score to card
		scores = (players[i-1]).get()->getScore(); // gets score for comparison
		if (i == 1) // if first player is chosen, set high and low scores to the score
		{

			highScore = scores;
			lowScore = scores;

		}
		if (scores > highScore) // if score is greater than high score, set new high
		{

			highScore = scores;

		}
		if (scores < lowScore) // if score is greater than low score, set new low
		{

			lowScore = scores;

		}
		scores = 0;
		std::cout << "Player" << i << "'s score: " << (players[i-1]).get()->getScore() << std::endl; // print out current scores

	}
	for (int i = 1; i <= 4; i++) // loop through players
	{

		if (highScore >= 80 && players[i-1]->getScore() == lowScore) // if the high score is greater than 80 and this player has the lowest score
		{

			std::cout << "Player" << i << " wins!" << std::endl; // print out that the player wins
			win = true;

		}
		players[i-1]->clearDisc(); // clear discard
		field[i-1].clear(); // clear field

	}
	return win; // return if the game has been won

}

void Game::printDeck(bool ascii) // prints deck
{

	if (!ascii) // without UI enhancement
	{

		for (int i = 0; i < 4; i++) // loop through player
		{

			for (int j = 0; j < 13; j++) // loop through cards
			{

				std::cout << deck[i * 13 + j].get()->getNum() << deck[i * 13 + j].get()->getSuit() << " "; // print card

			}
			std::cout << std::endl;

		}

	}
	else // with UI enhancement
	{

		for (int i = 0; i < 4; i++) // loop through player
		{

			for (int j = 0; j < 13; j++) // loop through cards, print top
			{

				std::cout << "------ ";

			}
			std::cout << std::endl;
			for (int j = 0; j < 13; j++) // loop through cards, print top middle and info
			{

				std::cout << "| " << deck[i * 13 + j].get()->getNum() << deck[i * 13 + j].get()->getSuit() << " | ";

			}
			std::cout << std::endl;
			for (int j = 0; j < 13; j++) // loop through cards, print bottom middle
			{

				std::cout << "|    | ";

			}
			std::cout << std::endl;
			for (int j = 0; j < 13; j++) // loop through cards, print bottom
			{

				std::cout << "------ ";

			}
			std::cout << std::endl;

		}

	}

}
