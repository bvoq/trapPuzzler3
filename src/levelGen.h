//
//  levelGen.h
//  trapPuzzler3
//
//  Created by kdkdk on 11.09.17.
//
//

#ifndef levelGen_h
#define levelGen_h

deque<deque<int> > initField(int h, int w) {
    deque<deque<int> > field(h, deque<int> (w,0));
    
    vector< vector<pair<int, int> > > stonesBlack = {
        {{0,0},{0,1}}, {{0,0}}, {{0,0}}, {{0,0},{1,0}}, {{0,0},{0,1},{1,0},{1,1}}
    };
    vector< vector<pair<int,int> > > stonesRed = stonesBlack;
    vector<vector<pair<int,int> > > stonesYellow = stonesBlack;
    int minPlayers = 1, maxPlayers = 1;
    int minPink = 0, maxPink = 1;
    int yellowBlocksToBePlaced = minPlayers + (rand() % (maxPlayers - minPlayers + 1));
    int pinkBlocksToBePlaced = minPink + (rand() % (maxPink - minPink + 1));
    //int darkBlocksToBePlaced = 7 + (rand()%8);
    //int redBlocksToBePlaced = 2 + (rand()%14);
    //IDEAL FOR 10x10
    int darkBlocksToBePlaced = 16 + (rand() % 5);
    int redBlocksToBePlaced = 13 + (rand() % 5);
    
    while(yellowBlocksToBePlaced != 0) {
        //offsetY = h/2; offsetX = w/2;
        int offsetY = (rand() % (h-1))+1; int offsetX = (rand() % (w-1))+1;
        int randTile = rand() % stonesYellow.size();
        bool noAdd = false;
        for(int i = 0; i < stonesYellow[randTile].size(); ++i) {
            if(stonesYellow[randTile][i].first + offsetY >= h || stonesYellow[randTile][i].second + offsetX >= w ||
               field[stonesYellow[randTile][i].first + offsetY][stonesYellow[randTile][i].second + offsetX] != 0) {
                noAdd = true;
            }
        }
        if(noAdd == false) {
            for(int i = 0; i < stonesYellow[randTile].size(); ++i) {
                field[stonesYellow[randTile][i].first + offsetY][stonesYellow[randTile][i].second + offsetX] = yellowBlocksToBePlaced;
            }
            yellowBlocksToBePlaced--;
        }
    }
    assert(h > 5 && w > 5);
    while(pinkBlocksToBePlaced != 0) {
        //offsetY = h/2; offsetX = w/2;
        int offsetY = (rand() % (h/2))+h/4; int offsetX = (rand() % (w/2))+w/4;
        int randTile = rand() % stonesYellow.size();
        bool noAdd = false;
        for(int i = 0; i < stonesYellow[randTile].size(); ++i) {
            if(stonesYellow[randTile][i].first + offsetY >= h || stonesYellow[randTile][i].second + offsetX >= w ||
               field[stonesYellow[randTile][i].first + offsetY][stonesYellow[randTile][i].second + offsetX] != 0) {
                noAdd = true;
            }
        }
        if(noAdd == false) {
            for(int i = 0; i < stonesYellow[randTile].size(); ++i) {
                field[stonesYellow[randTile][i].first + offsetY][stonesYellow[randTile][i].second + offsetX] = 3000000+pinkBlocksToBePlaced;
            }
            pinkBlocksToBePlaced--;
        }
    }
    int breakTries = 0;
    while(darkBlocksToBePlaced != 0 && breakTries < 100) {
        int offsetY = rand() % h; int offsetX = rand() % w;
        int randTile = rand() % stonesBlack.size();
        bool noAdd = false;
        for(int i = 0; i < stonesBlack[randTile].size(); ++i) {
            if(stonesBlack[randTile][i].first + offsetY >= h || stonesBlack[randTile][i].second + offsetX >= w ||
               field[stonesBlack[randTile][i].first + offsetY][stonesBlack[randTile][i].second + offsetX] != 0) {
                noAdd = true;
            }
        }
        if(noAdd == false) {
            for(int i = 0; i < stonesBlack[randTile].size(); ++i) {
                field[stonesBlack[randTile][i].first + offsetY][stonesBlack[randTile][i].second + offsetX] = 2000000+darkBlocksToBePlaced;
            }
            darkBlocksToBePlaced--;
        }
        breakTries++;
    }
    breakTries = 0;
    while(redBlocksToBePlaced !=0 && breakTries < 100) {
        int offsetY = rand() % h; int offsetX = rand() % w;
        int randTile = rand() % stonesRed.size();
        bool noAdd = false;
        for(int i = 0; i < stonesRed[randTile].size(); ++i) {
            if(stonesRed[randTile][i].first + offsetY >= h || stonesRed[randTile][i].second + offsetX >= w ||
               field[stonesRed[randTile][i].first + offsetY][stonesRed[randTile][i].second + offsetX] != 0) {
                noAdd = true;
            }
        }
        if(noAdd == false) {
            for(int i = 0; i < stonesRed[randTile].size(); ++i) {
                field[stonesRed[randTile][i].first + offsetY][stonesRed[randTile][i].second + offsetX] = 1000000+redBlocksToBePlaced;
            }
            redBlocksToBePlaced--;
        }
        breakTries++;
    }
    return field;
}



deque<deque<int> > initSymmetricField(int fh, int fw) {
    assert(fh % 2 == 1 && fh == fw && fw > 2); //remove for efficiency
    deque<deque<int> > field(fh, deque<int> (fw,0));
    
    vector< vector<pair<int, int> > > stonesBlack = {
        {{0,0},{0,1}}, {{0,0}}, {{0,0}}, {{0,0},{1,0}}, {{0,0},{0,1},{1,0},{1,1}}
    };
    vector< vector<pair<int,int> > > stonesRed = stonesBlack;
    vector<vector<pair<int,int> > > stonesYellow = stonesBlack;
    int yellowBlocksToBePlaced = 1;
    int darkBlocksToBePlaced = 7 + (rand() % 11) - 4;
    int redBlocksToBePlaced = 4 + (rand()%11) - 4;
   	int totBlocks = darkBlocksToBePlaced + redBlocksToBePlaced + 20;
    
    int w = fh/2, h = fw / 2;
    
    field[w][h] = 1;
    ++w;++h;
    /*
     while(yellowBlocksToBePlaced != 0) {
     int offsetY = rand() % h; int offsetX = rand() % w;
     int randTile = rand() % stonesYellow.size();
     bool noAdd = false;
     for(int i = 0; i < stonesYellow[randTile].size(); ++i) {
     if(stonesYellow[randTile][i].first + offsetY >= h || stonesYellow[randTile][i].second + offsetX >= w ||
     field[stonesYellow[randTile][i].first + offsetY][stonesYellow[randTile][i].second + offsetX] != 0) {
     noAdd = true;
     }
     }
     if(noAdd == false) {
     for(int i = 0; i < stonesYellow[randTile].size(); ++i) {
     field[stonesYellow[randTile][i].first + offsetY][stonesYellow[randTile][i].second + offsetX] = yellowBlocksToBePlaced;
     }
     yellowBlocksToBePlaced--;
     }
     } */
    
    int breakTries = 0;
    while(darkBlocksToBePlaced != 0 && breakTries < 100) {
        int offsetY = rand() % h; int offsetX = rand() % w;
        int randTile = rand() % stonesBlack.size();
        bool noAdd = false;
        for(int i = 0; i < stonesBlack[randTile].size(); ++i) {
            if(stonesBlack[randTile][i].first + offsetY >= h || stonesBlack[randTile][i].second + offsetX >= w ||
               field[stonesBlack[randTile][i].first + offsetY][stonesBlack[randTile][i].second + offsetX] != 0) {
                noAdd = true;
            }
        }
        if(noAdd == false) {
            for(int i = 0; i < stonesBlack[randTile].size(); ++i) {
                field[stonesBlack[randTile][i].first + offsetY][stonesBlack[randTile][i].second + offsetX] = 2000000+darkBlocksToBePlaced;
            }
            darkBlocksToBePlaced--;
        }
        breakTries++;
    }
    breakTries = 0;
    while(redBlocksToBePlaced !=0 && breakTries < 100) {
        int offsetY = rand() % h; int offsetX = rand() % w;
        int randTile = rand() % stonesRed.size();
        bool noAdd = false;
        for(int i = 0; i < stonesRed[randTile].size(); ++i) {
            if(stonesRed[randTile][i].first + offsetY >= h || stonesRed[randTile][i].second + offsetX >= w ||
               field[stonesRed[randTile][i].first + offsetY][stonesRed[randTile][i].second + offsetX] != 0) {
                noAdd = true;
            }
        }
        if(noAdd == false) {
            for(int i = 0; i < stonesRed[randTile].size(); ++i) {
                field[stonesRed[randTile][i].first + offsetY][stonesRed[randTile][i].second + offsetX] = 1000000+redBlocksToBePlaced;
            }
            redBlocksToBePlaced--;
        }
        breakTries++;
    }
    //joint-symmetric mirroring
    bool joint = false;
    if(joint) {
        for(int i = 0; i <= h + 1; ++i) {
            for(int j = 0; j <= w + 1; ++j) {
                field[fh-1-i][j] = field[i][j];
                field[i][fw-1-j] = field[i][j];
                field[fh-1-i][fw-1-j] = field[i][j];
            }
        }
    }
    //normal symemtric mirroring
    else {
        for(int i = 0; i < fw; ++i) {
            field[h-1][i] = (field[h-1][i] < 10 ? 0 : totBlocks) + field[h-1][i];
        }
        for(int i = 0; i < fh; ++i) {
            field[i][w-1] = (field[i][w-1] < 10 ? 0 : totBlocks) + field[i][w-1];
        }
        totBlocks *= 2;
        for(int i = 0; i < h; ++i) {
            for(int j = 0; j < w; ++j) {
                //field[fh-1-i][j] = (field[i][j] < 10 ? 0 : totBlocks) + field[i][j];
                field[i][fw-1-j] = (field[i][j] < 10 ? 0 : totBlocks) + field[i][j];
                //field[fh-1-i][fw-1-j] = (field[i][j] < 10 ? 0 : totBlocks * 3) + field[i][j];
            }
        }
        for(int i = 0; i < h; ++i) {
            for(int j = 0; j < fw; ++j) {
                //field[fh-1-i][j] = (field[i][j] < 10 ? 0 : totBlocks) + field[i][j];
                field[fh-1-i][j] = (field[i][j] < 10 ? 0 : totBlocks * 4) + field[i][j];
                //field[fh-1-i][fw-1-j] = (field[i][j] < 10 ? 0 : totBlocks * 3) + field[i][j];
            }
        }
    }
    return field;
}






deque<deque<int> > initGravityField(int h, int w) {
    deque<deque<int> > field(h, deque<int> (w+3,0));
    
    vector< vector<pair<int, int> > > stonesBlack = {
        {{0,0},{0,1}}, {{0,0}}, {{0,0}}, {{0,0},{1,0}}, {{0,0},{0,1},{1,0},{1,1}}, {{0,0},{1,0},{2,0}}
    };
    vector< vector<pair<int,int> > > stonesRed = stonesBlack;
    vector<vector<pair<int,int> > > stonesYellow = stonesBlack;
    int minPlayers = 1, maxPlayers = 1;
    int minPink = 0, maxPink = 1;
    int yellowBlocksToBePlaced = minPlayers + (rand() % (maxPlayers - minPlayers + 1));
    int pinkBlocksToBePlaced = minPink + (rand() % (maxPink - minPink + 1));
    //int darkBlocksToBePlaced = 7 + (rand()%8);
    //int redBlocksToBePlaced = 2 + (rand()%14);
    //IDEAL FOR 10x10
    int darkBlocksToBePlaced = 10 + (rand() % 5); //less dark blocks needed for gravity levels.
    int redBlocksToBePlaced = 13 + (rand() % 5);
    
    while(yellowBlocksToBePlaced != 0) {
        //offsetY = h/2; offsetX = w/2;
        int offsetY = (rand() % (h-1))+1; int offsetX = (rand() % (w-1))+1;
        int randTile = rand() % stonesYellow.size();
        bool noAdd = false;
        for(int i = 0; i < stonesYellow[randTile].size(); ++i) {
            if(stonesYellow[randTile][i].first + offsetY >= h || stonesYellow[randTile][i].second + offsetX >= w ||
               field[stonesYellow[randTile][i].first + offsetY][stonesYellow[randTile][i].second + offsetX] != 0) {
                noAdd = true;
            }
        }
        if(noAdd == false) {
            for(int i = 0; i < stonesYellow[randTile].size(); ++i) {
                field[stonesYellow[randTile][i].first + offsetY][stonesYellow[randTile][i].second + offsetX] = yellowBlocksToBePlaced;
            }
            yellowBlocksToBePlaced--;
        }
    }
    assert(h > 5 && w > 5);
    while(pinkBlocksToBePlaced != 0) {
        //offsetY = h/2; offsetX = w/2;
        int offsetY = (rand() % (h/2))+h/4; int offsetX = (rand() % (w/2))+w/4;
        int randTile = rand() % stonesYellow.size();
        bool noAdd = false;
        for(int i = 0; i < stonesYellow[randTile].size(); ++i) {
            if(stonesYellow[randTile][i].first + offsetY >= h || stonesYellow[randTile][i].second + offsetX >= w ||
               field[stonesYellow[randTile][i].first + offsetY][stonesYellow[randTile][i].second + offsetX] != 0) {
                noAdd = true;
            }
        }
        if(noAdd == false) {
            for(int i = 0; i < stonesYellow[randTile].size(); ++i) {
                field[stonesYellow[randTile][i].first + offsetY][stonesYellow[randTile][i].second + offsetX] = 3000000+pinkBlocksToBePlaced;
            }
            pinkBlocksToBePlaced--;
        }
    }
    int breakTries = 0;
    while(darkBlocksToBePlaced != 0 && breakTries < 100) {
        int offsetY = rand() % h; int offsetX = rand() % w;
        int randTile = rand() % stonesBlack.size();
        bool noAdd = false;
        for(int i = 0; i < stonesBlack[randTile].size(); ++i) {
            if(stonesBlack[randTile][i].first + offsetY >= h || stonesBlack[randTile][i].second + offsetX >= w ||
               field[stonesBlack[randTile][i].first + offsetY][stonesBlack[randTile][i].second + offsetX] != 0) {
                noAdd = true;
            }
        }
        if(noAdd == false) {
            for(int i = 0; i < stonesBlack[randTile].size(); ++i) {
                field[stonesBlack[randTile][i].first + offsetY][stonesBlack[randTile][i].second + offsetX] = 2000000+darkBlocksToBePlaced;
            }
            darkBlocksToBePlaced--;
        }
        breakTries++;
    }
    breakTries = 0;
    while(redBlocksToBePlaced !=0 && breakTries < 100) {
        int offsetY = rand() % h; int offsetX = rand() % w;
        int randTile = rand() % stonesRed.size();
        bool noAdd = false;
        for(int i = 0; i < stonesRed[randTile].size(); ++i) {
            if(stonesRed[randTile][i].first + offsetY >= h || stonesRed[randTile][i].second + offsetX >= w ||
               field[stonesRed[randTile][i].first + offsetY][stonesRed[randTile][i].second + offsetX] != 0) {
                noAdd = true;
            }
        }
        if(noAdd == false) {
            for(int i = 0; i < stonesRed[randTile].size(); ++i) {
                field[stonesRed[randTile][i].first + offsetY][stonesRed[randTile][i].second + offsetX] = 1000000+redBlocksToBePlaced;
            }
            redBlocksToBePlaced--;
        }
        breakTries++;
    }
    
    for(int i = 0; i < h; ++i) {
        if(h/2==i) field[i][w] = GRAVITYMONSTEREYEID;
        else {
            field[i][w+2] = GRAVITYMONSTERMOUTHID;
        }
    }
    
    return field;
}
#endif /* levelGen_h */
