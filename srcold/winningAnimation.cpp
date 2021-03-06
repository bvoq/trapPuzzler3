#include "winningAnimation.h"

#include "eyes.h"
#include "globals.h"
#include "grid.h"
#include "keyMap.h"
#include "levels.h"
#include "mouseTouchEvent.h"
#include "movement.h"
#include "saves.h"
#include "updateGrid.h"

#ifndef compiledWithoutOpenframeworks
void blockMovementForWinning() {
    blockMovementDueToWinningAnimation = true;
    playerTouches.clear();
}
#endif

bool winState(deque<deque<int> > & moveGrid, bool winningAnimationAction) {
    //gravity must be disabled in order to win!
    assert(moveGrid.size() != 0);
    bool gravityLevel = false;
    for(int i = 0; i < moveGrid.size(); ++i) {
        for(int j = 0; j < moveGrid[i].size(); ++j) {
            if(getCellType(moveGrid[i][j]) == GRAVITYMONSTEREYE) gravityLevel = true;
        }
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
        if(uP || dP || lP || rP) {
            if(winningAnimationAction) {
                if(uP || dP || lP || rP) timeForMovement = timeForFastMovement;
                if(uP) {
                    for(int i = lowestPoint; i >= 0; --i) {
                        move(moveGrid, moveEyeGrid, playerID, UP, timeForMovement, false, true);
                    }
                    return true;
                }
                if(lP) {
                    for(int j = mostLeftPoint; j >= 0; --j) {
                        move(moveGrid, moveEyeGrid, playerID, LEFT, timeForMovement, false, true);
                    }
                    return true;
                }
                
                if(rP) {
                    int origSize = moveGrid[0].size();
                    for(int j = mostRightPoint; j < origSize; ++j) {
                        move(moveGrid, moveEyeGrid, playerID, RIGHT, timeForMovement, false, true);
                    }
                    return true;
                }
                if(dP) {
                    int origSize = moveGrid.size();
                    for(int i = highestPoint; i < origSize; ++i) {
                        move(moveGrid, moveEyeGrid, playerID, DOWN, timeForMovement, false, true);
                    }
                    return true;
                }
            }
            return true;
        }
    }
    return false;
}

#ifndef compiledWithoutOpenframeworks
#include "globals.h"
void winningAnimation() {
    if(!firstMovementHCI) {
        auto end = chrono::high_resolution_clock::now();
        long long timeMeasured = chrono::duration_cast<chrono::nanoseconds>(end-timeMeasuredForHCI).count();
        cout << "Measured time as: " << timeMeasured << " ns" << endl;
        firstMovementHCI = true;
    }
    blockMovementForWinning();
    switchRenderMode(FULL); //will enable cool after graphics.
    if(beautifulGraphics) scrollX = getWidth()/2;
    else scrollX = 0;
    //cout << max(grid.size(), grid[0].size()) << endl;
    if(grid.size() > 100 || grid[0].size() > 100) {
        if(currentLevel >= 0 && currentLevel < beaten.size()) {
            beaten[currentLevel] = true;
            saveSaveData();
        }
        blockMovementDueToWinningAnimation = false;
        cleanupLevelPlayingData();
        mode = MENU;
    }
}
#endif
