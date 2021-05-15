//
//  setupDrawEvent.h
//  trapPuzzler3
//
//  Created by kdkdk on 17.04.17.
//
//

#ifndef setupDrawEvent_h
#define setupDrawEvent_h

void updateEvent() {
    if(mode == PLAYING || mode == LEVEL_EDITOR_PLAYING || mode == MAINMENU) checkMovement();
}

void drawEvent() {
    //cout << "Draw: " << ofGetLastFrameTime() << endl;
    static int redrawCount = 100; //Do one draw at 10 (should make it faster) and 1
    static playMode previousMode = UNKNOWN;
    if(renderMode == FULL || redrawCount == 1 || redrawCount == 90 || redrawCount == 100) ofBackground(backgroundColor);
    switch(mode) {
        case PLAYING:
            
            backgroundColor = scheme.colorBACKGROUND;
            //ofBackground(backgroundColor);

            if(winState(moveGrid,true)) {
                winningAnimation();
            }
            
            if(isWindowResized > 1) isWindowResized--;
            if(isWindowResized == 1 && renderMode == PARTIAL) {
                isWindowResized = 0;
                cout << "Resize/Orientation flip happened" << endl;
                switchRenderMode(PARTIAL);
                ofBackground(backgroundColor);
            }
            if(redrawCount == 1 || redrawCount == 90 || redrawCount == 100) switchRenderMode(PARTIAL);

            if(renderMode == PARTIAL) {
                displayLevelWORefresh(grid, moveGrid, movements);
                displayToolBar();
            }
            else {
                
                if(lightmode == 0 && grid.size() != 0) { //enable the shade of the player
                    ofBackground(0);
                    ofFill();
                    ofEnableAlphaBlending();    // turn on alpha blending
                    //ofSetColor(255,0,0,127);    // red, 50% transparent
                    ofColor colorDark(0, 0, 0,255);
                    ofPushMatrix();
                    ofRectangle pos;
                    int w = getWidth(), h = getHeight();
                    float scaleY = (h * 1.) / (MAX(grid.size() + 2, MIN_CELL_SIZE) * 1.);
                    float scaleX = (w * 1.) / (MAX(grid[currentWatchY].size() + 2, MIN_CELL_SIZE) * 1.);
                    float scale = min(scaleY, scaleX);
                    generateLookAt(eyeGrid);
                    if(movements.size() == 0) pos = calculatePosition(currentWatchY, currentWatchX, grid.size(), grid[currentWatchY].size());
                    else pos = movements.front().calculatePosition(currentWatchY, currentWatchX);
                    
                    float orbScale = 1.7;//sqrt(2);
                    ofTranslate(pos.getX() + scale/2. - ofGetWidth()/2.*orbScale, pos.getY() + scale/2. - ofGetHeight()/2.*orbScale);
                    ofScale(orbScale,orbScale);
                    ofBackgroundGradient(backgroundColor, colorDark, OF_GRADIENT_CIRCULAR);
                    ofPopMatrix();
                }
                
                
                displayLevel(grid, moveGrid, movements);
                /*
                ofFill();
                ofEnableAlphaBlending();    // turn on alpha blending
                ofColor colorZero(255, 255, 255, 0);
                ofColor colorOne(200, 200, 200, 0);
                ofColor colorTwo(0, 0, 0,255);
                ofPushMatrix();
                orbScale = 1.7;//sqrt(2);
                ofTranslate(pos.getX() + scale/2. - ofGetWidth()/2.*orbScale, pos.getY() + scale/2. - ofGetHeight()/2.*orbScale);
                ofScale(orbScale,orbScale);
                ofBackgroundGradient(colorZero, colorTwo, OF_GRADIENT_CIRCULAR);
                ofPopMatrix();
                */
                /*
                ofPushMatrix();
                orbScale = 1.7; //sqrt(2);
                ofTranslate(pos.getX() + scale/2. - ofGetWidth()/2.*orbScale, pos.getY() + scale/2. - ofGetHeight()/2.*orbScale);
                ofScale(orbScale,orbScale);
                ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_CIRCULAR);
                ofPopMatrix();*/
                
                //cout << "draw the rect" << endl;
                //ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
                //displayLevelWORefresh(grid, moveGrid, movements);
                displayMessage();
                displayToolBar();
            }
            break;
            
        case LEVEL_EDITOR_PLAYING:
            backgroundColor = scheme.colorBACKGROUND;
            //ofBackground(backgroundColor);
            if(isWindowResized > 1) isWindowResized--;
            if(isWindowResized == 1 && renderMode == PARTIAL) {
                isWindowResized = 0;
                switchRenderMode(PARTIAL);
                ofBackground(backgroundColor);
            }
            if(redrawCount == 1 || redrawCount == 90 || redrawCount == 100) switchRenderMode(PARTIAL);
            if(renderMode == PARTIAL) displayLevelWORefresh(grid, moveGrid, movements);
            else displayLevel(grid, moveGrid, movements);
            
            displayToolBar();
            break;
            
        case LEVEL_EDITOR:
            renderMode = FULL;
            backgroundColor = scheme.colorBACKGROUND;

            displayLevelEditor();
            displayToolBar();
            break;
            
        case MENUOLD:
            renderMode = FULL;
            backgroundColor = scheme.colorBACKGROUND_VOID;
            displayMenu();
            
            
            break;
        case MENU:
            renderMode = FULL;
            backgroundColor = scheme.colorBACKGROUND_VOID;
            displayOldMenu();
            displayMessage();
            displayToolBar();
            break;
        case MAINMENU:
            backgroundColor = scheme.colorBACKGROUND;
            if(isWindowResized > 1) isWindowResized--;
            if(isWindowResized == 1 && renderMode == PARTIAL) {
                isWindowResized = 0;
                cout << "Resize/Orientation flip happened" << endl;
                ofBackground(backgroundColor);
                switchRenderMode(PARTIAL);
            }
            //if(yo > 0) displayLevel(grid, moveGrid, movements);
            if(redrawCount == 1 || redrawCount == 90 || redrawCount == 100) switchRenderMode(PARTIAL);
            if(renderMode == PARTIAL) displayLevelWORefresh(grid, moveGrid, movements);
            else displayLevel(grid, moveGrid, movements);
            displayMainMenu();

            //displayMainMenu();
            //if(renderMode == PARTIAL) displayLevelWORefresh(); else
            break;
        case CREDITS:
            renderMode = FULL;
            backgroundColor = scheme.colorBACKGROUND;
            displayCredits();
            displayToolBar();
            break;
        case CONTROL_CHANGE:
            renderMode = FULL;
            backgroundColor = scheme.colorBACKGROUND;
            displayControlChange();
            displayToolBar();
            break;
        default:
            cerr << "Unknown mode" << endl;
    }
    isMouseReleased = false; //RESET MOUSE LISTENER
    if(mode != previousMode) redrawCount = 100; //{redrawCount = 100; message.clear(); }
    else redrawCount--;
    previousMode = mode;
}

void drawEventWithScreenShake() {
    if(renderMode == FULL && isScreenShaking()) {
        ofPushMatrix();
        screenShakeRotationMatrix();
        //ofRotate(PI,ofGetWidth()/2, ofGetHeight()/2,0);
        drawEvent();
        ofPopMatrix();
    } else {
        drawEvent();
    }
}
#endif /* setupDrawEvent_h */
