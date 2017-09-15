//
//  screenShake.h
//  trapPuzzler3
//
//  Created by kdkdk on 15.09.17.
//
//

#ifndef screenShake_h
#define screenShake_h

bool screenShake = true;
keyType shakeDirection = LEFT;
float angle = 0.1;

long long screenShakeStartTime, screenShakeDuration;
//CACTUS IGS 2009
void screenShakeRotationMatrix() {
    long long time = getAdjustedTime();
    if(time < screenShakeStartTime + screenShakeDuration) {
        float incr = 0.;
        if(time < screenShakeStartTime + screenShakeDuration/2) incr = easeInElastic(screenShakeStartTime + screenShakeDuration/2., 0., 1.,screenShakeDuration);
        else incr = 1.-easeOutElastic(screenShakeStartTime - screenShakeDuration/2.,0.,1.,screenShakeDuration);
        
        if(grid.size() != 0 && grid[0].size() >= 2) {
            ofRectangle rect = calculatePosition(0, 0, grid.size(), grid[0].size());
            
            if(shakeDirection == LEFT) ofTranslate(-rect.getWidth() * incr,0);
            else if(shakeDirection == RIGHT) ofTranslate(rect.getWidth() * incr,0);
            else if(shakeDirection == UP) ofTranslate(0,-rect.getWidth() * incr);
            else if(shakeDirection == DOWN) ofTranslate(0,rect.getHeight() * incr);
        }
        ofRotate(angle,ofGetWidth()/2, ofGetHeight()/2,0);
    
    }
}




#endif /* screenShake_h */
