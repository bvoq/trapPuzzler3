//
//  mainmenu.h
//  trapPuzzler3
//
//  Created by kdkdk on 17.09.17.
//
//

#ifndef mainmenu_h
#define mainmenu_h


//For reference

float displayLevelInMenu(deque<deque<int> > & theLevel, bool displayPlayer, int width, bool displayEyes);
ddd zenMode = {
    /*
    {2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000},
    {2000000,      1,      1,      1,      1,      1,      1,      1,2000000},
    {2000000,      1,      1,      1,      1,      1,      1,      1,2000000},
    {2000000,      0,      0,      0,      0,      0,      0,      0,2000000},
    {2000000,      0,      0,      0,      0,      0,      0,      0,2000000},
    {2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000}
     */
    {2000000,2000000,2000000,2000000,2000000},
    {2000000,      1,      1,      1,2000000},
    {2000000,      0,      0,      0,1000000},
    {2000000,      0,      0,      0,1000001},
    {2000000,      0,      0,      0,1000002},
    {2000000,      1,      1,      1,2000000},
    {2000000,2000000,2000000,2000000,2000000}
    };
ddd mainMenuLevel, mainMenuMoveLevel;

void updateCellularAutomaton(ddd & cellLevel, int & cellularAutomatonLevel, int seed) {
    assert(cellularAutomatonLevel >= 1);
    if(cellularAutomatonLevel < cellLevel.size()) {
        for(int j = 0; j < cellLevel[cellularAutomatonLevel].size(); ++j) {
            int cellValue = 0; //values of cellular automaton
            cellValue |= (j > 0 && cellLevel[cellularAutomatonLevel-1][j-1] != 0) ? 1 : 0;
            cellValue |= cellLevel[cellularAutomatonLevel-1][j] != 0 ? 2 : 0;
            cellValue |= (j+1 < cellLevel[cellularAutomatonLevel-1].size() && cellLevel[cellularAutomatonLevel-1][j+1] != 0) ? 4 : 0;
            
            if((seed >> cellValue) & 1) {
                cellLevel[cellularAutomatonLevel][j] = 2000000;
            }
            assert(cellValue >= 0 && cellValue <= 7);
        }
        cellularAutomatonLevel++;
    }
}

int menuwidth = 5;
int additionalsfxwidth = 10;
int startPoint = menuwidth + additionalsfxwidth;
int menulength = 16;
int structurewidth = 16;
int sfxlength = 8, sfxwidth = 15;//24; //looks cool with 31

deque<deque<int> > cellularAutomata () {
    deque<deque<int> > cellLevel = deque<deque<int> > (menulength+sfxlength, deque<int> (startPoint+structurewidth-1,0)); //mainMenuLevel = deque<deque<int> > (32, deque<int> (65,0));
    cellLevel[0][startPoint-1] = 2000000;
    //for(int i = 0; i < cellLevel[0].size(); ++i)  cellLevel[0][i] = rand() % 2 == 0 ? 0 : 2000000;
    
    int cellularAutomatonLevel = 1;
    int nseed = 636196562;//rand();//636196562; // 266285627
    cout << "CELLULAR AUTOMATON " << nseed << " " << endl;
    
    
    for(int i = 0; i < menulength+1; ++i) {
        if(i < menulength-1) updateCellularAutomaton(cellLevel, cellularAutomatonLevel, nseed);
        
        --i;
        for(int j = 0; i >= 0 && j < additionalsfxwidth+menuwidth; ++j) cellLevel[i][j] = 0;
        for(int j = additionalsfxwidth; i >= 0 && j < additionalsfxwidth+menuwidth; ++j) {
            if(j == additionalsfxwidth && i == 2) cellLevel[i][j] = 1000000;
            else if(j == additionalsfxwidth && i == menulength/3) cellLevel[i][j] = 1000001;
            else if(j == additionalsfxwidth && i == menulength/3*2) cellLevel[i][j] = 1000002;
            else if(j == additionalsfxwidth && i == menulength-3) cellLevel[i][j] = 1000003;
            
            else if(i < 1 || j < additionalsfxwidth+1 || i >= menulength-1 || j >= additionalsfxwidth + menuwidth - 1) cellLevel[i][j] = 2000001+i*menulength+j;
            
            else if(i < 2) cellLevel[i][j] = 1;
            else {}//air
        }
        ++i;
    }
    
    
    //cellLevel[cellLevel.size()-1][0] = 2000003;
    for(int i = 0; i < sfxwidth; ++i) {
        //if(i%2==0) {
        cellLevel[cellLevel.size()-3][i] = 2000003+i;
        cellLevel[cellLevel.size()-1][i] = 2000003;
    }
    for(int i = cellLevel[0].size()-1; i >= cellLevel[0].size()-sfxwidth; --i) {
        cellLevel[cellLevel.size()-3][i] = 2000003+i;
        cellLevel[cellLevel.size()-1][i] = 2000003;
    }
    cellLevel[cellLevel.size()-2][0] = 2000002;
    cellLevel[cellLevel.size()-2][sfxwidth-1] = 2000002;
    cellLevel[cellLevel.size()-2][cellLevel[0].size()-sfxwidth]=2000001;
    cellLevel[cellLevel.size()-2][cellLevel[0].size()-1]=2000001;
    
    cellLevel[cellLevel.size()-2][1+musicaudiolevel] = 2;
    cellLevel[cellLevel.size()-2][cellLevel[0].size()-sfxwidth+1+sfxaudiolevel] = 3;
    return cellLevel;
}

void initMainMenu() {
    mode = MAINMENU;
    assert(getCellType(2000000) == UNMOVABLE_ENEMY);
    mainMenuLevel = cellularAutomata();
    updateGrid(mainMenuLevel);
}

inline float getMenuTileWidth() {
    return min((getHeight() * 1.) / (grid.size()+2),  (getWidth() * 1.) / (grid[0].size()+2));
}

ofTrueTypeFont mainMenuFont; float previousMenuWidthForMainMenuFont = -2; //License see 1.4 http://theleagueof.github.io/licenses/ofl-faq.html
ofTrueTypeFont mainMenuFontLarge;
void displayMainMenu() {
    
    //cout << "I am displaying the main menu " << rand() << endl;
    ofPushMatrix();
    float menuWidth = max(getWidth(),getHeight());
    
    //ofTranslate(getWidth()/2-squareWidth/2,getHeight()/2-squareWidth/2);

    
    //ofTranslate((getWidth()-menuWidth)/1.5,(getHeight()-menuWidth)/2);
    //float singleMenuTileWidth = displayLevelInMenu(mainMenuLevel, true, menuWidth, false);
    
    float singleMenuTileWidth = getMenuTileWidth();
    
    /*if(renderMode == PARTIAL) displayLevelWORefresh();
    else*/ displayLevel(grid, moveGrid, movements);

    if(singleMenuTileWidth != previousMenuWidthForMainMenuFont) {
        mainMenuFont.load(locationOfResources + "font/Share/Share-Italic.ttf",singleMenuTileWidth/1.75);
        mainMenuFontLarge.load(locationOfResources + "font/Share/Share-BoldItalic.ttf",singleMenuTileWidth/1.75);
        previousMenuWidthForMainMenuFont = singleMenuTileWidth;
    }
    ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
    //ofTranslate(-singleMenuTileWidth*5, singleMenuTileWidth * 5);
    //ofScale(0.125/2.,0.125/2.);
    ofFill();
    /* For CinzelDecorative
    ofDrawRectangle(0, -singleMenuTileWidth, mainMenuFont.stringWidth("Zen-mode"), singleMenuTileWidth);
    ofSetColor(scheme.colorBACKGROUND);
    mainMenuFont.drawString("Zen-mode", 0, -singleMenuTileWidth*.25);
    */
    ofTranslate(.5*(getWidth()-singleMenuTileWidth*(grid[0].size()+2)),.5*(getHeight()-singleMenuTileWidth*(grid.size()+2)));
    float transX = .5*(getWidth()-singleMenuTileWidth*(grid[0].size()+2));
    float transY = .5*(getHeight()-singleMenuTileWidth*(grid.size()+2));
    ofTranslate((additionalsfxwidth)*singleMenuTileWidth,4*singleMenuTileWidth-.125/2.*singleMenuTileWidth);
    transX += (additionalsfxwidth)*singleMenuTileWidth;
    transY += 4*singleMenuTileWidth-.125/2.*singleMenuTileWidth;
    
    int locationOfPlayer1Y=0, gotoYOption = -1;
    
    for(int i = 1; i <= menulength; ++i) {
        if(moveGrid[i][additionalsfxwidth+1] == PLAYER) locationOfPlayer1Y = i;
    }
    
    if(getCellType(grid[2][additionalsfxwidth+1]) == PLAYER || (mousetouchY >=  -singleMenuTileWidth + transY && mousetouchY <= transY && mousetouchX >= transX - mainMenuFont.stringWidth("Story-mode") && mousetouchX <= transX)) {
        ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
        
        ofDrawRectangle(-mainMenuFont.stringWidth("Story-mode"), -singleMenuTileWidth, mainMenuFont.stringWidth("Story-mode"), singleMenuTileWidth);
        ofSetColor(scheme.colorBACKGROUND);
        mainMenuFont.drawString("Story-mode", -mainMenuFont.stringWidth("Story-mode"), -singleMenuTileWidth*.25);
    } else {
        ofSetColor(scheme.colorBACKGROUND);
        ofDrawRectangle(-mainMenuFont.stringWidth("Story-mode"), -singleMenuTileWidth, mainMenuFont.stringWidth("Story-mode"), singleMenuTileWidth);
        ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
        mainMenuFont.drawString("Story-mode", -mainMenuFont.stringWidth("Story-mode"), -singleMenuTileWidth*.25);
    }
    
    if(isMousePressed && (mousetouchY >=  -singleMenuTileWidth + transY && mousetouchY <= transY && mousetouchX >= transX - mainMenuFont.stringWidth("Story-mode") && mousetouchX <= transX)) {
        gotoYOption = 2;
    }
    if(getCellType(grid[2][additionalsfxwidth]) == PLAYER) {
        initMenu();
    }
    
    ofTranslate(0,3*singleMenuTileWidth);
    transY += 3*singleMenuTileWidth;
    
    if(getCellType(grid[menulength/3][additionalsfxwidth+1]) == PLAYER || (mousetouchY >=  -singleMenuTileWidth + transY && mousetouchY <= transY && mousetouchX >= transX - mainMenuFont.stringWidth("Zen-mode") && mousetouchX <= transX)) {
        ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
        
        ofDrawRectangle(-mainMenuFont.stringWidth("Zen-mode"), -singleMenuTileWidth, mainMenuFont.stringWidth("Zen-mode"), singleMenuTileWidth);
        ofSetColor(scheme.colorBACKGROUND);
        mainMenuFont.drawString("Zen-mode", -mainMenuFont.stringWidth("Zen-mode"), -singleMenuTileWidth*.25);
    } else {
        ofSetColor(scheme.colorBACKGROUND);
        ofDrawRectangle(-mainMenuFont.stringWidth("Zen-mode"), -singleMenuTileWidth, mainMenuFont.stringWidth("Zen-mode"), singleMenuTileWidth);
        ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
        mainMenuFont.drawString("Zen-mode", -mainMenuFont.stringWidth("Zen-mode"), -singleMenuTileWidth*.25);
    }

    if(isMousePressed && (mousetouchY >=  -singleMenuTileWidth + transY && mousetouchY <= transY && mousetouchX >= transX - mainMenuFont.stringWidth("Zen-mode") && mousetouchX <= transX)) {
        gotoYOption = menulength/3;
    }
    if(getCellType(grid[menulength/3][additionalsfxwidth]) == PLAYER) {
        initMenu();
    }
    
    ofTranslate(0,5*singleMenuTileWidth);
    transY += 5*singleMenuTileWidth;
    
    if(getCellType(grid[menulength/3*2][additionalsfxwidth+1]) == PLAYER || (mousetouchY >=  -singleMenuTileWidth + transY && mousetouchY <= transY && mousetouchX >= transX - mainMenuFont.stringWidth("Controls") && mousetouchX <= transX)) {
        ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
        
        ofDrawRectangle(-mainMenuFont.stringWidth("Controls"), -singleMenuTileWidth, mainMenuFont.stringWidth("Controls"), singleMenuTileWidth);
        ofSetColor(scheme.colorBACKGROUND);
        mainMenuFont.drawString("Controls", -mainMenuFont.stringWidth("Controls"), -singleMenuTileWidth*.25);
    } else {
        ofSetColor(scheme.colorBACKGROUND);
        ofDrawRectangle(-mainMenuFont.stringWidth("Controls"), -singleMenuTileWidth, mainMenuFont.stringWidth("Controls"), singleMenuTileWidth);
        ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
        mainMenuFont.drawString("Controls", -mainMenuFont.stringWidth("Controls"), -singleMenuTileWidth*.25);
    }
    if(isMousePressed && (mousetouchY >=  -singleMenuTileWidth + transY && mousetouchY <= transY && mousetouchX >= transX - mainMenuFont.stringWidth("Controls") && mousetouchX <= transX)) {
        gotoYOption = menulength/3*2;
    }
    if(getCellType(grid[menulength/3*2][additionalsfxwidth]) == PLAYER) {
        initMenu();
    }
    
    ofTranslate(0,3*singleMenuTileWidth);
    transY += 3*singleMenuTileWidth;
    
    if(getCellType(grid[menulength-3][additionalsfxwidth+1]) == PLAYER || (mousetouchY >=  -singleMenuTileWidth + transY && mousetouchY <= transY && mousetouchX >= transX - mainMenuFont.stringWidth("Credits") && mousetouchX <= transX) ) {
        ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
        
        ofDrawRectangle(-mainMenuFont.stringWidth("Credits"), -singleMenuTileWidth, mainMenuFont.stringWidth("Credits"), singleMenuTileWidth);
        ofSetColor(scheme.colorBACKGROUND);
        mainMenuFont.drawString("Credits", -mainMenuFont.stringWidth("Credits"), -singleMenuTileWidth*.25);
    } else {
        ofSetColor(scheme.colorBACKGROUND);
        ofDrawRectangle(-mainMenuFont.stringWidth("Credits"), -singleMenuTileWidth, mainMenuFont.stringWidth("Credits"), singleMenuTileWidth);
        ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
        mainMenuFont.drawString("Credits", -mainMenuFont.stringWidth("Credits"), -singleMenuTileWidth*.25);
    }
    
    if(isMousePressed && (mousetouchY >=  -singleMenuTileWidth + transY && mousetouchY <= transY && mousetouchX >= transX - mainMenuFont.stringWidth("Credits") && mousetouchX <= transX)) {
        gotoYOption = menulength-3;
    }
    if(getCellType(grid[menulength-3][additionalsfxwidth]) == PLAYER) {
        initMenu();
    }
    
    
    if(gotoYOption != -1 && movements.size() == 0) {
        screenShake(timeForMovement*2, LEFT, wallShakeIntensity);
        if(playerID != 1) {
            movement m = movement(moveGrid, moveGrid, moveEyeGrid, moveEyeGrid,
                                  CHANGE_TO_PLAYER, {}, false, timeForMovement, false, PLAYER_CHANGEMT
                                  );
            changePlayerIdDeterministic(moveGrid,playerID,false);
            m.newPlayerID = playerID;
            movements.push_back(m);
        }
        for(int i = locationOfPlayer1Y; i < gotoYOption; ++i) move(moveGrid, moveEyeGrid, playerID, DOWN, timeForMovement, false, true);
        for(int i = locationOfPlayer1Y; i > gotoYOption; --i) move(moveGrid, moveEyeGrid, playerID, UP, timeForMovement, false, true);
        move(moveGrid, moveEyeGrid, playerID, LEFT, timeForMovement, false, true);
    }
    
    
    
    
    //E R E V A D E
    ofTranslate(6*singleMenuTileWidth,(sfxlength/2)*singleMenuTileWidth);
    ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
    ofDrawRectangle(-mainMenuFontLarge.stringWidth("E r e v a d e")/2., -singleMenuTileWidth, mainMenuFontLarge.stringWidth("E r e v a d e"), singleMenuTileWidth);
    ofSetColor(scheme.colorBACKGROUND);
    mainMenuFontLarge.drawString("E r e v a d e", -mainMenuFontLarge.stringWidth("E r e v a d e")/2., -singleMenuTileWidth*.25);
    
    ofTranslate(0, singleMenuTileWidth);
    ofSetColor(scheme.colorBACKGROUND);
    ofDrawRectangle(-mainMenuFont.stringWidth("Made by kdkdk & Baege")/2., -singleMenuTileWidth, mainMenuFont.stringWidth("Made by kdkdk & Baege"), singleMenuTileWidth);
    ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
    mainMenuFont.drawString("Made by kdkdk & Baege", -mainMenuFont.stringWidth("Made by kdkdk & Baege")/2., -singleMenuTileWidth*.25);
    
    
    ofTranslate(0,-5*singleMenuTileWidth);
    ofTranslate(-7.5*singleMenuTileWidth,(sfxlength-1.5)*singleMenuTileWidth);
    if(playerID == 2) {
        ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
        ofDrawRectangle(-mainMenuFont.stringWidth("Music Volume")/2., -singleMenuTileWidth, mainMenuFont.stringWidth("Music Volume"), singleMenuTileWidth);
        ofSetColor(scheme.colorBACKGROUND);
        mainMenuFont.drawString("Music Volume", -mainMenuFont.stringWidth("Music Volume")/2., -singleMenuTileWidth*.25);
    } else {
        ofSetColor(scheme.colorBACKGROUND);
        ofDrawRectangle(-mainMenuFont.stringWidth("Music Volume")/2., -singleMenuTileWidth, mainMenuFont.stringWidth("Music Volume"), singleMenuTileWidth);
        ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
        mainMenuFont.drawString("Music Volume", -mainMenuFont.stringWidth("Music Volume")/2., -singleMenuTileWidth*.25);
    }
    
    ofTranslate(17.5*singleMenuTileWidth,0);
    if(playerID == 3) {
        ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
        ofDrawRectangle(-mainMenuFont.stringWidth("SFX Volume"), -singleMenuTileWidth, mainMenuFont.stringWidth("SFX Volume"), singleMenuTileWidth);
        ofSetColor(scheme.colorBACKGROUND);
        mainMenuFont.drawString("SFX Volume", -mainMenuFont.stringWidth("SFX Volume"), -singleMenuTileWidth*.25);
    } else {
        ofSetColor(scheme.colorBACKGROUND);
        ofDrawRectangle(-mainMenuFont.stringWidth("SFX Volume"), -singleMenuTileWidth, mainMenuFont.stringWidth("SFX Volume"), singleMenuTileWidth);
        ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
        mainMenuFont.drawString("SFX Volume", -mainMenuFont.stringWidth("SFX Volume"), -singleMenuTileWidth*.25);
    }
    
    //ofTranslate(-13*singleMenuTileWidth,-3*singleMenuTileWidth);
    

    //float singleMenuTileWidth = getMenuTileWidth();

    
    
    /*
    ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
    ofDrawRectangle(-mainMenuFont.stringWidth("Erevade"), singleMenuTileWidth);
    ofSetColor(scheme.colorBACKGROUND);
    mainMenuFont.drawString("Erevade",-mainMenuFont.stringWidth("Erevade")/2.,-singleMenuTileWidth*.25);
     */
    
    for(int i = 0; i < sfxwidth-2; ++i) {
        if(getCellType(grid[grid.size()-2][1+i]) == PLAYER && musicaudiolevel != i) {
            musicaudiolevel = i;
            cout << "SET MUSIC AUDIO LEVEL TO " << i << endl;
            saveSaveData();
            updateVolume();
        }
        if(getCellType(grid[grid.size()-2][grid[0].size()+1-sfxwidth+i]) == PLAYER && sfxaudiolevel != i) {
            sfxaudiolevel = i;
            cout << "SET AUDIO LEVEL TO " << i << endl;
            saveSaveData();
            updateVolume();
        }
    }
    
    
    
    //cout << "HEYO " << moveGrid.size() << endl;
    ofPopMatrix();
    
}

/*
void initCredits() {
    mode = CREDITS;
    assert(getCellType(2000000) == UNMOVABLE_ENEMY);
    mainMenuLevel = cellularAutomata();
    updateGrid(mainMenuLevel);
}*/
#endif /* mainmenu_h */
