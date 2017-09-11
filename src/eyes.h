//
//  eyes.h
//  trapPuzzler3
//
//  Created by Kivifreak on 04/02/16.
//
//

#ifndef trapPuzzler3_eyes_h
#define trapPuzzler3_eyes_h

deque<deque<int> > eyeGrid, moveEyeGrid;
int currentWatchY = 0, currentWatchX = 0;
#ifndef islevelgen
void generateLookAt(deque<deque<int> > & eGrid) {
    currentWatchY = 0; currentWatchY = 0;
    for(int i = 0; i < grid.size(); ++i) {
        for(int j = 0; j < grid[i].size(); ++j) {
            if(grid[i][j] == playerID && getCellType(eGrid[i][j]) == PLAYER) {
                currentWatchY = i; currentWatchX = j;
                //ofRectangle pos = calculatePosition(i,j,eGrid.size(), eGrid[i].size());
                //currentWatchY = pos.getY() + pos.getHeight() / 2.;
                //currentWatchX = pos.getX() + pos.getWidth() / 2.;
                break;
            }
        }
    }
}

void generateEyeGrid() {
    eyeGrid = deque<deque<int> >(grid.size(), deque<int> (grid[0].size(), 0));
    multimap<int, pair<int, int> > allNumbers;
    for(int i = 0; i < grid.size(); ++i) {
        for(int j = 0; j < grid[i].size(); ++j) {
            // Eye easter egg if air is added: !!!!!
            if(getCellType(grid[i][j]) == PLAYER || getCellType(grid[i][j]) == ENEMY || getCellType(grid[i][j]) == LOVE)
            allNumbers.insert( {grid[i][j], {i, j}} );
        }
    }
    for( auto it = allNumbers.begin(), end = allNumbers.end(); it != end; it = allNumbers.upper_bound(it->first) ) {
        int randEye = rand() % allNumbers.count(it->first);
        advance(it, randEye);
        int eyeID = 0;
        if(getCellType(it->first) == PLAYER) eyeID = 1;
        else if(getCellType(it->first) == ENEMY) eyeID = 2;
        else if(getCellType(it->first) == LOVE) eyeID = 3;
        //else if(getCellType(it->first) == ) eyeID = 1000;
        eyeGrid[(it->second).first][(it->second).second] = eyeID;
        //cout << it->first << ' ' << (it->second).first << ' ' << (it->second).second << endl;
    }
    /*for(int i = 0; i < grid.size(); ++i) {
        for(int j = 0; j < grid[i].size(); ++j) {
            if(grid[i][j] == GRAVITYMONSTERMOUTHID) eyeGrid[i][j] = GRAVITYMONSTERMOUTHID;
            else if(grid[i][j] == GRAVITYMONSTEREYEID) eyeGrid[i][j] = GRAVITYMONSTEREYEID;
        }
    }*/
    moveEyeGrid = eyeGrid;
}

void drawEnemyEye(bool direction, int i , int j, float scale, int gridY, int gridX) {
    ofEnableSmoothing();
    ofFill();
    ofSetColor(255, 255, 255);
    ofDrawEllipse(scale * 0.5, scale * 0.33, scale * 0.5, scale * 0.5);
    ofSetColor(0, 0, 0);
    float angle = atan2( (float)(currentWatchY - i) , (float)(currentWatchX - j) );
    ofDrawEllipse(scale * 0.5  + cos(angle)*2 , scale * 0.33 + sin(angle)*2, scale * 0.25, scale * 0.25);
    ofSetColor(scheme.colorENEMY);
    ofDrawRectangle(scale * 0.25, 0, scale * 0.5, scale * 0.33);
    ofSetColor(scheme.colorENEMYSTROKE);
    ofSetLineWidth(scale * 0.05);
    if(direction == false) ofDrawLine(scale * 0.25, scale * 0.25, scale * 0.75, scale * 0.33);
    else ofDrawLine(scale * 0.25, scale * 0.33, scale * 0.75, scale * 0.25);
    ofSetLineWidth(1);
}

//CREATE scale DP
pair<float,ofPath> loveEyeDP;
void drawLoveEye(float scale) {
    ofEnableSmoothing();

    if(loveEyeDP.first != scale) {
        ofPath eyeLid;
        eyeLid.setColor(0);
        
        float wimperLength = scale * .15;
        eyeLid.moveTo(scale*.5-scale*.2-wimperLength,scale*.5);
        eyeLid.arcNegative(scale*.5,scale*.5,scale*.2, scale*.2, 180,135); //180°-90°
        eyeLid.lineTo(scale*.5 - (scale*.2+wimperLength)*1./sqrt(2), scale*.5 + (scale*.2+wimperLength)*1./sqrt(2));
        eyeLid.arcNegative(scale*.5,scale*.5,scale*.2, scale*.2, 135,90);
        eyeLid.lineTo(scale*.5, scale*.5+scale*.2+wimperLength);
        eyeLid.arcNegative(scale*.5,scale*.5,scale*.2, scale*.2, 90,45);
        eyeLid.lineTo(scale*.5 + (scale*.2+wimperLength)*1./sqrt(2), scale*.5 + (scale*.2+wimperLength)*1./sqrt(2));
        eyeLid.arcNegative(scale*.5,scale*.5,scale*.2, scale*.2, 45,0);
        eyeLid.lineTo(scale*.5+scale*.2+wimperLength, scale*.5);
        eyeLid.setFilled(false);
        eyeLid.setStrokeWidth(2);
        loveEyeDP = {scale, eyeLid};
    }
    ofPushMatrix();
    ofTranslate(0,-scale*.1); //people like eyes a little bit higher.
    loveEyeDP.second.draw();
    ofPopMatrix();
}

void drawPlayerEye(float scale) {
    ofDisableSmoothing();
    ofFill();
    ofSetColor(255, 255, 255);
    ofDrawEllipse(scale * 0.5, scale * 0.5, scale * 0.5, scale * 0.5);
    ofSetColor(0, 0, 0);
    ofDrawEllipse(scale * 0.5, scale * 0.5, scale * 0.25, scale * 0.25);
}

void drawEyes(int i, int j, float scale, float tScale, deque<deque<int> > & eGrid) {
    if(eGrid[i][j] == 0) {} //eyeless
    else if(eGrid[i][j] == 2) {
        drawEnemyEye(false,i, j, scale * 0.75, eGrid.size(), eGrid[0].size());
        ofPushMatrix();
        ofTranslate(scale * 0.25, 0);
        drawEnemyEye(true, i, j, scale * 0.75, eGrid.size(), eGrid[0].size());
        ofPopMatrix();
    }
    else if(eGrid[i][j] == 1) {
        drawPlayerEye(scale);
    }
    else if(eGrid[i][j] == 3) {
        drawLoveEye(scale);
    }
    else assert(false); //unknown eyes
    //if(eGrid[i][j] == 1) ofDrawRectangle(scale * 0.25, scale * 0.25, scale * 0.25, scale * 0.25);
}
#endif

#endif
