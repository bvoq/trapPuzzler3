
//
//  levels.h
//  trapStory2
//
//  Created by kdkdk on 25/12/15.
//
//

#ifndef levels_h
#define levels_h

#include "macros.h"

extern int currentLevel;

struct LevelInfo {
    LevelInfo() {}
};

extern vector<ddd > levels;
extern vector<ddd > defaultlevels;
extern vector<LevelInfo> levelsInfo;
extern vector<LevelInfo> defaultlevelsInfo;
extern vector<bool> beaten;


extern bool validateLevel(ddd & level, LevelInfo levelInfo);

extern void saveLevelData();
extern void loadLevelData();

extern void saveLevelData();
extern void createLevels();

#endif
