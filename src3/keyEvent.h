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


void restart() {
    firstMovementHCI = true;
    if(mode == PLAYING) {
        /*
         for(int i = 0; i < grid.size(); ++i) for(int j = 0; j < grid[i].size(); ++j) {
         cout << grid[i][j] << ((j==grid[i].size() - 1) ? "\n" : ((grid[i][j]< 1000) ? "\t\t" : "\t"));
         }
         */
        if(grid == levels[currentLevel]) mode = MENU; ///!!! maybe remove
        else loadLevel(currentLevel, false);
    }
    else if(mode == LEVEL_EDITOR_PLAYING) mode = LEVEL_EDITOR;
}


void tryPlayLevel(int currentLevel, bool levelEditorInMenu) {
    bool playable = true;
    /*
    if(currentLevel % 9 == 4) {
        for(int i = 0; i < 9; ++i) {
            if(i != 4 && beaten[currentLevel+i-4] == false) playable = false;
        }
    }*/
    if(playable == true) {
        if(levelEditorInMenu == false) loadLevel(currentLevel, true);
        else if(beaten[currentLevel]) initLevelEditor(currentLevel,false);
    }
}

string keycodeToStr(int keycode) {
    string outstr = "";
    if(keycode >= 'A' && keycode <= 'Z') outstr = (char)keycode;
    else if(keycode >= 'a' && keycode <= 'z') outstr = (char)keycode;
    else if(keycode >= '0' && keycode <= '9') outstr = (char)keycode;
    else if(keycode == 13) outstr = "ENTER";
    else if(keycode == 32) outstr = "SPACE";
    else if(keycode == 356) outstr = "LEFT";
    else if(keycode == 357) outstr = "UP";
    else if(keycode == 358) outstr = "RIGHT";
    else if(keycode == 359) outstr = "DOWN";
    else if(keycode == 27) outstr = "ESC";
    return outstr;
}

void initMainMenu();
void keyEvent (keyType kt) {
    if(mode == PLAYING || mode == LEVEL_EDITOR_PLAYING || mode == MAINMENU) {
        switch(kt) {
            case UP:
            case DOWN:
            case RIGHT:
            case LEFT:
                if(!blockMovementDueToWinningAnimation && !forceUndo) move(moveGrid,moveEyeGrid,playerID,kt, timeForTypedMovement, false, true);
                break;
            case PLAYER_CHANGE:
                if(!blockMovementDueToWinningAnimation && !forceUndo) {
                    //only change player AFTER adding movement.
                    movement m = movement(moveGrid, moveGrid, moveEyeGrid, moveEyeGrid,
                                          CHANGE_TO_PLAYER, {}, false, timeForTypedMovement, false, PLAYER_CHANGEMT
                                          );
                    changePlayerIdDeterministic(moveGrid,playerID,false);
                    m.newPlayerID = playerID;
                    movements.push_back(m);
                }
                break;
        }
        
        if(mode == PLAYING || mode == LEVEL_EDITOR_PLAYING) {
            switch(kt) {
                case RESTART:
                    restart();
                break;
                case UNDO:
                    if(!blockMovementDueToWinningAnimation) undoMovement(maxUndoTime);
                break;
                case SOLVE:
                    if(mode == LEVEL_EDITOR_PLAYING) solveInGame(); //auto solver shouldn't work during the game, but is convenient to enable.
                    //cout << "SOLVABLE: " << tryForSolution() << endl; //! mark this
                break;
                case EXPORT:
                    levelFormattedExportWithoutCropping(cout, moveEyeGrid);
                    //!!!levelExport(cout, levels[currentLevel]);
                cout << endl;
                break;
                case TOGGLE_TOOLBAR:
                    if(toolbarOrientation == NOTOOLBAR) toolbarOrientation = BOTTOMTOOLBAR;
                    else if(toolbarOrientation == BOTTOMTOOLBAR) toolbarOrientation = NOTOOLBAR;
                    else assert(false);
                break;
            }
        }
            //default:
            //    DEB("Unused keyMap: " << kt << " on key " << ("Inverse of keyMap[key], so key") << " in mode " << mode);
        
    }
    else if(mode == LEVEL_EDITOR) {
        switch(kt) {
            case EXPORT:
                levelExport(cout, editorGrid);
                cout << endl;
                break;
            case RESTART:
                tilesToBePlaced.clear();
                loadLevel(-1, false);
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
            case CHANGE_TO_LOVE:
                changeBrush(LOVE);
                break;
            case CHANGE_TO_MONSTERMOUTH:
                changeBrush(GRAVITYMONSTERMOUTH);
                break;
            case CHANGE_TO_MONSTEREYE:
                changeBrush(GRAVITYMONSTEREYE);
                break;
            case CHANGE_TO_SUPERAIR:
                changeBrush(SUPERAIR);
                break;
            case CLEAR:
                initLevelEditor(currentLevel,true);
                break;
            case UP:
            case DOWN:
            case RIGHT:
            case LEFT:
                addLayer(kt);
                break;
            case TOGGLE_TOOLBAR:
                if(toolbarOrientation == NOTOOLBAR) toolbarOrientation = BOTTOMTOOLBAR;
                else if(toolbarOrientation == BOTTOMTOOLBAR) toolbarOrientation = NOTOOLBAR;
                else assert(false);
                break;
            case IMPROVE:
                improveLevelEditor();
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
                tryPlayLevel(currentLevel, levelEditorInMenu);
                break;
            }
            case SOLVE:
            {
                levelEditorInMenu = !levelEditorInMenu;
            }
                break;
            case TOGGLE_TOOLBAR:
                if(toolbarOrientation == NOTOOLBAR) toolbarOrientation = BOTTOMTOOLBAR;
                else if(toolbarOrientation == BOTTOMTOOLBAR) toolbarOrientation = NOTOOLBAR;
                else assert(false);
                break;
            case RESTART:
                initMainMenu();
                break;
            default:;
        }
    }
    else if(mode == CREDITS) {
        switch(kt) {
            case RESTART:
                initMainMenu();
                break;
            case TOGGLE_TOOLBAR:
                if(toolbarOrientation == NOTOOLBAR) toolbarOrientation = BOTTOMTOOLBAR;
                else if(toolbarOrientation == BOTTOMTOOLBAR) toolbarOrientation = NOTOOLBAR;
                else assert(false);
                break;
            default:;
        }
    }
    else if(mode == CONTROL_CHANGE) {
        if(!setRemapKey) {
            switch(kt) {
                case RESTART:
                    initMainMenu();
                    break;
                case TOGGLE_TOOLBAR:
                    if(toolbarOrientation == NOTOOLBAR) toolbarOrientation = BOTTOMTOOLBAR;
                    else if(toolbarOrientation == BOTTOMTOOLBAR) toolbarOrientation = NOTOOLBAR;
                    else assert(false);
                    break;
                default:;
            }
        }
    }
}

#endif /* keyEvent_h */
