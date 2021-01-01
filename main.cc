#include "game.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include <sstream>
#include <iostream>

int main(int argv, char ** argc) // main method
{

	int intarg = 0; // holds whether or not seed has been set
	bool loopcheck = true; // holds whether or not there has been an argument with all integers
	bool ascii = false; // holds whether or not UI enhancements should be used
	int ai = 0; // holds current ai level
	int seed = 0; // holds seed
	if (argv > 1) // if arguments were passed
	{
		
		for (int j = 1; j < argv; j++) // loops through arguments
		{
			std::string seedcheck = argc[j]; // gets string of current argument
			for (unsigned i = 0; i < seedcheck.length(); i++) // loops through string
			{

				loopcheck = true;
				if (seedcheck[i] > '9' || seedcheck[i] < '0') // if the character isn't a number
				{

					loopcheck = false; // set loopcheck to false

				}
				if (seedcheck[i] == 'T') // checks if the character is a T
				{

					ascii = true; // applies enhancements

				}
				if (seedcheck[i] == 'S') // checks if the character is an S
				{

					ai = 1; // applies level 1 AI

				}

			}
			if (loopcheck) // if argument of all numbers
			{

				intarg = j; // set intarg to argument number

			}

		}

	}
	if (intarg != 0) // if there was an integer argument
	{

	  std::string seedtransfer = argc[intarg];
	  std::stringstream str;
	  str << seedtransfer;
		str >> seed; // gets seed from argc

	}
	std::vector<std::shared_ptr<Player>> players; // vector of players 
	std::unique_ptr<Game> g = std::make_unique<Game>(); // creates Game object
	for (int i = 1; i <= 4; i++) // loops through players
	{

		std::string tak = "";
		std::cout << "Is Player" << i << " a human (h) or a computer (c)?" << std::endl;
		std::cin >> tak; // gets whether player is human or computer
		while (tak != "h" && tak != "c") // if neither human, nor computer, ask again
		{

			std::cout << "Please enter a valid option." << std::endl;
			std::cout << "Is Player" << i << " a human (h) or a computer (c)?" << std::endl;
			std::cin >> tak;
		
		}
		if (tak == "h") // if human player, create one and put on players vector
		{

			std::shared_ptr<Human> p = std::make_shared<Human>();
			players.emplace_back(std::move(p));

		}
		else // if computer player, create one and put on players vector
		{

			std::shared_ptr<Computer> p = std::make_shared<Computer>(ai);
			players.emplace_back(std::move(p));

		}

	}
	std::cout << std::endl;
	bool quit = false; // holds whether player has chosen to quit
	do
	{

		int shuf = (*g).shuffle(players, seed); // shuffles deck
		for (int i = 0; i < 52 && !quit; i++) // loops through turns
		{

			if (players[(shuf + i) % 4].get()->isHuman()) // if human player
			{
				bool played = false; // set player to not have played card
        			g.get()->cards(ascii); // print cards on table
	        		std::cout << "Your hand:" << std::endl;
				std::vector<Card *> hand = players[(shuf + i) % 4].get()->getHand(); // get player's hand
				if (ascii) // if UI enhancements
				{

					int l = hand.size(); // holds hand size
                                        for (int j = 0; j < l; j++) // loops through hand, prints top border
                                        {

                                                std::cout << "------ ";

                                        }
                                        std::cout << std::endl;
                                        for (int j = 0; j < l; j++) // prints top middle and card info
                                        {

                                                std::cout << "| " << hand[j]->getNum() << hand[j]->getSuit() << " | ";

                                        }
                                        std::cout << std::endl;
                                        for (int j = 0; j < l; j++) // prints bottom middle
                                        {

                                                std::cout << "|    | ";

                                        }
                                        std::cout << std::endl;
                                        for (int j = 0; j < l; j++) // prints bottom border
                                        {

                                                std::cout << "------ ";

                                        }
                                        std::cout << std::endl;

				}
				else // if no UI enhancements
				{

     					for (auto n: hand) // loops through hand
					{

						std::cout << " " << (*n).getNum() << (*n).getSuit(); // prints card info

					}

				}
        			std::cout << std::endl;
        			std::cout << "Legal plays:";
	        		std::vector<Card *> lp;
				for (auto n: hand) // loops through hand
				{

					if (g.get()->checkValid(n)) // if card is valid, add to legal plays
					{

						lp.emplace_back(n);
						if (!ascii) // if no UI enhancement
						{

							std::cout << " " << n->getNum() << n->getSuit(); // print out card info

						}

					}

				}
				if (ascii) // if UI enhancement
				{
					
					std::cout << std::endl;
					int l = lp.size(); // holds size of lp
					for (int j = 0; j < l; j++) // loops through legal plays, prints top border
	                                {

        	                                std::cout << "------ ";

                	                }
                        	        std::cout << std::endl;
                                	for (int j = 0; j < l; j++) // prints top middle and card info
	                                {

        	                                std::cout << "| " << lp[j]->getNum() << lp[j]->getSuit() << " | ";

                	                }
                        	        std::cout << std::endl;
	                                for (int j = 0; j < l; j++) // prints bottom middle
        	                        {

                	                        std::cout << "|    | ";

                        	        }
	                                std::cout << std::endl;
        	                        for (int j = 0; j < l; j++) // prints bottom border
                	                {

                        	                std::cout << "------ ";

                                	}
                                	std::cout << std::endl;

				}
				std::cout << std::endl;
                		while (!played && !quit) // while no card played and player hasn't chosen to quit, get response
                		{

					std::string rec;
	                        	std::cin >> rec; // takes input from user
        	               		if (rec == "play" && !(lp.empty())) // if player has chosen to play a card and there is a legal play
                	       		{

						std::string carin;
                                		std::cin >> carin; // get the card
                                		char nu = carin[0]; // get the number
                               			char su = carin[1]; // get the suit
	                               		for (auto n: lp) //loop through legal plays
        	                       		{
	
        	                               		if ((*n).getNum() == nu && (*n).getSuit() == su) // if a card with the number and suit is a legal play
                	                       		{

                       	                        		played = true; // player has played a card
                               	                		std::cout << "Player" << (shuf + i) % 4 + 1 << " plays " << nu << su << "." << std::endl;
                                       	        		g.get()->play(n); // play card in game
                                               			players[(shuf + i) % 4].get()->play(n); // play card in player

                                       			}

	                               		}
       	                        		if (!played) // if no play has been made, print message
               	                		{
	
       	                                		std::cout << "This is not a legal play." << std::endl;

               	                		}

                       			}
					else if (rec == "play") // if the player has chosen to play and there are no legal plays
					{

						std::string dump;
	                        		std::cin >> dump; // take card
        	                		std::cout << "This is not a legal play." << std::endl; // print message

					}
                        		else if (rec == "discard" && !(lp.empty())) // if player has chosen to discard and there is a legal play
                       			{

						std::string car;
                                		std::cin >> car; // take card
						std::cout << "You have a legal play. You may not discard." << std::endl; // print message

                	        	}
					else if (rec == "discard") // if the player has chosen to discard and there are no legal plays
					{

						std::vector<Card *> hand = players[(shuf + i) % 4].get()->getHand(); // gets hand
						std::string carin;
						std::cin >> carin; // takes in card to discard
						char nu = carin[0]; // sets number
						char su = carin[1]; // sets suit
						for (auto n: hand) // loops through hand
						{
	
							if ((*n).getNum() == nu && (*n).getSuit() == su) // if card in hand has same number and suit
							{

								played = true; // mark that a player has been made
								std::cout << "Player " << (shuf + i) % 4 + 1 << " discards " << nu << su << "." << std::endl;
								players[(shuf + i) % 4].get()->discard(n); // discard card

							}
	
						}
	
					}
                	        	else if (rec == "deck") // if the player wishes to see the deck
					{

                               			g.get()->printDeck(ascii); // prints deck

                       			}
	                        	else if (rec == "quit" || std::cin.eof()) // if the player has chosen quit or if they've sent an EOF message
        	                	{
	
        	                       		quit = true; // set quit

                	       		}
                       			else if (rec == "ragequit") // if the player has chosen to ragequit
                       			{

                                		std::cout << "Player" << (shuf + i) % 4 + 1 << " ragequits. A computer will now take over." << std::endl; // print message
	                               		std::shared_ptr<Computer> newc = std::make_shared<Computer>(*(players[(shuf + i) % 4].get()), ai); // create computer player
                	       	        	players.erase((players.begin() + ((shuf + i) % 4))); // remove human player
						players.insert((players.begin() + ((shuf + i) % 4)), newc); // add computer player
						played = true; // set that a play has been made
                	               		i--; // decrease the number of cards so that all cards will still be played

        	                	}
					else // if no legal command used, print commands
					{

						std::cout << "Please enter one of the following commands: play <X>; discard <X>; deck; quit; ragequit." << std::endl;

					}
		

				}

       			}
			
			else // if computer player
			{

				std::vector<Card *> hand = players[(shuf + i) % 4].get()->getHand(); // get hand
				std::vector<Card *> lp;
				Card * n = nullptr;
                                for (unsigned i = 0; i < hand.size(); i++) // loops through hand, checks if card is valid, if so adds to legal plays
                                {

					n = hand[i];
                                        if (g.get()->checkValid(n))
                                        {

                                                lp.emplace_back(n);

                                        }

                                }
				n = players[(shuf + i) % 4].get()->choose(lp); // gets card choice from Computer
				if (lp.size() == 0) // if no legal plays
				{
						
					std::cout << "Player" << (shuf + i) % 4 + 1 << " discards " << n->getNum() << n->getSuit() << "." << std::endl;
					players[(shuf + i) % 4].get()->discard(n); // discard card

				}
				else // if legal plays
				{

					g.get()->play(n); // play card in game
					std::cout << "Player" << (shuf + i) % 4 + 1 << " plays " << n->getNum() << n->getSuit() << "." << std::endl;
					players[(shuf + i) % 4].get()->play(n); // play card in player

				}

			}

		}

	}
	while(!quit && !(g.get()->checkWin(players, ascii))); // run loop while player has not quit and nobody's won

}
