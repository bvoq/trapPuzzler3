//
//  puzzleSolver.h
//  trapStory2
//
//  Created by kdkdk on 01/01/16.
//
//

#ifndef puzzleSolver_h
#define puzzleSolver_h

#include "macros.h"

//Set hasGravity = true, if uncertain.
//returns -1 = UNSOLVABLE, non-negative = Number of steps used to compute the solution , -2 = UNKNOWN (not fully computed), -3 = ERROR, such as no player
extern bool winState(ddd &,bool);
extern int newSolver(ddd gridtosolve, bool hasGravity, vector<keyType> & solution, int maxComputationFields);

#ifndef compiledWithoutOpenframeworks
extern void keyEvent(keyType);
extern void solveInGame();
#endif

extern deque<deque<int> > improveLevel(deque<deque<int> > oldLevel, bool hasGravity, int tries, int maxBreadth);


#endif



























