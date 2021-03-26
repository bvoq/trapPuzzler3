//
//  eyes.h
//  trapPuzzler3
//
//  Created by kdkdk on 04/02/16.
//
//

#ifndef eyes_h
#define eyes_h

#include "macros.h"

extern deque<deque<int> > eyeGrid, moveEyeGrid;
extern int currentWatchY, currentWatchX;

#ifndef compiledWithoutOpenframeworks
extern void generateLookAt(deque<deque<int> > & eGrid);

extern void generateEyeGrid();
extern void drawEnemyEye(bool direction, int i , int j, float scale, int gridY, int gridX, bool surpriseOrAnger, float incr);

extern void drawLoveEye(float scale);
extern void drawPlayerEye(float scale, float incr);
extern void drawEyes(int i, int j, float scale, float tScale, deque<deque<int> > & eGrid, deque<deque<int> > & grid, float incr);
#endif

#endif
