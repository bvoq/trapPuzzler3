//
//  keyEvent.h
//  trapPuzzler3
//
//  Created by kdkdk on 17.04.17.
//
//

//This is for key events on the keyboard, but also for iOS controls!

#ifndef keyEvent_h
#define keyEvent_h

void keyEvent (keyType kt) {
    if(mode == PLAYING || mode == LEVEL_EDITOR_PLAYING) {
        switch(kt) {
            case UP:
            case DOWN:
            case RIGHT:
            case LEFT:
                if(!blockMovementDueToWinningAnimation) move(kt, timeForMovement);
                break;
            case PLAYER_CHANGE:
                changePlayerIdRandom();
                break;
            case RESTART:
                if(mode == PLAYING) {
                    /*
                     for(int i = 0; i < grid.size(); ++i) for(int j = 0; j < grid[i].size(); ++j) {
                     cout << grid[i][j] << ((j==grid[i].size() - 1) ? "\n" : ((grid[i][j]< 1000) ? "\t\t" : "\t"));
                     }
                     */
                    if(grid == levels[currentLevel]) mode = MENU; ///!!! maybe remove
                    else loadLevel(currentLevel);
                }
                else if(mode == LEVEL_EDITOR_PLAYING) mode = LEVEL_EDITOR;
                break;
            case UNDO:
                undoMovement(timeForMovement);
                break;
            case SOLVE:
                cout << "SOLVABLE: " << tryForSolution() << endl; //! mark this
                break;
            case EXPORT:
                levelFormattedExportWithoutCropping(cout, moveEyeGrid);
                //!!!levelExport(cout, levels[currentLevel]);
                cout << endl;
                break;
            default:
                DEB("Unused keyMap: " << kt << " on key " << ("Inverse of keyMap[key], so key") << " in mode " << mode);
        }
    }
    else if(mode == LEVEL_EDITOR) {
        switch(kt) {
            case EXPORT:
                levelExport(cout, editorGrid);
                cout << endl;
                break;
            case RESTART:
                tilesToBePlaced.clear();
                loadLevel(-1);
                break;
            case UNDO:
                undoLevelEditorMove();
                break;
            case CHANGE_TO_AIR:
                changeBrush(AIR);
                break;
            case CHANGE_TO_PLAYER:
                changeBrush(PLAYER);
                break;
            case CHANGE_TO_ENEMY:
                changeBrush(ENEMY);
                break;
            case CHANGE_TO_UNMOVABLE_ENEMY:
                changeBrush(UNMOVABLE_ENEMY);
                break;
            case CHANGE_TO_SUPERAIR:
                changeBrush(SUPERAIR);
                break;
            case CLEAR:
                initLevelEditor(-1);
                break;
            case UP:
            case DOWN:
            case RIGHT:
            case LEFT:
                addLayer(kt);
                break;
            default:
                DEB("Unused keyMap: " << kt << " on key " << "(inv of keymap)" << " in mode " << mode);
        }
    }
    else if(mode == MENUOLD) {
    }
    else if(mode == MENU) {
        switch(kt) {
            case UP:
                if(currentLevel % 3 != 0) currentLevel--;
                break;
            case DOWN:
                if(currentLevel % 3 != 2 && levels.size() > currentLevel + 1) currentLevel++;
                break;
            case LEFT:
                if(currentLevel >= 3) currentLevel -= 3;
                break;
            case RIGHT:
                if(levels.size() > currentLevel + 3) currentLevel += 3;
                break;
            case PLAYER_CHANGE:
            {
                bool playable = true;
                if(currentLevel % 9 == 4) {
                    for(int i = 0; i < 9; ++i) {
                        if(i != 4 && beaten[currentLevel+i-4] == false) playable = false;
                    }
                }
                if(playable == true) {
                    if(levelEditorInMenu == false) loadLevel(currentLevel);
                    else if(beaten[currentLevel]) initLevelEditor(currentLevel);
                }
                break;
            }
            case SOLVE:
            {
                levelEditorInMenu = !levelEditorInMenu;
            }
                break;
            default:;
        }
    }
}

#endif /* keyEvent_h */
