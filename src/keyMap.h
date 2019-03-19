
//
//  keyMap.h
//  trapStory2
//
//  Created by kdkdk on 28/12/15.
//
//

#ifndef trapPuzzler3_keyMap_h
#define trapPuzzler3_keyMap_h

#include "bitsstdc.h"

enum keyType {
    UP, LEFT, DOWN, RIGHT, PLAYER_CHANGE, UNDO, RESTART, EXPORT, CHANGE_TO_AIR, CHANGE_TO_PLAYER, CHANGE_TO_ENEMY, CHANGE_TO_UNMOVABLE_ENEMY, CHANGE_TO_LOVE, CHANGE_TO_MONSTERMOUTH, CHANGE_TO_MONSTEREYE, CHANGE_TO_SUPERAIR, CLEAR, SOLVE, TOGGLE_TOOLBAR, IMPROVE, UNKNOWNKEYT
};
extern std::string strkeytype(keyType in);

extern std::map<int, keyType> keyMapper;
extern std::map<keyType, std::pair<long long,bool> > keyPressedDown;
extern std::map<keyType, bool> timeWaitForRepress;

extern bool setRemapKey;
extern keyType remapKey;

extern void initDefaultKeyMapping();

#endif
