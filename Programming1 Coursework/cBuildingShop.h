#ifndef _CBUILDINGSHOP_H
#define _CBUILDINGSHOP_H

#include "cPlayerDeck.h"
#include "cHand.h"

class cBuildingShop
{
private:
	//A vector that will hold all cards in the shop building deck
	std::vector<cCard*> bShopDeck;
	//cPlayerDeck* shopDeck;

	//Create the shop Building deck
	void createBuildingShopDeck(); //cPlayerDeck* theDeck

	//The shop's revealed cards are effectively a hand
	cHand buildingShopHand;

public:
	//Construct an instance of the shop Building deck
	cBuildingShop(); //cPlayerDeck* theDeck

	//Add a card to the Building Shop deck
	void addCard(cCard* aCard);

	//Draw a card from Building Shop deck
	cCard* drawBuildingCard();

	//Add a card to the shop's "hand"
	void setBuildingShopHand(cCard* aCard);

	//Get a card from the shops "hand"
	cCard* getBuildingCard(int pos);

	//Show the shop's "hand"
	void showBuildingShopHand();

	//Get the number of revealed cards
	int getNumberOfCards();

	//Shuffle shuffle
	void shuffleBuildingShopDeck();

	//Erase a card from the shop's "hand"
	void replaceCard(int pos, cCard* aCard);
};

#endif
