//
//  grid.h
//  trapStory2
//
//  Created by kdkdk on 25/12/15.
//
//

#ifndef trapPuzzler3_grid_h
#define trapPuzzler3_grid_h

#include "bitsstdc.h"

extern const int GRAVITYMONSTERMOUTHID, GRAVITYMONSTEREYEID, GRAVITYMONSTERDEADEYEID;
enum cellType {
    AIR=0, PLAYER=1, ENEMY=2, UNMOVABLE_ENEMY=3, LOVE=4, SUPERAIR=9, GRAVITYMONSTERMOUTH=10101010, GRAVITYMONSTEREYE=10101011, GRAVITYMONSTERDEADEYE = 10101012
};

extern std::string strcelltype(cellType cT);
extern cellType getCellType(int ID);

extern std::deque<std::deque<int> > grid, moveGrid;
//int gridX, gridY, moveGridX, moveGridY;

extern void pushBackRowOf(std::deque<std::deque<int> > &input);
extern void pushFrontRowOf(std::deque<std::deque<int> > &input);
extern void pushBackColumnOf(std::deque<std::deque<int> > &input);
extern void pushFrontColumnOf(std::deque<std::deque<int> > &input);

extern void popBackRowOf(std::deque<std::deque<int> > &input);
extern void popFrontRowOf(std::deque<std::deque<int> > &input);
extern void popBackColumnOf(std::deque<std::deque<int> > &input);
extern void popFrontColumnOf(std::deque<std::deque<int> > &input);

extern void cropBordersOf(std::deque<std::deque<int> > &tempGrid);
extern void cropBordersOfBoth(std::deque<std::deque<int> > &tempGrid, std::deque<std::deque<int> > &cropSameWay);

//MAKE SURE TO CHANGE GRID COORDS ASWELL!!
extern void extendGridToFit(std::deque<std::deque<int> > & tempGrid, int sizeY, int sizeX);


#ifndef islevelgen

#include "ofMain.h"
extern ofRectangle calculatePosition(float idY, float idX, int gridY, int gridX);
extern pair<int,int> calculateInversePosition(int coordY, int coordX, int gridY, int gridX);

#endif

extern void levelExport(ostream & o, std::deque<std::deque<int> > copied);

#endif
