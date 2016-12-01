#include "cCard.h";
#include <iostream>
using namespace std;

cCard::cCard()
{
	aBuilding.cTitle = FARM;
	aBuilding.cLevel = FIRST;
	aBuilding.cMatCost = MZERO;
	aBuilding.cKnowCost = KZERO;
	aBuilding.cResQuan = RONE;
	aBuilding.cResType = FOOD;
	aBuilding.cFilename = "";
	aBuilding.cCardname = "";
}
//constructor
cCard::cCard(eBuildingTitle ccTitle, short ccLevel, short ccMatCost, short ccKnowCost, short ccResQuan, eResType ccResType)
{
	aBuilding.cTitle = ccTitle;
	aBuilding.cLevel = ccLevel;
	aBuilding.cMatCost = ccMatCost;
	aBuilding.cKnowCost = ccKnowCost;
	aBuilding.cResQuan = ccResQuan;
	aBuilding.cResType = ccResType;
	aBuilding.cFilename = "Images/" + (string)strTitle[ccTitle] + ".png";
	aBuilding.cCardname = (string)strTitle[ccTitle];
}

//Return details for current instance of a card
BUILDINGCARD cCard::getCard()
{
	return aBuilding;
}


//Display the details for the current card, rough layout equivalent to sprite
void cCard::showCard()
{
	BUILDINGCARD sCard = cCard::getCard();
	std::cout << strTitle[sCard.cTitle] << endl <<
		"Level: " << intLevel[sCard.cLevel] << endl <<
		"Material Cost: " << intMatCost[sCard.cMatCost] << endl <<
		"Research Cost: " << intKnowCost[sCard.cKnowCost] << endl <<
		"At the beginning of your turn gain " << outValue[sCard.cResQuan] << " " << outType[sCard.cResType] << endl << endl;
}
//Return current card level, will be used to seperate all cards into individual 'decks' based on level in game setup
short cCard::getLevel() 
{
	BUILDINGCARD glCard = cCard::getCard();
	return glCard.cLevel;
}

//Return a building's material cost so it can be played from hand
short cCard::getMatCost()
{
	BUILDINGCARD gmcCard = cCard::getCard();
	return gmcCard.cMatCost;
}

//Return a building's knowledge cost so it can be bought from the shop
short cCard::getKnowCost()
{
	BUILDINGCARD gkcCard = cCard::getCard();
	return gkcCard.cKnowCost;
}

//Return quantity of resource produced by a building to add to available resources at start of each turn
short cCard::getOutput()
{
	BUILDINGCARD goCard = cCard::getCard();
	return goCard.cResQuan;
}

//Return type of resource produced by a building so the quantity returned goes to the right place
eResType cCard::getOutType()
{
	BUILDINGCARD gotCard = cCard::getCard();
	return gotCard.cResType;
}

//Return the filename of the associated card image
LPCSTR cCard::getImage()
{
	return aBuilding.cFilename.c_str();
}

//Return the card name of the associated card image
LPCSTR cCard::getCardName()
{
	return aBuilding.cCardname.c_str();
}