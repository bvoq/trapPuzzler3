//
//  levelEditor.h
//  trapStory2
//
//  Created by kdkdk on 31/12/15.
//
//

#ifndef levelEditor_h
#define levelEditor_h

#include "macros.h"

extern ddd editorGrid;
//int editorGridY, editorGridX;

extern int playerCount, enemyCount, unmovableEnemyCount, loveCount;
extern cellType placeType;

extern void changeBrush (cellType newPlaceType);

extern set<pair<int, int> > tilesToBePlaced;
extern vector<ddd > levelEditorSaves;

extern void initLevelEditor(int loadFromLevel, bool empty);

extern void switchAwayFromIDE();

extern void improveLevelEditor();

extern void placeSelectedTiles();

extern void undoLevelEditorMove();

extern void levelFormattedExportWithoutCropping(ostream & o, ddd copied);

extern void displayLevelEditor();

extern void addLayer(keyType direction);

#endif
