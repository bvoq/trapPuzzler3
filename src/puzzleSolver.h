//
//  puzzleSolver.h
//  trapStory2
//
//  Created by Kivifreak on 01/01/16.
//
//

#ifndef trapPuzzler3_puzzleSolver_h
#define trapPuzzler3_puzzleSolver_h



//Set hasGravity = true, if uncertain.
//returns -1 = UNSOLVABLE, non-negative = Number of steps used to compute the solution , -2 = UNKNOWN (not fully computed), -3 = ERROR, such as no player
bool winState(deque<deque<int> > &,bool);
int newSolver(ddd gridtosolve, bool hasGravity, vector<keyType> & solution, int maxComputationFields) {
    set<pair<ddd,int> > computed; //<*,THIS> :=  ID of player
    vector<pair<int,keyType> > previousMove; //can then be used to backtrace the solution.
    
    previousMove = vector<pair<int,keyType> >(maxComputationFields);
    queue<pair<ddd,int> > q;
    
    {   // MOVE PLAYER
        int firstPlayer = changePlayerIdDeterministic(gridtosolve, -1,true);
        if(firstPlayer == -1) {
            cout << "No player in the grid: " << firstPlayer << endl;
            return -3;
        }
        
        
        q.push({gridtosolve,firstPlayer});
        computed.insert({gridtosolve,firstPlayer});
    }
    
    int currentPosition = -1, newMovePosition = -1;
    ddd tempEyeGrid = {{0}}; //temporarily used eye grid
    while(q.size() != 0 && newMovePosition < maxComputationFields) {
        assert(!forceUndo);
        pair<ddd,int> current = q.front();
        q.pop();
        pair<ddd,int> left = current, right = current, up = current, down = current, changeplayer = current;
        if(move(left.first, tempEyeGrid, left.second, LEFT, -1, true, hasGravity)) {
            if(computed.count(left) == 0 && newMovePosition + 1 < maxComputationFields) {
                computed.insert(left);
                newMovePosition++;
                previousMove[newMovePosition] = {currentPosition, LEFT};
                if(winState(left.first,false)) {
                    int cm = newMovePosition;
                    while(cm != -1) {
                        solution.push_back(previousMove[cm].second);
                        cm = previousMove[cm].first;
                    }
                    reverse(solution.begin(), solution.end());
                    return newMovePosition;
                }

                q.push(left);
            }
        }
        if(move(right.first, tempEyeGrid, right.second, RIGHT, -1, true, hasGravity)) {
            if(computed.count(right) == 0 && newMovePosition + 1 < maxComputationFields) {
                computed.insert(right);
                newMovePosition++;
                previousMove[newMovePosition] = {currentPosition, RIGHT};
                if(winState(right.first,false)) {
                    int cm = newMovePosition;
                    while(cm != -1) {
                        solution.push_back(previousMove[cm].second);
                        cm = previousMove[cm].first;
                    }
                    reverse(solution.begin(), solution.end());
                    return newMovePosition;
                }
                q.push(right);
            }
        }
        if(move(up.first, tempEyeGrid, up.second, UP, -1, true, hasGravity)) {
            if(computed.count(up) == 0 && newMovePosition + 1 < maxComputationFields) {
                computed.insert(up);
                newMovePosition++;
                previousMove[newMovePosition] = {currentPosition, UP};
                if(winState(up.first,false)) {
                    int cm = newMovePosition;
                    while(cm != -1) {
                        solution.push_back(previousMove[cm].second);
                        cm = previousMove[cm].first;
                    }
                    reverse(solution.begin(), solution.end());
                    return newMovePosition;
                }
                q.push(up);
            }
        }
        if(move(down.first, tempEyeGrid, down.second, DOWN, -1, true, hasGravity)) {
            if(computed.count(down) == 0 && newMovePosition + 1 < maxComputationFields) {
                computed.insert(down);
                newMovePosition++;
                previousMove[newMovePosition] = {currentPosition, DOWN};
                if(winState(down.first,false)) {
                    int cm = newMovePosition;
                    while(cm != -1) {
                        solution.push_back(previousMove[cm].second);
                        cm = previousMove[cm].first;
                    }
                    reverse(solution.begin(), solution.end());
                    return newMovePosition;
                }
                q.push(down);
            }
        }
        
        {
            changeplayer.second = changePlayerIdDeterministic(changeplayer.first,changeplayer.second,true);
            if(computed.count(changeplayer) == 0 && newMovePosition + 1 < maxComputationFields) {
                computed.insert(changeplayer);
                newMovePosition++;
                previousMove[newMovePosition] = {currentPosition, PLAYER_CHANGE};
                //should not make a win state
                q.push(changeplayer);
            }
        }
        currentPosition++;
    }
    if(newMovePosition+1 >= maxComputationFields) return -2; //UNKNOWN
    else return -1; //DEFINETELY UNSOLVABLE
}

#ifndef islevelgen
void keyEvent(keyType);
void solveInGame() {
    bool hasGravity = false;
    for(int i = 0; i < moveGrid.size(); ++i) {
        for(int j = 0; j < moveGrid[i].size(); ++j) {
            if(getCellType(moveGrid[i][j]) == GRAVITYMONSTEREYE) hasGravity = true;
        }
    }
    vector<keyType> solution;
    int value = newSolver(moveGrid, hasGravity, solution, 4096*16);
    if(value >= 0) {
        cout << "It is solvable!" << endl;
        int firstPlayer = changePlayerIdDeterministic(moveGrid, -1,true);
        playerID = firstPlayer; //actually change to that player
        for(int i = 0; i < solution.size(); ++i) {
            cout << strkeytype(solution[i]) << " ";
            keyEvent(solution[i]);
        }
    }
    else if(value == -1) cout << "Unsolvable level" << endl;
    else if(value == -2) cout << "Couldn't compute a solution in time." << endl;
    else cout << "Error when trying to solve the level." << endl;
}
#endif


#endif
