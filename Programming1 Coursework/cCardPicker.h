#ifndef _CCARDPICKER_H
#define _CCARDPICKER_H
#include "GameConstants.h"
#include "cBuildingShop.h"
#include "cSprite.h"
#include "cTextureMgr.h"


class cCardPicker : public cSprite
{
protected:
	int buildingShopList[5]; //Always 5 buildings in the shop

private:
	SDL_Point buildingListStartXY;
	SDL_Point buildingClicked;
	cSprite aBuilding;
	int theBuildingPicked;

public:
	cCardPicker();
	void update(SDL_Point theAreaClicked, int lowXBoundary, int cardWidth, int cardHeight, int cardsInHand);
	void setCardPicked(int aCardPicked);
	int getCardPicked();
};

#endif