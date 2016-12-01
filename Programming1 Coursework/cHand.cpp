#include "cHand.h"

cHand::cHand() //Constructor to create an instance of the card class
{
	cHand::aHand.reserve(20); //Define a temporary array to hold the cards
}

void cHand::addCard(cCard* aCard) //Add a card to current hand
{
	cHand::aHand.push_back(aCard);
}

void cHand::showHand() //Show contents of current hand
{
	std::vector<cCard*>::iterator iter = aHand.begin();
	//Iterate through hand showing each card
	for (iter = cHand::aHand.begin(); iter != cHand::aHand.end(); ++iter)
	{
		(*iter)->showCard();
	}
}

int cHand::getNumberofCards() // return the number of cards in the vector
{
	return cHand::aHand.size();
}

cCard* cHand::getCardFromHand(int pos) // return a card from the hand
{
	return aHand[pos];
}

void cHand::replaceCard(int pos, cCard* aCard)
{
	aHand[pos] = aCard;
}