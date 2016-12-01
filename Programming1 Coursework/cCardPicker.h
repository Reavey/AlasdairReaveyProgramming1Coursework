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

	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, cTextureMgr* theTxtMgr, vector<LPCSTR> theTxt, FPoint scale);
	void update(SDL_Point theAreaClicked,int lowXBoundary, int cardWidth);
	void setBuildingListStartXY(SDL_Point startPosXY);
	SDL_Point getBuildingListStartXY();
	void setCardPicked(int aCardPicked);
	int getCardPicked();
};

#endif