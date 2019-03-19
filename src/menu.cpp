#include "menu.h"

#include "colorScheme.h"
#include "displayLevel.h"
#include "eyes.h"
#include "globals.h"
#include "grid.h"
#include "keyEvent.h"
#include "levels.h"

//int MENUlevelWidth;
static int MENUscrollDist = 100;
static int MENUselected = 0;

void initMenu() {
    mode = MENU;
}

//returns the width/height of a single block.
float displayLevelInMenu(ddd & theLevel, bool displayPlayer, int width, bool displayEyes) {
    if(theLevel.size() != 0) {
        float scaleY = (width * 1.) / ((theLevel.size() + 2) * 1.);
        float scaleX = (width * 1.) / ((theLevel[0].size() + 2) * 1.);
        float scale = MIN(scaleY, scaleX);
        LINE_WIDTH = MAX(1, scale / 20.);
        
        //for eyes
        if(displayEyes) {
            grid = theLevel;
            generateEyeGrid();
            recheckGrid();
            //if(renderMode == PARTIAL) switchRenderMode(PARTIAL);
        }
        
        ofNoFill();
        ofSetColor(0, 0, 0);
        
        vector<vector<ofRectangle> > rects(theLevel.size(), vector<ofRectangle>(theLevel[0].size()));
        
        int w = width;
        int h = w;
        float miniScale = min((h * 1.) / theLevel.size(),  (w * 1.) / theLevel[0].size());
        
        for(int i = 0; i < theLevel.size(); ++i) {
            for(int j = 0; j < theLevel[i].size(); ++j) {
                float idX = j - theLevel[i].size() / 2.;
                float idY = i - theLevel.size() / 2.;
                
                ofRectangle output(idX * miniScale, idY * miniScale, miniScale, miniScale);
                output.translate(w / 2., h / 2.);
                
                rects[i][j] = output;
            }
        }
        for(int i = 0; i < theLevel.size(); ++i) {
            for(int j = 0; j < theLevel[i].size(); ++j) {
                cellType cT = getCellType(theLevel[i][j]);
                
                if(theLevel[i][j] != 0 && (cT != PLAYER || displayPlayer == true)) {
                    ofFill();
                    ofPushMatrix();
                    ofTranslate(rects[i][j].getTopLeft());
                    //ofScale(roughScale,roughScale);
                    if(cT == PLAYER) ofSetColor(scheme.colorPLAYERSELECTED);//ofSetColor(255, 255, 0);
                    else if(cT == ENEMY) ofSetColor(scheme.colorENEMY);//ofSetColor(255, 100, 0);
                    else if(cT == UNMOVABLE_ENEMY) ofSetColor(scheme.colorUNMOVABLE_ENEMY); //ofSetColor(50, 50, 50)
                    else if(cT == LOVE) ofSetColor(scheme.colorLOVE);
                    if(cT != GRAVITYMONSTERMOUTH && cT != GRAVITYMONSTEREYE && cT != GRAVITYMONSTERDEADEYE) {
                        drawCellFill(i, j, miniScale, (miniScale / 4.), theLevel);
                        if(displayEyes) drawEyes(i, j, miniScale, miniScale / 2., eyeGrid, theLevel, 0);
                    }
                    ofPopMatrix();
                }
            }
        }
        
        for(int i = 0; i < theLevel.size(); ++i) {
            for(int j = 0; j < theLevel[i].size(); ++j) {
                cellType cT = getCellType(theLevel[i][j]);
                
                if(theLevel[i][j] != 0 && cT != PLAYER) {
                    ofPushMatrix();
                    ofTranslate(rects[i][j].getTopLeft());
                    
                    if(cT == ENEMY) ofSetColor(scheme.colorENEMYSTROKE); //ofSetColor(255, 0, 0); //NOT SURE
                    else if(cT == UNMOVABLE_ENEMY) ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE); //ofSetColor(0, 0, 0); //NOT SURE YET
                    else if(cT == LOVE) ofSetColor(scheme.colorLOVESTROKE);
                    if(cT == ENEMY || cT == UNMOVABLE_ENEMY || cT == LOVE) drawCellStroke(i, j, miniScale, miniScale / 4., theLevel);
                    ofPopMatrix();
                }
            }
        }
        return miniScale;
    }
    return 0;
}

static deque<deque<int> > questionMarkLevel = {{1000011,1000011,1000011,1000011,1000011,1000011,1000011,1000011,1000011},{1000011,1000011,1000011,1000011,1000011,1000011,1000011,1000011,1000011},{1000011,1000011,1000011,2001001,2001001,2001001,1000011,1000011,1000011},{1000011,1000011,1000011,1000011,1000011,2001001,1000011,1000011,1000011},{1000011,1000011,1000011,1000011,2001001,2001001,1000011,1000011,1000011},{1000011,1000011,1000011,1000011,2001001,1000011,1000011,1000011,1000011},{1000011,1000011,1000011,1000011,1000011,1000011,1000011,1000011,1000011},{1000011,1000011,1000011,1000011,2001000,1000011,1000011,1000011,1000011},{1000011,1000011,1000011,1000011,1000011,1000011,1000011,1000011,1000011},{1000011,1000011,1000011,1000011,1000011,1000011,1000011,1000011,1000011}};

static pair<pair<int,int>, ofMesh> backgroundTile  = {{-2,-2},ofMesh()};
static pair<pair<int,int>, ofMesh> levelselectTile = {{-2,-2},ofMesh()};

/*
 map<int,ofImage> renderedImages;
 int previousLevel = 1;
 void displayOldMenu();
 void displayMenuIMGDPed() {
 if(renderedImages.size() == 0 || renderedImages[0].getWidth() != getWidth() || renderedImages[0].getHeight() != getHeight()) renderedImages.clear();
 if(renderedImages.count(currentLevel) != 0) {
 displayOldMenu();
 ofImage imgSaver;
 imgSaver.grabScreen(0, 0, getWidth(), getHeight());
 renderedImages[currentLevel] = imgSaver;
 }
 else {
 renderedImages[currentLevel].draw();
 }
 previousLevel = currentLevel;
 
 }*/

void displayOldMenu() {
    ofFill();
    //ofSetColor(scheme.colorBACKGROUND_VOID);
    //ofDrawRectangle(0,0,getWidth(), getHeight());
    
    if(!isMousePressed) scrollX -= scrollX / 5.;
    ofPushMatrix();
    ofTranslate(scrollX,0);
    int sizeOfAllLevels = levels.size();
    //Every world has N levels:
    int minSize = min(getWidth(), getHeight());
    int startX = 0.05 * minSize + (getWidth() - minSize) / 2;
    int startY = 0.05 * minSize + (getHeight() - minSize) / 2;
    
    ofSetColor(scheme.colorBACKGROUND_SHADED);
    roundedRect(startX, startY, 0.9 * minSize, 0.91 * minSize, .05 * minSize);
    //ofSetColor(scheme.colorBACKGROUND);
    //roundedRect(startX, startY, 0.9 * minSize, 0.9 * minSize, .05 * minSize);
    if(backgroundTile.first.first != getWidth() || backgroundTile.first.second != getHeight()) backgroundTile = {{getWidth(), getHeight()},
        generateMeshTile(0.9*minSize, 0.9*minSize, .05*minSize, scheme.colorBACKGROUND_LIGHT, scheme.colorBACKGROUND_LIGHT, scheme.colorBACKGROUND, scheme.colorBACKGROUND , false, false, false, false)};
    
    int levelCountPerWorld = 9;
    int currentWorld = currentLevel / levelCountPerWorld;
    
    ofPushMatrix();
    ofTranslate(startX, startY);
    backgroundTile.second.draw();
    ofTranslate(getWidth(), 0);
    if(scrollX < 0 && currentLevel+levelCountPerWorld < levels.size()) backgroundTile.second.draw();
    ofTranslate(-2*getWidth(),0);
    if(scrollX > 0 && currentLevel-levelCountPerWorld >= 0) backgroundTile.second.draw();
    ofPopMatrix();
    
    for(int i = 0; i < levels.size(); ++i) {
        if((i / levelCountPerWorld == currentWorld-1&&scrollX > 0) || i / levelCountPerWorld == currentWorld || (i/levelCountPerWorld == currentWorld+1 && scrollX < 0)) {
            if(i/levelCountPerWorld == currentWorld-1) {
                ofPushMatrix();
                ofTranslate(-getWidth(),0);
            }
            if(i/levelCountPerWorld == currentWorld+1) {
                ofPushMatrix();
                ofTranslate(getWidth(),0);
            }
            int positionX = (i % levelCountPerWorld) / 3, positionY = i % 3; //LAST IS BOSS
            
            int w = 0.9/3. * minSize;
            int h = w;
            
            positionX = startX + positionX * w;
            positionY = startY + positionY * h;
            
            
            int sizeOfMap = .8 * w;
            
            ofPushMatrix();
            ofTranslate(positionX + .1*w, positionY + .1*w);
            if(i == currentLevel) {
                
                //Draw level selection:
                if(levelselectTile.first.first != getWidth() || levelselectTile.first.second != getHeight()) levelselectTile = {{getWidth(), getHeight()},
                    generateMeshTile(sizeOfMap + .2*w + 2, sizeOfMap + .2*h + 2, .05*minSize, scheme.colorLEVELSELECT, scheme.colorLEVELSELECT_LIGHT, scheme.colorLEVELSELECT, scheme.colorLEVELSELECT)};
                //glLineWidth(5);
                ofPushMatrix();
                ofTranslate(-.1*w-1, -.1*h-1);
                levelselectTile.second.draw();
                ofPopMatrix();
                //glLineWidth(1);
            }
            //Check for king level solvable...
            
            if(i == 9 || i == 10) {
                bool canBePlayed = true;
                for(int j=0;j<9;++j) if(beaten[j]==false) canBePlayed = false;
                /*for(int j = 0; j < 9; ++j) {
                 if(j != 4 && beaten[i+j-4] == false) canBePlayed = false;
                 }*/
                if(canBePlayed) displayLevelInMenu(levels[i], i == currentLevel, sizeOfMap, false);
                else displayLevelInMenu(questionMarkLevel, i == currentLevel, sizeOfMap, false);
            }
            else {
                displayLevelInMenu(levels[i], i == currentLevel, sizeOfMap, false);
            }
            
            glLineWidth(5);
            ofSetColor(0, 255, 0);
            float miniScale = min((h * 1.) / 12.,  (w * 1.) / 12.);
            if(i == currentLevel) miniScale = min((h * 1.) / 15.,  (w * 1.) / 15.);
            if(beaten[i]) {
                //ofPushMatrix();
                //ofTranslate()
                ofSetColor(0,255,0);
                ofFill();
                bool selectedPencil = false;
                //min(getWidth(),getHeight())/750.,min(getWidth(),getHeight())/750.,min(getWidth(),getHeight())/750.
                
                if(i / levelCountPerWorld == currentWorld) {
                    if(mousetouchX >  positionX + .1*w - 50.*min(getWidth(),getHeight())/750. && mousetouchX < positionX + .1*w + 10.*min(getWidth(),getHeight())/750.
                       && mousetouchY >  positionY + .1*h - 20.*min(getWidth(),getHeight())/750. && mousetouchY < positionY + .1*h + 30.*min(getWidth(),getHeight())/750.) {
                        selectedPencil = true;
                    }
                    
                    if(isMousePressed) {
                        if(mousePressedX > positionX && mousePressedX < positionX + w && mousePressedY > positionY && mousePressedY < positionY + h) currentLevel = i;
                    }
                }
                displayPencil(selectedPencil);
            }
            
            if(isMouseReleased && i / levelCountPerWorld == currentWorld) {
                if(beaten[i] && mousetouchX >  positionX + .1*w - 50.*min(getWidth(),getHeight())/750. && mousetouchX < positionX + .1*w + 10.*min(getWidth(),getHeight())/750.
                   && mousetouchY >  positionY + .1*h - 20.*min(getWidth(),getHeight())/750. && mousetouchY < positionY + .1*h + 30.*min(getWidth(),getHeight())/750.) {
                    currentLevel = i;
                    tryPlayLevel(i,true);
                }
                else if(mouseReleasedX > positionX && mouseReleasedX < positionX + w && mouseReleasedY > positionY && mouseReleasedY < positionY + h) {
                    currentLevel = i; //In case it hasn't been updated before.
                    tryPlayLevel(i,false);
                }
            }
            glLineWidth(1);
            ofPopMatrix();
            if(i/levelCountPerWorld == currentWorld-1 || i/levelCountPerWorld == currentWorld+1) ofPopMatrix();
        }
    }
    ofPopMatrix();
}


//int unlockedLevels = 0;
static deque<pair<float, float> > characterOnMapLocation;
void displayCharacterOnMap() {
    if(characterOnMapLocation.size() == 0) {
        characterOnMapLocation.push_front({getWidth() / 2, getHeight() / 2});
    }
    
    if(keyPressedDown[UP].second || keyPressedDown[DOWN].second || keyPressedDown[LEFT].second || keyPressedDown[RIGHT].second) {
        for(int i = 0; i < (int)characterOnMapLocation.size() - 1; ++i) {
            characterOnMapLocation[i+1] = characterOnMapLocation[i];
        }
        pair<float, float> currentLocation = characterOnMapLocation.front();
        
        float actualVelocity = 2.5;
        if(keyPressedDown[UP].second + keyPressedDown[DOWN].second + keyPressedDown[LEFT].second + keyPressedDown[RIGHT].second > 1) actualVelocity *= sin(3.1415926/4.);
        if(keyPressedDown[UP].second) characterOnMapLocation.front().first -= actualVelocity;
        if(keyPressedDown[DOWN].second) characterOnMapLocation.front().first += actualVelocity;
        if(keyPressedDown[LEFT].second) characterOnMapLocation.front().second -= actualVelocity;
        if(keyPressedDown[RIGHT].second) characterOnMapLocation.front().second += actualVelocity;
    }
    
    ///!!! Make sure the appropriate characters are in here.
    
    float scaleY = (getHeight() * 1.);
    float scaleX = (getWidth() * 1.);
    float scale = MIN(scaleY, scaleX);
    LINE_WIDTH = MAX(1, scale / 100.);
    
    deque<deque<int> > levelMan = {{1}};
    for(int i = (int)characterOnMapLocation.size() - 1; i >= 0; --i) {
        ofPushMatrix();
        ofTranslate(characterOnMapLocation[i].second, characterOnMapLocation[i].first);
        displayLevelInMenu(levelMan, true,  10., true);
        /*ofSetColor(scheme.colorPLAYERSELECTED);
         drawCellFill(0, 0, scale / 50., (scale / (50.*4.)), levelMan);
         //drawCellStroke(0, 0, scale / 50., (scale / (50.*4.)), levelMan);
         drawEyes(0,0,)
         */
        ofPopMatrix();
    }
}

void displayMenu() {
    displayCharacterOnMap();
    ofPushMatrix();
    ofTranslate(100, 100);
    displayLevelInMenu(levels[0], false,100., false);
    ofPopMatrix();
}
