#ifndef _CCARD_H
#define _CCARD_H

#include "GameConstants.h"

class cCard
{
private: 
	BUILDINGCARD aBuilding;

public:
	cCard(eBuildingTitle ccTitle, short ccLevel, short ccMatCost, short ccKnowCost, short ccResQuan,eResType ccResType);
	cCard();

	//Return details for current instance of a card
	BUILDINGCARD getCard(); 

	//Display the details for the current card, rough layout equivalent to sprite
	void showCard(); 

	//Return current card level, will be used to seperate all cards into individual 'decks' based on level in game setup
	short getLevel(); 

	//Return a building's material cost so it can be played from hand
	short getMatCost();

	//Return a building's knowledge cost so it can be bought from the shop
	short getKnowCost();

	//Return quantity of resource produced by a building to add to available resources at start of each turn
	short getOutput();

	//Return type of resource produced by a building so the quantity returned goes to the right place
	eResType getOutType();

	//Return the filename of the associated card image
	LPCSTR getImage();

	//Return the card name of the associated card image
	LPCSTR getCardName();
};
#endif