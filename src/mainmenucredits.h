//
//  mainmenu.h
//  trapPuzzler3
//
//  Created by kdkdk on 17.09.17.
//
//

#ifndef mainmenu_h
#define mainmenu_h

#include "bitsstdc.h"
#include "macros.h"

#include "keyMap.h"

extern void updateCellularAutomaton(ddd & cellLevel, int & cellularAutomatonLevel, int seed);
extern ddd cellularAutomata ();

extern void initMainMenu();

extern void checkMainMenuFont(float singleMenuTileWidth);

extern void highlightedMainMenuPrintRightAligned(string toprint, float singleMenuTileWidth);
extern void unhighlightedMainMenuPrintRightAligned(string toprint, float singleMenuTileWidth);
extern void highlightedMainMenuPrintCentered(string toprint, float singleMenuTileWidth);
extern void unhighlightedMainMenuPrintCentered(string toprint, float singleMenuTileWidth);
extern void highlightedMainMenuPrintLeftAligned(string toprint, float singleMenuTileWidth);
extern void unhighlightedMainMenuPrintLeftAligned(string toprint, float singleMenuTileWidth);

extern void displayMainMenu();
extern void initCredits();
extern void displayCredits();
extern void initControlChange();
extern void displayKeyCode(string keyStr, keyType keyT, float singleMenuTileWidth, float & translationY);
extern void displayControlChange();


#endif /* mainmenu_h */
