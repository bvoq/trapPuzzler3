//
//  screenShake.h
//  trapPuzzler3
//
//  Created by kdkdk on 15.09.17.
//
//

#ifndef screenShake_h
#define screenShake_h

#include "macros.h"

extern bool isScreenShaking();
extern void screenShake(long long duration, keyType keytype, float intensity);
extern void screenShakeRotationMatrix();

#endif /* screenShake_h */
