//
//  globals.h
//  trapPuzzler3
//
//  Created by kdkdk on 11.09.17.
//
//

#ifndef globals_h
#define globals_h

#define DEB(x) cout << x << endl;
#define printVec(x) for(int __i = 0; __i < x.size(); ++__i) for(int __j = 0; __j < x[__i].size(); ++__j) cout << x[__i][__j] << (__j==x[__i].size() - 1) ? "\n" : "";
string locationOfResources = "data/";// basically finds in Resources/data
//SEE ALSO http://stackoverflow.com/questions/4882572/how-to-bundle-an-openframeworks-application-in-xcode-relative-resource-linking
//See ofApp.cpp for operating system specifics

float MIN_CELL_SIZE = 12;
int playerID;
//int currentLevel; declared in levels.h
long long timeForSlowEyeMovement = 800000;
long long timeForSlowMovement = 160000;//160000; //is relative, also used for duration of sounds and shaking.
long long timeForFastMovement = 20000; //winning
long long timeForFlickering = 640000; //time it takes to cycle a flicker (done with modulo).
double gravityAcceleration = 1.2*1./160000/*160000*/, gravityQuadraticFriction = 0.1, gravityStokesFriction = 0.1;
long long timeForKeypressWait = 2 * timeForSlowMovement;
long long timeForSlowClickMovement = 1000;
long long timeForMovement = timeForSlowMovement;

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

float wallShakeIntensity = .25+.125;

int isWindowResized = 0;
bool blockMovementDueToWinningAnimation = false;
bool forceUndo = false;

bool beautifulGraphics = false; //This has to be false for iOS devices to run smooth
enum RenderMode {
    PARTIAL, FULL
} renderMode;

enum playMode {
    PLAYING=0, LEVEL_EDITOR_PLAYING=1, LEVEL_EDITOR=2, MENU=3, PAUSE=4, MENUOLD=5, MAINMENU=6, CREDITS=7, CONTROL_CHANGE=8, UNKNOWN=100
} mode;
string strmode(playMode m) {
    return m == PLAYING ? "PLAYING" : m == LEVEL_EDITOR_PLAYING ? "LEVEL_EDITOR_PLAYING" : m == LEVEL_EDITOR ? "LEVEL_EDITOR" : m == MENU ? "MENU" : m == MENUOLD ? "MENU_OLD" : m == MAINMENU ? "MAIN_MENU" : "UNKNOWN";
}

#ifndef islevelgen
ofColor backgroundColor;
#endif

#include <cassert>
#include <cmath>
#include <stdio.h>

//Linked methods

void updateGrid(deque<deque<int> >);
int getWidth(); int getHeight();

#ifndef islevelgen
void switchRenderMode(RenderMode ini);
#endif

#endif /* globals_h */
