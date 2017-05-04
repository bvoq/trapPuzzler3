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
ofMesh returnKey;

void displayToolBar() {
    if(!messageBlockingToolbar) {
        if(toolbarOrientation != NOTOOLBAR) {
            if(dpDrawCoordinates.first != ofGetHeight() && dpDrawCoordinates.second != ofGetHeight()) {
                //Redraw all the keys
                returnKey = generateMeshTile(toolbarSize * .9, toolbarSize * .9, toolbarSize * .05, scheme.colorLEVELSELECT, scheme.colorLEVELSELECT_LIGHT, scheme.colorLEVELSELECT, scheme.colorLEVELSELECT);
            }
            
            if(toolbarOrientation == BOTTOMTOOLBAR) {
                ofFill();
                ofSetColor(0,255,0);
                ofDrawRectangle(0,ofGetHeight()-toolbarSize,ofGetWidth(),toolbarSize);
                
                ofPushMatrix();
                ofTranslate(toolbarSize * 0.05, ofGetHeight() - toolbarSize + toolbarSize * 0.05);
                returnKey.draw();
                ofPopMatrix();
            }
        }
    }
}

#endif /* toolbar_h */
