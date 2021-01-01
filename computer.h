#include "player.h"
class Computer : public Player // Computer is subclass of Player
{

	int a; // holds level of AI
	public:
	Computer(int ai); // constructor from scratch
	Computer(Player p, int ai); // constructor from other Player
	void play(Card * c = nullptr); // plays card
	Card * choose(std::vector<Card *> lp); // chooses card to play or discard
        void discard(Card * c = nullptr); // discards card
	bool isHuman(); // checks if Computer is human

};
