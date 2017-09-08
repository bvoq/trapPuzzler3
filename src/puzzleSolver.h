//
//  puzzleSolver.h
//  trapStory2
//
//  Created by Kivifreak on 01/01/16.
//
//

#ifndef trapPuzzler3_puzzleSolver_h
#define trapPuzzler3_puzzleSolver_h

set<deque<deque<int> > > solveGrids;

int origSolveY, origSolveX;
int solveY, solveX;
bool moreOptimized = false;

int diffForSolved = 3;

int origGridSizeY, origGridSizeX;
bool dfsSolvableWithDepth(int depth, int _y, int _x) {
    int currentGridSizeY = moveGrid.size(), currentGridSizeX = moveGrid[0].size();
    if(depth > 0 && solveGrids.count(moveGrid) == 0) {
        bool d;
        if(moreOptimized == true && abs(_y - origSolveY) > solveY) {
            solveY = abs(_y - origSolveY);
            d = dfsSolvableWithDepth(5, _y, _x);
            if(d) return d;
        }
        if(moreOptimized == true && abs(_x - origSolveX) > solveX) {
            solveX = abs(_x - origSolveX);
            d = dfsSolvableWithDepth(5, _y, _x);
            if(d) return d;
        }
        solveGrids.insert(moveGrid);
        if(move(moveGrid, playerID, UP, -1,false,false)) {
            checkMovement();
            if(moveGrid.size() > origGridSizeY + diffForSolved) return true;
            d = dfsSolvableWithDepth(depth - 1, _y-1, _x);
            if(d) return d;
            undoMovement(-1);
            checkMovement();
        }
        
        if(move(moveGrid, playerID, DOWN, -1,false,false)) {
            checkMovement();
            //if(moveGrid.size() > currentGridSizeY) return true;
            d = dfsSolvableWithDepth(depth - 1, _y+1, _x);
            if(d) return d;
            if(moveGrid.size() > origGridSizeY + diffForSolved) return true;
            undoMovement(-1);
            checkMovement();
        }
        
        if(move(moveGrid, playerID, LEFT, -1,false,false)) {
            checkMovement();
            //if(moveGrid.size() > currentGridSizeY) return true;
            d = dfsSolvableWithDepth(depth - 1, _y, _x-1);
            if(d) return d;
            if(moveGrid[0].size() > origGridSizeX + diffForSolved) return true;
            undoMovement(-1);
            checkMovement();
            
        }
        
        if(move(moveGrid, playerID, RIGHT, -1,false,false)) {
            checkMovement();
            //if(moveGrid.size() > currentGridSizeY) return true;
            d = dfsSolvableWithDepth(depth - 1, _y, _x+1);
            if(moveGrid[0].size() > origGridSizeX + diffForSolved) return true;
            if(d) return d;
            undoMovement(-1);
            checkMovement();
        }
        
        //CHANGE FOR LATER!!!
        //HOW TO CHECK IF SOLVED??? WELL WHEN GRID SIZE CHANGES I GUESS
    }
    return false;
}

bool dfk(int depth) {
    for(int i = 0; i < grid.size(); ++i) {
        for(int j = 0; j < grid[i].size(); ++j) {
            if(grid[i][j] == playerID) {
                origSolveY = i;
                origSolveX = j;
            }
        }
    }
    solveY = 0; solveX = 0;
    origGridSizeY = grid.size();
    assert(grid.size() > 0);
    origGridSizeX = grid[0].size();
    solveGrids.clear();
    bool canGetSolved = dfsSolvableWithDepth(depth, origSolveY, origSolveX);
    solveGrids.clear();
    return canGetSolved;
}

int tryForSolution() {
    int timeTaken = 0;
    bool tryToSolve = false;
    int i;
    for(i = 5; timeTaken < /*2000000*/50000000 && tryToSolve == false; ++i) {
        timeTaken = clock();
        tryToSolve = dfk(i);
        timeTaken = clock() - timeTaken;
    }
    if(timeTaken >= 50000000) return -2;
    else if(tryToSolve == false) return -1;
    else return i;
}


deque<deque<int> > generateRandomLevel(int sizeY, int sizeX, int stuffToPlace) {
    deque<deque<int> > newLevel(sizeY, deque<int> (sizeX));
    int i = 0, tryRand = 0;
    vector<vector<pair<int, int> > > shapes = {{{0,0}},{{0,0},{0,1}},{{0,0},{1,0}}};
    int enemyCount = 10;
    int unmovableEnemyCount = 1000;
    int atLeast = 20;
    newLevel[(sizeY/2)+1][(sizeX/2)+1] = 1;
    while(i < stuffToPlace) {
        int y = rand() % sizeY;
        int x = rand() % sizeX;
        int rShape = rand() % shapes.size();
        bool placable = true;
        for(int j = 0; j < shapes[rShape].size(); ++j) {
            if(y+shapes[rShape][j].first >= newLevel.size() || x+shapes[rShape][j].second >= newLevel[0].size() ||
               newLevel[y+shapes[rShape][j].first][x+shapes[rShape][j].second] != 0) placable = false;
        }
        if(placable) {
            ++i;
            int randEn = rand() % 100;
            int idToPlace;
            if(randEn < 40) idToPlace = ++enemyCount;
            else idToPlace = ++unmovableEnemyCount;
            for(int j = 0; j < shapes[rShape].size(); ++j) {
                newLevel[y+shapes[rShape][j].first][x+shapes[rShape][j].second] = idToPlace;
            }
            tryRand = 0;
            stuffToPlace++;
        }
        else tryRand++;
        if(tryRand > atLeast) i = stuffToPlace;
    }
    return newLevel;
}
void levelExport(ostream &, deque<deque<int> >);
void generateSomeCoolLevels() {
    int theReturnTime = 2;
    int failedNums = 0;
    float ratioOfFailedNums = 0;
    srand(time(NULL));
    for(int i = 0; i < 1000000000; ++i) {
        deque<deque<int> > k = generateRandomLevel(7,7,28);
        updateGrid(k);
        int ret = tryForSolution();
        if(ret == -1) ratioOfFailedNums = ++failedNums * 1.0 / i * 1.0;
        //cout << ret << endl;
        for(int j = 0; j < 10; ++j) checkMovement();
        if(ret > theReturnTime || (ret > 12)) {
            theReturnTime = ret;
            updateGrid(k);
            cout << endl << endl << endl << "LEVEL: " << ret << " failed ratio: " << ratioOfFailedNums << endl;
            levelExport(cout, grid);
            cout << endl;
        }
        
    }
    cout << endl << endl << endl << "done :(" << endl;
}
















//Set hasGravity = true, if uncertain.
//returns -1 = UNSOLVABLE, x = SOLVABLE in STEP, -2 = UNKNOWN (not fully computed), -3 = ERROR, such as no player
bool winState(deque<deque<int> > &);
int newSolver(ddd gridtosolve, bool hasGravity, vector<keyType> & solution) {
    set<pair<ddd,int> > computed; //<*,THIS> :=  ID of player
    vector<pair<int,keyType> > previousMove; //can then be used to backtrace the solution.
    
    int maxSize = 256; //number of moves which are tried.
    previousMove = vector<pair<int,keyType> >(maxSize);
    queue<pair<ddd,int> > q;
    
    {   // MOVE PLAYER
        int firstPlayer = changePlayerIdRandom(gridtosolve, -1,true);
        if(firstPlayer == -1) {
            cout << "No player in the grid: " << firstPlayer << endl;
            return -3;
        }
        
        q.push({gridtosolve,firstPlayer});
        computed.insert({gridtosolve,firstPlayer});
    }
    
    int currentPosition = -1, newMovePosition = -1;
    while(q.size() != 0 && newMovePosition < maxSize) {
        assert(!forceUndo);
        pair<ddd,int> current = q.back();
        q.pop();
        pair<ddd,int> left = current;
        pair<ddd,int> right = current;
        pair<ddd,int> up = current;
        pair<ddd,int> down = current;
        pair<ddd,int> changeplayer = current;
        if(move(left.first, left.second, LEFT, -1, true, hasGravity)) {
            if(computed.count(left) == 0) {
                newMovePosition++;
                previousMove[newMovePosition] = {currentPosition, LEFT};
                if(winState(down.first)) {
                    int cm = newMovePosition;
                    while(cm != -1) {
                        solution.push_back(previousMove[cm].second);
                        cm = previousMove[cm].first;
                    }
                    reverse(solution.begin(), solution.end());
                    return newMovePosition;
                }                if(newMovePosition < maxSize) q.push(left);
            }
        }
        if(move(right.first, right.second, RIGHT, -1, true, hasGravity)) {
            if(computed.count(right) == 0) {
                newMovePosition++;
                previousMove[newMovePosition] = {currentPosition, RIGHT};
                if(winState(down.first)) {
                    int cm = newMovePosition;
                    while(cm != -1) {
                        solution.push_back(previousMove[cm].second);
                        cm = previousMove[cm].first;
                    }
                    reverse(solution.begin(), solution.end());
                    return newMovePosition;
                }                if(newMovePosition < maxSize) q.push(right);
            }
        }
        if(move(up.first, up.second, UP, -1, true, hasGravity)) {
            if(computed.count(up) == 0) {
                newMovePosition++;
                previousMove[newMovePosition] = {currentPosition, UP};
                if(winState(down.first)) {
                    int cm = newMovePosition;
                    while(cm != -1) {
                        solution.push_back(previousMove[cm].second);
                        cm = previousMove[cm].first;
                    }
                    reverse(solution.begin(), solution.end());
                    return newMovePosition;
                }                if(newMovePosition < maxSize) q.push(up);
            }
        }
        if(move(down.first, down.second, DOWN, -1, true, hasGravity)) {
            if(computed.count(down) == 0) {
                newMovePosition++;
                previousMove[newMovePosition] = {currentPosition, DOWN};
                if(winState(down.first)) {
                    int cm = newMovePosition;
                    while(cm != -1) {
                        solution.push_back(previousMove[cm].second);
                        cm = previousMove[cm].first;
                    }
                    reverse(solution.begin(), solution.end());
                    return newMovePosition;
                }
                if(newMovePosition < maxSize) q.push(down);
            }
        }
        
        {
            if(computed.count(changeplayer) == 0) {
                newMovePosition++;
                previousMove[newMovePosition] = {currentPosition, CHANGE_TO_PLAYER};
                //should not make a win state
                if(newMovePosition < maxSize) q.push(down);
            }
        }
        currentPosition++;
    }
    
    
    return -1;
}



#endif
