
//
//  updateGrid.h
//  trapStory2
//
//  Created by Kivifreak on 31/12/15.
//
//

#ifndef trapPuzzler3_updateGrid_h
#define trapPuzzler3_updateGrid_h

void loadLevel(int level) {
    createLevels();
    if(level == -1 && editorGrid.size() > 0 && editorGrid[0].size() > 0) {
        //currentLevel = -1; In editor mode, but old level ID should be kept.
        deque<deque<int> > copyLevel = editorGrid;
        cropBordersOf(copyLevel);
        if(copyLevel.size() > 0 && copyLevel[0].size() > 0) { //Cannot load an empty level.
            mode = LEVEL_EDITOR_PLAYING;
            updateGrid(copyLevel);
        }
        //TODO - REDO
        // gravityLevel = gravityLevels[currentLevel]; //can be changed, currently take it from currentLevel
        // gravityDirection = gravityDirections[currentLevel];
    }
    else if(level >= levels.size()) {
        //currentLevel = level;
        //mode = PLAYING;
        DEB("Loading inexistant level: " << level << ". Current amount of levels = " << levels.size());
    }
    else {
        if(levels[level].size() > 0 && levels[level][0].size() > 0) { //Cannot load an empty level.
            
            //Messages come here !!!
            if(level == 0) {/*
                addMessage({"This is the story of","a little yellow squarish blob."}, 4);
                addMessage({"Although he was little,","he dreamt about a bigger world."}, 4);
                addMessage({"He wanted to know what","the world was made of,"}, 4);
                addMessage({"but his red neighbors just stared","at him with boredom in their eyes."}, 4);
                addMessage({"They must've turned red from boredom","the little blob thought."}, 4);
                addMessage({"He took all his courage and finally decided","to leave these miserable people."}, 4);
                addMessage({"But little did he know,","what he got himself into."}, 4);
                addMessage({"Move him using","the arrow keys or WASD"}, 4);*/
            }
        
            mode = PLAYING;
            DEB("Init level: " << level);
            updateGrid(levels[level]);
            
            levelInfo = levelsInfo[level];
        }
    }
}

void updateGrid(deque<deque<int> > newGrid) {
    blockMovementDueToWinningAnimation = false;
    forceUndo = false;
    
    timeForMovement = timeForSlowMovement;
    
    switchRenderMode(PARTIAL);
    backgroundColor = scheme.colorBACKGROUND;
    ofBackground(backgroundColor); //call this once to update buffer
    //deque<movement> empty;
    //swap(movements, empty );
    movements.clear();
    previousMovements.clear();
    
    grid = newGrid;
    cropBordersOf(grid);
    moveGrid = grid;
    playerID = 1; //Autochange
    changePlayerIdDeterministic(moveGrid,playerID,false);
    //playerID = 1; //SHOULD BE THE CASE!!
    
    generateEyeGrid();
}

#endif
