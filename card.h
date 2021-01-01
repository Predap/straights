#ifndef CARD_H_
#define CARD_H_

class Card
{

	char s; // holds suit
	int n; // holds number
	public:
	Card(int n_n, char s_s); // constructor
	char getSuit(); // returns suit
	char getNum(); // returns character associated with number
	int getIntNum(); // returns number as an integer

};

#endif
