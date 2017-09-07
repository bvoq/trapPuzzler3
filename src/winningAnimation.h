//
//  winningAnimation.h
//  trapPuzzler3
//
//  Created by kdkdk on 22.04.17.
//
//

#ifndef winningAnimation_h
#define winningAnimation_h

void blockMovementForWinning() {
    blockMovementDueToWinningAnimation = true;
    playerTouches.clear(); //TODO Make it unplayable also for keyboard!
}

bool winState() {
    //gravity must be disabled in order to win!
    bool gravityLevel = false;
    for(int i = 0; i < moveGrid.size(); ++i) {
        for(int j = 0; j < moveGrid[i].size(); ++j) {
            if(getCellType(moveGrid[i][j]) == GRAVITYMONSTEREYE) gravityLevel = true;
        }
    }
    cout << endl;
    for(int i = 0; i < grid.size(); ++i) {
        for(int j = 0; j < grid[i].size(); ++j) {
            cout << grid[i][j] << ",";
        }
        cout << "|" << endl;
    }
    if(!gravityLevel) {
        //ALL PLAYERS MUST BE MERGED & 'FREE'
        int thePlayer = -1;
        for(int i = 0; i < moveGrid.size(); ++i) {
            for(int j = 0; j < moveGrid[i].size(); ++j) {
                if(getCellType(moveGrid[i][j]) == PLAYER || getCellType(moveGrid[i][j]) == LOVE) {
                    if(thePlayer == -1) thePlayer = moveGrid[i][j];
                    else if(thePlayer != moveGrid[i][j]) return false;
                }
            }
        }
        if(thePlayer == -1) return false;

        bool lP = true, rP = true, dP = true, uP = true;
        int lowestPoint = 0, highestPoint = moveGrid.size(), mostRightPoint = 0, mostLeftPoint = moveGrid[0].size();
        for(int i = 0; i < moveGrid.size(); ++i) {
            for(int j = 0; j < moveGrid[i].size(); ++j) {
                if(moveGrid[i][j] == thePlayer) {
                    if(i < highestPoint) highestPoint = i;
                    if(i > lowestPoint) lowestPoint = i;
                    if(j < mostLeftPoint) mostLeftPoint = j;
                    if(j > mostRightPoint) mostRightPoint = j;

                    for(int k = i; k >= 0; --k) {
                        if(!(moveGrid[k][j] == thePlayer || moveGrid[k][j] == 0)) uP = false;
                    }
                    for(int k = i; k < moveGrid.size(); ++k) {
                        if(!(moveGrid[k][j] == thePlayer || moveGrid[k][j] == 0)) dP = false;
                    }
                    for(int k = j; k >= 0; --k) {
                        if(!(moveGrid[i][k] == thePlayer || moveGrid[i][k] == 0)) lP = false;
                    }
                    for(int k = j; k < moveGrid[i].size(); ++k) {
                        if(!(moveGrid[i][k] == thePlayer || moveGrid[i][k] == 0)) rP = false;
                    }
                }
            }
        }
        if(uP || dP || lP || rP) timeForMovement = timeForFastMovement;
        if(uP) {
            for(int i = lowestPoint; i >= 0; --i) {
                move(UP, timeForMovement);
            }
            return true;
        }
        if(lP) {
            for(int j = mostLeftPoint; j >= 0; --j) {
                move(LEFT, timeForMovement);
            }
            return true;
        }

        if(rP) {
            for(int j = mostRightPoint; j < moveGrid[0].size(); ++j) {
                move(RIGHT, timeForMovement);
            }
            return true;
        }
        if(dP) {
            for(int i = highestPoint; i < moveGrid.size(); ++i) {
                move(DOWN, timeForMovement);
            }
            return true;
        }
    }
    return false;
}

void winningAnimation() {
    blockMovementForWinning();
    switchRenderMode(FULL);
    cout << max(grid.size(), grid[0].size()) << endl;
    if(grid.size() > 100 || grid[0].size() > 100) {
        if(currentLevel >= 0 && currentLevel < beaten.size()) {
            beaten[currentLevel] = true;
            saveSaveData();
        }
        mode = MENU;
    }
}


#endif /* winningAnimation_h */
