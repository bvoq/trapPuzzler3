//
//  parallelLevelCreation.h
//  trapPuzzler3
//
//  Created by kdkdk on 11.09.17.
//
//

#ifndef parallelLevelCreation_h
#define parallelLevelCreation_h

#include "macros.h"

extern long long threadCount;

extern ddd improveLevel(ddd oldLevel, bool hasGravity, int tries, int maxBreadth);
extern void runThread(int threadID, int size, bool symmetric, bool gravitymonsterlevel, int maxComputationFields);

#endif /* parallelLevelCreation_h */
