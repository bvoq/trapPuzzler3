//
//  mouseTouchEvent.h
//  trapPuzzlerIOS
//
//  Created by kdkdk on 22.04.17.
//
//

#ifndef mouseTouchEvent_h
#define mouseTouchEvent_h

#include "bitsstdc.h"

struct playerTouchMovement {
    int y, x;
    int touchid;
    playerTouchMovement() {}
    playerTouchMovement(int _y, int _x, int _touchid) : y(_y), x(_x), touchid(_touchid) {}
};

extern std::map<int, playerTouchMovement> playerTouches; //player id of touch.
extern std::map<int,std::pair<int,int> > origMouseTouch;

extern void mouseTouchDown(int mouseTouchY, int mouseTouchX, int touchid);
extern void mouseTouchMoved(int mouseTouchY, int mouseTouchX, int touchid);
extern void mouseTouchUp(int mouseTouchY, int mouseTouchX, int touchid);

#endif /* mouseTouchEvent_h */
