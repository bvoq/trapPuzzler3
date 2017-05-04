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
void mouseTouchDown(int mouseTouchY, int mouseTouchX, int touchid) {
    switch(mode) {
        case PLAYING:
        case LEVEL_EDITOR_PLAYING:
        {
            assert(grid.size() > 0);
            if(grid.size() > 0 && !blockMovementDueToWinningAnimation) {
                pair<int,int> tilePos = calculateInversePosition(mouseTouchY, mouseTouchX, grid.size(), grid[0].size());
                //If click is in bound.
                if(0 <= tilePos.first && tilePos.first < grid.size() && 0 <= tilePos.second && tilePos.second < grid[0].size())
                {
                    if(getCellType(grid[tilePos.first][tilePos.second]) == PLAYER) {
                        playerTouchMovement newMovement(tilePos.first,tilePos.second,grid[tilePos.first][tilePos.second]);
                        playerTouches.insert({touchid,newMovement});
                        changePlayerId(grid[tilePos.first][tilePos.second]);
                    }
                    
                }
                
                
                
            }
        }
            break;
        case MENU:
            
            if(mouseTouchX < getWidth()/3) keyEvent(LEFT);
            if(mouseTouchX > 2*getWidth()/3) keyEvent(RIGHT);
            if(mouseTouchY < getHeight()/3) keyEvent(UP);
            if(mouseTouchY > 2*getHeight()/3) keyEvent(DOWN);
            if(mouseTouchX > getWidth()/3 && mouseTouchX < 2*getWidth()/3 && mouseTouchY > getHeight()/3 && mouseTouchY < 2*getHeight()/3) keyEvent(PLAYER_CHANGE);
            break;
        default:
            cout << "Unknown mode " << mode << endl;
    }
}


void mouseTouchMoved(int mouseTouchY, int mouseTouchX, int touchid) {
    switch(mode) {
        case PLAYING:
        case LEVEL_EDITOR_PLAYING:
            if(playerTouches.count(touchid) != 0) {
                assert(grid.size() > 0);
                pair<int,int> tilePos = calculateInversePosition(mouseTouchY, mouseTouchX, grid.size(), grid[0].size());
                //Can click outside the box.
                if(tilePos.first == playerTouches[touchid].y-1 && tilePos.second == playerTouches[touchid].x) {
                    if(move(UP, timeForMovement)) { //Move succeeded
                        playerTouches[touchid].y = tilePos.first;
                        playerTouches[touchid].x = tilePos.second;
                    }
                }
                if(tilePos.first == playerTouches[touchid].y+1 && tilePos.second == playerTouches[touchid].x) {
                    if(move(DOWN, timeForMovement)) { //Move succeeded
                        playerTouches[touchid].y = tilePos.first;
                        playerTouches[touchid].x = tilePos.second;
                    }
                }
                if(tilePos.first == playerTouches[touchid].y && tilePos.second == playerTouches[touchid].x-1) {
                    if(move(LEFT, timeForMovement)) { //Move succeeded
                        playerTouches[touchid].y = tilePos.first;
                        playerTouches[touchid].x = tilePos.second;
                    }
                }
                if(tilePos.first == playerTouches[touchid].y && tilePos.second == playerTouches[touchid].x+1) {
                    if(move(RIGHT, timeForMovement)) { //Move succeeded
                        playerTouches[touchid].y = tilePos.first;
                        playerTouches[touchid].x = tilePos.second;
                    }
                }
                
                //playerTouches[touch.id].x;
            }
            break;
        default:
            cout << "Unknown mode " << mode << endl;
    }
}


void mouseTouchUp(int mouseTouchY, int mouseTouchX, int touchid) {
    //Call as if it moved one last time.
    mouseTouchMoved(mouseTouchY, mouseTouchX, touchid);
    
    //Control scheme: Execute move on touch maybe.
    playerTouches.erase(touchid);
}

#endif /* mouseTouchEvent_h */
