//
//  grid.h
//  trapStory2
//
//  Created by Kivifreak on 25/12/15.
//
//

#ifndef trapPuzzler3_grid_h
#define trapPuzzler3_grid_h

deque<deque<int> > grid, moveGrid;
//int gridX, gridY, moveGridX, moveGridY;

void pushBackRowOf(deque<deque<int> > &input) {
    deque<int> emptyCells (input[0].size(), 0);
    input.push_back(emptyCells);
}

void pushFrontRowOf(deque<deque<int> > &input) {
    deque<int> emptyCells (input[0].size(), 0);
    input.push_front(emptyCells);
}

void pushBackColumnOf(deque<deque<int> > &input) {
    for(auto &it : input) it.push_back(0);
}

void pushFrontColumnOf(deque<deque<int> > &input) {
    for(auto &it : input) it.push_front(0);
}

void popBackRowOf(deque<deque<int> > &input) {
    input.pop_back();
}

void popFrontRowOf(deque<deque<int> > &input) {
    input.pop_front();
}

void popBackColumnOf(deque<deque<int> > &input) {
    for(auto &it : input) it.pop_back();
}

void popFrontColumnOf(deque<deque<int> > &input) {
    for(auto &it : input) it.pop_front();
}

void cropBordersOf(deque<deque<int> > &tempGrid) {
    //This should maybe only happen when the size is less then 12
    bool upOrTop = false;
    /*while(tempGrid.size() < MIN_CELL_SIZE) {
     if(upOrTop) pushBackRowOf(tempGrid);
     else pushFrontRowOf(tempGrid);
     upOrTop = !upOrTop;
     }
     while(tempGrid[0].size() < MIN_CELL_SIZE) {
     if(upOrTop) pushBackColumnOf(tempGrid);
     else pushFrontColumnOf(tempGrid);
     upOrTop = !upOrTop;
     }*/
    bool isEmpty = true;
    bool emptyOverall = false;
    while(emptyOverall == false) {
        
        if(tempGrid.size() < 1) return;
        if(tempGrid[0].size() < 1) return;
        
        isEmpty = true;
        emptyOverall = true;
        //if( tempGrid.size() > MIN_CELL_SIZE) {
        for(int i = 0; i < tempGrid.back().size(); ++i) {
            if(tempGrid.back()[i] != 0) isEmpty = false;
        }
        if(isEmpty) {
            emptyOverall = false;
            if(tempGrid.size() > 0) tempGrid.pop_back();
            else return;
        }
        isEmpty = true;
        for(int i = 0; i < tempGrid.front().size(); ++i) {
            if(tempGrid.front()[i] != 0) isEmpty = false;
        }
        if(isEmpty) {
            emptyOverall = false;
            if(tempGrid.size() > 0) tempGrid.pop_front();
            else return;
        }
        //}
        //if(tempGrid[0].size() > MIN_CELL_SIZE) {
        isEmpty = true;
        for(int i = 0; i < tempGrid.size(); ++i) {
            if(tempGrid[i].back() != 0) isEmpty = false;
        }
        if(isEmpty) {
            emptyOverall = false;
            for(auto &it : tempGrid) it.pop_back();
        }
        isEmpty = true;
        for(int i = 0; i < tempGrid.size(); ++i) {
            if(tempGrid[i].front() != 0) isEmpty = false;
        }
        if(isEmpty) {
            emptyOverall = false;
            for(auto &it : tempGrid) it.pop_front();
        }
        //}
    }
}

void cropBordersOfBoth(deque<deque<int> > &tempGrid, deque<deque<int> > &cropSameWay) {
    bool upOrTop = false;

    bool isEmpty = true;
    bool emptyOverall = false;
    while(emptyOverall == false) {
        
        if(tempGrid.size() < 1) return;
        if(tempGrid[0].size() < 1) return;
        
        isEmpty = true;
        emptyOverall = true;
        for(int i = 0; i < tempGrid.back().size(); ++i) {
            if(tempGrid.back()[i] != 0) isEmpty = false;
        }
        if(isEmpty) {
            emptyOverall = false;
            tempGrid.pop_back();
            cropSameWay.pop_back();
        }
        isEmpty = true;
        for(int i = 0; i < tempGrid.front().size(); ++i) {
            if(tempGrid.front()[i] != 0) isEmpty = false;
        }
        if(isEmpty) {
            emptyOverall = false;
            tempGrid.pop_front();
            cropSameWay.pop_front();
        }
        
        isEmpty = true;
        for(int i = 0; i < tempGrid.size(); ++i) {
            if(tempGrid[i].back() != 0) isEmpty = false;
        }
        if(isEmpty) {
            emptyOverall = false;
            for(auto &it : tempGrid) it.pop_back();
            for(auto &it : cropSameWay) it.pop_back();
        }
        isEmpty = true;
        for(int i = 0; i < tempGrid.size(); ++i) {
            if(tempGrid[i].front() != 0) isEmpty = false;
        }
        if(isEmpty) {
            emptyOverall = false;
            for(auto &it : tempGrid) it.pop_front();
            for(auto &it : cropSameWay) it.pop_front();
        }
    }
}

//MAKE SURE TO CHANGE GRID COORDS ASWELL!!
void extendGridToFit(deque<deque<int> > & tempGrid, int sizeY, int sizeX) {
    bool state = false;
    while(tempGrid.size() < sizeY) {
        if(state) pushBackRowOf(tempGrid);
        else pushFrontRowOf(tempGrid);
        state = !state;
    }

    while(tempGrid[0].size() < sizeX) {
        if(state) pushBackColumnOf(tempGrid);
        else pushFrontColumnOf(tempGrid);
        state = !state;
    }
}

int GRAVITYMONSTERMOUTHID = 10101010, GRAVITYMONSTEREYEID = 10101011, GRAVITYMONSTERDEADEYEID = 10101012;
enum cellType {
    AIR=0, PLAYER=1, ENEMY=2, UNMOVABLE_ENEMY=3, LOVE=4, SUPERAIR=9, GRAVITYMONSTERMOUTH=10101010, GRAVITYMONSTEREYE=10101011, GRAVITYMONSTERDEADEYE = 10101012
};

string strcelltype(cellType cT) {
    return cT==AIR ? "AIR" : cT==PLAYER ? "PLAYER" : cT==ENEMY ? "ENEMY" : cT==LOVE ? "LOVE" : cT==SUPERAIR ? "SUPERAIR" : cT==GRAVITYMONSTERMOUTH ? "GRAVITYMONSTERMOUTH" : cT == GRAVITYMONSTEREYE ? "GRAVITYMONSTEREYE" : cT==GRAVITYMONSTERDEADEYE ? "GRAVITYMONSTERDEADEYE" : cT==SUPERAIR ? "SUPERAIR" : "UNKNOWNCT"+to_string(cT);
}

cellType getCellType(int ID) {
    if(ID == 0) return AIR;
    else if(ID > 0 && ID < 1000000) return PLAYER;
    else if(ID >= 1000000 && ID < 2000000) return ENEMY;
    else if(ID >= 2000000 && ID < 3000000) return UNMOVABLE_ENEMY;
    else if(ID >= 3000000 && ID < 4000000) return LOVE;
    else if(ID == GRAVITYMONSTERMOUTHID) return GRAVITYMONSTERMOUTH;
    else if(ID == GRAVITYMONSTEREYEID) return GRAVITYMONSTEREYE;
    else if(ID == GRAVITYMONSTERDEADEYEID) return GRAVITYMONSTERDEADEYE;
    else assert(false);
    return SUPERAIR;
}
#ifndef islevelgen
ofRectangle calculatePosition(float idY, float idX, int gridY, int gridX) {
    int w = getWidth(), h = getHeight();
    float scaleY = (h * 1.) / (MAX(gridY + 2, MIN_CELL_SIZE) * 1.);
    float scaleX = (w * 1.) / (MAX(gridX + 2, MIN_CELL_SIZE) * 1.);
    float scale = min(scaleY, scaleX);
    idX -= gridX / 2.;
    idY -= gridY / 2.;
    
    ofRectangle output(idX * scale, idY * scale, scale, scale);
    output.translate(w / 2, h / 2);
    
    return output;
}

pair<int,int> calculateInversePosition(int coordY, int coordX, int gridY, int gridX) {
    int w = getWidth(), h = getHeight();
    float scaleY = (h * 1.) / (MAX(gridY + 2, MIN_CELL_SIZE) * 1.);
    float scaleX = (w * 1.) / (MAX(gridX + 2, MIN_CELL_SIZE) * 1.);
    float scale = min(scaleY, scaleX);
    float transY = (h - gridY * scale) / 2.;
    float transX = (w - gridX * scale) / 2.;
    coordY -= transY;
    coordX -= transX;
    

    if(coordY < 0) coordY -= scale; //since it is rounded up when negative
    if(coordX < 0) coordX -= scale;
    int posY = coordY / scale;
    int posX = coordX / scale;
    return {posY, posX};
}

#endif

void levelExport(ostream & o, deque<deque<int> > copied) {
    cropBordersOf(copied);
    o << "{";
    for(int i = 0; i < copied.size(); ++i) {
        o << "{";
        for(int j = 0; j < copied[i].size(); ++j) {
            o << copied[i][j];
            if(j != copied[i].size() - 1) o << ",";
        }
        o << "}";
        if(i != copied.size() - 1) o << ",";
    }
    o << "}";
}



#endif
