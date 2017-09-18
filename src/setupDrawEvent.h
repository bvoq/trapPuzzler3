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
    if(mode == PLAYING || mode == LEVEL_EDITOR_PLAYING) checkMovement();
}

void drawEvent() {
    //cout << "Draw: " << ofGetLastFrameTime() << endl;
    if(renderMode == FULL) ofBackground(backgroundColor);

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
            if(renderMode == PARTIAL) displayLevelWORefresh();
            else displayLevel();
            displayToolBar();
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
            if(renderMode == PARTIAL) displayLevelWORefresh();
            else displayLevel();
            
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

        case MAINMENU:
            backgroundColor = scheme.colorBACKGROUND_VOID;
            displayMainMenu();
            break;
        default:
            cerr << "Unkown mode" << endl;
    }
    displayMessage();

    isMouseReleased = false; //RESET MOUSE LISTENER
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
