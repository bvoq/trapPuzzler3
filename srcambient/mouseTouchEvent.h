//
//  mouseTouchEvent.h
//  trapPuzzlerIOS
//
//  Created by kdkdk on 22.04.17.
//
//

#ifndef mouseTouchEvent_h
#define mouseTouchEvent_h

//TODO: Assert, that no other movements happen during a movement.
struct playerTouchMovement {
    int y, x;
    int touchid;
    playerTouchMovement() {}
    playerTouchMovement(int _y, int _x, int _touchid) : y(_y), x(_x), touchid(_touchid) {}
};

map<int, playerTouchMovement> playerTouches; //player id of touch.
map<int,pair<int,int> > origMouseTouch;
void mouseTouchDown(int mouseTouchY, int mouseTouchX, int touchid) {
    if(firstMovementHCI) {
        timeMeasuredForHCI = std::chrono::high_resolution_clock::now();

        cout << "Started counter" << endl;
        firstMovementHCI = false;
    }
    if(origMouseTouch.count(touchid) == 0) {
        setRemapKey = !setRemapKey;
        if(!setRemapKey) remapKey = UNKNOWNKEYT;
    }
    
    isMousePressed = true;
    mousePressedY = mouseTouchY;
    mousePressedX = mouseTouchX;
    origMouseTouch.insert({touchid,{mouseTouchY, mouseTouchX}});
    switch(mode) {
        case PLAYING:
        case LEVEL_EDITOR_PLAYING:
        case MAINMENU:
        {
            assert(grid.size() > 0);
            if(grid.size() > 0 && !blockMovementDueToWinningAnimation && !forceUndo) {
                pair<int,int> tilePos = calculateInversePosition(mouseTouchY, mouseTouchX, grid.size(), grid[0].size());
                //If click is in bound.
                if(0 <= tilePos.first && tilePos.first < grid.size() && 0 <= tilePos.second && tilePos.second < grid[0].size())
                {
                    if(getCellType(grid[tilePos.first][tilePos.second]) == PLAYER) {
                        playerTouchMovement newMovement(tilePos.first,tilePos.second,grid[tilePos.first][tilePos.second]);
                        playerTouches.insert({touchid,newMovement});
                        
                        movement m = movement(moveGrid, moveGrid, moveEyeGrid, moveEyeGrid,
                                              CHANGE_TO_PLAYER, {}, false, timeForDragMovement, false, PLAYER_CHANGEMT
                                              );
                        changePlayerId(grid[tilePos.first][tilePos.second]);
                        m.newPlayerID = playerID;
                        movements.push_back(m);
                    }
                }
            }
        }
            break;
        default:
            cout << "Unknown mode " << mode << endl;
    }
    
    
    if(toolbarOrientation == BOTTOMTOOLBAR) {
        if(mode == CREDITS || mode == CONTROL_CHANGE) {
            if(mouseTouchX > (ofGetWidth() - toolbarSize + toolbarSize * 0.05) && mouseTouchX < (ofGetWidth() - toolbarSize * 0.05) && mouseTouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mouseTouchY < ofGetHeight() - toolbarSize * .05) {
                setRemapKey = false;
                keyEvent(RESTART);
            }
        }
        else if(mode == MENU) {
            //RESTART
            if(mouseTouchX > (ofGetWidth() - toolbarSize + toolbarSize * 0.05) && mouseTouchX < (ofGetWidth() - toolbarSize * 0.05) && mouseTouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mouseTouchY < ofGetHeight() - toolbarSize * .05) {
                initMainMenu();
            }
        }
        else if(mode == PLAYING || mode == LEVEL_EDITOR_PLAYING) {
            //UNDO
            if(mouseTouchX > toolbarSize * 0.05 && mouseTouchX < toolbarSize * 0.9 && mouseTouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mouseTouchY < ofGetHeight() - toolbarSize * .05) {
                undoMovement(maxUndoTime);
            }
            //RESTART
            if(mouseTouchX > (ofGetWidth() - toolbarSize + toolbarSize * 0.05) && mouseTouchX < (ofGetWidth() - toolbarSize * 0.05) && mouseTouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mouseTouchY < ofGetHeight() - toolbarSize * .05) {
                restart();
            }
        }
        else if(mode == LEVEL_EDITOR) {
            if(mouseTouchX > toolbarSize * 0.05 && mouseTouchX < toolbarSize * 0.9 && mouseTouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mouseTouchY < ofGetHeight() - toolbarSize * .05) {
                undoLevelEditorMove();
            }
            if(mouseTouchX > toolbarSize * 0.05 + 1*toolbarSize && mouseTouchX < toolbarSize * 0.9 + 1*toolbarSize && mouseTouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mouseTouchY < ofGetHeight() - toolbarSize * .05) {
                changeBrush(PLAYER);
            }
            if(mouseTouchX > toolbarSize * 0.05 + 2*toolbarSize && mouseTouchX < toolbarSize * 0.9 + 2*toolbarSize && mouseTouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mouseTouchY < ofGetHeight() - toolbarSize * .05) {
                changeBrush(ENEMY);
            }
            if(mouseTouchX > toolbarSize * 0.05 + 3*toolbarSize && mouseTouchX < toolbarSize * 0.9 + 3*toolbarSize && mouseTouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mouseTouchY < ofGetHeight() - toolbarSize * .05) {
                changeBrush(UNMOVABLE_ENEMY);
            }
            if(mouseTouchX > toolbarSize * 0.05 + 4*toolbarSize && mouseTouchX < toolbarSize * 0.9 + 4*toolbarSize && mouseTouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mouseTouchY < ofGetHeight() - toolbarSize * .05) {
                changeBrush(LOVE);
            }
            if(mouseTouchX > (ofGetWidth() - 4*toolbarSize + toolbarSize * 0.05) && mouseTouchX < (ofGetWidth() - toolbarSize * 0.05 - 3*toolbarSize) && mouseTouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mouseTouchY < ofGetHeight() - toolbarSize * .05) {
                changeBrush(SUPERAIR);
            }
            if(mouseTouchX > (ofGetWidth() - 3*toolbarSize + toolbarSize * 0.05) && mouseTouchX < (ofGetWidth() - toolbarSize * 0.05 - 2*toolbarSize) && mouseTouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mouseTouchY < ofGetHeight() - toolbarSize * .05) {
                changeBrush(AIR);
            }
            if(mouseTouchX > (ofGetWidth() - 2*toolbarSize + toolbarSize * 0.05) && mouseTouchX < (ofGetWidth() - toolbarSize * 0.05 - toolbarSize) && mouseTouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mouseTouchY < ofGetHeight() - toolbarSize * .05) {
                tilesToBePlaced.clear();
                loadLevel(-1, false);
            }
            
            if(mouseTouchX > (ofGetWidth() - 1*toolbarSize + toolbarSize * 0.05) && mouseTouchX < (ofGetWidth() - toolbarSize * 0.05 - 0*toolbarSize) && mouseTouchY > ofGetHeight() - toolbarSize + toolbarSize * 0.05 && mouseTouchY < ofGetHeight() - toolbarSize * .05) {
                cropBordersOf(editorGrid);
                cout << "SAVING: " << currentLevel << " and " << levels.size() << endl;
                levels[currentLevel] = editorGrid;
                saveLevelData();
                mode = MENU;
            }
        }
    }
    
    
}


void mouseTouchMoved(int mouseTouchY, int mouseTouchX, int touchid) {
    switch(mode) {
        case PLAYING:
        case LEVEL_EDITOR_PLAYING:
        case MAINMENU:
            if(playerTouches.count(touchid) != 0) {
                assert(grid.size() > 0);
                pair<int,int> tilePos = calculateInversePosition(mouseTouchY, mouseTouchX, grid.size(), grid[0].size());
                //cout << "y: " << playerTouches[touchid].y << " x: " << playerTouches[touchid].x << endl;
                //cout << "ty: " << tilePos.first << " tx: " << tilePos.second << endl;
                deque<movement> backupmovements = movements;
                //Can click outside the box.
                size_t oldMoveGridY = moveGrid.size();
                size_t oldMoveGridX = moveGrid[0].size();
                if(tilePos.first == playerTouches[touchid].y-1 && tilePos.second == playerTouches[touchid].x) {
                    if(move(moveGrid, moveEyeGrid, playerID, UP, timeForDragMovement, false, true)) { //Move succeeded
                        if(moveGrid.size()>oldMoveGridY && movements.size() >= 2) {
                            moveEyeGrid = movements.back().oldEyeGrid;
                            moveGrid = movements.back().oldGrid;
                            playerID = movements.back().oldPlayerID;
                            movements.pop_back();
                        }
                        if(moveGrid.size()>oldMoveGridY) tilePos.first = MIN(moveGrid.size()-1,tilePos.first+1);
                    
                        playerTouches[touchid].y = MAX(tilePos.first,0);
                        playerTouches[touchid].x = tilePos.second;
                    }
                }
                if(tilePos.first == playerTouches[touchid].y+1 && tilePos.second == playerTouches[touchid].x) {
                    if(move(moveGrid, moveEyeGrid, playerID, DOWN, timeForDragMovement, false, true)) { //Move succeeded
                        if(moveGrid.size()<oldMoveGridY) tilePos.first = MAX(0,tilePos.first-1);
                        playerTouches[touchid].y = MIN(tilePos.first,moveGrid.size()-1);
                        playerTouches[touchid].x = tilePos.second;
                    }
                }
                if(tilePos.first == playerTouches[touchid].y && tilePos.second == playerTouches[touchid].x-1) {
                    if(move(moveGrid, moveEyeGrid, playerID, LEFT, timeForDragMovement, false, true)) { //Move succeeded
                        if(moveGrid[0].size()>oldMoveGridX && movements.size() >= 2) {
                            moveEyeGrid = movements.back().oldEyeGrid;
                            moveGrid = movements.back().oldGrid;
                            playerID = movements.back().oldPlayerID;
                            movements.pop_back();
                        }
                        if(moveGrid.size()>oldMoveGridY) tilePos.first = MIN(moveGrid.size()-1,tilePos.first+1);
                        
                        if(moveGrid[0].size()>oldMoveGridX) tilePos.second = MIN(moveGrid[0].size()-1,tilePos.second+1);
                        playerTouches[touchid].y = tilePos.first;
                        playerTouches[touchid].x = MAX(tilePos.second,0);
                    }
                }
                if(tilePos.first == playerTouches[touchid].y && tilePos.second == playerTouches[touchid].x+1) {
                    if(move(moveGrid, moveEyeGrid, playerID, RIGHT, timeForDragMovement, false, true)) { //Move succeeded
                        if(moveGrid[0].size()<oldMoveGridX) tilePos.second = MAX(0,tilePos.second-1);
                        playerTouches[touchid].y = tilePos.first;
                        playerTouches[touchid].x = MIN(tilePos.second,moveGrid[0].size());
                    }
                }
                
                //playerTouches[touch.id].x;
            }
            break;
        default:
            cout << "Unknown mode " << mode << endl;
    }
    scrollY =  mouseTouchY - origMouseTouch[touchid].first;
    scrollX =  mouseTouchX - origMouseTouch[touchid].second;
}

void mouseTouchUp(int mouseTouchY, int mouseTouchX, int touchid) {
    //Call as if it moved one last time.
    if(mode == LEVEL_EDITOR) placeSelectedTiles();

    mouseTouchMoved(mouseTouchY, mouseTouchX, touchid);
    
    if(mode == MENU) {
        if(fabs(scrollX) > getWidth()/10.) {
            //do movement in direction
            if(scrollX > getWidth()/10. && (currentLevel/9) * 9 - 9 >= 0) {
                currentLevel = (currentLevel/9) * 9 - 9;
                scrollX -= getWidth();
            }
            else if(scrollX < -getWidth()/10. &&  (currentLevel/9) * 9 + 9 < levels.size()) {
                currentLevel = (currentLevel/9) * 9 + 9;
                scrollX += getWidth();
            }
        }
        
        if(fabs(scrollX) < getWidth()/100.) {
            isMouseReleased = true;
            mouseReleasedX = mouseTouchX;
            mouseReleasedY = mouseTouchY;
        }
        /*
        {
        if(mouseTouchX < getWidth()/3) keyEvent(LEFT);
        if(mouseTouchX > 2*getWidth()/3) keyEvent(RIGHT);
        if(mouseTouchY < getHeight()/3) keyEvent(UP);
        if(mouseTouchY > 2*getHeight()/3) keyEvent(DOWN);
        if(mouseTouchX > getWidth()/3 && mouseTouchX < 2*getWidth()/3 && mouseTouchY > getHeight()/3 && mouseTouchY < 2*getHeight()/3) keyEvent(PLAYER_CHANGE);
        }
        */
    }
    
    
    /* SILLY IDEA
    if(mode == LEVEL_EDITOR) {
        if(abs(scrollX) > getWidth()/10.) {
            if(scrollX < 0) addLayer(LEFT);
            if(scrollX > 0) addLayer(RIGHT);
        }
        if(abs(scrollY) > getWidth()/10.) {
            if(scrollY < 0) addLayer(UP);
            if(scrollY > 0) addLayer(DOWN);
        }
    }*/

    
    //scrollX = 0
    
    isMousePressed = false;

    //Control scheme: Execute move on touch maybe.
    playerTouches.erase(touchid);
    origMouseTouch.erase(touchid);
}

#endif /* mouseTouchEvent_h */
