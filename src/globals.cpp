#include "globals.h"

#include <cassert>
#include <cmath>
#include <stdio.h>

const string locationOfResources = "data/";// basically finds in Resources/data
    //SEE ALSO http://stackoverflow.com/questions/4882572/how-to-bundle-an-openframeworks-application-in-xcode-relative-resource-linking
    //See ofApp.cpp for operating system specifics

float MIN_CELL_SIZE = 12; //The level gets scaled to fit the window. However 12x12 blocks should always be shown, even if the level is say only 6x6
int playerID = -1; //Currently active player character.

//hardcoded movement speeds in microseconds
const long long timeForSlowEyeMovement = 800000;
const long long timeForSlowMovement = 80000;  //8000;//160000; //is relative, also used for duration of sounds and shaking.
const long long timeForTypedMovement = 160000;
const long long timeForFastMovement = 20000; //winning
const long long timeForDragMovement = 80000;
const long long timeForFlickering = 640000; //time it takes to cycle a flicker (done with modulo).
const double gravityAcceleration = 1.2*1./160000/*160000*/, gravityQuadraticFriction = 0.1, gravityStokesFriction = 0.1;
const long long timeForKeypressWait = 1.5*timeForTypedMovement;
const long long timeForAnotherKeypressWait = 64000;
const long long timeForSlowClickMovement = 1000;
const long long maxUndoTime = timeForTypedMovement * 8;
long long timeForMovement = timeForSlowMovement;

std::chrono::time_point<std::chrono::high_resolution_clock> timeMeasuredForHCI;
bool firstMovementHCI = false;

bool levelEditorInMenu = false;
bool isMousePressed = false;
bool isMouseReleased = false;
int mousePressedX = -1;
int mousePressedY = -1;
int mouseReleasedX = -1;
int mouseReleasedY = -1;
int scrollX = 0;
int scrollY = 0;
int mousetouchX = -100, mousetouchY = -100;
int isWindowResized = 0;

float wallShakeIntensity = .25+.125;

bool blockMovementDueToWinningAnimation = false;
bool forceUndo = false;

bool beautifulGraphics = true; //This has to be false for iOS devices to run smooth

RenderMode renderMode = PARTIAL;
playMode mode = UNKNOWN;

string strmode(playMode m) {
    return m == PLAYING ? "PLAYING" : m == LEVEL_EDITOR_PLAYING ? "LEVEL_EDITOR_PLAYING" : m == LEVEL_EDITOR ? "LEVEL_EDITOR" : m == MENU ? "MENU" : m == MENUOLD ? "MENU_OLD" : m == MAINMENU ? "MAIN_MENU" : m == ADVENTURE ? "ADVENTURE" : "UNKNOWN";
}


#ifndef islevelgen
ofColor backgroundColor;
void switchRenderMode(RenderMode ini);
#endif
