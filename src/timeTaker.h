//
//  timeTaker.h
//  trapPuzzler3
//
//  Created by kdkdk on 14.09.17.
//
//

#ifndef timeTaker_h
#define timeTaker_h


/*
long long slowdownUntilHit = -1;
void makeSlowdown(long long time) {
    slowdownUntilHit = ofGetElapsedTimeMicros() + time*10;
}

long long previousAdjustment = -1;
long long adding = 0;
bool slowDown = false, previousSlowDown = false;
 */
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

#endif /* timeTaker_h */
