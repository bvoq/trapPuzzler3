//
//  screenShake.h
//  trapPuzzler3
//
//  Created by kdkdk on 15.09.17.
//
//

#ifndef screenShake_h
#define screenShake_h

keyType shakeDirection = LEFT;
long long screenShakeStartTime=-1, screenShakeDuration=-1;
float screenShakeIntensity = 0;
//CACTUS IGS 2009
bool isScreenShaking() {
    return (getAdjustedTime() < screenShakeStartTime + screenShakeDuration);
}

//intensity 1.0 is equal to the screen shake.
void screenShake(long long duration, keyType keytype, float intensity) {
    screenShakeStartTime = getAdjustedTime();
    screenShakeDuration = duration;
    shakeDirection = keytype;
    screenShakeIntensity = intensity;
}
void screenShakeRotationMatrix() {
    long long time = getAdjustedTime();
    if(isScreenShaking()) {
        float incr = 0.;
        if(time < screenShakeStartTime + screenShakeDuration/2) incr = easeInElastic(time-screenShakeStartTime+screenShakeDuration/2, 0., 1.,screenShakeDuration);
        else incr = 1.-easeOutElastic(time-screenShakeStartTime-screenShakeDuration/2,0.,1.,screenShakeDuration);
        
        if(grid.size() != 0 && grid[0].size() >= 2) {
            ofRectangle rect = calculatePosition(0, 0, grid.size(), grid[0].size());
            
            if(shakeDirection == LEFT) ofTranslate(rect.getWidth()*incr*.5*screenShakeIntensity,0);
            else if(shakeDirection == RIGHT) ofTranslate(-rect.getWidth()*incr*.5*screenShakeIntensity,0);
            else if(shakeDirection == UP) ofTranslate(0,rect.getWidth()*incr*.5*screenShakeIntensity);
            else if(shakeDirection == DOWN) ofTranslate(0,-rect.getHeight()*incr*.5*screenShakeIntensity);
        }
        ofRotate((incr-0.5) * PI/1.5,ofGetWidth()/2, ofGetHeight()/2,0);
    }
}




#endif /* screenShake_h */
