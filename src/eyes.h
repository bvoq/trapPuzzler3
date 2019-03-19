//
//  eyes.h
//  trapPuzzler3
//
//  Created by kdkdk on 04/02/16.
//
//

#ifndef trapPuzzler3_eyes_h
#define trapPuzzler3_eyes_h

#include "bitsstdc.h"

extern std::deque<std::deque<int> > eyeGrid, moveEyeGrid;
extern int currentWatchY, currentWatchX;

#ifndef islevelgen
extern void generateLookAt(std::deque<std::deque<int> > & eGrid);

extern void generateEyeGrid();
extern void drawEnemyEye(bool direction, int i , int j, float scale, int gridY, int gridX, bool surpriseOrAnger, float incr);

extern void drawLoveEye(float scale);
extern void drawPlayerEye(float scale, float incr);
extern void drawEyes(int i, int j, float scale, float tScale, std::deque<std::deque<int> > & eGrid, std::deque<std::deque<int> > & grid, float incr);
#endif

#endif
