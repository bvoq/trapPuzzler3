#pragma once

#define ddd std::deque<std::deque<int> >

// DEBUG MACROS
#define DEB(x) cout << x << endl;
#define printVec(x) for(int __i = 0; __i < x.size(); ++__i) for(int __j = 0; __j < x[__i].size(); ++__j) cout << x[__i][__j] << (__j==x[__i].size() - 1) ? "\n" : "";


#ifndef islevelgen
#include "ofMain.h"
inline long long getAdjustedTime() {
    return ofGetElapsedTimeMicros();
    /*
     long long now = ofGetElapsedTimeMicros();
     if(previousAdjustment != -1 && previousAdjustment < slowdownUntilHit && slowdownUntilHit != -1) adding += min(now,slowdownUntilHit) - previousAdjustment;
     //if((slowDown || previousSlowDown) && previousAdjustment != -1) adding += now - previousAdjustment;
     previousAdjustment = ofGetElapsedTimeMicros();
     previousSlowDown = slowDown;
     //cout << adding << endl;
     return now - adding;
     //return now;*/
}
#endif
