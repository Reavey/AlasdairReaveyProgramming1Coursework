#include "cCardPicker.h"

//Default constructor
cCardPicker::cCardPicker()
{
	this->theBuildingPicked = -1;
}

/*
=================================================================
Return which card has been picked from shop or player hand
=================================================================
*/

void cCardPicker::update(SDL_Point theAreaClicked, int lowXBoundary, int cardWidth, int cardHeight, int cardsInHand)
{
	SDL_Point areaClicked = theAreaClicked;
	if (areaClicked.x > lowXBoundary && areaClicked.x < cardWidth*cardsInHand)
	{
		this->buildingClicked.x = (int)(areaClicked.x - lowXBoundary) / cardWidth;
		this->theBuildingPicked = this->buildingClicked.x;
	}
}
/*
=================================================================
- set value of card to be used
=================================================================
*/
void cCardPicker::setCardPicked(int aCardPicked)
{
	this->theBuildingPicked = aCardPicked;
}
/*
=================================================================
- get value of card to be used
=================================================================
*/
int cCardPicker::getCardPicked()
{
	return this->theBuildingPicked;
}