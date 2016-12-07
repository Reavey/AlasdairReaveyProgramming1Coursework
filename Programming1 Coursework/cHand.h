#ifndef _CHAND_H
#define _CHAND_H
#include "cPlayerDeck.h"

class cHand
{
private:
	std::vector<cCard*> aHand; //The vector to contain the hand

public:
	cHand(); //The hand constructor
	void addCard(cCard* aCard); //Add a card to the hand from the pack
	void showHand(); //Show contetnts of hand
	int cHand::getNumberofCards(); // return the number of cards in the vector
	cCard* getCardFromHand(int pos); // return a card from the hand
	void replaceCard(int pos, cCard* aCard); // remove a specific card from hand
	void removeCard(int pos); // Delete a specific card from hand
};
#endif