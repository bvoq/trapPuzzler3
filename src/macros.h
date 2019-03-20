/*
 MUST READ:
 ==========
 The structure of the code follows a bit of my own C++ style. Every header file only includes this file 'macros.h'.
 This way, if you include a header you don't automatically include other headers recursively.
 As a downside all enums which are passed along to functions have to be defined in this file and all structs/classes which are passed along functions need to be declared in a forward fashion in this file.
 */

#pragma once

#include "bitsstdc.h" //Include all C++ libraries, see bitsstdc.h for the list of included libraries.

#ifndef compiledWithoutOpenframeworks
#include "ofMain.h"
inline long long getAdjustedTime() {
    return ofGetElapsedTimeMicros();
}
#endif

using namespace std; //For every source file, namespace std is required!

#define ddd std::deque<std::deque<int> > //ddd is a short-hand indicating a level instance.

// DEBUG MACRO, can remove all debug statements by commenting out the other line:
#define DEB(x) cerr << x << endl;
//#define DEB(x) while(0) cerr << x << endl;
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

//ENUM Declarations

enum keyType {
    UP, LEFT, DOWN, RIGHT, PLAYER_CHANGE, UNDO, RESTART, EXPORT, CHANGE_TO_AIR, CHANGE_TO_PLAYER, CHANGE_TO_ENEMY, CHANGE_TO_UNMOVABLE_ENEMY, CHANGE_TO_LOVE, CHANGE_TO_MONSTERMOUTH, CHANGE_TO_MONSTEREYE, CHANGE_TO_SUPERAIR, CLEAR, SOLVE, TOGGLE_TOOLBAR, IMPROVE, UNKNOWNKEYT
};

enum RenderMode {
    PARTIAL, FULL
};

enum cellType {
    AIR=0, PLAYER=1, ENEMY=2, UNMOVABLE_ENEMY=3, LOVE=4, SUPERAIR=9, GRAVITYMONSTERMOUTH=10101010, GRAVITYMONSTEREYE=10101011, GRAVITYMONSTERDEADEYE = 10101012
};

//Class forward declaration
class movement;
