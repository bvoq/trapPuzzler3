//
//  toolbar.h
//  trapPuzzler3
//
//  Created by kdkdk on 22.04.17.
//
//

#ifndef toolbar_h
#define toolbar_h

//Basically the toolbar for level_editor_playing and playing.


//ofGetWidth() vs. ofGetWindowWidth() difference: https://forum.openframeworks.cc/t/difference-between-ofgetscreenwidth-ofgetwidth-and-ofgetwindowwidth/12172

int toolbarX = 0, toolbarY = 0;
enum ToolbarOrientation {
    NOTOOLBAR=0, BOTTOMTOOLBAR=1, RIGHTTOOLBAR=2 //, BOTTOMTOOLBAR=3, LEFTTOOLBAR=4
} toolbarOrientation = NOTOOLBAR;

bool messageBlockingToolbar = false; //maybe make this messa

int toolbarSize = 100; //TODO! Make this dynamic and initialize its height
int messageSize = 0;
int getWidth() {
    if((mode == LEVEL_EDITOR_PLAYING || mode == PLAYING) && toolbarOrientation == RIGHTTOOLBAR) return ofGetWidth() - toolbarSize;
    else return ofGetWidth();
}
int getHeight() {
    if(messageBlockingToolbar) return ofGetHeight() - messageSize;
    if((mode == LEVEL_EDITOR_PLAYING || mode == PLAYING) && toolbarOrientation == BOTTOMTOOLBAR) return ofGetHeight() - toolbarSize;
    return ofGetHeight();
}

pair<int,int> dpDrawCoordinates = {-1,-1};
ofMesh backgroundKey;

void displayToolBar() {
    if(!messageBlockingToolbar) {
        if(toolbarOrientation != NOTOOLBAR) {
            if(dpDrawCoordinates.first != ofGetHeight() && dpDrawCoordinates.second != ofGetHeight()) {
                toolbarSize = 0.1 * ofGetHeight();
                //Redraw all the keys
                backgroundKey = generateMeshTile(toolbarSize * .9, toolbarSize * .9, toolbarSize * .05, scheme.colorTOOLBARBUTTON, scheme.colorTOOLBARBUTTON_LIGHT, scheme.colorTOOLBARBUTTON, scheme.colorTOOLBARBUTTON);

            }
            
            if(toolbarOrientation == BOTTOMTOOLBAR) {
                ofFill();
                //ofSetColor(scheme.colorTOOLBAR);
                //ofDrawRectangle(0,ofGetHeight()-toolbarSize,ofGetWidth(),toolbarSize); //toolbar bar.

                
                
                //UNDO
                ofPushMatrix();

                ofTranslate(toolbarSize * 0.05, ofGetHeight() - toolbarSize + toolbarSize * 0.05);
                backgroundKey.draw();
                ofFill();
                ofSetColor(255);
                ofSetLineWidth(5);
                if(ofGetAppPtr()->mouseX > toolbarSize * 0.05 && ofGetAppPtr()->mouseX < toolbarSize * 0.9
                   && ofGetAppPtr()->mouseY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && ofGetAppPtr()->mouseY < ofGetWidth() - toolbarSize * .05) {
                    //ofTranslate(-toolbarSize*.9/5.,-toolbarSize*.9/5.);
                    ofScale(1.05,1.05);
                    ofTranslate(-toolbarSize*.025,-toolbarSize*.025);
                }
                ofBeginShape();
                ofVertex((toolbarSize*.9/5.)*4.,(toolbarSize*.9/5.)*1.);
                ofVertex((toolbarSize*.9/5.)*1.,toolbarSize*.9/2.);
                ofVertex((toolbarSize*.9/5.)*4.,(toolbarSize*.9/5.)*4.);
                ofEndShape();
                ofSetLineWidth(1);
                ofPopMatrix();

                //RETRY
                ofPushMatrix();
                ofTranslate(ofGetWidth() - 2*toolbarSize + toolbarSize * 0.05, ofGetHeight() - toolbarSize + toolbarSize * 0.05);
                backgroundKey.draw();
                
                if(ofGetAppPtr()->mouseX > (ofGetWidth() - 2*toolbarSize + toolbarSize * 0.05) && ofGetAppPtr()->mouseX < (ofGetWidth() - 1*toolbarSize - toolbarSize * 0.05)
                   && ofGetAppPtr()->mouseY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && ofGetAppPtr()->mouseY < ofGetWidth() - toolbarSize * .05) {
                    ofScale(1.05,1.05);
                    ofTranslate(-toolbarSize*.025,-toolbarSize*.025);

                }
                ofPath path;
                path.moveTo(toolbarSize*.9/2.,toolbarSize*.9/2.-toolbarSize*.5/2.);
                path.arc(toolbarSize*.9/2.,toolbarSize*.9/2.,toolbarSize*.5/2.,toolbarSize*.5/2.,270,270+270);
                path.setFilled(false);
                path.setStrokeWidth(5);
                path.draw();
                
                ofPushMatrix();
                ofTranslate(toolbarSize*.9/2.,toolbarSize*.9/2.);
                ofRotate(1);
                ofTranslate(-toolbarSize*.9/2.,-toolbarSize*.9/2.);
                path.draw();
                ofPopMatrix();
                
                ofFill();
                ofBeginShape();
                ofVertex(toolbarSize*.9/2.,toolbarSize*.9/2.-toolbarSize*.5/2.-toolbarSize*.125);
                ofVertex(toolbarSize*.9/2.,toolbarSize*.9/2.-toolbarSize*.5/2.+toolbarSize*.125);
                ofVertex(toolbarSize*.9/2.-toolbarSize*.125,toolbarSize*.9/2.-toolbarSize*.5/2.);
                ofEndShape();
                ofPopMatrix();
                
                //MAIN MENU
                ofPushMatrix();
                ofTranslate(ofGetWidth() - toolbarSize + toolbarSize * 0.05, ofGetHeight() - toolbarSize + toolbarSize * 0.05);
                backgroundKey.draw();
                deque<deque<int> > blackOnly = {{1000}};
                ofSetColor(255);
                ofFill();
                // ...
                // :::
                if(ofGetAppPtr()->mouseX > (ofGetWidth() - 1*toolbarSize + toolbarSize * 0.05) && ofGetAppPtr()->mouseX < (ofGetWidth() - toolbarSize * 0.05)
                   && ofGetAppPtr()->mouseY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && ofGetAppPtr()->mouseY < ofGetWidth() - toolbarSize * .05) {
                    ofScale(1.05,1.05);
                    ofTranslate(-toolbarSize*.025,-toolbarSize*.025);
                }
                
                float actualtilesize = toolbarSize*.9*.175;
                float tilesize = toolbarSize*.9*.25;
                for(int i = 0; i < 3; ++i) {
                    for(int j = 0; j < 3; ++j) {
                        ofPushMatrix();
                        ofTranslate((toolbarSize*.9-toolbarSize*.9*.75)/2. + (tilesize-actualtilesize)/2.+i*tilesize,
                                    (toolbarSize*.9-toolbarSize*.9*.75)/2. + (tilesize-actualtilesize)/2.+j*tilesize);
                        drawCellFill(0,0, actualtilesize, actualtilesize*.75/6., blackOnly);
                        ofPopMatrix();
                    }
                }
                ofPopMatrix();
                
                ofSetColor(255);
                ofNoFill();
                
                
                
                
                //EXIT
                /*
                ofPushMatrix();
                ofTranslate(ofGetWidth() - toolbarSize + toolbarSize * 0.05, ofGetHeight() - toolbarSize + toolbarSize * 0.05);
                backgroundKey.draw();
                
                deque<deque<int> > redOnly = {{100}};
                ofSetColor(255,0,0);
                
                ofTranslate((toolbarSize*.9 - toolbarSize*.9/1.50)/2.,(toolbarSize*.9 - toolbarSize*.9/1.50)/2.);
                drawCellFill(0,0, toolbarSize*.9/1.50, toolbarSize*.9/1.5, redOnly);
                ofTranslate(-(toolbarSize*.9 - toolbarSize*.9/1.50)/2.,-(toolbarSize*.9 - toolbarSize*.9/1.50)/2.);
                
                ofSetColor(255);
                ofTranslate((toolbarSize*.9 - toolbarSize*.9/1.25)/2.,(toolbarSize*.9 - toolbarSize*.9/1.25)/2.);
                drawCellStroke(0,0, toolbarSize*.9/1.25, toolbarSize*.9/6., redOnly);
                ofPopMatrix();
                */
                
                
            }
        }
    }
}

#endif /* toolbar_h */

