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

            if(renderMode == PARTIAL) displayLevelWORefresh(grid, moveGrid, movements);
            else displayLevel(grid, moveGrid, movements);
            displayMessage();
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
