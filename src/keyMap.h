
//
//  keyMap.h
//  trapStory2
//
//  Created by Kivifreak on 28/12/15.
//
//

#ifndef trapPuzzler3_keyMap_h
#define trapPuzzler3_keyMap_h

enum keyType {
    UP, LEFT, DOWN, RIGHT, PLAYER_CHANGE, UNDO, RESTART, EXPORT, CHANGE_TO_AIR, CHANGE_TO_PLAYER, CHANGE_TO_ENEMY, CHANGE_TO_UNMOVABLE_ENEMY, CHANGE_TO_LOVE, CHANGE_TO_MONSTERMOUTH, CHANGE_TO_MONSTEREYE, CHANGE_TO_SUPERAIR, CLEAR, SOLVE, TOGGLE_TOOLBAR, IMPROVE
};
string strkeytype(keyType in) {
    return in == UP ? "UP" : in == DOWN ? "DOWN" : in == LEFT ? "LEFT" : in == RIGHT ? "RIGHT" : in == PLAYER_CHANGE ? "CHANGE" : "other";
}
map<int, keyType> keyMapper;
map<keyType, pair<long long,bool> > keyPressedDown;
map<keyType, bool> timeWaitForRepress;
/*
 Key Codes:
 ----------
 */

void initDefaultKeyMapping() {
    keyMapper.insert({87, UP});
    keyMapper.insert({119, UP});
    keyMapper.insert({357, UP});
    
    keyMapper.insert({65, LEFT});
    keyMapper.insert({97, LEFT});
    keyMapper.insert({356, LEFT});
    
    keyMapper.insert({83, DOWN});
    keyMapper.insert({115, DOWN});
    keyMapper.insert({359, DOWN});
    
    keyMapper.insert({68, RIGHT});
    keyMapper.insert({100, RIGHT});
    keyMapper.insert({358, RIGHT});
    
    keyMapper.insert({32, PLAYER_CHANGE});

    keyMapper.insert({85, UNDO});
    keyMapper.insert({117, UNDO});
    
    keyMapper.insert({82, RESTART});
    keyMapper.insert({114, RESTART});
    
    keyMapper.insert({69, EXPORT});
    keyMapper.insert({101, EXPORT});
    
    keyMapper.insert({48, CHANGE_TO_AIR});
    keyMapper.insert({49, CHANGE_TO_PLAYER});
    keyMapper.insert({50, CHANGE_TO_ENEMY});
    keyMapper.insert({51, CHANGE_TO_UNMOVABLE_ENEMY});
    keyMapper.insert({52, CHANGE_TO_LOVE});
    keyMapper.insert({53, CHANGE_TO_MONSTERMOUTH});
    keyMapper.insert({54, CHANGE_TO_MONSTEREYE});
    
    keyMapper.insert({57, CHANGE_TO_SUPERAIR});
    
    keyMapper.insert({67, CLEAR});
    keyMapper.insert({99, CLEAR});
    
    keyMapper.insert({76, SOLVE});
    keyMapper.insert({108, SOLVE});
    
    keyMapper.insert({27, TOGGLE_TOOLBAR});
    
    keyMapper.insert({105, IMPROVE});

    
}

#endif
