//
//  menu.h
//  trapPuzzler3
//
//  Created by kdkdk on 14/01/16.
//
//

#ifndef trapPuzzler3_menu_h
#define trapPuzzler3_menu_h

#include "bitsstdc.h"
#include "macros.h"

extern void initMenu();

//returns the width/height of a single block.
extern float displayLevelInMenu(ddd & theLevel, bool displayPlayer, int width, bool displayEyes);
extern void displayOldMenu();
extern void displayCharacterOnMap();
extern void displayMenu();

#endif
