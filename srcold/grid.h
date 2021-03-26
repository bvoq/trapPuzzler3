//
//  grid.h
//  trapStory2
//
//  Created by kdkdk on 25/12/15.
//
//

#ifndef grid_h
#define grid_h

#include "macros.h"

extern const int GRAVITYMONSTERMOUTHID, GRAVITYMONSTEREYEID, GRAVITYMONSTERDEADEYEID;

extern string strcelltype(cellType cT);
extern cellType getCellType(int ID);

extern deque<deque<int> > grid, moveGrid;
//int gridX, gridY, moveGridX, moveGridY;

extern void pushBackRowOf(deque<deque<int> > &input);
extern void pushFrontRowOf(deque<deque<int> > &input);
extern void pushBackColumnOf(deque<deque<int> > &input);
extern void pushFrontColumnOf(deque<deque<int> > &input);

extern void popBackRowOf(deque<deque<int> > &input);
extern void popFrontRowOf(deque<deque<int> > &input);
extern void popBackColumnOf(deque<deque<int> > &input);
extern void popFrontColumnOf(deque<deque<int> > &input);

extern void cropBordersOf(deque<deque<int> > &tempGrid);
extern void cropBordersOfBoth(deque<deque<int> > &tempGrid, deque<deque<int> > &cropSameWay);

//MAKE SURE TO CHANGE GRID COORDS ASWELL!!
extern void extendGridToFit(deque<deque<int> > & tempGrid, int sizeY, int sizeX);


#ifndef compiledWithoutOpenframeworks
extern ofRectangle calculatePosition(float idY, float idX, int gridY, int gridX);
extern pair<int,int> calculateInversePosition(int coordY, int coordX, int gridY, int gridX);
#endif

extern void levelExport(ostream & o, deque<deque<int> > copied);

#endif
