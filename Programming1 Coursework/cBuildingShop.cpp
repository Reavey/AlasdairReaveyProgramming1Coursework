#include "cBuildingShop.h"
cBuildingShop::cBuildingShop() //Constructor to create an instance of the card class cPlayerDeck* theDeck
{
	cBuildingShop::bShopDeck.reserve(0); //Create a vector to hold the cards
	cBuildingShop::bShopDeck.clear();
	cBuildingShop::createBuildingShopDeck(); //theDeck
}

void cBuildingShop::createBuildingShopDeck() //cPlayerDeck* theDeck
{
	//shopDeck = theDeck;
	/*for (int i = 0; i < 10; i++)
	{
		cBuildingShop::addCard(shopDeck->getCard());
	}*/

	for (int title = FARM; title <= SCHOOL; title++)
	{
		//Farms and Mines get 2 Copies
		for (int duplicate = 0; duplicate < 3; duplicate++)
		{
			if (duplicate >= 1)
			{
				if (title == FARM)
				{
					cBuildingShop::bShopDeck.push_back(new cCard(static_cast<eBuildingTitle>(title), 0, 0, 0, 0, static_cast<eResType>(FOOD)));
				}
				if (title == MINE)
				{
					cBuildingShop::bShopDeck.push_back(new cCard(static_cast<eBuildingTitle>(title), 0, 0, 0, 0, static_cast<eResType>(MATERIALS)));
				}
			}
			//Markets and schools get three copies			
			if (title == MARKET)
			{
				cBuildingShop::bShopDeck.push_back(new cCard(static_cast<eBuildingTitle>(title), 0, 1, 0, 0, static_cast<eResType>(GOLD)));
			}
			if (title == SCHOOL)
			{
				cBuildingShop::bShopDeck.push_back(new cCard(static_cast<eBuildingTitle>(title), 0, 1, 0, 0, static_cast<eResType>(KNOWLEDGE)));
			}
			
		}
	}

	srand(time(NULL));
	cBuildingShop::shuffleBuildingShopDeck();
}

//Add a new card to the deck
void cBuildingShop::addCard(cCard* aCard)
{
	cBuildingShop::bShopDeck.push_back(aCard);
}

//Draw a card from Building Shop deck
cCard* cBuildingShop::drawBuildingCard()
{
	cCard* aCard;
	aCard = cBuildingShop::bShopDeck.back();
	cBuildingShop::bShopDeck.pop_back();
	return aCard;
}

//Add a card to the shop's "hand"
void cBuildingShop::setBuildingShopHand(cCard* aCard)
{
	cBuildingShop::buildingShopHand.addCard(aCard);
}

//Get a card from the building shop's "hand" (face-up cards)
cCard* cBuildingShop::getBuildingCard(int pos)
{
	return buildingShopHand.getCardFromHand(pos);
}

//Reveal the building shop's "Hand"
void cBuildingShop::showBuildingShopHand()
{
	cBuildingShop::buildingShopHand.showHand();
}

//Get number of currently revealed cards
int cBuildingShop::getNumberOfCards()
{
	return cBuildingShop::buildingShopHand.getNumberofCards();
}

//Shuffle shuffle
void cBuildingShop::shuffleBuildingShopDeck()
{
	random_shuffle(cBuildingShop::bShopDeck.begin(), cBuildingShop::bShopDeck.end());
}

//Erase a card from the shop's "hand"
void cBuildingShop::replaceCard(int pos, cCard* aCard)
{
	buildingShopHand.replaceCard(pos, aCard);
}