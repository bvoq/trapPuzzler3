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

int playerCount = 1, enemyCount = 1000000, unmovableEnemyCount = 2000000, loveCount = 3000000; //These values will be overwritten...
cellType placeType;

void changeBrush (cellType newPlaceType) {
    placeType = newPlaceType;
}

set<pair<int, int> > tilesToBePlaced;
vector<deque<deque<int> > > levelEditorSaves;

deque<deque<int> > improveLevel(deque<deque<int> > lvl, bool hasGravity, int tries, int maxBreadth);
void improveLevelEditor(){
	assert(editorGrid.size() != 0);
	int topRows = 0, botRows = 0, leftRows = 0, rightRows = 0;
	
	auto tempEditGrid = editorGrid;
	bool doneSearchingSpaces = false;
	for(int i = 0, doneSearchingSpaces = false; i < editorGrid.size() && !doneSearchingSpaces; ++i){
		for(int j = 0; j < editorGrid[0].size(); ++j){
			if(getCellType(editorGrid[i][j]) != cellType.AIR){
				doneSearchingSpaces = true;
				break;
			}
		}
		topRows = i+1;
	}
	for(int i = editorGrid.size()-1, doneSearchingSpaces = false; i >= 0 && !doneSearchingSpaces; --i){
		for(int j = 0; j < editorGrid[0].size(); ++j){
			if(getCellType(editorGrid[i][j]) != cellType.AIR){
				doneSearchingSpaces = true;
				break;
			}
		}
		botRows = editorGrid.size()-1-(i-1);
	}
	for(int j = 0, doneSearchingSpaces = false; j < editorGrid[0].size() && !doneSearchingSpaces; ++j){
		for(int i = 0; i < editorGrid.size(); ++i){
			if(getCellType(editorGrid[i][j]) != cellType.AIR){
				doneSearchingSpaces = true;
				break;
			}
		}
		leftRows = j+1;
	} 
	for(int j = editorGrid[0].size()-1, doneSearchingSpaces = false; j >= 0 && !doneSearchingSpaces; --j)
		for(int i = 0; i < editorGrid.size(); ++i){
			if(getCellType(editorGrid[i][j]) != cellType.AIR){
				doneSearchingSpaces = true;
				break;
			}
		}
		rightRows = editorGrid[0].size()-1-(j-1);
	}
	cropBordersOf(editorGrid);
	editorGrid = improveLevel(editorGrid, true, 100, 4096*16);
	for(int i = 0; i < topRows; ++i) pushFrontRowOf(editorGrid);
	for(int i = 0; i < botRows; ++i) pushBackRowOf(editorGrid);
	for(int i = 0; i < leftRows; ++i) pushFrontColumnOf(editorGrid);
	for(int i = 0; i < rightRows; ++i) pushBackColumnOf(editorGrid);
	
	if(editorGrid != tempEditGrid) levelEditorSaves.push_back(tempEditGrid);
}

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
    else if(placeType == LOVE) {
        placeID = loveCount;
        loveCount++;
    }
    else if(placeType == GRAVITYMONSTEREYE) {
        placeID = GRAVITYMONSTEREYEID;
        // there can only be one gravity monster.
    }
    else if(placeType == GRAVITYMONSTERMOUTH) {
        placeID = GRAVITYMONSTERMOUTHID;
        // there can only be one gravity monster.
    }
    for(auto & it : tilesToBePlaced) {
        if(placeID == 0) {
            bool otherOnes = false;
            for(int i = 0; i < editorGrid.size(); ++i) {
                for(int j = 0; j < editorGrid[i].size(); ++j) {
                    if(! (it.first == i && it.second == j) && editorGrid[i][j] == editorGrid[it.first][it.second]) otherOnes = true;
                }
            }
            
            //CHANGE RANGE (currently for PLAYER, ENEMY, UNMOVABLE_ENEMY, LOVE)
            if(otherOnes == false) {
                int pos = editorGrid[it.first][it.second];
                pair<int, int> changeRange;
                if(pos > 0 && pos < 1000000) {changeRange = {pos, 1000000}; playerCount--;}
                else if(pos >= 1000000 && pos < 2000000) {changeRange = {pos, 2000000}; enemyCount--;}
                else if(pos >= 2000000 && pos < 3000000) {changeRange = {pos, 3000000}; unmovableEnemyCount--;}
                else if(pos >= 3000000 && pos < 4000000) {changeRange = {pos, 4000000}; loveCount--;}
            
                for(int i = 0; i < editorGrid.size(); ++i) {
                    for(int j = 0; j < editorGrid[i].size(); ++j) {
                        if(editorGrid[i][j] > changeRange.first && editorGrid[i][j] < changeRange.second) editorGrid[i][j]--;
                    }
                }
            }
        }
        
        if(placeType == GRAVITYMONSTERMOUTH) {
            if(it.second+2 < editorGrid[it.first].size()) editorGrid[it.first][it.second+2] = placeID;
        }
        else editorGrid[it.first][it.second] = placeID;
    }
    
    tilesToBePlaced.clear();
}

void undoLevelEditorMove() {
    if(levelEditorSaves.size() > 0) {
        editorGrid = levelEditorSaves.back();
        levelEditorSaves.pop_back();
    }
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
            if(isMousePressed && mousetouchX >= rects[i][j].getTopLeft().x &&
               mousetouchY >= rects[i][j].getTopLeft().y &&
               mousetouchX < rects[i][j].getBottomRight().x &&
               mousetouchY < rects[i][j].getBottomRight().y) {
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
                else if(cT == LOVE) ofSetColor(scheme.colorLOVE);
                else if(cT == GRAVITYMONSTERMOUTH) ofSetColor(0);
                else if(cT == GRAVITYMONSTEREYE) ofSetColor(255,255,255);
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
                else if(cT == LOVE) ofSetColor(scheme.colorLOVESTROKE);
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
    loveCount = 3000000;
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
                if(getCellType(editorGrid[i][j]) == LOVE && loveCount < editorGrid[i][j]+1) loveCount = editorGrid[i][j] + 1;
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
