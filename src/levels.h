
//
//  levels.h
//  trapStory2
//
//  Created by kdkdk on 25/12/15.
//
//

#ifndef trapPuzzler3_levels_h
#define trapPuzzler3_levels_h

#include "bitsstdc.h"

#define ddd std::deque<std::deque<int> >


extern int currentLevel;

struct LevelInfo {
    LevelInfo() {}
};

extern std::vector<ddd > levels;
extern std::vector<ddd > defaultlevels;
extern std::vector<LevelInfo> levelsInfo;
extern std::vector<LevelInfo> defaultlevelsInfo;
extern std::vector<bool> beaten;


extern bool validateLevel(ddd & level, LevelInfo levelInfo);

extern void saveLevelData();
extern void loadLevelData();

extern void saveLevelData();
extern void createLevels();

#endif
