#ifndef _CPLAYER_H
#define _CPLAYER_H
#include "cHand.h"

class cPlayer
{
private:
	cHand playerHand;

public:
	cPlayer(); //The constructor
	void setPlayerHand(cCard* aCard);
	cCard* getPlayerCard(int pos); //return the a card from the players hand
	void showPlayerHand();
	int getNumberofCards(); //Return the number of cards in the vector

};
#endif