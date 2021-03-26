#include "puzzleSolver.h"


#include "globals.h"
#include "grid.h"
#include "keyMap.h"
#include "movement.h"

//#include "hopscotch_set.h"

//Set hasGravity = true, if uncertain.
//returns -1 = UNSOLVABLE, non-negative = Number of steps used to compute the solution , -2 = UNKNOWN (not fully computed), -3 = ERROR, such as no player
bool winState(deque<deque<int> > &,bool);
int newSolver(ddd gridtosolve, bool hasGravity, vector<keyType> & solution, int maxComputationFields) {
    set<pair<ddd,int> > computed; //<*,THIS> :=  ID of player
    //unordered_set<pair<ddd, int> > computed;
    //tsl::hopscotch_set<pair<ddd, int> > computed(true);
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

#ifndef compiledWithoutOpenframeworks
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
        cout << "It is solvable! Depth: " << solution.size() << " Breadth: " << value << endl;
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

deque<deque<int> > improveLevel(deque<deque<int> > oldLevel, bool hasGravity, int tries, int maxBreadth){
    int placeBlocksRed = 1;
    int placeBlocksDark = 1;
    vector<keyType> bestSol;
    newSolver(oldLevel, hasGravity, bestSol, maxBreadth);
    //cout << "initial lvl: depth " << bestSol.size();
    vector<keyType> sol;
    auto bestLevel = oldLevel;
    int MAXRED = 1000000;
    int MAXBLACK = 2000000;
    for(auto a : oldLevel){
        for(auto b : a){
            if(b < 2000000) MAXRED = MAX(MAXRED, b);
            if(b < 3000000) MAXBLACK = MAX(MAXBLACK, b);
        }
    }
    
    for(int i = 0; i < tries; ++i){
        auto tempImprovedLevel = oldLevel;
        vector< vector<pair<int, int> > > stonesBlack = {
            {{0,0},{0,1}}, {{0,0}}, {{0,0},{1,0}}, {{0,0},{0,1},{1,0},{1,1}}
        };
        vector< vector<pair<int,int> > > stonesRed = stonesBlack;
        
        int darkBlocksToBePlaced = placeBlocksDark;
        int redBlocksToBePlaced = placeBlocksRed;
        int breakTries = 0;
        int h = oldLevel.size();
        int w = oldLevel[0].size();
        if(hasGravity) w -= 2;
        while(darkBlocksToBePlaced != 0 && breakTries < 100) {
            int offsetY = rand() % h; int offsetX = rand() % w;
            int randTile = rand() % stonesBlack.size();
            bool noAdd = false;
            for(int i = 0; i < stonesBlack[randTile].size(); ++i) {
                if(stonesBlack[randTile][i].first + offsetY >= h || stonesBlack[randTile][i].second + offsetX >= w ||
                   tempImprovedLevel[stonesBlack[randTile][i].first + offsetY][stonesBlack[randTile][i].second + offsetX] != 0) {
                    noAdd = true;
                }
            }
            if(noAdd == false) {
                for(int i = 0; i < stonesBlack[randTile].size(); ++i) {
                    tempImprovedLevel[stonesBlack[randTile][i].first + offsetY][stonesBlack[randTile][i].second + offsetX] = MAXBLACK+1+darkBlocksToBePlaced;
                }
                darkBlocksToBePlaced--;
            }
            breakTries++;
        }
        breakTries = 0;
        while(redBlocksToBePlaced !=0 && breakTries < 100) {
            int offsetY = rand() % h; int offsetX = rand() % w;
            int randTile = rand() % stonesRed.size();
            bool noAdd = false;
            for(int i = 0; i < stonesRed[randTile].size(); ++i) {
                if(stonesRed[randTile][i].first + offsetY >= h || stonesRed[randTile][i].second + offsetX >= w ||
                   tempImprovedLevel[stonesRed[randTile][i].first + offsetY][stonesRed[randTile][i].second + offsetX] != 0) {
                    noAdd = true;
                }
            }
            if(noAdd == false) {
                for(int i = 0; i < stonesRed[randTile].size(); ++i) {
                    tempImprovedLevel[stonesRed[randTile][i].first + offsetY][stonesRed[randTile][i].second + offsetX] = MAXRED + 1 +redBlocksToBePlaced;
                }
                redBlocksToBePlaced--;
            }
            breakTries++;
        }
        
        
        
        
        if(newSolver(tempImprovedLevel, hasGravity, sol, maxBreadth) < 0) {
            sol.clear();
            continue;
        }
        if(sol.size() > bestSol.size()){
            bestSol = sol;
            //cout << "new lvl depth: " << sol.size();
            bestLevel = tempImprovedLevel;
        }
        sol.clear();
    }
    //cout << ", now: " << bestSol.size() << endl;
    return bestLevel;
}
