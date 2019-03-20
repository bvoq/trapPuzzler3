//
//  keyEvent.h
//  trapPuzzler3
//
//  Created by kdkdk on 17.04.17.
//
//

//This is for key events on the keyboard, but also for iOS controls!

#ifndef keyEvent_h
#define keyEvent_h

#include "macros.h"

extern void restart();

extern void tryPlayLevel(int currentLevel, bool levelEditorInMenu);

extern string keycodeToStr(int keycode);

extern void initMainMenu();
extern void keyEvent (keyType kt);

#endif /* keyEvent_h */
