
//
//  levels.h
//  trapStory2
//
//  Created by Kivifreak on 25/12/15.
//
//

#ifndef trapPuzzler3_levels_h
#define trapPuzzler3_levels_h
#define ddd deque<deque<int> >
int currentLevel = 0;
bool gravityLevel = false;
keyType gravityDirection = LEFT;

vector<ddd > levels;
vector<ddd > defaultlevels;
vector<bool> gravityLevels;
vector<bool> defaultGravityLevels;
vector<keyType> gravityDirections;
vector<keyType> defaultGravityDirections;
vector<bool> beaten;

void saveLevelData();
void loadLevelData() {
    levels.clear();
    if(!ofFile::doesFileExist(locationOfResources+"levels/levels")) {
        DEB("File containing the levels not found at location: " << (locationOfResources+"levels/levels"));
        assert(false);
    }
    else if(!ofFile::doesFileExist(locationOfResources+"levels/defaultlevels")) {
        DEB("File containing the levels not found at location: " << (locationOfResources+"levels/defaultlevels"));
        assert(false);
    }
    else {
        vector<string> lines = ofSplitString(ofBufferFromFile(locationOfResources+"levels/levels"), "\n");
        for(int i = 0; i < lines.size(); ++i) {
            if(lines[i].size() > 2) {
                if(lines[i][0] == '/' && lines[i][1] == '/') { /* ignore */ }
                else {
                    ddd level;
                    deque<int> currentLayer;
                    int depth = 0;
                    string info = "";
                    bool gravity = false; keyType gravityDir = UP;
                    int j;
                    for(j = 0; j < lines[i].size(); ++j) {
                        char c = lines[i][j];
                        if(c == '{') {
                            depth++;
                            info = "";
                        }
                        else if(c == '}') {
                            depth--;
                            if(depth == 1) {
                                currentLayer.push_back(stoi(info));
                                info = "";
                                level.push_back(currentLayer);
                                currentLayer.clear();
                            }
                        }
                        else if(c == ',') {
                            if(depth == 2) {
                                currentLayer.push_back(stoi(info));
                                info = "";
                            }
                        }
                        else if(c >= '0' && c <= '9') info.push_back(c);
                        if(depth == 0) {
                            j++;
                            break;
                        }
                    }
                    for(; j < lines[i].size(); ++j) {
                        if(lines[i][j] == 'g') {
                            assert(j+1 < lines[i].size());
                            gravity = true;
                            assert(lines[i][j+1] == 'u' || lines[i][j+1] == 'd' || lines[i][j+1] == 'l' || lines[i][j+1] == 'r');
                            gravityDir = lines[i][j+1] == 'u' ? UP : lines[i][j+1] == 'd' ? DOWN : lines[i][j+1] == 'l' ? LEFT : lines[i][j+1] == 'r' ? RIGHT : UP;
                            ++j;
                        }
                    }
                    levels.push_back(level);
                    gravityLevels.push_back(gravity);
                    gravityDirections.push_back(gravityDir);
                }
            }
        }
        
        vector<string> lines2 = ofSplitString(ofBufferFromFile(locationOfResources+"levels/defaultlevels"), "\n");
        for(int i = 0; i < lines2.size(); ++i) {
            if(lines2[i].size() > 2) {
                if(lines2[i][0] == '/' && lines2[i][1] == '/') { /* ignore */ }
                else {
                    ddd level;
                    deque<int> currentLayer;
                    int depth = 0;
                    string info = "";
                    bool gravity = false; keyType gravityDir = UP;
                    int j;
                    for(j = 0; j < lines2[i].size(); ++j) {
                        char c = lines2[i][j];
                        if(c == '{') {
                            depth++;
                            info = "";
                        }
                        else if(c == '}') {
                            depth--;
                            if(depth == 1) {
                                currentLayer.push_back(stoi(info));
                                info = "";
                                level.push_back(currentLayer);
                                currentLayer.clear();
                            }
                        }
                        else if(c == ',') {
                            if(depth == 2) {
                                currentLayer.push_back(stoi(info));
                                info = "";
                            }
                        }
                        else if(c >= '0' && c <= '9') info.push_back(c);
                        
                        
                        if(depth == 0) {
                            j++;
                            break;
                        }
                    }
                    for(; j < lines2[i].size(); ++j) {
                        if(lines2[i][j] == 'g') {
                            assert(j+1 < lines2[i].size());
                            gravity = true;
                            assert(lines2[i][j+1] == 'u' || lines2[i][j+1] == 'd' || lines2[i][j+1] == 'l' || lines2[i][j+1] == 'r');
                            gravityDir = lines2[i][j+1] == 'u' ? UP : lines2[i][j+1] == 'd' ? DOWN : lines2[i][j+1] == 'l' ? LEFT : lines2[i][j+1] == 'r' ? RIGHT : UP;
                            ++j;
                        }
                    }
                    defaultlevels.push_back(level);
                    defaultGravityLevels.push_back(gravity);
                    defaultGravityDirections.push_back(gravityDir);
                }
            }
        }
    }
    if(levels.size() != defaultlevels.size()) cout << "The levels and defaultlevels files contain a different number of levels." << endl;
    assert(levels.size() == defaultlevels.size());

    for(int i = 0; i < levels.size(); ++i) {
        for(int j = 0; j < levels[i].size(); ++j) {
            if(levels[i][j].size() != levels[i][0].size()) {
                cout << "Level " << i+1 << " in levels is not rectangular, see row " << j+1 << endl;
                assert(false);
            }
        }
    }
    for(int i = 0; i < defaultlevels.size(); ++i) {
        for(int j = 0; j < defaultlevels[i].size(); ++j) {
            if(defaultlevels[i][j].size() != defaultlevels[i][0].size()) {
                cout << "Level " << i+1 << " in defaultlevels is not rectangular, see row " << j+1 << endl;
                assert(false);
            }
        }
    }
    
    for(int i = 0; i < levels.size(); ++i) {
        for(auto a : levels[i]) { for(int b : a) cout << b << ","; cout << "|";}
        cout << endl;
        cropBordersOf(levels[i]);
    }
    for(int i = 0; i < defaultlevels.size(); ++i) {
        cropBordersOf(defaultlevels[i]);
    }
    saveLevelData();
    //locationOfLevels;
}


#include <stdio.h> //for removing files
void saveLevelData() {
    ofFile writefile(locationOfResources+"levels/levels",ofFile::WriteOnly);
    for(int l = 0; l < levels.size(); ++l) {
        writefile << "Level "<<(l+1) << " =";
        writefile << "{";
        for(int i = 0; i < levels[l].size(); ++i) {
            writefile << "{";
            for(int j = 0; j < levels[l][i].size(); ++j) {
                writefile << levels[l][i][j];
                if(j + 1 != levels[l][i].size()) writefile <<",";
            }
            writefile << "}";
            if(i + 1 != levels[l].size()) writefile << ",";
        }
        writefile << "}"; writefile << (gravityLevels[l] ? (gravityDirections[l] == UP ? "gu" : gravityDirections[l] == DOWN ? "gd" : gravityDirections[l] == LEFT ? "gl" : "gr") : "" );
        writefile << endl;
    }
}

void createLevels() {
    if(levels.size() == 0) loadLevelData();
    /*
    levels.clear();
    levels.push_back(l0);
    levels.push_back(l1);
    levels.push_back(l2);
    levels.push_back(l3);
    levels.push_back(l4);
    levels.push_back(l5);
    levels.push_back(l6);
    levels.push_back(l7);
    levels.push_back(l8);
    levels.push_back(l9);
    levels.push_back(l10);
    levels.push_back(l11);
    levels.push_back(l12);
    levels.push_back(l13);
    levels.push_back(l14);
    levels.push_back(l15);
    levels.push_back(l16);
    levels.push_back(l17);
    levels.push_back(l18);

    levels.push_back(l20);
    levels.push_back(l21);
    levels.push_back(l22);
    
    levels.push_back(l120);
    levels.push_back(l121);
    levels.push_back(l122);
    levels.push_back(l123);

    levels.push_back(l1027);
    levels.push_back(l1028);
    levels.push_back(l1029);
    levels.push_back(l1030);
    levels.push_back(l1031);
    levels.push_back(l1032);
    levels.push_back(l1033);
    levels.push_back(l1034);
    levels.push_back(l1035);
    levels.push_back(l1036);
    
    for(int i = 0; i < levels.size(); ++i) {
        cropBordersOf(levels[i]);
    }
     */
}


#endif
