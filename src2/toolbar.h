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
} toolbarOrientation = BOTTOMTOOLBAR;

bool messageBlockingToolbar = false; //maybe make this messa

int toolbarSize = 100; //Will be dynamically overwritten, later in the code.
int messageSize = 0;

int getWidth() {
    if((mode == LEVEL_EDITOR_PLAYING || mode == PLAYING || mode == LEVEL_EDITOR || mode == CREDITS || mode == CONTROL_CHANGE) && toolbarOrientation == RIGHTTOOLBAR) return ofGetWidth() - toolbarSize;
    else return ofGetWidth();
}
int getHeight() {
    if(messageBlockingToolbar) return ofGetHeight() - max(messageSize,toolbarSize); //might look nicer during transition of messages.
    if((mode == LEVEL_EDITOR_PLAYING || mode == PLAYING || mode == LEVEL_EDITOR || mode == CREDITS || mode == CONTROL_CHANGE) && toolbarOrientation == BOTTOMTOOLBAR) return ofGetHeight() - toolbarSize;
    return ofGetHeight();
}

pair<int,int> dpDrawCoordinates = {-1,-1};
ofMesh backgroundKey, backgroundKeySelected;

void displayToolBar() {
    if(!messageBlockingToolbar && !blockMovementDueToWinningAnimation) {
        if(toolbarOrientation != NOTOOLBAR) {
            if(dpDrawCoordinates.first != ofGetHeight() && dpDrawCoordinates.second != ofGetHeight()) {
                toolbarSize = 0.1 * min(ofGetWidth(),ofGetHeight());
                //Redraw all the keys
                backgroundKey = generateMeshTile(toolbarSize * .9, toolbarSize * .9, toolbarSize * .05, scheme.colorTOOLBARBUTTON, scheme.colorTOOLBARBUTTON_LIGHT, scheme.colorTOOLBARBUTTON, scheme.colorTOOLBARBUTTON);
                backgroundKeySelected = generateMeshTile(toolbarSize * .9, toolbarSize * .9, toolbarSize * .05, scheme.colorTOOLBARBUTTON_SELECTED, scheme.colorTOOLBARBUTTON_SELECTED_LIGHT, scheme.colorTOOLBARBUTTON_SELECTED, scheme.colorTOOLBARBUTTON_SELECTED);
                
            }
            //PLAYING=0, LEVEL_EDITOR_PLAYING=1, LEVEL_EDITOR=2, MENU=3, PAUSE=4, MENUOLD=5, MAINMENU=6, CREDITS=7, CONTROL_CHANGE=8, UNKNOWN=100

            if(toolbarOrientation == BOTTOMTOOLBAR) {
                
                if(mode == CREDITS || mode == CONTROL_CHANGE) {
                    //MAIN MENU
                    ofPushMatrix();
                    ofTranslate(ofGetWidth() - toolbarSize + toolbarSize * 0.05, ofGetHeight() - toolbarSize + toolbarSize * 0.05);
                    backgroundKey.draw();
                    deque<deque<int> > blackOnly = {{1000}};
                    ofSetColor(255);
                    ofFill();
                    // ...
                    // :::
                    if(mousetouchX > (ofGetWidth() - 1*toolbarSize + toolbarSize * 0.05) && mousetouchX < (ofGetWidth() - toolbarSize * 0.05)
                       && mousetouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mousetouchY < ofGetWidth() - toolbarSize * .05) {
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
                }
                
                
                if(mode == PLAYING || mode == LEVEL_EDITOR_PLAYING) {
                    //ofSetColor(scheme.colorTOOLBAR);
                    //ofDrawRectangle(0,ofGetHeight()-toolbarSize,ofGetWidth(),toolbarSize); //toolbar bar.
                    
                    //UNDO
                    ofPushMatrix();
                    
                    ofTranslate(toolbarSize * 0.05, ofGetHeight() - toolbarSize + toolbarSize * 0.05);
                    backgroundKey.draw();
                    ofFill();
                    ofSetColor(255);
                    ofSetLineWidth(5);
                    if(mousetouchX > toolbarSize * 0.05 && mousetouchX < toolbarSize * 0.9
                       && mousetouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mousetouchY < ofGetWidth() - toolbarSize * .05) {
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
                    
                    
                    //MAIN MENU
                    ofPushMatrix();
                    ofTranslate(ofGetWidth() - toolbarSize + toolbarSize * 0.05, ofGetHeight() - toolbarSize + toolbarSize * 0.05);
                    backgroundKey.draw();
                    deque<deque<int> > blackOnly = {{1000}};
                    ofSetColor(255);
                    ofFill();
                    // ...
                    // :::
                    bool pencilselected = false;
                    if(mousetouchX > (ofGetWidth() - 1*toolbarSize + toolbarSize * 0.05) && mousetouchX < (ofGetWidth() - toolbarSize * 0.05)
                       && mousetouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mousetouchY < ofGetWidth() - toolbarSize * .05) {
                        if(mode == PLAYING) {
                            ofScale(1.05,1.05);
                            ofTranslate(-toolbarSize*.025,-toolbarSize*.025);
                        } else pencilselected = true;
                    }
                    if(mode == PLAYING) {
                        if(grid != levels[currentLevel]) { //RESTART
                            ofPath path;
                            path.moveTo(toolbarSize*.9/2.,toolbarSize*.9/2.-toolbarSize*.5/2.);
                            path.arc(toolbarSize*.9/2.,toolbarSize*.9/2.,toolbarSize*.5/2.,toolbarSize*.5/2.,270,270+270);
                            path.setFilled(false);
                            path.setStrokeWidth(5);
                            path.draw();
                            
                            ofTranslate(toolbarSize*.9/2.,toolbarSize*.9/2.);
                            ofRotate(1);
                            ofTranslate(-toolbarSize*.9/2.,-toolbarSize*.9/2.);
                            path.draw();
                            
                            ofFill();
                            ofBeginShape();
                            ofVertex(toolbarSize*.9/2.,toolbarSize*.9/2.-toolbarSize*.5/2.-toolbarSize*.125);
                            ofVertex(toolbarSize*.9/2.,toolbarSize*.9/2.-toolbarSize*.5/2.+toolbarSize*.125);
                            ofVertex(toolbarSize*.9/2.-toolbarSize*.125,toolbarSize*.9/2.-toolbarSize*.5/2.);
                            ofEndShape();
                        } else { //BACK TO MENU
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
                        }
                    } else if(mode == LEVEL_EDITOR_PLAYING) {
                        ofTranslate(toolbarSize*.9*.77,toolbarSize*.9*.4);
                        displayPencil(pencilselected);
                    }
                    ofPopMatrix();

                    
                    ofSetColor(255);
                    ofNoFill();
                }
                
                if(mode == LEVEL_EDITOR) {
                    //UNDO
                    ofPushMatrix();
                    
                    ofTranslate(toolbarSize * 0.05, ofGetHeight() - toolbarSize + toolbarSize * 0.05);
                    backgroundKey.draw();
                    ofFill();
                    ofSetColor(255);
                    ofSetLineWidth(5);
                    if(mousetouchX > toolbarSize * 0.05 && mousetouchX < toolbarSize * 0.9
                       && mousetouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mousetouchY < ofGetWidth() - toolbarSize * .05) {
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
                    
                    //YELLOW BLOCK
                    ofSetColor(scheme.colorPLAYERSELECTED);
                    ofPushMatrix();
                    deque<deque<int> > yellowOne = {{1}};
                    ofTranslate(toolbarSize * 0.05 + toolbarSize, ofGetHeight() - toolbarSize + toolbarSize * 0.05);
                    if(placeType == PLAYER) backgroundKeySelected.draw();
                    else backgroundKey.draw();
                    if(mousetouchX > toolbarSize * 0.05 + toolbarSize && mousetouchX < toolbarSize * 0.9 + toolbarSize
                        && mousetouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mousetouchY < ofGetWidth() - toolbarSize * .05) {
                        //ofTranslate(-toolbarSize*.9/5.,-toolbarSize*.9/5.);
                        ofScale(1.05,1.05);
                        ofTranslate(-toolbarSize*.025,-toolbarSize*.025);
                    }
                    ofTranslate(toolbarSize*.25-toolbarSize*0.05,toolbarSize*.25-toolbarSize*0.05);
                    drawCellFill(0,0,toolbarSize*.5, toolbarSize*.1, yellowOne);
                    drawEyes(0,0, toolbarSize*.5, toolbarSize*.1, yellowOne, yellowOne, 0);
                    ofPopMatrix();
                    
                    //RED BLOCK
                    ofSetColor(scheme.colorENEMY);
                    ofPushMatrix();
                    deque<deque<int> > redOne = {{2}};
                    ofTranslate(toolbarSize * 0.05 + 2*toolbarSize, ofGetHeight() - toolbarSize + toolbarSize * 0.05);
                    if(placeType == ENEMY) backgroundKeySelected.draw();
                    else backgroundKey.draw();
                    if(mousetouchX > toolbarSize * 0.05 + toolbarSize*2 && mousetouchX < toolbarSize * 0.9 + toolbarSize*2
                       && mousetouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mousetouchY < ofGetWidth() - toolbarSize * .05) {
                        //ofTranslate(-toolbarSize*.9/5.,-toolbarSize*.9/5.);
                        ofScale(1.05,1.05);
                        ofTranslate(-toolbarSize*.025,-toolbarSize*.025);
                    }
                    ofTranslate(toolbarSize*.25-toolbarSize*0.05,toolbarSize*.25-toolbarSize*0.05);
                    drawCellFill(0,0,toolbarSize*.5, toolbarSize*.1, redOne);
                    //ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
                    drawEyes(0,0, toolbarSize*.5, toolbarSize*.1, redOne, redOne, 0);
                    ofPopMatrix();
                    
                    //GRAY BLOCK
                    ofSetColor(scheme.colorUNMOVABLE_ENEMY);
                    ofPushMatrix();
                    deque<deque<int> > grayOne = {{0}};
                    ofTranslate(toolbarSize * 0.05 + 3*toolbarSize, ofGetHeight() - toolbarSize + toolbarSize * 0.05);
                    if(placeType == UNMOVABLE_ENEMY) backgroundKeySelected.draw();
                    else backgroundKey.draw();
                    if(mousetouchX > toolbarSize * 0.05 + toolbarSize*3 && mousetouchX < toolbarSize * 0.9 + toolbarSize*3
                       && mousetouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mousetouchY < ofGetWidth() - toolbarSize * .05) {
                        //ofTranslate(-toolbarSize*.9/5.,-toolbarSize*.9/5.);
                        ofScale(1.05,1.05);
                        ofTranslate(-toolbarSize*.025,-toolbarSize*.025);
                    }
                    ofTranslate(toolbarSize*.25-toolbarSize*0.05,toolbarSize*.25-toolbarSize*0.05);
                    drawCellFill(0,0,toolbarSize*.5, toolbarSize*.05, grayOne);
                    ofNoFill();
                    ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
                    ofTranslate(-toolbarSize*.025,-toolbarSize*.025);
                    drawCellStroke(0,0, toolbarSize*.5*1.1, toolbarSize*.1, grayOne);
                    ofPopMatrix();
                    
                    //LOVE BLOCK
                    ofSetColor(scheme.colorLOVE);
                    deque<deque<int> > loveOne = {{3}};
                    ofPushMatrix();
                    ofTranslate(toolbarSize * 0.05 + 4*toolbarSize, ofGetHeight() - toolbarSize + toolbarSize * 0.05);
                    if(placeType == LOVE) backgroundKeySelected.draw();
                    else backgroundKey.draw();
                    if(mousetouchX > toolbarSize * 0.05 + toolbarSize*4 && mousetouchX < toolbarSize * 0.9 + toolbarSize*4
                       && mousetouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mousetouchY < ofGetWidth() - toolbarSize * .05) {
                        //ofTranslate(-toolbarSize*.9/5.,-toolbarSize*.9/5.);
                        ofScale(1.05,1.05);
                        ofTranslate(-toolbarSize*.025,-toolbarSize*.025);
                    }
                    ofTranslate(toolbarSize*.25-toolbarSize*0.05,toolbarSize*.25-toolbarSize*0.05);
                    drawCellFill(0,0,toolbarSize*.5, toolbarSize*.1, loveOne);
                    //ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
                    drawEyes(0,0, toolbarSize*.5, toolbarSize*.1, loveOne, loveOne, 0);
                    ofPopMatrix();
                    
                    
                    //START PLAYING LEVEL
                    ofPushMatrix();
                    
                    ofTranslate(ofGetWidth() - 2*toolbarSize + toolbarSize * 0.05, ofGetHeight() - toolbarSize + toolbarSize * 0.05);
                    backgroundKey.draw();
                    if(mousetouchX > (ofGetWidth() - 2*toolbarSize + toolbarSize * 0.05) && mousetouchX < (ofGetWidth() - toolbarSize * 0.05 - toolbarSize)
                       && mousetouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mousetouchY < ofGetWidth() - toolbarSize * .05) {
                        ofScale(1.05,1.05);
                        ofTranslate(-toolbarSize*.025,-toolbarSize*.025);
                    }
                    ofFill();
                    ofSetColor(255);
                    ofSetLineWidth(5);
                    if(mousetouchX > toolbarSize * 0.05 && mousetouchX < toolbarSize * 0.9
                       && mousetouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mousetouchY < ofGetWidth() - toolbarSize * .05) {
                        //ofTranslate(-toolbarSize*.9/5.,-toolbarSize*.9/5.);
                        ofScale(1.05,1.05);
                        ofTranslate(-toolbarSize*.025,-toolbarSize*.025);
                    }
                    ofBeginShape();
                    ofVertex((toolbarSize*.9/5.)*1.,(toolbarSize*.9/5.)*1.);
                    ofVertex((toolbarSize*.9/5.)*4.,toolbarSize*.9/2.);
                    ofVertex((toolbarSize*.9/5.)*1.,(toolbarSize*.9/5.)*4.);
                    ofEndShape();
                    ofSetLineWidth(1);
                    ofPopMatrix();
                    
                    
                    
                    //MAIN MENU
                    ofPushMatrix();
                    ofTranslate(ofGetWidth() - toolbarSize + toolbarSize * 0.05, ofGetHeight() - toolbarSize + toolbarSize * 0.05);
                    backgroundKey.draw();
                    deque<deque<int> > blackOnly = {{1000}};
                    ofSetColor(255);
                    ofFill();
                    if(mousetouchX > (ofGetWidth() - 1*toolbarSize + toolbarSize * 0.05) && mousetouchX < (ofGetWidth() - toolbarSize * 0.05)
                       && mousetouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mousetouchY < ofGetWidth() - toolbarSize * .05) {
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
                    
                    
                    //AIR
                    ofPushMatrix();

                    ofTranslate(ofGetWidth() - 3*toolbarSize + toolbarSize * 0.05, ofGetHeight() - toolbarSize + toolbarSize * 0.05);
                    if(placeType == AIR) backgroundKeySelected.draw();
                    else backgroundKey.draw();
                    if(mousetouchX > (ofGetWidth() - 3*toolbarSize + toolbarSize * 0.05) && mousetouchX < (ofGetWidth() - toolbarSize * 0.05 - 2*toolbarSize)
                       && mousetouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mousetouchY < ofGetWidth() - toolbarSize * .05) {
                        ofScale(1.05,1.05);
                        ofTranslate(-toolbarSize*.025,-toolbarSize*.025);
                    }
                    ofFill();
                    ofSetColor(scheme.colorBACKGROUND);
                    ofTranslate(toolbarSize*.25-toolbarSize*0.05,toolbarSize*.25-toolbarSize*0.05);
                    ofDrawRectangle(0,0,toolbarSize*.5,toolbarSize*.5);
                    ofNoFill();
                    ofSetColor(0);
                    ofDrawRectangle(0,0,toolbarSize*.5,toolbarSize*.5);
                    
                    //drawCellFill(0,0,toolbarSize*.5, toolbarSize*.1,blackOnly);
                    ofPopMatrix();
                    
                    
                    //SUPERAIR
                    ofPushMatrix();
                    deque<deque<int> > redRow = {{100,100,100}};
                    ofTranslate(ofGetWidth() - 4*toolbarSize + toolbarSize * 0.05, ofGetHeight() - toolbarSize + toolbarSize * 0.05);
                    if(placeType == SUPERAIR) backgroundKeySelected.draw();
                    else backgroundKey.draw();

                    if(mousetouchX > (ofGetWidth() - 4*toolbarSize + toolbarSize * 0.05) && mousetouchX < (ofGetWidth() - toolbarSize * 0.05 - 3*toolbarSize)
                       && mousetouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mousetouchY < ofGetWidth() - toolbarSize * .05) {
                        ofScale(1.05,1.05);
                        ofTranslate(-toolbarSize*.025,-toolbarSize*.025);
                    }
                    
                    ofFill();
                    ofSetColor(scheme.colorENEMY);
                    ofTranslate(toolbarSize*.9*.2-toolbarSize*0.05,toolbarSize*.9*.4);
                    drawCellFill(0,0,toolbarSize*.2, toolbarSize*.05, redRow);
                    ofTranslate(toolbarSize*.9*.25,0);
                    ofSetColor(scheme.colorBACKGROUND);
                    drawCellFill(0,1,toolbarSize*.2, toolbarSize*.05, redRow);
                    ofSetColor(scheme.colorENEMY);
                    ofTranslate(toolbarSize*.9*.25,0);
                    drawCellFill(0,2,toolbarSize*.2, toolbarSize*.05, redRow);
                    
                    //drawCellFill(0,0,toolbarSize*.5, toolbarSize*.1,blackOnly);
                    ofPopMatrix();
                }
                
                
                
                
                
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
            else assert(false); //only know bottom toolbar as of now.
        }
    }
}

#endif /* toolbar_h */

