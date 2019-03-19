//
//  winningAnimation.h
//  trapPuzzler3
//
//  Created by kdkdk on 22.04.17.
//
//

#ifndef winningAnimation_h
#define winningAnimation_h

#include "macros.h"

#ifndef islevelgen
extern void blockMovementForWinning();
#endif

extern bool winState(ddd & moveGrid, bool winningAnimationAction);

#ifndef islevelgen
extern void winningAnimation();
#endif

#endif /* winningAnimation_h */
