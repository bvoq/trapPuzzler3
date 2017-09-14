//
//  movement.h
//  trapStory2
//
//  Created by Kivifreak on 28/12/15.
//
//

#ifndef trapPuzzler3_movement_h
#define trapPuzzler3_movement_h


#include <iostream>
using namespace std;

void checkForMerge(ddd &, int &);
void recheckGrid();

//from b to c, starting at time t taking d time.

float easeInQuad (float t,float b , float c, float d) {
    return c*(t/=d)*t + b;
}
float easeOutQuad(float t,float b , float c, float d) {
    return -c *(t/=d)*(t-2) + b;
}

float easeInOutQuad(float t,float b , float c, float d) {
    t /= d/2;
    if (t < 1) return c/2*t*t + b;
    t--;
    return -c/2 * (t*(t-2) - 1) + b;
}

float easeInOutTripple(float t, float b, float c, float d) {
    if ((t/=d/2) < 1) return c/2*t*t*t + b;
    return c/2*((t-=2)*t*t + 2) + b;
}

float easeInOutQuint(float t,float b , float c, float d) {
    if ((t/=d/2) < 1) return c/2*t*t*t*t*t + b;
    return c/2*((t-=2)*t*t*t*t + 2) + b;
}

float easeInOutElastic(float t,float b , float c, float d) {
    if (t==0) return b;  if ((t/=d/2)==2) return b+c;
    float p=d*(.3f*1.5f);
    float a=c;
    float s=p/4;
    
    if (t < 1) {
        float postFix =a*pow(2,10*(t-=1)); // postIncrement is evil
        return -.5f*(postFix* sin( (t*d-s)*(2*PI)/p )) + b;
    }
    float postFix =  a*pow(2,-10*(t-=1)); // postIncrement is evil
    return postFix * sin( (t*d-s)*(2*PI)/p )*.5f + c + b;
}

float easeInOutSine(float t,float b , float c, float d) {
    return -c/2 * (cos(PI*t/d) - 1) + b;
}


#ifndef islevelgen
struct movement {
    long long timeWhenStarted;
    deque<deque<int> > newGrid, oldGrid, newEyeGrid, oldEyeGrid;
    keyType movementDirection;
    set<int> hasMoved;
    bool isUndoMove;
    int movementTime;
    int oldPlayerID;
    bool gravityMove;
    movement(deque<deque<int> > _nG, deque<deque<int> > _oG, deque<deque<int> > _nEG, deque<deque<int> > _oEG,
             keyType _mD, set<int> _hM, bool _isUndoMove, int _movementTime, bool _gravityMove) {
        newGrid = _nG;
        oldGrid = _oG;
        newEyeGrid = _nEG;
        oldEyeGrid = _oEG;
        movementDirection = _mD;
        hasMoved = _hM;
        timeWhenStarted = ofGetElapsedTimeMicros();
        isUndoMove = _isUndoMove;
        movementTime = _movementTime;
        oldPlayerID = playerID;
        gravityMove = _gravityMove;
    }
    
    void changeGrid() {
        grid = newGrid;
        eyeGrid = newEyeGrid;
        recheckGrid();
        if(renderMode == PARTIAL) switchRenderMode(PARTIAL);
    }
    
    float getDelay() {
        return ofGetElapsedTimeMicros() - timeWhenStarted;
    }
    
    bool isUsed = false;
    ofRectangle calculatePosition(int i, int j) {
        if(!isUsed) {
            if(!blockMovementDueToWinningAnimation && !isUndoMove && !gravityMove) playMoveSound();
            else if(!blockMovementDueToWinningAnimation && isUndoMove && !gravityMove) playUndoSound();
            isUsed = true;
        }
        float gD = getDelay();
        
        float idY = i; float idX = j;
        float sign = 1;
        int gridY = grid.size(), gridX = grid[0].size(), newGridY = newGrid.size(), newGridX = newGrid[0].size();
        
        if(movementDirection == UP && newGridY > gridY) sign = -1;
        if(movementDirection == LEFT && newGridX > gridX) sign = -1;
        if(movementDirection == DOWN && newGridY < gridY) sign = -1;
        if(movementDirection == RIGHT && newGridX < gridX) sign = -1;
        
        float incr = gD / movementTime;
        if(incr > 1.0) incr = 1.0;
        int w = getWidth(), h = getHeight();
        float compGridY = gridY + sign * (1.*(newGridY - gridY)) * incr;
        float compGridX = gridX + sign * (1.*(newGridX - gridX)) * incr;
        
        float compGrid2Y = gridY +   (1.*(newGridY - gridY)) * incr;
        float compGrid2X = gridX +   (1.*(newGridX - gridX)) * incr;
        
        float theAdd = 2;
        if(sign == -1) theAdd = 2;
        float scaleY = (h * 1.) / (MAX(compGrid2Y + theAdd, MIN_CELL_SIZE) * 1.);
        float scaleX = (w * 1.) / (MAX(compGrid2X + theAdd, MIN_CELL_SIZE) * 1.);
        float scale = min(scaleY, scaleX);
        
        idY -= (compGridY) / 2.;
        idX -= (compGridX) / 2.;
        
        ofRectangle output(idX * scale, idY * scale, scale, scale);
        output.translate(w / 2, h / 2);
        
        //Add movement delay
        
        
        if(hasMoved.count(grid[i][j]) != 0) {
            //easeInOutQuad();
            if(gravityMove || blockMovementDueToWinningAnimation) {
                //alternative try easeInQuad(getDelay(),0.,1.,movementTime)
                if(movementDirection == UP) output.y -= incr * scale;
                else if(movementDirection == DOWN) output.y += incr * scale;
                else if(movementDirection == LEFT) output.x -= incr * scale;
                else if(movementDirection == RIGHT) output.x += incr * scale;
            }
            if(!gravityMove) {
                if(movementDirection == UP) output.y -= easeInOutQuad(getDelay(),0.,1.,movementTime) * scale;
                else if(movementDirection == DOWN) output.y += easeInOutQuad(getDelay(),0.,1.,movementTime) * scale;
                else if(movementDirection == LEFT) output.x -= easeInOutQuad(getDelay(),0.,1.,movementTime) * scale;
                else if(movementDirection == RIGHT) output.x += easeInOutQuad(getDelay(),0.,1.,movementTime) * scale;
            }
        }
        return output;
    }
};

deque<movement> movements;
vector<movement> previousMovements;

void checkMovement() {
    if(movements.size() != 0) {
        if(movements.front().getDelay() > movements.front().movementTime) {
            movements.front().changeGrid();
            if(movements.front().isUndoMove == false) previousMovements.push_back(movements.front());
            movements.pop_front();
            movements.front().timeWhenStarted = ofGetElapsedTimeMicros();
            recheckGrid();
            if(renderMode == PARTIAL) switchRenderMode(PARTIAL);
        }
    }
}

void undoMovement(long long maxtime) {
    if((movements.size() == 0 || movements.back().isUndoMove) && previousMovements.size() != 0) {
        forceUndo = false;
        bool lastGravity = false;
        do {
            keyType oppositeKeyType;
            if(previousMovements.back().movementDirection == UP) oppositeKeyType = DOWN;
            else if(previousMovements.back().movementDirection == DOWN) oppositeKeyType = UP;
            else if(previousMovements.back().movementDirection == LEFT) oppositeKeyType = RIGHT;
            else if(previousMovements.back().movementDirection == RIGHT) oppositeKeyType = LEFT;
            
            cropBordersOfBoth(previousMovements.back().oldGrid, previousMovements.back().oldEyeGrid);
            //cropBordersOf(previousMovements.back().oldEyeGrid);
            
            moveGrid = previousMovements.back().oldGrid;
            playerID = previousMovements.back().oldPlayerID;
            lastGravity = previousMovements.back().gravityMove;
            moveEyeGrid = previousMovements.back().oldEyeGrid;
            movement undoMove(previousMovements.back().oldGrid, previousMovements.back().newGrid,
                          previousMovements.back().oldEyeGrid, previousMovements.back().newEyeGrid,
                          oppositeKeyType, previousMovements.back().hasMoved, true,
                          MIN(maxtime,previousMovements.back().movementTime), previousMovements.back().gravityMove);
            movements.push_back(undoMove);
            previousMovements.pop_back();
        } while(lastGravity);
        
    }
}
#endif

int moveTile(ddd & moveGrid, ddd & moveEyeGrid, int elementId, keyType& input, set<int>& checked, ddd & tempGrid, set<pair<int, int> >& eyesToChange, bool solver) {
    checked.insert(elementId);
    for(int k = 0; k < tempGrid.size(); ++k) {
        for(int l = 0; l < tempGrid[k].size(); ++l) {
            if(moveGrid[k][l] == elementId) {
                moveGrid[k][l] = 0;
                if(!solver) if(moveEyeGrid[k][l] != 0) eyesToChange.insert({k,l});
            }
        }
    }
    for(int k = 0; k < tempGrid.size(); ++k) {
        for(int l = 0; l < tempGrid[k].size(); ++l) {
            if(tempGrid[k][l] == elementId) {
                int i, j;
                if(input == UP) {i = k - 1; j = l;}
                else if(input == DOWN) {i = k + 1; j = l;}
                else if(input == LEFT) {i = k; j = l - 1;}
                else if(input == RIGHT) {i = k; j = l + 1;}
                else assert(false);
                cellType cT = getCellType(moveGrid[i][j]);
                int cB = 0;
                if(cT == ENEMY || cT == PLAYER || cT == LOVE) cB = moveTile(moveGrid, moveEyeGrid, moveGrid[i][j], input, checked, tempGrid, eyesToChange, solver);
                else if(cT == UNMOVABLE_ENEMY || cT == GRAVITYMONSTERMOUTH || cT == GRAVITYMONSTEREYE || cT == GRAVITYMONSTERDEADEYE) return -1;
                else if(cT != AIR) assert(false);
                if(cB == -1) return -1;
                moveGrid[i][j] = elementId;
                tempGrid[k][l] = 0;
            }
        }
    }
    return 0;
}

//returns a set with the blocks affected by gravity. currentlychecking makes sure no infinite loops happen.
bool affectGravity(ddd & moveGrid, ddd & moveEyeGrid, int elementId, keyType& gravityDirection, set<int>& checked, set<int>& currentlyChecking, set<int> &
                   affectedByGravity, set<pair<int,int> > & affectedEyes, bool solver ) {
    assert(elementId != 0);
    if(checked.count(elementId) != 0) return affectedByGravity.count(elementId) != 0;
    
    currentlyChecking.insert(elementId);
    bool isAffected = (getCellType(elementId) == PLAYER || getCellType(elementId) == ENEMY || getCellType(elementId) == LOVE);
    vector<pair<int,int> > eyePositions;
    for(int k = 0; k < moveGrid.size() && isAffected; ++k) {
        for(int l = 0; l < moveGrid[k].size() && isAffected; ++l) {
            if(moveGrid[k][l] == elementId) {
                int i = k, j = l;
                if     (gravityDirection == UP) i--;
                else if(gravityDirection == DOWN) i++;
                else if(gravityDirection == LEFT) j--;
                else if(gravityDirection == RIGHT) j++;
                else assert(false);
                if(!solver) if(moveEyeGrid[k][l] != 0) eyePositions.push_back({k,l});
                
                if(moveGrid[i][j] != elementId && currentlyChecking.count(moveGrid[i][j])==0) { //currentlyChecking prevents infinite loops
                    cellType cT = getCellType(moveGrid[i][j]);
                    if(cT == ENEMY || cT == PLAYER || cT == LOVE) isAffected = affectGravity(moveGrid, moveEyeGrid, moveGrid[i][j], gravityDirection, checked, currentlyChecking, affectedByGravity, affectedEyes, solver);
                    else if(cT == UNMOVABLE_ENEMY || cT == GRAVITYMONSTERMOUTH || cT == GRAVITYMONSTEREYE || cT == GRAVITYMONSTERDEADEYE) isAffected = false;
                    else if(cT != AIR) assert(false);
                }
            }
        }
    }
    currentlyChecking.erase(elementId);
    checked.insert(elementId);
    if(isAffected) {
        affectedByGravity.insert(elementId);
        if(!solver) {
            for(int i = 0; i < eyePositions.size(); ++i) affectedEyes.insert(eyePositions[i]);
            eyePositions.clear();
        }
    }
    return isAffected;
}

//WILL NOT CALL THE GLOBAL MOVEGRID or playerID so it can be used with the solver!
bool move(ddd & moveGrid, ddd & moveEyeGrid, int & playerID, keyType input, long long timeAllowed, bool solver, bool possibleGravity) {
    //INSTEAD CHECK THE TOP OF
    //moveGridX = gridX;
    //moveGridY = gridY;
    //moveGrid = grid;
    deque<deque<int> > oldGrid = moveGrid;
    deque<deque<int> > oldEyeGrid = moveEyeGrid;
    
    if(input == UP) pushFrontRowOf(moveGrid);
    else if(input == DOWN) pushBackRowOf(moveGrid);
    else if(input == LEFT) pushFrontColumnOf(moveGrid);
    else if(input == RIGHT) pushBackColumnOf(moveGrid);
    
    #ifndef islevelgen
    if(!solver) {
        if(input == UP) pushFrontRowOf(moveEyeGrid);
        else if(input == DOWN) pushBackRowOf(moveEyeGrid);
        else if(input == LEFT) pushFrontColumnOf(moveEyeGrid);
        else if(input == RIGHT) pushBackColumnOf(moveEyeGrid);
    }
    #endif
    
    deque<deque<int> > tempGrid = moveGrid;
    
    set<int> checked;
    set<pair<int, int> > eyesToChange;
    int theReturn = moveTile(moveGrid, moveEyeGrid, playerID, input, checked, tempGrid, eyesToChange, solver);
    
    if(theReturn != -1) {
        //Move eyes
        int yTrans = 0, xTrans = 0;
        if(input == UP) yTrans = -1;
        else if(input == DOWN) yTrans = 1;
        else if(input == LEFT) xTrans = -1;
        else if(input == RIGHT) xTrans = 1;
        
        #ifndef islevelgen
        if(!solver) {
            vector<int> eyeColor;
            for(auto it : eyesToChange) {
                eyeColor.push_back(moveEyeGrid[it.first][it.second]);
                moveEyeGrid[it.first][it.second] = 0;
            }
            int i = 0;
            for(auto it : eyesToChange) {
                moveEyeGrid[it.first+yTrans][it.second+xTrans] = eyeColor[i++];
            }
            cropBordersOfBoth(moveGrid, moveEyeGrid);
        }
        else
        #else
            cropBordersOf(moveGrid);
        #endif
        if(possibleGravity) {
            //Extend monsters after cropping (maximum by one):
            for(int i = 0; i < moveGrid.size(); ++i) {
                for(int j = 0; j < moveGrid[i].size(); ++j) {
                    if((i+1 == moveGrid.size()-1 && moveGrid[i+1][j] == GRAVITYMONSTERMOUTHID) || (i-1 == 0 && moveGrid[i-1][j] == GRAVITYMONSTERMOUTHID)) {
                        if(moveGrid[i][j] == AIR) {
                            moveGrid[i][j] = GRAVITYMONSTERMOUTHID;
                        }
                    }
                }
            }
        }
        checkForMerge(moveGrid,playerID);
        #ifndef islevelgen
        if(!solver) {
            movement newMovement(moveGrid, oldGrid, moveEyeGrid, oldEyeGrid, input, checked, false, timeAllowed, false);
            movements.push_back(newMovement);
        }
        #endif
        checked.clear();

        bool hasEyeAndThereforeGravity = false;
        int positionOfGravityMonsterX = -1;
        if(possibleGravity) {
            for(int i = 0; i < moveGrid.size(); ++i) {
                for(int j = 0; j < moveGrid[i].size(); ++j) {
                    if(getCellType(moveGrid[i][j]) == GRAVITYMONSTERMOUTH) positionOfGravityMonsterX = j;
                    if(getCellType(moveGrid[i][j]) == GRAVITYMONSTEREYE) hasEyeAndThereforeGravity = true;
                }
            }
        }
        
        if(hasEyeAndThereforeGravity) { //asserts gravity.
            set<int> checked, currentlyChecking, affectedByGravity; set<pair<int,int> > affectedEyes;
            int gravityMaxCount = 100;
            keyType gravityDirection = RIGHT; //always to the right as of now.
            
            double velocity = 1./timeAllowed; //from here acceleration will take over.
            do {
                
                for(int i = 0; i < moveGrid.size(); ++i) {
                    for(int j = 0; j < moveGrid[i].size(); ++j) {
                        if(getCellType(moveGrid[i][j]) == GRAVITYMONSTERMOUTH) positionOfGravityMonsterX = j;
                        if(getCellType(moveGrid[i][j]) == GRAVITYMONSTEREYE) hasEyeAndThereforeGravity = true;
                    }
                }
                
                if(positionOfGravityMonsterX-1 >= 0) {
                    for(int i = 0; i < moveGrid.size(); ++i) {
                        
                        if(getCellType(moveGrid[i][positionOfGravityMonsterX]) == GRAVITYMONSTERMOUTH) {
                            if(getCellType(moveGrid[i][positionOfGravityMonsterX-1]) == PLAYER
                               || getCellType(moveGrid[i][positionOfGravityMonsterX-1]) == ENEMY
                               || getCellType(moveGrid[i][positionOfGravityMonsterX-1]) == LOVE) {
                                if(getCellType(moveGrid[i][positionOfGravityMonsterX-1]) == PLAYER) {
                                    bool mustUndo = true;
                                    for(int k = 0; k < moveGrid.size(); ++k) {
                                        for(int l = 0; l < moveGrid[k].size(); ++l) {
                                            if(!(k == i && l == positionOfGravityMonsterX-1) && moveGrid[i][positionOfGravityMonsterX-1] == moveGrid[k][l]) {
                                                mustUndo = false; //Only gets triggered if all movements are false.
                                            }
                                        }
                                    }
                                    if(solver && mustUndo) return false;
                                    else forceUndo = mustUndo;
                                }
                                moveGrid[i][positionOfGravityMonsterX-1] = 0;
                            }
                        }
                        else if(positionOfGravityMonsterX-2 >= 0 && getCellType(moveGrid[i][positionOfGravityMonsterX-2]) == GRAVITYMONSTEREYE) {
                            if(positionOfGravityMonsterX-3 >= 0 && (getCellType(moveGrid[i][positionOfGravityMonsterX-3]) == PLAYER
                               || getCellType(moveGrid[i][positionOfGravityMonsterX-3]) == ENEMY
                               || getCellType(moveGrid[i][positionOfGravityMonsterX-3]) == LOVE)) {
                                //moveGrid[i][positionOfGravityMonsterX] = GRAVITYMONSTERDEADEYEID;
                            }
                        }
                        else if(positionOfGravityMonsterX-2 >= 0 && getCellType(moveGrid[i][positionOfGravityMonsterX-2]) == GRAVITYMONSTERDEADEYE) {}
                        else {
                            cout << "Unexpected celltype: " << getCellType(moveGrid[i][positionOfGravityMonsterX]) << " at location (" << i << "," << positionOfGravityMonsterX << ")" << endl;
                            for(int i = 0; i < moveGrid.size(); ++i) {
                                for(int j = 0; j < moveGrid[i].size(); ++j) {
                                    cout << j << ":" << moveGrid[i][j] << ",";
                                }
                                cout << endl;
                            }
                            //assert(false);
                        } //should only be filled by GRAVITYMONSTERMOUTH and GRAVITYMONSTEREYE
                    }
                }
                
                oldGrid = moveGrid;
                oldEyeGrid = moveEyeGrid;
                checked.clear(); affectedByGravity.clear(); affectedEyes.clear(); currentlyChecking.clear();
                if(gravityDirection == UP) pushFrontRowOf(moveGrid);
                else if(gravityDirection == DOWN) pushBackRowOf(moveGrid);
                else if(gravityDirection == LEFT) pushFrontColumnOf(moveGrid);
                else if(gravityDirection == RIGHT) pushBackColumnOf(moveGrid);
                
                if(gravityDirection == UP) pushFrontRowOf(moveEyeGrid);
                else if(gravityDirection == DOWN) pushBackRowOf(moveEyeGrid);
                else if(gravityDirection == LEFT) pushFrontColumnOf(moveEyeGrid);
                else if(gravityDirection == RIGHT) pushBackColumnOf(moveEyeGrid);
                
                for(int i = 0; i < moveGrid.size(); ++i) {
                    for(int j = 0; j < moveGrid[i].size(); ++j) {
                        if(moveGrid[i][j] != 0) affectGravity(moveGrid, moveEyeGrid, moveGrid[i][j], gravityDirection, checked, currentlyChecking, affectedByGravity, affectedEyes, solver);
                    }
                }
                tempGrid = moveGrid;
                
                for(int i = 0; i < moveGrid.size(); ++i) {
                    for(int j = 0; j < moveGrid[i].size(); ++j) {
                        if(affectedByGravity.count(moveGrid[i][j]) != 0) tempGrid[i][j] = 0;
                    }
                }
                
                yTrans = 0, xTrans = 0;
                if(gravityDirection == UP) yTrans = -1;
                else if(gravityDirection == DOWN) yTrans = 1;
                else if(gravityDirection == LEFT) xTrans = -1;
                else if(gravityDirection == RIGHT) xTrans = 1;
                
                for(int i = 0; i < moveGrid.size(); ++i) {
                    for(int j = 0; j < moveGrid[i].size(); ++j) {
                        if(affectedByGravity.count(moveGrid[i][j]) != 0) {
                            tempGrid[i+yTrans][j+xTrans] = moveGrid[i][j];
                        }
                    }
                }
                
                moveGrid = tempGrid;
                
                #ifndef islevelgen
                if(!solver) {
                    vector<int> eyeColor;
                    for(auto it : affectedEyes) {
                        eyeColor.push_back(moveEyeGrid[it.first][it.second]);
                        moveEyeGrid[it.first][it.second] = 0;
                    }
                    int i = 0;
                    for(auto it : affectedEyes) {
                        moveEyeGrid[it.first+yTrans][it.second+xTrans] = eyeColor[i++];
                    }
                    cropBordersOfBoth(moveGrid, moveEyeGrid);
                } else
                #else
                    cropBordersOf(moveGrid);
                #endif
                
                checkForMerge(moveGrid,playerID);
                #ifndef islevelgen
                if(!solver && affectedByGravity.size() > 0) {
                    movement newGravityMovement(moveGrid, oldGrid, moveEyeGrid, oldEyeGrid, gravityDirection, affectedByGravity, false, (long long)(1./velocity), true);
                    movements.push_back(newGravityMovement);
                    velocity += gravityAcceleration - gravityStokesFriction*velocity - gravityQuadraticFriction*velocity*velocity;
                }
                #endif
            } while(affectedByGravity.size() > 0 && gravityMaxCount-->0);
            if(solver && affectedByGravity.size()!=0) return false;
            
            #ifndef islevelgen
            while(affectedByGravity.size()!=0 && movements.size() > 10 && affectedByGravity == movements.back().hasMoved) {
                moveGrid = movements.back().oldGrid;
                moveEyeGrid = movements.back().oldEyeGrid;
                movements.pop_back();
            }
            #endif
            
        }
        return true;
    }
    else {
        moveGrid = oldGrid;
        moveEyeGrid = oldEyeGrid;
        return false;
    }
}

#ifndef islevelgen
void changePlayerId(int i) {
    playerID = i;
    if(renderMode == PARTIAL) switchRenderMode(PARTIAL);
    //checkForMerge();
}
#endif

int changePlayerIdDeterministic(deque<deque<int> > & moveGrid, int playerID, bool solver) {
    set<int> playerIDs;
    for(int i = 0; i < moveGrid.size(); ++i) {
        for(int j = 0; j < moveGrid[i].size(); ++j) {
            if (getCellType(moveGrid[i][j]) == PLAYER) {
                playerIDs.insert(moveGrid[i][j]);
            }
        }
    }
    
    if(playerIDs.size() == 0) return playerID;
    if(playerIDs.size() == 1) {
        #ifndef islevelgen
        if(!solver) changePlayerId(*playerIDs.begin());
        #endif
        return *playerIDs.begin();
    }
    bool next = false;
    for(auto c : playerIDs) {
        if(next) {
            #ifndef islevelgen
            if(!solver) changePlayerId(c);
            #endif
            return c;
        }
        if(c == playerID) next = true;
    }
    #ifndef islevelgen
    if(!solver) changePlayerId(*playerIDs.begin());
    #endif
    return *playerIDs.begin();
}

void checkForMerge(deque<deque<int> > & moveGrid, int & playerID) {
    for(int i = 0; i < moveGrid.size(); ++i) {
        for(int j = 0; j < moveGrid[i].size(); ++j) {
            if(getCellType(moveGrid[i][j]) == PLAYER || getCellType(moveGrid[i][j]) == LOVE) {
                //CHANGE PLAYERID
                if(i != 0 && getCellType(moveGrid[i-1][j]) == PLAYER && moveGrid[i-1][j] != moveGrid[i][j]) {
                    int toReplaceID = moveGrid[i][j];
                    for(int k = 0; k < moveGrid.size(); ++k) {
                        for(int l = 0; l < moveGrid[k].size(); ++l) {
                            if(moveGrid[k][l] == toReplaceID) moveGrid[k][l] = moveGrid[i-1][j];
                        }
                    }
                    if(toReplaceID == playerID) playerID = moveGrid[i-1][j];
                }
                if(i+1 < moveGrid.size() && getCellType(moveGrid[i+1][j]) == PLAYER && moveGrid[i+1][j] != moveGrid[i][j]) {
                    int toReplaceID = moveGrid[i][j];
                    for(int k = 0; k < moveGrid.size(); ++k) {
                        for(int l = 0; l < moveGrid[k].size(); ++l) {
                            if(moveGrid[k][l] == toReplaceID) moveGrid[k][l] = moveGrid[i+1][j];
                        }
                    }
                    if(toReplaceID == playerID) playerID = moveGrid[i+1][j];
                }
                if(j != 0 && getCellType(moveGrid[i][j-1]) == PLAYER && moveGrid[i][j-1] != moveGrid[i][j]) {
                    int toReplaceID = moveGrid[i][j];
                    for(int k = 0; k < moveGrid.size(); ++k) {
                        for(int l = 0; l < moveGrid[k].size(); ++l) {
                            if(moveGrid[k][l] == toReplaceID) moveGrid[k][l] = moveGrid[i][j-1];
                        }
                    }
                    if(toReplaceID == playerID) playerID =  moveGrid[i][j-1];
                }
                if(j+1 < moveGrid[i].size() && getCellType(moveGrid[i][j+1]) == PLAYER && moveGrid[i][j+1] != moveGrid[i][j]) {
                    int toReplaceID = moveGrid[i][j];
                    for(int k = 0; k < moveGrid.size(); ++k) {
                        for(int l = 0; l < moveGrid[k].size(); ++l) {
                            if(moveGrid[k][l] == toReplaceID) moveGrid[k][l] = moveGrid[i][j+1];
                        }
                    }
                    if(toReplaceID == playerID) playerID =  moveGrid[i][j+1];
                }
            }
        }
    }

}
#endif
