
//
//  keyMap.h
//  trapStory2
//
//  Created by kdkdk on 28/12/15.
//
//

#ifndef keyMap_h
#define keyMap_h

#include "macros.h"

extern string strkeytype(keyType in);

extern map<int, keyType> keyMapper;
extern map<keyType, pair<long long,bool> > keyPressedDown;
extern map<keyType, bool> timeWaitForRepress;

extern bool setRemapKey;
extern keyType remapKey;

extern void initDefaultKeyMapping();

#endif
