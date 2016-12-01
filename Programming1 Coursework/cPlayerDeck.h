#ifndef _CPLAYERDECK_H
#define _CPLAYERDECK_H
#include "cBuildingDeck.h"

class cPlayerDeck
{
private:
	std::vector<cCard*> pDeck;
	void createPDeck();

public:
	cPlayerDeck(); //The Constructor
	void addCard(cCard* aCard); //Add a card to plaer deck from main pack
	cCard* getCard(); //Draw a card from the deck
	void shuffleDeck(); //Shuffle the player deck
	cBuildingDeck buildingDeck;
};
#endif