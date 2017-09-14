//
//  timeTaker.h
//  trapPuzzler3
//
//  Created by kdkdk on 14.09.17.
//
//

#ifndef timeTaker_h
#define timeTaker_h


long long slowdownUntilHit = -1;
long long adding = 0;
long long previousAdjustment = -1;
void makeSlowdown(long long time) {
    slowdownUntilHit = ofGetElapsedTimeMicros() + time;
}

long long getAdjustedTime() {
    long long now = ofGetElapsedTimeMicros();
    if(previousAdjustment != -1 && previousAdjustment < slowdownUntilHit && slowdownUntilHit != -1) adding += min(now,slowdownUntilHit) - previousAdjustment;
    previousAdjustment = ofGetElapsedTimeMicros();
    return now - adding;
}

#endif /* timeTaker_h */
