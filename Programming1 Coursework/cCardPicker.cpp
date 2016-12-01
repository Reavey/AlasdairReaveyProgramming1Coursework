#include "cCardPicker.h"

//Default constructor
cCardPicker::cCardPicker()
{
	this->theBuildingPicked = -1;
}

/*
=================================================================
Update the sprite position
=================================================================
*/

void cCardPicker::update(SDL_Point theAreaClicked, int lowXBoundary, int cardWidth)
{
	SDL_Point areaClicked = theAreaClicked;
	if (areaClicked.x > lowXBoundary && areaClicked.x < cardWidth*5)
	{
		this->buildingClicked.x = (int)(areaClicked.x - lowXBoundary) / cardWidth;
		//this->buildingClicked.y = (int)(areaClicked.y - this->buildingListStartXY.y) / this->aBuilding.getSpriteDimensions().h;
		this->theBuildingPicked = this->buildingClicked.x;
	}
}

/*
=================================================================
- set start position for tile map
=================================================================
*/
void cCardPicker::setBuildingListStartXY(SDL_Point startPosXY)
{
	this->buildingListStartXY = startPosXY;
}
/*
=================================================================
- get start pposition for tile map
=================================================================
*/
SDL_Point cCardPicker::getBuildingListStartXY()
{
	return this->buildingListStartXY;
}
/*
=================================================================
- set value of tree to be used
=================================================================
*/
void cCardPicker::setCardPicked(int aCardPicked)
{
	this->theBuildingPicked = aCardPicked;
}
/*
=================================================================
- get value of tree to be used
=================================================================
*/
int cCardPicker::getCardPicked()
{
	return this->theBuildingPicked;
}