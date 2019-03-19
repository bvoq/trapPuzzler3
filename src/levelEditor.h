//
//  levelEditor.h
//  trapStory2
//
//  Created by kdkdk on 31/12/15.
//
//

#ifndef trapPuzzler3_levelEditor_h
#define trapPuzzler3_levelEditor_h

#include "bitsstdc.h"
#include "macros.h"

#include "grid.h"
#include "keyMap.h"

extern ddd editorGrid;
//int editorGridY, editorGridX;

extern int playerCount, enemyCount, unmovableEnemyCount, loveCount;
extern cellType placeType;

extern void changeBrush (cellType newPlaceType);

extern std::set<std::pair<int, int> > tilesToBePlaced;
extern std::vector<ddd > levelEditorSaves;

extern void initLevelEditor(int loadFromLevel, bool empty);

extern void switchAwayFromIDE();

extern void improveLevelEditor();

extern void placeSelectedTiles();

extern void undoLevelEditorMove();

extern void levelFormattedExportWithoutCropping(std::ostream & o, ddd copied);

extern void displayLevelEditor();

extern void addLayer(keyType direction);

#endif
