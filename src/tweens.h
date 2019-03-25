//
//  tweens.hpp
//  trapPuzzler3
//
//  Created by kdkdk on 23.03.19.
//

#ifndef tweens_h
#define tweens_h

#include "macros.h"


//from b to c, starting at time t taking d time.
extern float easeInElastic(float t, float b, float c, float d);
extern float easeOutElastic(float t, float b, float c, float d);
extern float easeOutBounce(float t, float b, float c, float d);
extern float easeInBounce (float t, float b, float c, float d);
extern float easeInQuad (float t, float b, float c, float d);
extern float easeOutQuad(float t, float b, float c, float d);
extern float easeInOutQuad(float t, float b, float c, float d);
extern float easeInOutTripple(float t, float b, float c, float d);
extern float easeInOutQuint(float t, float b, float c, float d);
extern float easeInOutElastic(float t, float b, float c, float d);
extern float easeInSine (float t, float b, float c, float d);
extern float easeOutSine (float t, float b, float c, float d);
extern float easeInOutSine(float t, float b, float c, float d);


#endif /* tweens_h */
