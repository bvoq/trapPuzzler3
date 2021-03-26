
//
//  displayLevel.h
//  trapStory
//
//  Created by kdkdk on 25/12/15.
//
//

#ifndef displayLevel_h
#define displayLevel_h

#include "macros.h"

extern int LINE_WIDTH;

extern void gradientFilledRect(float x, float y, float w, float h, ofColor tl, ofColor tr, ofColor bl, ofColor br);

extern void quadraticBezierVertex(float cpx, float cpy, float x, float y, float prevX, float prevY);

extern void roundedRect(float x, float y, float w, float h, float r);

extern ofMesh generateMeshTile(float w, float h, float r, ofFloatColor tlc, ofFloatColor trc, ofFloatColor blc, ofFloatColor brc, bool neighL=false, bool neighR=false, bool neighU=false, bool neighD=false);

extern bool isCenterTile(int idX, int idY, ddd & grid);


extern void drawCellFill(int i, int j,  float scale, float tScale, ddd & grid);
extern void drawCellMonsterFill(int i, int j,  float scale, float tScale, ddd & grid, keyType directionNotExtending);
extern void drawMonsterEye(int i, int j, float scale, float tScale, ddd & grid, float deathGradient);

extern int fastrandtoothgenint();
extern float fastrandtoothgennegpos();
extern float fastrandtoothgenpos();

extern void drawMonsterMouth(int i, int j, float scale, float tScale, ddd & grid, ofRectangle &  position);

extern void drawMonsterTeethLeft(int i, int j, float scale, float tScale, ddd & grid, ofRectangle & position);
extern void drawMonsterTeethRight(int i, int j, float scale, float tScale, ddd & grid, ofRectangle & position);

extern void drawCellStroke(int o, int p, float scale, float tScale, ddd & grid);

extern void recheckGrid();

extern void displayLevel(ddd & grid, ddd & moveGrid, deque<Movement> & movements);

extern void switchRenderMode(RenderMode in);

extern void displayLevelWORefresh(ddd & grid, ddd & moveGrid, deque<Movement> & movements);

extern void displayPencil(bool selected);

#endif
