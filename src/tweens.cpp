//
//  tweens.cpp
//  trapPuzzler3
//
//  Created by kdkdk on 23.03.19.
//

#include "tweens.h"


//from b to c, starting at time t taking d time.

float easeInElastic(float t,float b , float c, float d) {
    if (t==0) return b;  if ((t/=d)==1) return b+c;
    float p=d*.3f;
    float a=c;
    float s=p/4;
    float postFix =a*pow(2,10*(t-=1)); // this is a fix, again, with post-increment operators
    return -(postFix * sin((t*d-s)*(2*M_PI)/p )) + b;
}

float easeOutElastic(float t,float b , float c, float d) {
    if (t==0) return b;  if ((t/=d)==1) return b+c;
    float p=d*.3f;
    float a=c;
    float s=p/4;
    return (a*pow(2,-10*t) * sin( (t*d-s)*(2*M_PI)/p ) + c + b);
}

float easeOutBounce(float t,float b , float c, float d) {
    if ((t/=d) < (1/2.75f)) {
        return c*(7.5625f*t*t) + b;
    } else if (t < (2/2.75f)) {
        float postFix = t-=(1.5f/2.75f);
        return c*(7.5625f*(postFix)*t + .75f) + b;
    } else if (t < (2.5/2.75)) {
        float postFix = t-=(2.25f/2.75f);
        return c*(7.5625f*(postFix)*t + .9375f) + b;
    } else {
        float postFix = t-=(2.625f/2.75f);
        return c*(7.5625f*(postFix)*t + .984375f) + b;
    }
}

float easeInBounce (float t,float b , float c, float d) {
    return c - easeOutBounce (d-t, 0, c, d) + b;
}

float easeInQuad (float t,float b , float c, float d) {
    return c*(t/=d)*t + b;
}
float easeOutQuad(float t,float b , float c, float d) {
    return -c *(t/=d)*(t-2) + b;
}

float easeInOutQuad(float t,float b , float c, float d) {
    t /= d/2;
    if (t < 1) return c/2*t*t + b;
    t--;
    return -c/2 * (t*(t-2) - 1) + b;
}

float easeInOutTripple(float t, float b, float c, float d) {
    if ((t/=d/2) < 1) return c/2*t*t*t + b;
    return c/2*((t-=2)*t*t + 2) + b;
}

float easeInOutQuint(float t,float b , float c, float d) {
    if ((t/=d/2) < 1) return c/2*t*t*t*t*t + b;
    return c/2*((t-=2)*t*t*t*t + 2) + b;
}

float easeInOutElastic(float t,float b , float c, float d) {
    if (t==0) return b;  if ((t/=d/2)==2) return b+c;
    float p=d*(.3f*1.5f);
    float a=c;
    float s=p/4;
    
    if (t < 1) {
        float postFix =a*pow(2,10*(t-=1)); // postIncrement is evil
        return -.5f*(postFix* sin( (t*d-s)*(2*M_PI)/p )) + b;
    }
    float postFix =  a*pow(2,-10*(t-=1)); // postIncrement is evil
    return postFix * sin( (t*d-s)*(2*M_PI)/p )*.5f + c + b;
}

float easeInSine (float t,float b , float c, float d) {
    return -c * cos(t/d * (M_PI/2)) + c + b;
}
float easeOutSine (float t,float b , float c, float d) {
    return c * sin(t/d * (M_PI/2)) + b;
}

float easeInOutSine(float t,float b , float c, float d) {
    return -c/2 * (cos(M_PI*t/d) - 1) + b;
}
