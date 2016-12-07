#include "cBuildingDeck.h"

cBuildingDeck::cBuildingDeck()
{
	cBuildingDeck::bDeck.reserve(20); //Create a temporary array for the cards
	cBuildingDeck::bDeck.clear();
	cBuildingDeck::createBDeck();
	cBuildingDeck::shufflePack();
}

void cBuildingDeck::createBDeck()
{
	for (int title = FARM; title <= SCHOOL; title++)
	{
		//Each card gets 5 copies
		for (int duplicate = 0; duplicate < 5; duplicate++) 
		{
			if (title == FARM) 
			{
				cBuildingDeck::bDeck.push_back(new cCard(static_cast<eBuildingTitle>(title), 0, 0, 0, 0,static_cast<eResType>(FOOD)));
			}
			if (title == MARKET)
			{
				cBuildingDeck::bDeck.push_back(new cCard(static_cast<eBuildingTitle>(title), 0, 1, 0, 0, static_cast<eResType>(GOLD)));
			}
			if (title == MINE)
			{
				cBuildingDeck::bDeck.push_back(new cCard(static_cast<eBuildingTitle>(title), 0, 0, 0, 0, static_cast<eResType>(MATERIALS)));
			}
			if (title == SCHOOL)
			{
				cBuildingDeck::bDeck.push_back(new cCard(static_cast<eBuildingTitle>(title), 0, 1, 0, 0, static_cast<eResType>(KNOWLEDGE)));
			}
		}
	}
}

//Randomise the building deck
void cBuildingDeck::shufflePack()
{
	random_shuffle(cBuildingDeck::bDeck.begin(), cBuildingDeck::bDeck.end());
}

//Draw top card to the building deck
cCard* cBuildingDeck::getCard()
{
	cCard* aCard;
	aCard = cBuildingDeck::bDeck.back();
	cBuildingDeck::bDeck.pop_back();
	return aCard;
}

//Get a specific card from the building deck
cCard* cBuildingDeck::findCard(int cardRef)
{
	cCard* aCard;
	aCard = cBuildingDeck::bDeck.at(cardRef);
	cBuildingDeck::bDeck.erase(cBuildingDeck::bDeck.begin()+cardRef);
	return aCard;
}