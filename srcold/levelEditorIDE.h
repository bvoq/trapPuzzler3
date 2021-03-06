//
//  levelEditorIDE.h
//  trapPuzzler3
//
//  Created by kdkdk on 09.03.19.
//

#ifndef levelEditorIDE_h
#define levelEditorIDE_h

#include "macros.h"

extern bool activeIDE;
extern float ideFactor; //how much of the screen should be IDE

extern vector<string> ideString;

extern void initLevelEditorIDE();
extern void switchToIDE();

extern void displayLevelEditorIDE();

extern void ideKeyPressed(int key, bool isSuperKey);

#endif /* levelEditorIDE_h */
