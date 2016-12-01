#ifndef _GAMECONSTANTS_H
#define _GAMECONSTANTS_H

//Windows and OpenGL and SDL
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <SDL.h>

//Image texture loading library
#include <SDL_image.h>
//Font loading library
#include <SDL_ttf.h>
//Audio loading library
#include <SDL_mixer.h>
//Maths functions
#include <math.h>
#define PI 3.14159265
#include "..\glm\glm\glm.hpp"
#include "..\glm\glm\gtc\matrix_transform.hpp"
#include "..\glm\glm\geometric.hpp"
#include "..\glm\glm\gtc\quaternion.hpp"
#include "..\glm\glm\gtc\type_ptr.hpp"
#include "..\glm\glm\gtx\quaternion.hpp"

//SDL container and algorithms
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
using namespace std::chrono;

using namespace std;

//Define the string to appear in the top left of the window
#define WINDOW_TITLE "Programming 1 Coursework - Alasdair Reavey S1518179"
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

//Properties of a building card
enum eBuildingTitle {FARM,MARKET,MINE,SCHOOL};
enum eLevel {FIRST,SECOND,THIRD};
enum eMatCost {MZERO,MTHREE};
enum eKnowCost {KZERO};
enum eResType {FOOD, GOLD, KNOWLEDGE, MATERIALS};
enum eResQuan {RONE, RTWO};

enum textType { SOLID, BLENDED, SHADED };
enum soundType { SFX, MUSIC };
enum gameState { MENU, INSTRUCTIONS,  PLAYING, END, QUIT };
enum btnTypes { EXIT, INSTRUCT, LOAD, PLAY, SAVE, SETTINGS };

const string strTitle[4] = { "Farm", "Market", "Mine", "School" };
const int intLevel[3] = { 0, 1, 2};
const string outType[4] = { "Food", "Gold", "Knowledge", "Materials" };
const int outValue[1] = { 1 };
const int intMatCost[2] = { 0, 3};
const int intKnowCost[1] = { 0 };

struct BUILDINGCARD {
	eBuildingTitle cTitle; //The card's name
	short cLevel; //The card's level
	short cMatCost; //The cost to buy a building from the shop
	short cKnowCost; //The cost to play a card from hand
	short cResQuan; //The quantity of a resource produced
	eResType cResType; //The type of resource produced
	string cFilename;
	string cCardname;
};

typedef struct
{
	float  X;
	float  Y;
}FPoint;
#endif