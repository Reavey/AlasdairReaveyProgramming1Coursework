#include "cPlayerDeck.h"

cPlayerDeck::cPlayerDeck() //Constructor to create an instance of the card class
{
	cPlayerDeck::pDeck.reserve(0); //Define a temporary array to hold the cards
	cPlayerDeck::pDeck.clear();
	cPlayerDeck::createPDeck();

}

void cPlayerDeck::createPDeck() //Construct the player's starting deck
{
	for (int title = FARM; title <= SCHOOL; title++)
	{
		//Farms and Mines get 3 Copies
		for (int duplicate = 0; duplicate < 3; duplicate++)
		{
			if (title == FARM)
			{
				cPlayerDeck::pDeck.push_back(new cCard(static_cast<eBuildingTitle>(title), 0, 0, 0, 1, static_cast<eResType>(FOOD)));
			}
			if (title == MINE)
			{
				cPlayerDeck::pDeck.push_back(new cCard(static_cast<eBuildingTitle>(title), 0, 0, 0, 1, static_cast<eResType>(MATERIALS)));
			}
			//Markets and schools get two copies
			if (duplicate >= 1)
			{
				if (title == MARKET)
				{
					cPlayerDeck::pDeck.push_back(new cCard(static_cast<eBuildingTitle>(title), 0, 3, 3, 1, static_cast<eResType>(GOLD)));
				}
				if (title == SCHOOL)
				{
					cPlayerDeck::pDeck.push_back(new cCard(static_cast<eBuildingTitle>(title), 0, 3, 3, 1, static_cast<eResType>(KNOWLEDGE)));
				}
			}
		}
	}
	srand(time(NULL));
	cPlayerDeck::shuffleDeck();

}

void cPlayerDeck::addCard(cCard* aCard) //Add a card to the deck
{
	cPlayerDeck::pDeck.push_back(aCard);
}

cCard* cPlayerDeck::getCard() //Draw the top card of the player deck
{
	cCard* aCard;
	aCard = cPlayerDeck::pDeck.back();
	cPlayerDeck::pDeck.pop_back();
	return aCard;
}

void cPlayerDeck::shuffleDeck() //Shuffle the player deck
{
	random_shuffle(cPlayerDeck::pDeck.begin(), cPlayerDeck::pDeck.end());
}

int cPlayerDeck::cardsInDeck() //Number of cards remaining in the deck
{
	return cPlayerDeck::pDeck.size();
}