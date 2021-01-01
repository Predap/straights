#include "card.h"

Card::Card(int n_n, char s_s) // constructor
{

	if (n_n < 1 || n_n > 13) // if number is invalid, sets to -1
	{

		n = -1;

	}
	else
	{

		n = n_n; // sets number to passed number

	}
	if (s_s != 'C' && s_s != 'D' && s_s != 'H' && s_s != 'S') // if suit is invalid, sets to e
	{

		s = 'e';

	}
	else
	{

		s = s_s; // sets suit to passed suit

	}

}

char Card::getSuit() // returns suit
{

	return s;

}

char Card::getNum() // returns number as character
{

	switch(n) // switch based around number, returns character associated with number
	{

		case 1:
			return 'A';
			break;
		case 2:
			return '2';
			break;
		case 3:
			return '3';
			break;
		case 4:
			return '4';
			break;
		case 5:
			return '5';
			break;
		case 6:
			return '6';
			break;
		case 7:
			return '7';
			break;
		case 8:
			return '8';
			break;
		case 9:
			return '9';
			break;
		case 10:
			return 'T';
			break;
		case 11:
			return 'J';
			break;
		case 12:
			return 'Q';
			break;
		case 13:
			return 'K';
			break;
		default:
			return 'E';
			break;

	}
	return 'E';

}

int Card::getIntNum() // returns number as integer
{

	return n;

}
