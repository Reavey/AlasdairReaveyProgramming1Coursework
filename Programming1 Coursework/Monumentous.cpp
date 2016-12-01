//C++ headers
#include <string>
#include <iostream>

//OpenGL /glew Headers
#define GL3_PROTOTYPES 1

//SDL2 headers
#include <SDL.h>

#include "cSDL2WNDManager.h"
#include "cGame.h"

using namespace std;

string windowTitle = "Programming 1 Coursework - Alasdair Reavey S1518179";

//This is the SDL Window
static cSDL2WNDManager* programWindowManager = cSDL2WNDManager::getInstance();

//This is the game
static cGame* theGame = cGame::getInstance();

int main(int argc, char *argv[])
{
	if (!programWindowManager->initWND(windowTitle, 1280, 720))
	{
		return -1;
	}
	theGame->initialise(programWindowManager->getSDLWindow(), programWindowManager->getSDLRenderer());

	theGame->run(programWindowManager->getSDLWindow(), programWindowManager->getSDLRenderer());

	theGame->cleanUp(programWindowManager->getSDLWindow());

	return 0;
}