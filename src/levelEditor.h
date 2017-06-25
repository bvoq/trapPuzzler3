//
//  levelEditor.h
//  trapStory2
//
//  Created by Kivifreak on 31/12/15.
//
//

#ifndef trapPuzzler3_levelEditor_h
#define trapPuzzler3_levelEditor_h

deque<deque<int> > editorGrid;
//int editorGridY, editorGridX;

int playerCount = 1, enemyCount = 1000000, unmovableEnemyCount = 2000000;
cellType placeType;

void changeBrush (cellType newPlaceType) {
    placeType = newPlaceType;
}

set<pair<int, int> > tilesToBePlaced;
vector<deque<deque<int> > > levelEditorSaves;
void placeSelectedTiles() {
    levelEditorSaves.push_back(editorGrid);
    int placeID;
    if(placeType == AIR || placeType == SUPERAIR) {
        placeID = 0;
    }
    else if(placeType == PLAYER) {
        placeID = playerCount;
        playerCount++;
    }
    else if(placeType == ENEMY) {
        placeID = enemyCount;
        enemyCount++;
    }
    else if(placeType == UNMOVABLE_ENEMY) {
        placeID = unmovableEnemyCount;
        unmovableEnemyCount++;
    }
    
    for(auto & it : tilesToBePlaced) {
        if(placeID == 0) {
            bool otherOnes = false;
            for(int i = 0; i < editorGrid.size(); ++i) {
                for(int j = 0; j < editorGrid[i].size(); ++j) {
                    if(! (it.first == i && it.second == j) && editorGrid[i][j] == editorGrid[it.first][it.second]) otherOnes = true;
                }
            }
            if(otherOnes == false) {
                int pos = editorGrid[it.first][it.second];
                pair<int, int> changeRange;
                if(pos > 0 && pos < 1000000) {changeRange = {pos, 1000000}; playerCount--;}
                else if(pos >= 1000000 && pos < 2000000) {changeRange = {pos, 2000000}; enemyCount--;}
                else if(pos >= 2000000 && pos < 3000000) {changeRange = {pos, 3000000}; unmovableEnemyCount--;}
                for(int i = 0; i < editorGrid.size(); ++i) {
                    for(int j = 0; j < editorGrid[i].size(); ++j) {
                        if(editorGrid[i][j] > changeRange.first && editorGrid[i][j] < changeRange.second) editorGrid[i][j]--;
                    }
                }
            }
        }
        editorGrid[it.first][it.second] = placeID;
    }
    
    tilesToBePlaced.clear();
}

void undoLevelEditorMove() {
    if(levelEditorSaves.size() > 0) {
        editorGrid = levelEditorSaves.back();
        levelEditorSaves.pop_back();
    }
}

void levelExport(ostream & o, deque<deque<int> > copied) {
    cropBordersOf(copied);
    o << "{";
    for(int i = 0; i < copied.size(); ++i) {
        o << "{";
        for(int j = 0; j < copied[i].size(); ++j) {
            o << copied[i][j];
            if(j != copied[i].size() - 1) o << ",";
        }
        o << "}";
        if(i != copied.size() - 1) o << ",";
    }
    o << "}";
}

void levelFormattedExportWithoutCropping(ostream & o, deque<deque<int> > copied) {
    o << "{";
    for(int i = 0; i < copied.size(); ++i) {
        o << "{";
        for(int j = 0; j < copied[i].size(); ++j) {
            string toPrint = to_string(copied[i][j]);
            while(toPrint.size()<6) toPrint.push_back(' ');
            o << toPrint;
            if(j != copied[i].size() - 1) o << ",";
        }
        o << "}";
        if(i != copied.size() - 1) o << ",";
    }
    o << "}";
}

void displayLevelEditor() {
    float scaleY = (getHeight() * 1.) / ((editorGrid.size() + 2) * 1.);
    float scaleX = (getWidth() * 1.) / ((editorGrid[0].size() + 2) * 1.);
    float scale = MIN(scaleY, scaleX);
    float tScale = scale / 2.;
    LINE_WIDTH = MAX(1, scale / 20.); //CHECK IF THIS IS OK
    
    ofNoFill();
    ofSetColor(0, 0, 0);
    vector<vector<ofRectangle> > rects(editorGrid.size(), vector<ofRectangle>(editorGrid[0].size()));
    
    for(int i = 0; i < editorGrid.size(); ++i) {
        for(int j = 0; j < editorGrid[i].size(); ++j) {
            rects[i][j] = calculatePosition(i, j, editorGrid.size(), editorGrid[i].size());
            if(isMousePressed && ofGetAppPtr()->mouseX >= rects[i][j].getTopLeft().x &&
               ofGetAppPtr()->mouseY >= rects[i][j].getTopLeft().y &&
               ofGetAppPtr()->mouseX < rects[i][j].getBottomRight().x &&
               ofGetAppPtr()->mouseY < rects[i][j].getBottomRight().y) {
                if(placeType == AIR) {
                    int currentID = editorGrid[i][j];
                    for(int k = 0; k < editorGrid.size(); ++k) {
                        for(int l = 0; l < editorGrid[i].size(); ++l) {
                            if(editorGrid[k][l] == currentID) tilesToBePlaced.insert({k, l});
                        }
                    }
                }
                else tilesToBePlaced.insert({i, j});
            }
        }
    }
    for(int i = 0; i < editorGrid.size(); ++i) {
        for(int j = 0; j < editorGrid[i].size(); ++j) {
            ofSetColor(0, 0, 0);
            ofFill();
            if(tilesToBePlaced.count({i,j}) != 0) ofSetColor(100, 100, 100);
            else ofNoFill();
            ofDrawRectangle(rects[i][j]);
            if(editorGrid[i][j] != 0) {
                ofFill();
                ofPushMatrix();
                ofTranslate(rects[i][j].getTopLeft());
                cellType cT = getCellType(editorGrid[i][j]);
                if(cT == PLAYER) ofSetColor(scheme.colorPLAYERSELECTED);//ofSetColor(255, 255, 0);
                else if(cT == ENEMY) ofSetColor(scheme.colorENEMY);//ofSetColor(255, 100, 0);
                else if(cT == UNMOVABLE_ENEMY) ofSetColor(scheme.colorUNMOVABLE_ENEMY); //ofSetColor(50, 50, 50);
                drawCellFill(i, j, scale, tScale, editorGrid);
                ofPopMatrix();
            }
        }
    }
    
    for(int i = 0; i < editorGrid.size(); ++i) {
        for(int j = 0; j < editorGrid[i].size(); ++j) {
            if(editorGrid[i][j] != 0) {
                ofPushMatrix();
                ofTranslate(rects[i][j].getTopLeft());
                cellType cT = getCellType(editorGrid[i][j]);
                if(cT == ENEMY) ofSetColor(scheme.colorENEMYSTROKE); //ofSetColor(255, 0, 0);
                else if(cT == UNMOVABLE_ENEMY) ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE); // ofSetColor(0, 0, 0);
                
                if(cT == ENEMY || cT == UNMOVABLE_ENEMY) drawCellStroke(i, j, scale, tScale, editorGrid);
                ofPopMatrix();
            }
        }
    }
}

void addLayer(keyType direction) {
    if(direction == UP) {
        pushFrontRowOf(editorGrid);
    }
    else if(direction == DOWN) {
        pushBackRowOf(editorGrid);
    }
    else if(direction == LEFT) {
        pushFrontColumnOf(editorGrid);
    }
    else if(direction == RIGHT) {
        pushBackColumnOf(editorGrid);
    }
}

void initLevelEditor(int loadFromLevel, bool empty) {
    mode = LEVEL_EDITOR;
    editorGrid.clear();
    playerCount = 1;
    enemyCount = 1000000;
    unmovableEnemyCount = 2000000;
    //levelEdit orSaves.clear();
    assert(loadFromLevel >= 0);
    if(empty) {
        editorGrid.resize(20, deque<int>(20, 0));
    }
    else {
        createLevels();
        editorGrid = levels[loadFromLevel];
        for(int i = 0; i < editorGrid.size(); ++i) {
            for(int j = 0; j < editorGrid[i].size(); ++j) {
                if(getCellType(editorGrid[i][j]) == PLAYER && playerCount < editorGrid[i][j] + 1) playerCount = editorGrid[i][j] + 1;
                if(getCellType(editorGrid[i][j]) == ENEMY && enemyCount < editorGrid[i][j] + 1) enemyCount = editorGrid[i][j] + 1;
                if(getCellType(editorGrid[i][j]) == UNMOVABLE_ENEMY && unmovableEnemyCount < editorGrid[i][j] + 1) unmovableEnemyCount = editorGrid[i][j] + 1;
            }
        }
        
        extendGridToFit(editorGrid, 20, 20);
        //editorGridY = editorGrid.size();
        //editorGridX = editorGrid[0].size();
    }
    tilesToBePlaced.clear();
    placeType = ENEMY; //!START KEYTYPE
}

#endif
