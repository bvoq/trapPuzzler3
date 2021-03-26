//
//  globals.h
//  trapPuzzler3
//
//  Created by kdkdk on 11.09.17.
//
//

#ifndef globals_h
#define globals_h

#include "macros.h"

extern const string locationOfResources;// basically finds in Resources/data

extern float MIN_CELL_SIZE;
extern int playerID;
//int currentLevel; declared in levels.h
extern const long long timeForSlowEyeMovement;
extern const long long timeForSlowMovement;  //8000;//160000; //is relative, also used for duration of sounds and shaking.
extern const long long timeForTypedMovement;
extern const long long timeForFastMovement; //winning
extern const long long timeForDragMovement;
extern const long long timeForFlickering; //time it takes to cycle a flicker (done with modulo).
extern const double gravityAcceleration, gravityQuadraticFriction, gravityStokesFriction;
extern const long long timeForKeypressWait;
extern const long long timeForAnotherKeypressWait;
extern const long long timeForSlowClickMovement;
extern const long long maxUndoTime;

extern long long timeForMovement;

extern chrono::time_point<chrono::high_resolution_clock> timeMeasuredForHCI;
extern bool firstMovementHCI;

extern bool levelEditorInMenu;

extern bool isMousePressed;
extern bool isMouseReleased;
extern int mousePressedX;
extern int mousePressedY;
extern int mouseReleasedX;
extern int mouseReleasedY;
extern int scrollX;
extern int scrollY;
extern int mousetouchX, mousetouchY;
extern int isWindowResized;

extern float wallShakeIntensity;

extern bool blockMovementDueToWinningAnimation;
extern bool forceUndo;

extern bool beautifulGraphics;

extern RenderMode renderMode;

enum playMode {
    PLAYING=0, LEVEL_EDITOR_PLAYING=1, LEVEL_EDITOR=2, MENU=3, PAUSE=4, MENUOLD=5, MAINMENU=6, ADVENTURE=7, CREDITS=8, CONTROL_CHANGE=9, UNKNOWN=100
};
extern playMode mode;
extern string strmode(playMode m);

#ifndef compiledWithoutOpenframeworks
extern ofColor backgroundColor;
extern void switchRenderMode(RenderMode ini);
#endif

//!TODO: Delete after refactoring
//Linked methods
extern void updateGrid(deque<deque<int> >);
extern int getWidth();
extern int getHeight();

#endif /* globals_h */
