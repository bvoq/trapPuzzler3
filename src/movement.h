//
//  movement.h
//  trapStory2
//
//  Created by Kivifreak on 28/12/15.
//
//

#ifndef trapPuzzler3_movement_h
#define trapPuzzler3_movement_h

int modifyKeys = 3;

#include <iostream>
using namespace std;

void checkForMerge();
struct movement {
    long long timeWhenStarted;
    deque<deque<int> > newGrid, oldGrid, newEyeGrid, oldEyeGrid;
    keyType movementDirection;
    set<int> hasMoved;
    bool isUndoMove;
    int movementTime;
    int oldPlayerID;
    movement(deque<deque<int> > _nG, deque<deque<int> > _oG, deque<deque<int> > _nEG, deque<deque<int> > _oEG,
             keyType _mD, set<int> _hM, bool _isUndoMove, int _movementTime) {
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
    }

    void changeGrid() {
        grid = newGrid;
        eyeGrid = newEyeGrid;
        checkForMerge();
    }

    float getDelay() {
        return ofGetElapsedTimeMicros() - timeWhenStarted;
    }

    ofRectangle calculatePosition(int i, int j) {
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

            if(movementDirection == UP) output.y -= scale * incr;
            else if(movementDirection == DOWN) output.y += scale * incr;
            else if(movementDirection == LEFT) output.x -= scale * incr;
            else if(movementDirection == RIGHT) output.x += scale * incr;
        }
        return output;
    }
};

queue<movement> movements;
vector<movement> previousMovements;

void checkMovement() {
    if(movements.size() != 0) {
        if(movements.front().getDelay() > movements.front().movementTime) {
            movements.front().changeGrid();
            if(movements.front().isUndoMove == false) previousMovements.push_back(movements.front());
            movements.pop();
            movements.front().timeWhenStarted = ofGetElapsedTimeMicros();
            checkForMerge();
        }
    }
}

void undoMovement(int timeAllowed) {
    if(movements.size() == 0 && previousMovements.size() != 0) {
        keyType oppositeKeyType;
        if(previousMovements.back().movementDirection == UP) oppositeKeyType = DOWN;
        else if(previousMovements.back().movementDirection == DOWN) oppositeKeyType = UP;
        else if(previousMovements.back().movementDirection == LEFT) oppositeKeyType = RIGHT;
        else if(previousMovements.back().movementDirection == RIGHT) oppositeKeyType = LEFT;

        cropBordersOfBoth(previousMovements.back().oldGrid, previousMovements.back().oldEyeGrid);
        //cropBordersOf(previousMovements.back().oldEyeGrid);
        movement undoMove(previousMovements.back().oldGrid, previousMovements.back().newGrid,
                          previousMovements.back().oldEyeGrid, previousMovements.back().newEyeGrid,
                          oppositeKeyType, previousMovements.back().hasMoved, true, timeAllowed);

        moveGrid = previousMovements.back().oldGrid;
        moveEyeGrid = previousMovements.back().oldEyeGrid;
        playerID = previousMovements.back().oldPlayerID;
        movements.push(undoMove);
        previousMovements.pop_back();
    }
}

int moveTile(int elementId, keyType& input, set<int>& checked, deque<deque<int> >& tempGrid, set<pair<int, int> >& eyesToChange) {
    checked.insert(elementId);
    for(int k = 0; k < tempGrid.size(); ++k) {
        for(int l = 0; l < tempGrid[k].size(); ++l) {
            if(moveGrid[k][l] == elementId) {
                moveGrid[k][l] = 0;
                if(moveEyeGrid[k][l] != 0) eyesToChange.insert({k,l});
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
                cellType cT = getCellType(moveGrid[i][j]);
                int cB = 0;
                if(cT == ENEMY || cT == PLAYER || cT == LOVE) cB = moveTile(moveGrid[i][j], input, checked, tempGrid, eyesToChange);
                else if(cT == UNMOVABLE_ENEMY) return -1;
                else if(cT != AIR) assert(false);
                if(cB == -1) return -1;
                moveGrid[i][j] = elementId;
                tempGrid[k][l] = 0;
            }
        }
    }
    return 0;
}

bool move(keyType input, int timeAllowed) {
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

    if(input == UP) pushFrontRowOf(moveEyeGrid);
    else if(input == DOWN) pushBackRowOf(moveEyeGrid);
    else if(input == LEFT) pushFrontColumnOf(moveEyeGrid);
    else if(input == RIGHT) pushBackColumnOf(moveEyeGrid);

    deque<deque<int> > tempGrid = moveGrid;

    set<int> checked;
    set<pair<int, int> > eyesToChange;
    int theReturn = moveTile(playerID, input, checked, tempGrid, eyesToChange);

    if(theReturn != -1) {
        //Move eyes
        int yTrans = 0, xTrans = 0;
        if(input == UP) yTrans = -1;
        else if(input == DOWN) yTrans = 1;
        else if(input == LEFT) xTrans = -1;
        else if(input == RIGHT) xTrans = 1;

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
        movement newMovement(moveGrid, oldGrid, moveEyeGrid, oldEyeGrid, input, checked, false, timeAllowed);
        movements.push(newMovement);

        return true;
    }
    else {
        moveGrid = oldGrid;
        moveEyeGrid = oldEyeGrid;
        return false;
    }
}

void changePlayerId(int i) {
    playerID = i;
    if(renderMode == PARTIAL) switchRenderMode(PARTIAL);
    checkForMerge();
}
void changePlayerIdRandom() {
    set<int> playerIDs;
    for(int i = 0; i < moveGrid.size(); ++i) {
        for(int j = 0; j < moveGrid[i].size(); ++j) {
            if (getCellType(moveGrid[i][j]) == PLAYER) {
                playerIDs.insert(moveGrid[i][j]);
            }
        }
    }

    if (playerIDs.size() <= 1) return;
    bool next = false;
    for(auto c : playerIDs) {
        if(next) {
            changePlayerId(c);
            return;
        }
        if(c == playerID) next = true;
    }
    changePlayerId(*playerIDs.begin());
}

void recheckGrid();
void checkForMerge() {
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
    recheckGrid();
    if(renderMode == PARTIAL) switchRenderMode(PARTIAL);
}
#endif
