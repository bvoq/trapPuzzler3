
//
//  includes.h
//  trapStory2
//
//  Created by Kivifreak on 25/12/15.
//
//

#ifndef trapPuzzler3_includes_h
#define trapPuzzler3_includes_h

#define DEB(x) cout << x << endl;
#define printVec(x) for(int __i = 0; __i < x.size(); ++__i) for(int __j = 0; __j < x[__i].size(); ++__j) cout << x[__i][__j] << (__j==x[__i].size() - 1) ? "\n" : "";
string locationOfResources = "data/";// basically finds in Resources/data
//SEE ALSO http://stackoverflow.com/questions/4882572/how-to-bundle-an-openframeworks-application-in-xcode-relative-resource-linking
//See ofApp.cpp for operating system specifics

float MIN_CELL_SIZE = 12;
int playerID;
//int currentLevel; declared in levels.h
long long timeForSlowMovement = 160000; //is relative
long long timeForFastMovement = 20000;
long long timeForSlowClickMovement = 1000;
long long timeForMovement = timeForSlowMovement;

bool levelEditorInMenu = false;
bool isMousePressed = false;
int isWindowResized = 0;
bool blockMovementDueToWinningAnimation = false;

bool beautifulGraphics = false; //This has to be false for iOS devices to run smooth
enum RenderMode {
    PARTIAL, FULL
} renderMode;

enum playMode {
    PLAYING=0, LEVEL_EDITOR_PLAYING=1, LEVEL_EDITOR=2, MENU=3, PAUSE=4, MENUOLD=5
} mode;

ofColor backgroundColor;

#include <cmath>
#include <stdio.h>

//Linked methods
void updateGrid(deque<deque<int> >);
int getWidth(); int getHeight();

#include "audio.h"
#include "keyMap.h"
#include "colorScheme.h"
#include "grid.h"
#include "eyes.h"
#include "levels.h"
#include "movement.h"
#include "displayLevel.h"
#include "puzzleSolver.h"
#include "levelEditor.h"
#include "toolbar.h"
#include "messages.h"
#include "updateGrid.h"
#include "menu.h"
#include "saves.h"
#include "keyEvent.h"
#include "mouseTouchEvent.h"
#include "winningAnimation.h"

#include "setupDrawEvent.h"


#endif
