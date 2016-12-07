#include "cGame.h"

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTextureManager = cTextureMgr::getInstance();
static cFontMgr* theFontManager = cFontMgr::getInstance();
static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();
static cButtonMgr* theButtonMgr = cButtonMgr::getInstance();

cGame::cGame() //Constructor
{
	
}

cGame* cGame::getInstance() //Singleton design pattern
{
	if (pInstance == NULL)
	{
		pInstance = new cGame();
	}
	return cGame::pInstance;
}

void cGame::initialise(SDL_Window* theSDLWindow, SDL_Renderer* theRenderer)
{
	// Get width and height of render context
	SDL_GetRendererOutputSize(theRenderer, &renderWidth, &renderHeight);
	this->m_lastTime = high_resolution_clock::now();
	// Clear the buffer with a black background
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);

	theTextureManager->setRenderer(theRenderer);
	theFontManager->initFontLib();
	theSoundMgr->initMixer();

	theAreaClicked = { 0, 0 };
	// Store the textures for the cards
	textureName = { "Farm", "Market", "Mine", "School", "theBackground", "DropPoint", "FarmHouse", "Market01", "Market02", "Market03", "Market04", 
		"Market05", "Mine01", "Mine02", "Mine03", "Mine04", "Mine05", "School01", "School02", "School03", "School04", 
		"School05" };
	//Each building requires several textures as it "levels up" as multiples are played
	texturesToUse = { "Images/Farm.png", "Images/Market.png", "Images/Mine.png", "Images/School.png",
	"Images/Background.png", "Images/DropZone.png", "Images/FarmHouse.png", "Images/MarketSprite01.png", 
	"Images/MarketSprite02.png", "Images/MarketSprite03.png", "Images/MarketSprite04.png", "Images/MarketSprite05.png",
	"Images/Mine01.png", "Images/Mine02.png", "Images/Mine03.png", "Images/Mine04.png", "Images/Mine05.png", "Images/School01",
	"Images/School01.png", "Images/School02.png", "Images/School03.png", "Images/School04.png", "Images/School05.png"};

	for (int tCount = 0; tCount < textureName.size(); tCount++)
	{
		theTextureManager->addTexture(textureName[tCount], texturesToUse[tCount]);
	}
	tempTextTexture = theTextureManager->getTexture(textureName[0]);
	aRect = { 0, 0, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
	aColour = { 228, 213, 238, 255 };
	// Store the textures for the buttons
	btnNameList = { "exit_btn", "instructions_btn", "load_btn", "menu_btn", "play_btn", "save_btn", "settings_btn" };
	btnTexturesToUse = { "Images/Buttons/button_exit.png", "Images/Buttons/button_instructions.png", "Images/Buttons/button_load.png", "Images/Buttons/button_menu.png", "Images/Buttons/button_play.png", "Images/Buttons/button_save.png", "Images/Buttons/button_settings.png"};
	btnPos = { { 400, 375 },{ 400, 300 },{ 400, 300 },{ 500, 500 },{ 400, 300 },{ 740, 500 },{ 400, 300 }, { 600, 500 } };
	for (int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		theTextureManager->addTexture(btnNameList[bCount], btnTexturesToUse[bCount]);
	}
	for (int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		cButton * newBtn = new cButton();
		newBtn->setTexture(theTextureManager->getTexture(btnNameList[bCount]));
		newBtn->setSpritePos(btnPos[bCount]);
		newBtn->setSpriteDimensions(theTextureManager->getTexture(btnNameList[bCount])->getTWidth(), theTextureManager->getTexture(btnNameList[bCount])->getTHeight());
		theButtonMgr->add(btnNameList[bCount], newBtn);
	}
	theGameState = MENU;
	theBtnType = EXIT;
	// Create textures for Game Dialogue (text)
	fontList = { "font1", "font2" };
	fontsToUse = { "Fonts/Cantate Beveled.ttf", "Fonts/Mawns_Handwriting.ttf" };
	for (int fonts = 0; fonts < fontList.size(); fonts++)
	{
		theFontManager->addFont(fontList[fonts], fontsToUse[fonts], 48);
	}
	// Create text Textures
	gameTextNames = { "TitleTxt", "ThanksTxt", "SeeYouTxt", "ResourceAvailable", "ResourcePerTurn", "Instructions1",
	"Instructions2", "Instructions3", "Instructions4", "Instructions5", "Instructions6", "Instructions7", "Turn", "Score"};
	gameTextList = { "Monumentous", "Game Over!", "See you again soon!","/","+", 
		"Your aim is to gather as many resources as possible within 7 turns.",
		"Your current resources and the amount gained per turn is displayed at the top of the screen.",
		"You can spend building materials to construct two building cards from your hand at the bottom of the screen.",
		"You can spend knowledge points to buy a new card from the building shop at the top of the screen.",
		"To construct a building or buy a card drag it to the drop zone.",
		"A card's material and knowedge costs are displayed on it. Left click on a card to get a larger view of it.",
		"At the end of the game each stored Food is worth 1 point, Materials are 2 points, Knowledge is 3 points and Gold is 4 points.",
		"Turn: ", "Score: "
	};
	for (int text = 0; text < gameTextNames.size(); text++)
	{
		LPCSTR font = "";
		if (text == 0)
		{
			font = "font1";
		}
		if (text > 0)
		{
			font = "font2";
		}
		theTextureManager->addTexture(gameTextNames[text], theFontManager->getFont(font)->createTextTexture(theRenderer, gameTextList[text], SOLID, { 228, 213, 238, 255 }, { 0, 0, 0, 0 }));
	}

	// Create icon textures
	iconName = { "FoodIcon", "GoldIcon", "MaterialsIcon", "KnowledgeIcon" };
	iconToUse = {"Images/Icons/Food_Icon.png", "Images/Icons/Gold_Icon.png", "Images/Icons/Materials_Icon.png", "Images/Icons/Knowledge_Icon.png"};
	for (int icons = 0; icons < iconName.size(); icons ++)
	{
		theTextureManager->addTexture(iconName[icons], iconToUse[icons]);
	}

	// Load game sounds
	soundList = { "theme", "click" };
	soundTypes = { MUSIC, SFX };
	soundsToUse = { "Audio/Theme/birds.wav", "Audio/SFX/ClickOn.wav" };
	for (int sounds = 0; sounds < soundList.size(); sounds++)
	{
		theSoundMgr->add(soundList[sounds], soundsToUse[sounds], soundTypes[sounds]);
	}

	theSoundMgr->getSnd("theme")->play(-1);

	spriteBkgd.setSpritePos({0, 0});
	spriteBkgd.setTexture(theTextureManager->getTexture("theBackground"));
	spriteBkgd.setSpriteDimensions(theTextureManager->getTexture("theBackground")->getTWidth(), theTextureManager->getTexture("theBackground")->getTHeight());

	thePlayer.push_back(new cPlayer);
	theDeck.push_back(new cPlayerDeck);
	theBuildingShopDeck.push_back(new cBuildingShop);
	//Draw the player their starting hand of 5 cards from the deck
	for (int i = 0; i < 5; i++)
	{
		theCard = theDeck[0]->getCard();
		thePlayer[0]->setPlayerHand(theCard);

	}
	//Draw the top 5 cards of the building deck for the starting shop
	for (int i = 0; i < 5; i++)
	{
		theCard = theBuildingShopDeck[0]->drawBuildingCard();
		theBuildingShopDeck[0]->setBuildingShopHand(theCard);
	}
	//Since the game has yet to start all booleans controlling progress are set to false
	isShopBuilding = false;
	isPlayerCard = false;
	gainResources = true;
	playBuildings = false;
	buildingCounter = 2;
	buyFromShop = false;
	drawCards = false;
	// Set initial values for resource vectors
	resStored = { 0,0,0,0 };
	resPerTurn = { 0,0,0,0 };
	resources = "";
	turn = 1;
	turnStr = "";
	score = 0;
	scoreStr = "";
	reset = false;
}

void cGame::run(SDL_Window* theSDLWindow, SDL_Renderer* theRenderer)
{
	bool loop = true;

	while (loop)
	{
		//We get the time that passed since the last frame
		double elapsedTime = this->getElapsedSeconds();

		loop = this->getInput(loop);
		this->update(elapsedTime);
		this->render(theSDLWindow, theRenderer);
	}
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	SDL_RenderClear(theRenderer);
	switch (theGameState)
	{
	case MENU:
	{
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		// Render the Title
		tempTextTexture = theTextureManager->getTexture("TitleTxt");
		pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		for (int i = 0; i < 7; i++)
		{
			string instructionText = "Instructions" + to_string(i+1);
			tempTextTexture = theTextureManager->getTexture(instructionText.c_str());
			pos = {20, 150 + (70*i),tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
			float x = 0.45;
			float y = 0.5;
			scale = { x, y };
			tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		}
		// Render Button
		theButtonMgr->getBtn("play_btn")->setSpritePos({ 597, 350 });
		theButtonMgr->getBtn("play_btn")->render(theRenderer, &theButtonMgr->getBtn("play_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("play_btn")->getSpritePos(), theButtonMgr->getBtn("play_btn")->getSpriteScale());
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 607, 420 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
	}
	break;
	case PLAYING:
	{
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		//Render the resource values
		for (int i = 0; i < 4; i++)
		{
			resources = gameTextList[3] + to_string(resStored[i]);
			theTextureManager->addTexture("ResourceAvailable", theFontManager->getFont("font2")->createTextTexture(theRenderer, resources.c_str(), SOLID, { 255, 255, 255, 255 }, { 0,0,0,0 }));
			tempTextTexture = theTextureManager->getTexture("ResourceAvailable");
			int xPos = 540 + (i * 150);
			int yPos = 10;
			pos = { xPos, yPos, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
			tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
			theTextureManager->deleteTexture("ResourceAvailable");
		}
		//Render the per turn resource increase
		for (int i = 0; i < 4; i++)
		{
			resources = gameTextList[4] + to_string(resPerTurn[i]);
			theTextureManager->addTexture("ResourcePerTurn", theFontManager->getFont("font2")->createTextTexture(theRenderer, resources.c_str(), SOLID, { 255,255,255,255 }, { 0,0,0,0 }));
			tempTextTexture = theTextureManager->getTexture("ResourcePerTurn");
			int xPos = 490 + (i * 150);
			int yPos = 10;
			pos = { xPos, yPos, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
			tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
			theTextureManager->deleteTexture("ResourcePerTurn");
		}
		//Render the turn counter
		turnStr = gameTextList[12] + to_string(turn);
		theTextureManager->addTexture("Turn", theFontManager->getFont("font2")->createTextTexture(theRenderer, turnStr.c_str(), SOLID, { 255,255,255,255 }, { 0,0,0,0 }));
		tempTextTexture = theTextureManager->getTexture("Turn");
		int xPos = 460;
		int yPos = 80;
		pos = { xPos, yPos, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		theTextureManager->deleteTexture("Turn");

		//Render the cards in the shop
		for (int i = 0; i < theBuildingShopDeck[0]->getNumberInHand(); i++)
		{
			LPCSTR cardName = theBuildingShopDeck[0]->getBuildingCard(i)->getCardName();
			int xPos = 10 + i * (theTextureManager->getTexture(cardName)->getTWidth());
			int yPos = 10;
			tempTextTexture = theTextureManager->getTexture(cardName);
			pos = { xPos, yPos, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
			scale = { 0.25,0.25 };
			tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		}
		scale = { 1,1 };
		//Render the constructed buildings
		for (int i = 0; i < 4; i++)
		{
			//Since each building adds 1 resource per turn we want to render a building for each resource per turn
			for (int j = 0; j < resPerTurn[i]; j++)
			{
				//Render the farms first
				if (i == 0)
				{
					int xPos = 750;
					int yPos = 50 + (j * 50);
					tempTextTexture = theTextureManager->getTexture("FarmHouse");
					pos = { xPos, yPos, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
					tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
				}
				//Render the market next
				if (i == 1)
				{
					int xPos = 400;
					int yPos = 200;
					string marketNumber = "Market0" + to_string(j+1);
					tempTextTexture = theTextureManager->getTexture(marketNumber.c_str());
					pos = { xPos, yPos, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
					tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
				}
				//Render the mines
				if (i == 2)
				{
					int xPos = 100;
					int yPos = 180;
					string mineNumber = "Mine0" + to_string(j + 1);
					tempTextTexture = theTextureManager->getTexture(mineNumber.c_str());
					pos = { xPos, yPos, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
					tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
				}
				//Render the school
				if (i == 3)
				{
					int xPos = 800;
					int yPos = 450;
					string schoolNumber = "School0" + to_string(j + 1);
					tempTextTexture = theTextureManager->getTexture(schoolNumber.c_str());
					pos = { xPos, yPos, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
					tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
				}
			}
		}

		//Render the cards in the player hand
		for (int i = 0; i < thePlayer[0]->getNumberofCards(); i++)
		{
			LPCSTR cardName = thePlayer[0]->getPlayerCard(i)->getCardName();
			scale = { 0.5,0.5 };
			int xPos = 10 + i * (theTextureManager->getTexture(cardName)->getTWidth());
			int yPos = theTextureManager->getTexture("theBackground")->getTHeight();
			tempTextTexture = theTextureManager->getTexture(cardName);
			pos = { xPos, yPos, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
			tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		}

		//Render the icons and resources available
		for (int i = 0; i < 4; i++)
		{
			LPCSTR name = iconName[i];
			LPCSTR currentResource = resStored[i] + gameTextList[3];
			LPCSTR currentPerTurn = resPerTurn[i] + gameTextList[4];
			scale = { 1,1 };
			int xPos = 460 + (i * 150);
			int yPos = 10;
			tempTextTexture = theTextureManager->getTexture(name);
			pos = { xPos, yPos, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
			tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		}

		//Render the drop zone for buying cards
		scale = { 1, 1 };
		tempTextTexture = theTextureManager->getTexture("DropPoint");
		pos = { 1050, 5, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		//Place and render the exit button
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 615, 650 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
		//If a card has been picked render the corresponding card and drag it around
		if (theCardPicker.getCardPicked() > -1)
		{
			int cardNum = theCardPicker.getCardPicked();
			int xPos = dragPos.x - 50;
			int yPos = dragPos.y - 50;
			LPCSTR currentCardName = "";
			if (isShopBuilding == true)
			{
				currentCardName = theBuildingShopDeck[0]->getBuildingCard(cardNum)->getCardName();
			}
			if (isPlayerCard == true)
			{
				currentCardName = thePlayer[0]->getPlayerCard(cardNum)->getCardName();
			}
			tempTextTexture = theTextureManager->getTexture(currentCardName);
			pos = { xPos, yPos, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
			tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		}
	}
	break;
	case END:
	{
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		// Render the Title
		tempTextTexture = theTextureManager->getTexture("TitleTxt");
		pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		//Render the thank you
		tempTextTexture = theTextureManager->getTexture("ThanksTxt");
		pos = { 10, 60, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		//Render the score
		score = resStored[0] + (resStored[1] * 2) + (resStored[2] * 4) + (resStored[3] * 3);
		scoreStr = gameTextList[13] + to_string(score);
		theTextureManager->addTexture("Score", theFontManager->getFont("font2")->createTextTexture(theRenderer, scoreStr.c_str(), SOLID, { 255,255,255,255 }, { 0,0,0,0 }));
		tempTextTexture = theTextureManager->getTexture("Score");
		int xPos = 500;
		int yPos = 340;
		pos = { xPos, yPos, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		theTextureManager->deleteTexture("Score");
		//Place and render the exit button
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 615, 500 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
	}
	case QUIT:
	{
		loop = false;
	}
	break;
	default:
		break;
	}
	SDL_RenderPresent(theRenderer);
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre)
{

	SDL_RenderPresent(theRenderer);
}

void cGame::update()
{

}

void cGame::update(double deltaTime)
{
	// Check Button clicked and change state
	if (theGameState == MENU || theGameState == END)
	{
		theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, QUIT, theAreaClicked);
	}
	else if (theGameState == END)
	{
		theGameState = theButtonMgr->getBtn("menu_btn")->update(theGameState, MENU, theAreaClicked);
		theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, QUIT, theAreaClicked);
	}
	else
	{
		theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, MENU, theAreaClicked);
		//Enforce the turn order through the use of booleans
		if (gainResources == true)
		{
			resStored[0] += resPerTurn[0];
			resStored[1] += resPerTurn[1];
			resStored[2] += resPerTurn[2];
			resStored[3] += resPerTurn[3];
			gainResources = false;
			playBuildings = true;
		}
		if (playBuildings == true)
		{
			if (thePlayer[0]->getNumberofCards() <= 0)
			{
				buildingCounter = 2;
				playBuildings = false;
				buyFromShop = true;
			}
			int costCounter = 0;
			bool affordable = false;
			//Check to make sure something in hand can actually be played, if not moce to next step
			for (int i = 0; i < thePlayer[0]->getNumberofCards(); i++)
			{
				if (resStored[2] < thePlayer[0]->getPlayerCard(i)->getMatCost())
				{
					costCounter = thePlayer[0]->getPlayerCard(i)->getMatCost();
				}
				if (resStored[2] >= thePlayer[0]->getPlayerCard(i)->getMatCost())
				{
					affordable = true;
				}
			}
			if (costCounter > resStored[2] && affordable != true)
			{
				buildingCounter = 2;
				playBuildings = false;
				buyFromShop = true;
				costCounter = 0;
				cout << "test";
			}
		}
			if (buildingCounter <= 0)
			{
				buildingCounter = 2;
				playBuildings = false;
				buyFromShop = true;
		}
		if (buyFromShop == true)
		{
			int costCounter = 0;
			bool affordable = false;
			//Check to make sure something in the shop can be bought, if not move to next step
			for (int i = 0; i < theBuildingShopDeck[0]->getNumberInHand(); i++)
			{
				if (resStored[3] < theBuildingShopDeck[0]->getBuildingCard(i)->getKnowCost())
				{
					costCounter = theBuildingShopDeck[0]->getBuildingCard(i)->getKnowCost();
				}
				if (resStored[3] >= theBuildingShopDeck[0]->getBuildingCard(i)->getKnowCost())
				{
					affordable = true;
				}
			}
			if (costCounter > resStored[3] && affordable != true)
			{
				costCounter = 0;
				buyFromShop = false;
				drawCards = true;
			}
		}
		if (drawCards == true)
		{
			//The player should always have as close to 5 cards in hand as possible
			for (int cards = thePlayer[0]->getNumberofCards(); cards < 5; cards++)
			{
				if (theDeck[0]->cardsInDeck() > 0)
				{
					thePlayer[0]->setPlayerHand(theDeck[0]->getCard());
				}
			}
			if (turn >= 7)
			{
				theGameState = END;
			}
			turn++;
			drawCards = false;
			gainResources = true;
		}
	}
	theGameState = theButtonMgr->getBtn("play_btn")->update(theGameState, PLAYING, theAreaClicked);
	if (reset == true)
	{
		//Empty all the resources
		for (int i = 0; i < 4; i++)
		{
			resStored[i] = 0;
			resPerTurn[i] = 0;
		}
		//Reset all the variables
		turn = 1;
		score = 0;
		isShopBuilding = false;
		isPlayerCard = false;
		gainResources = true;
		playBuildings = false;
		buildingCounter = 2;
		buyFromShop = false;
		drawCards = false;
		//Delete the game objects then create new ones
		thePlayer.erase( cGame::thePlayer.begin() );
		thePlayer.push_back(new cPlayer);
		theDeck.erase(cGame::theDeck.begin());
		theDeck.push_back(new cPlayerDeck);
		theBuildingShopDeck.erase(cGame::theBuildingShopDeck.begin());
		theBuildingShopDeck.push_back(new cBuildingShop);
		//Draw the player their starting hand of 5 cards from the deck
		for (int i = 0; i < 5; i++)
		{
			theCard = theDeck[0]->getCard();
			thePlayer[0]->setPlayerHand(theCard);

		}
		//Draw the top 5 cards of the building deck for the starting shop
		for (int i = 0; i < 5; i++)
		{
			theCard = theBuildingShopDeck[0]->drawBuildingCard();
			theBuildingShopDeck[0]->setBuildingShopHand(theCard);
		}

		reset = false;
	}
}

bool cGame::getInput(bool theLoop)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			theLoop = false;
		}

		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
			{
				theAreaClicked = { event.motion.x, event.motion.y };
				if (theGameState == PLAYING)
				{
					//Detect if card clicked is in the top row of the shop and if it is the buy from shop phases
					if (theAreaClicked.y < theTextureManager->getTexture("Farm")->getTHeight()*0.25 && buyFromShop == true)
					{
						isShopBuilding = true;
						theCardPicker.update(theAreaClicked, 10, theTextureManager->getTexture("Farm")->getTWidth()*0.25, theTextureManager->getTexture("Farm")->getTHeight()*0.25, 5);
						if (theCardPicker.getCardPicked() > -1)
						{
							int cardNum = theCardPicker.getCardPicked();
							SDL_Rect dimensions = theTextureManager->getTexture(theBuildingShopDeck[0]->getBuildingCard(cardNum)->getCardName())->getTextureRect();
							dragCard.setTexture(theTextureManager->getTexture(theBuildingShopDeck[0]->getBuildingCard(cardNum)->getCardName()));
							dragCard.setSpriteDimensions(dimensions.w, dimensions.h);
						}
					}
					//Detect if the card clicked is low enough to be in the player's hand and if it is the play buildings phase
					if (theAreaClicked.y > (theTextureManager->getTexture("theBackground")->getTHeight() - theTextureManager->getTexture("Farm")->getTHeight()*0.5) - 100 && playBuildings == true)
					{
						isPlayerCard = true;
						theCardPicker.update(theAreaClicked, 10, (theTextureManager->getTexture("Farm")->getTWidth()*0.5), theTextureManager->getTexture("Farm")->getTHeight()*0.5, thePlayer[0]->getNumberofCards());
						if (theCardPicker.getCardPicked() > -1)
						{
							int cardNum = theCardPicker.getCardPicked();
							SDL_Rect dimensions = theTextureManager->getTexture(thePlayer[0]->getPlayerCard(cardNum)->getCardName())->getTextureRect();
							dragCard.setTexture(theTextureManager->getTexture(thePlayer[0]->getPlayerCard(cardNum)->getCardName()));
							dragCard.setSpriteDimensions(dimensions.w, dimensions.h);
						}
					}
				}

				//If the exit button is clicked on the end screen, reset the game
				if (theGameState == END)
				{
					if (theAreaClicked.x > 615 && theAreaClicked.y > 500 && theAreaClicked.x < 691 && theAreaClicked.y < 540)
					{
						reset = true;
					}
				}
			}
			break;
			case SDL_BUTTON_RIGHT:
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
			{
				if (theGameState == PLAYING)
				{
					theAreaClicked = { event.motion.x, event.motion.y };
					//If the card is released in the correct area and it is affordable
					if (theCardPicker.getCardPicked() > -1 && theAreaClicked.x > 1050 && theAreaClicked.y < 320 && isShopBuilding == true && resStored[3] >= theBuildingShopDeck[0]->getBuildingCard(theCardPicker.getCardPicked())->getKnowCost())
					{
						resStored[3] -= theBuildingShopDeck[0]->getBuildingCard(theCardPicker.getCardPicked())->getKnowCost();
						theDeck[0]->addCard(theBuildingShopDeck[0]->getBuildingCard(theCardPicker.getCardPicked()));
						if (theBuildingShopDeck[0]->getNumberInDeck() > 0)
						{
							theBuildingShopDeck[0]->replaceCard(theCardPicker.getCardPicked(), theBuildingShopDeck[0]->drawBuildingCard());
						}
						if (theBuildingShopDeck[0]->getNumberInDeck() <= 0)
						{
							theBuildingShopDeck[0]->eraseCard(theCardPicker.getCardPicked());
						}
						buyFromShop = false;
						drawCards = true;
					}
					//If the card is played from hand then it must have the correct resource type added to the pool and it must be affordable
					if (theCardPicker.getCardPicked() > -1 && theAreaClicked.x > 1050 && theAreaClicked.y < 320 && isPlayerCard == true && resStored[2] >= thePlayer[0]->getPlayerCard(theCardPicker.getCardPicked())->getMatCost())
					{
						cCard* theCard = thePlayer[0]->getPlayerCard(theCardPicker.getCardPicked());
						if (theCard->getOutType() == FOOD)
						{
							resPerTurn[0] += theCard->getOutput();
							cout << resPerTurn[0];
							buildingCounter -= 1;
						}
						if (theCard->getOutType() == GOLD)
						{
							resStored[2] -= 3;
							resPerTurn[1] += theCard->getOutput();
							buildingCounter -= 1;
						}
						if (theCard->getOutType() == MATERIALS)
						{
							resPerTurn[2] += theCard->getOutput();
							buildingCounter -= 1;
						}
						if (theCard->getOutType() == KNOWLEDGE)
						{
							resStored[2] -= 3;
							resPerTurn[3] += theCard->getOutput();
							buildingCounter -= 1;
						}
						thePlayer[0]->removeCard(theCardPicker.getCardPicked());
					}
					isPlayerCard = false;
					isShopBuilding = false;
					theCardPicker.setCardPicked(-1);
				}
			}
			break;
			case SDL_BUTTON_RIGHT:
			{
				if (theGameState == PLAYING)
				{

				}
			}
			break;
			default:
				break;
			}
			break;
		case SDL_MOUSEMOTION:
		{
			dragPos.x = event.motion.x;
			dragPos.y = event.motion.y;
		}
		break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				theLoop = false;
				break;
			case SDLK_DOWN:
			{
			}
			break;

			case SDLK_UP:
			{
			}
			break;
			case SDLK_RIGHT:
			{
			}
			break;

			case SDLK_LEFT:
			{
			}
			break;
			case SDLK_SPACE:
			{
			}
			break;
			case SDLK_d:
			{
				thePlayer[0]->setPlayerHand(theDeck[0]->getCard());
				thePlayer[0]->showPlayerHand();
			}
			break;
			default:
				break;
			}

		default:
			break;
		}
	}
	return theLoop;
}

double cGame::getElapsedSeconds()
{
	this->m_CurrentTime = high_resolution_clock::now();
	this->deltaTime = (this->m_CurrentTime - this->m_lastTime);
	this->m_lastTime = this->m_CurrentTime;
	return deltaTime.count();
}

void cGame::cleanUp(SDL_Window* theSDLWND)
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(theSDLWND);

	// Destroy the window
	SDL_DestroyWindow(theSDLWND);

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}