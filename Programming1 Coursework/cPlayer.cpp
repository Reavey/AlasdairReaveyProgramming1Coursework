#include "cPlayer.h"

cPlayer::cPlayer()
{

}

//Add a card to the players hand
void cPlayer::setPlayerHand(cCard* aCard) 
{
	cPlayer::playerHand.addCard(aCard);
}

//return the a card from the players hand.
cCard* cPlayer::getPlayerCard(int pos)
{
	return playerHand.getCardFromHand(pos);
}

//Display the player's hand
void cPlayer::showPlayerHand()
{
	cPlayer::playerHand.showHand();
}

//Return the number of cards in the vector
int cPlayer::getNumberofCards()
{
	return cPlayer::playerHand.getNumberofCards();
}