#ifndef _GAME_H
#define _GAME_H

#include<SDL.h>

//Game specific includes
#include "GameConstants.h"
#include "cBuildingDeck.h"
#include "cBuildingShop.h"
#include "cButton.h"
#include "cButtonMgr.h"
#include "cCard.h"
#include "cCardPicker.h"
#include "cFont.h"
#include "cFontMgr.h"
#include "cHand.h"
#include "cPlayer.h"
#include "cSound.h"
#include "cSoundMgr.h"
#include "cSprite.h"
#include "cTexture.h"
#include "cTextureMgr.h"

using namespace std;

class cGame
{
public:
	cGame();

	void initialise(SDL_Window* theSDLWindow, SDL_Renderer* theRenderer);
	void run(SDL_Window* theSDLWindow, SDL_Renderer* theRenderer);
	bool getInput(bool theLoop);
	void cleanUp(SDL_Window* theSDLWindow);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre);
	void update();
	void update(double deltaTime);

	static cGame* getInstance();

private:
	static cGame* pInstance;

	// for framerates
	time_point< high_resolution_clock > m_lastTime;
	time_point< high_resolution_clock > m_CurrentTime;
	duration< double > deltaTime;
	bool loop;

	//Sprites for displaying cards
	cSprite spriteBkgd;
	cSprite cardSprite;

	//Game related variables
	vector<int> resStored; //Order in the vector is Food, Gold, Materials, Knowledge
	vector<int> resPerTurn; //Order in the vector is Food, Gold, Materials, Knowledge
	bool isShopBuilding; //Indiciate if clicked card is from the building shop
	bool isPlayerCard; //Indicate if clicked card is from player hand
	//A series of booleans to control the player turn
	bool gainResources;
	bool playBuildings;
	string resources;
	int buildingCounter;
	bool buyFromShop;
	bool drawCards;
	int turn;
	string turnStr;
	int score;
	string scoreStr;
	bool reset;
	vector<LPCSTR> textureName;
	vector<LPCSTR> textName;
	vector<LPCSTR> texturesToUse;

	// Fonts to use
	vector<LPCSTR> fontList;
	vector<LPCSTR> fontsToUse;
	// Text for Game
	vector<LPCSTR> gameTextNames;
	vector<LPCSTR> gameTextList;

	// Game Sounds
	vector<LPCSTR> soundList;
	vector<soundType> soundTypes;
	vector<LPCSTR> soundsToUse;

	// Create vector array of button textures
	vector<LPCSTR> btnNameList;
	vector<LPCSTR> btnTexturesToUse;
	vector<SDL_Point> btnPos;
	vector <cButton> theButtons;

	//Icons for use in the game
	vector<LPCSTR> iconName;
	vector<LPCSTR> iconToUse;

	//Game objects
	vector<cPlayer*> thePlayer;
	vector <cPlayerDeck*> theDeck;
	vector <cBuildingShop*> theBuildingShopDeck;
	cCard* theCard = NULL;
	cCardPicker theCardPicker;
	cSprite dragCard;
	cSprite aBuilding;

	int renderWidth, renderHeight;

	gameState theGameState;
	btnTypes theBtnType;
	bool gameOver = false;

	double getElapsedSeconds();

	SDL_Rect pos;
	SDL_Rect dragPos;
	FPoint scale;
	SDL_Rect aRect;
	SDL_Color aColour;

	cTexture* tempTextTexture;
	SDL_Point theAreaClicked;
};

#endif