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
	textureName = { "", "", "", "", "theBackground" };
	for (int title = FARM; title <= SCHOOL; title++)
	{
		if (title == FARM)
		{
			cGame::titleDeck.push_back(new cCard(static_cast<eBuildingTitle>(title), 0, 0, 0, 0, static_cast<eResType>(FOOD)));
		}
		if (title == MINE)
		{
			cGame::titleDeck.push_back(new cCard(static_cast<eBuildingTitle>(title), 0, 0, 0, 0, static_cast<eResType>(MATERIALS)));
		}
		if (title == MARKET)
		{
			cGame::titleDeck.push_back(new cCard(static_cast<eBuildingTitle>(title), 0, 1, 0, 0, static_cast<eResType>(GOLD)));
		}
		if (title == SCHOOL)
		{
			cGame::titleDeck.push_back(new cCard(static_cast<eBuildingTitle>(title), 0, 1, 0, 0, static_cast<eResType>(KNOWLEDGE)));
		}
	}
	for (int i = 0; i < 4; i++)
	{
		textureName[i] = titleDeck[i]->getCardName();
	}
	texturesToUse = { "Images/Farm.png", "Images/Market.png", "Images/Mine.png", "Images/School.png",
	"Images/Background.png" };

	for (int tCount = 0; tCount < textureName.size(); tCount++)
	{
		theTextureManager->addTexture(textureName[tCount], texturesToUse[tCount]);
	}
	tempTextTexture = theTextureManager->getTexture(textureName[0]);
	aRect = { 0, 0, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
	aColour = { 228, 213, 238, 255 };
	// Store the textures for the buttons
	btnNameList = { "exit_btn", "instructions_btn", "load_btn", "menu_btn", "play_btn", "save_btn", "settings_btn" };
	btnTexturesToUse = { "Images/Buttons/button_exit.png", "Images/Buttons/button_instructions.png", "Images/Buttons/button_load.png", "Images/Buttons/button_menu.png", "Images/Buttons/button_play.png", "Images/Buttons/button_save.png", "Images/Buttons/button_settings.png" };
	btnPos = { { 400, 375 },{ 400, 300 },{ 400, 300 },{ 500, 500 },{ 400, 300 },{ 740, 500 },{ 400, 300 } };
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
	theGameState = PLAYING;
	theBtnType = EXIT;
	// Create textures for Game Dialogue (text)
	fontList = { "font1", "font2" };
	fontsToUse = { "Fonts/Cantate Beveled.ttf", "Fonts/Mawns_Handwriting.ttf" };
	for (int fonts = 0; fonts < fontList.size(); fonts++)
	{
		theFontManager->addFont(fontList[fonts], fontsToUse[fonts], 48);
	}
	// Create text Textures
	gameTextNames = { "TitleTxt", "ThanksTxt", "SeeYouTxt" };
	gameTextList = { "Monumentous", "Thanks for playing!", "See you again soon!" };
	for (int text = 0; text < gameTextNames.size(); text++)
	{
		theTextureManager->addTexture(gameTextNames[text], theFontManager->getFont("font1")->createTextTexture(theRenderer, gameTextList[text], SOLID, { 228, 213, 238, 255 }, { 0, 0, 0, 0 }));
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

	theCardPicker.setBuildingListStartXY({5,5});

	//Draw the player their starting hand of 5 cards from the deck
	for (int i = 0; i < 5; i++)
	{
		theCard = theDeck.getCard();
		thePlayer.setPlayerHand(theCard);
		//theTextureManager->addTexture(theCard->getCardName(), theCard->getImage());

	}
	//Draw the top 5 cards of the building deck for the starting shop
	for (int i = 0; i < 5; i++)
	{
		theCard = theBuildingShopDeck.drawBuildingCard();
		theBuildingShopDeck.setBuildingShopHand(theCard);
		//theTextureManager->addTexture(theCard->getCardName(), theCard->getImage());
	}
	thePlayer.showPlayerHand();
}

void cGame::run(SDL_Window* theSDLWindow, SDL_Renderer* theRenderer)
{
	bool loop = true;
	this->render(theSDLWindow, theRenderer);

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
		// Render Button
		theButtonMgr->getBtn("play_btn")->render(theRenderer, &theButtonMgr->getBtn("play_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("play_btn")->getSpritePos(), theButtonMgr->getBtn("play_btn")->getSpriteScale());
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 400, 375 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
	}
	break;
	case PLAYING:
	{
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		//Set the details for and render the title
		tempTextTexture = theTextureManager->getTexture("TitleTxt");
		pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		//Render the cards in the shop
		for (int i = 0; i < 5; i++)
		{
			LPCSTR cardName = theBuildingShopDeck.getBuildingCard(i)->getCardName();
			LPCSTR currentCardName = theBuildingShopDeck.getBuildingCard(i)->getCardName();
			cout << cardName;
			int xPos = 10 + i * 10; // (theTextureManager->getTexture(cardName)->getTWidth());
			int yPos = 10;
			tempTextTexture = theTextureManager->getTexture(currentCardName);
			pos = { xPos, yPos, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
			scale = { 0.25,0.25 };
			tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		}
		//Place and render the exit button
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 740, 575 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
		//If a card has been picked render the corresponding card from the shop's hand and drag it around
		if (theCardPicker.getCardPicked() > -1)
		{
			int cardNum = theCardPicker.getCardPicked();
			int xPos = dragPos.x - 50;
			int yPos = dragPos.y - 50;
			LPCSTR currentCardName = theBuildingShopDeck.getBuildingCard(cardNum)->getCardName();
			tempTextTexture = theTextureManager->getTexture(currentCardName);
			pos = { xPos, yPos, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
			scale = { 0.25,0.25 };
			tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		}
	}
	break;
	case END:
	{

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
	}
	theGameState = theButtonMgr->getBtn("play_btn")->update(theGameState, PLAYING, theAreaClicked);
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
					theCardPicker.update(theAreaClicked, 10, theTextureManager->getTexture("farm")->getTWidth());
					if (theCardPicker.getCardPicked() > -1)
					{
						int cardNum = theCardPicker.getCardPicked();
						
						SDL_Rect dimensions = theTextureManager->getTexture(theBuildingShopDeck.getBuildingCard(cardNum)->getCardName())->getTextureRect();
						std::cout << dimensions.w;
						dragCard.setTexture(theTextureManager->getTexture(theBuildingShopDeck.getBuildingCard(cardNum)->getCardName()));
						dragCard.setSpriteDimensions(dimensions.w, dimensions.h);
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
					if (theCardPicker.getCardPicked() > -1)
					{
						theDeck.addCard(theBuildingShopDeck.getBuildingCard(theCardPicker.getCardPicked()));
						theBuildingShopDeck.replaceCard(theCardPicker.getCardPicked(), theBuildingShopDeck.drawBuildingCard());
						cout << theBuildingShopDeck.getNumberOfCards();
					}
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
				thePlayer.setPlayerHand(theDeck.getCard());
				thePlayer.showPlayerHand();
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