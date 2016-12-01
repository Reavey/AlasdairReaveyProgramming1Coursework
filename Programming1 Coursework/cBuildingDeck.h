#ifndef _CBUILDINGDECK_H
#define _CBUILDINGDECK_H

#include "cCard.h"

class cBuildingDeck
{
private:
	//A vector that will hold all the cards in the deck
	std::vector<cCard*> bDeck;

	//What it says on the tin
	void createBDeck();

public:
	//Contruct an instance of the building deck
	cBuildingDeck();

	//Every day I'm...
	void shufflePack();

	//Draw a card
	cCard* getCard();

	//Get a specific card
	cCard* findCard(int cardRef);
};
#endif