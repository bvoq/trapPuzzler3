#include "levels.h"

#include "ofMain.h"
#include "globals.h"

#include "grid.h"
#include "keyMap.h"

using namespace std;

int currentLevel = 0;

vector<ddd > levels;
vector<ddd > defaultlevels;
vector<LevelInfo> levelsInfo;
vector<LevelInfo> defaultlevelsInfo;
vector<bool> beaten;


bool validateLevel(deque<deque<int> > & level, LevelInfo levelInfo) {
    for(int i = 0; i < level.size(); ++i) {
        if(level[i].size() != level[0].size()) {
            cout << "The level is not rectangular at row " << i << " compared to row 0." << endl;
            return false;
        }
    }
    return true;
}

//void saveLevelData();
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
        vector<string> lineswithcomments = ofSplitString(ofBufferFromFile(locationOfResources+"levels/levels"), "\n");
        
        vector<string> lines;
        bool iscomment = false; string currentstr = "";
        for(int i = 0; i < lineswithcomments.size(); ++i) {
            for(int j = 0; j < lineswithcomments[i].size();++j) {
                if(j+1<lineswithcomments[i].size() && lineswithcomments[i][j] == '/' && lineswithcomments[i][j+1] == '*' && !iscomment) {
                    iscomment = true;
                    j++;
                }
                else if(lineswithcomments[i][j] == '*' && lineswithcomments[i][j+1] == '/' && iscomment) {
                    iscomment = false;
                    j++;
                }
                else if(!iscomment) currentstr.push_back(lineswithcomments[i][j]);
            }
            if(currentstr.size() > 0) {
                lines.push_back(currentstr);
                currentstr = "";
            }
        }
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
                            if(depth == 0) {
                                j++;
                                break;
                            }
                        }
                        else if(c == ',') {
                            if(depth == 2) {
                                currentLayer.push_back(stoi(info));
                                info = "";
                            }
                        }
                        else if(c >= '0' && c <= '9') info.push_back(c);
                    }
                    for(; j < lines[i].size(); ++j) {
                        /*if(lines[i][j] == 'g') {
                         assert(j+1 < lines[i].size());
                         gravity = true;
                         assert(lines[i][j+1] == 'u' || lines[i][j+1] == 'd' || lines[i][j+1] == 'l' || lines[i][j+1] == 'r');
                         gravityDir = lines[i][j+1] == 'u' ? UP : lines[i][j+1] == 'd' ? DOWN : lines[i][j+1] == 'l' ? LEFT : lines[i][j+1] == 'r' ? RIGHT : UP;
                         ++j;
                         }*/
                    }
                    
                    for(int i = 0; i < level.size(); ++i) {
                        for(int j = 0; j < level[i].size(); ++j) {
                            if(getCellType(level[i][j]) == GRAVITYMONSTERMOUTH) {
                                //gravity = true;
                                //gravityDir = RIGHT;
                            }
                        }
                    }
                    levels.push_back(level);
                    LevelInfo tempLevelInfo = LevelInfo();
                    levelsInfo.push_back(tempLevelInfo);
                }
            }
        }
        
        vector<string> lines2withcomments = ofSplitString(ofBufferFromFile(locationOfResources+"levels/defaultlevels"), "\n");
        
        vector<string> lines2;
        iscomment = false; currentstr = "";
        for(int i = 0; i < lines2withcomments.size(); ++i) {
            for(int j = 0; j < lines2withcomments[i].size();++j) {
                if(j+1<lines2withcomments[i].size() && lines2withcomments[i][j] == '/' && lines2withcomments[i][j+1] == '*' && !iscomment) {
                    iscomment = true;
                    j++;
                }
                else if(lines2withcomments[i][j] == '*' && lines2withcomments[i][j+1] == '/' && iscomment) {
                    iscomment = false;
                    j++;
                }
                else if(!iscomment) currentstr.push_back(lines2withcomments[i][j]);
            }
            if(currentstr.size() > 0) {
                lines2.push_back(currentstr);
                currentstr = "";
            }
        }
        
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
                            if(depth == 0) {
                                j++;
                                break;
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
                        /*
                         if(lines2[i][j] == 'g') {
                         assert(j+1 < lines2[i].size());
                         gravity = true;
                         assert(lines2[i][j+1] == 'u' || lines2[i][j+1] == 'd' || lines2[i][j+1] == 'l' || lines2[i][j+1] == 'r');
                         //gravityDir = lines2[i][j+1] == 'u' ? UP : lines2[i][j+1] == 'd' ? DOWN : lines2[i][j+1] == 'l' ? LEFT : lines2[i][j+1] == 'r' ? RIGHT : UP;
                         ++j;
                         }*/
                    }
                    
                    for(int i = 0; i < level.size(); ++i) {
                        for(int j = 0; j < level[i].size(); ++j) {
                            if(getCellType(level[i][j]) == GRAVITYMONSTERMOUTH) {
                                //gravity = true;
                                //gravityDir = RIGHT;
                            }
                        }
                    }
                    
                    defaultlevels.push_back(level);
                    LevelInfo tempDefaultLevelInfo = LevelInfo();
                    defaultlevelsInfo.push_back(tempDefaultLevelInfo);
                }
            }
        }
    }
    if(levels.size() != defaultlevels.size()) cout << "The levels "<< levels.size() << " and defaultlevels "<< defaultlevels.size() << " files contain a different number of levels." << endl;
    assert(levels.size() == defaultlevels.size());
    
    for(int i = 0; i < levels.size(); ++i) {
        cout << "Validating level " << i+1 << endl;
        assert( validateLevel(levels[i],levelsInfo[i]) );
        assert( validateLevel(defaultlevels[i],defaultlevelsInfo[i]) );
        cropBordersOf(levels[i]);
        cropBordersOf(defaultlevels[i]);
        
    }
    cout << levels[0].size() << endl;
    saveLevelData();
    //locationOfLevels;
}


#include <stdio.h> //for removing files
void saveLevelData() {
    cout << "Saving world data to " << locationOfResources << "levels/levels" << endl;
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
        writefile << "}";
        //writefile << (levelsInfo[l].gravityLevel ? (levelsInfo[l].gravityDirection == UP ? "gu" : levelsInfo[l].gravityDirection == DOWN ? "gd" : levelsInfo[l].gravityDirection == LEFT ? "gl" : "gr") : "" );
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
