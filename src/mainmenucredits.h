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

void checkMainMenuFont(float singleMenuTileWidth) {
    if(singleMenuTileWidth != previousMenuWidthForMainMenuFont) {
        mainMenuFont.load(locationOfResources + "font/Share/Share-Italic.ttf",singleMenuTileWidth/1.75);
        mainMenuFontLarge.load(locationOfResources + "font/Share/Share-BoldItalic.ttf",singleMenuTileWidth/1.75);
        previousMenuWidthForMainMenuFont = singleMenuTileWidth;
        if(renderMode == PARTIAL) {switchRenderMode(PARTIAL);} //clears screen (or should)
        displayLevel(grid, moveGrid, movements);

    }
}

void highlightedMainMenuPrintRightAligned(string toprint, float singleMenuTileWidth) {
    ofFill();
    ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
    ofDrawRectangle(-mainMenuFont.stringWidth(toprint), -singleMenuTileWidth, mainMenuFont.stringWidth(toprint), singleMenuTileWidth);
    ofSetColor(scheme.colorBACKGROUND);
    mainMenuFont.drawString(toprint, -mainMenuFont.stringWidth(toprint), -singleMenuTileWidth*.25);
}

void unhighlightedMainMenuPrintRightAligned(string toprint, float singleMenuTileWidth) {
    ofFill();
    ofSetColor(scheme.colorBACKGROUND);
    ofDrawRectangle(-mainMenuFont.stringWidth(toprint), -singleMenuTileWidth, mainMenuFont.stringWidth(toprint), singleMenuTileWidth);
    ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
    mainMenuFont.drawString(toprint, -mainMenuFont.stringWidth(toprint), -singleMenuTileWidth*.25);
}

void highlightedMainMenuPrintCentered(string toprint, float singleMenuTileWidth) {
    ofFill();
    ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
    ofDrawRectangle(-mainMenuFont.stringWidth(toprint)/2., -singleMenuTileWidth, mainMenuFont.stringWidth(toprint), singleMenuTileWidth);
    ofSetColor(scheme.colorBACKGROUND);
    mainMenuFont.drawString(toprint, -mainMenuFont.stringWidth(toprint)/2., -singleMenuTileWidth*.25);
}

void unhighlightedMainMenuPrintCentered(string toprint, float singleMenuTileWidth) {
    ofFill();
    ofSetColor(scheme.colorBACKGROUND);
    ofDrawRectangle(-mainMenuFont.stringWidth(toprint)/2., -singleMenuTileWidth, mainMenuFont.stringWidth(toprint), singleMenuTileWidth);
    ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
    mainMenuFont.drawString(toprint, -mainMenuFont.stringWidth(toprint)/2., -singleMenuTileWidth*.25);
}

void highlightedMainMenuPrintLeftAligned(string toprint, float singleMenuTileWidth) {
    ofFill();
    ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
    ofDrawRectangle(0, -singleMenuTileWidth, mainMenuFont.stringWidth(toprint), singleMenuTileWidth);
    ofSetColor(scheme.colorBACKGROUND);
    mainMenuFont.drawString(toprint, 0, -singleMenuTileWidth*.25);
}

void unhighlightedMainMenuPrintLeftAligned(string toprint, float singleMenuTileWidth) {
    ofFill();
    ofSetColor(scheme.colorBACKGROUND);
    ofDrawRectangle(0, -singleMenuTileWidth, mainMenuFont.stringWidth(toprint), singleMenuTileWidth);
    ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
    mainMenuFont.drawString(toprint, 0, -singleMenuTileWidth*.25);
}


void initCredits();
void initControlChange();
void displayMainMenu() {
    ofFill();
    //cout << "I am displaying the main menu " << rand() << endl;
    ofPushMatrix();
    float menuWidth = max(getWidth(),getHeight());
    
    //ofTranslate(getWidth()/2-squareWidth/2,getHeight()/2-squareWidth/2);

    
    //ofTranslate((getWidth()-menuWidth)/1.5,(getHeight()-menuWidth)/2);
    //float singleMenuTileWidth = displayLevelInMenu(mainMenuLevel, true, menuWidth, false);
    
    float singleMenuTileWidth = getMenuTileWidth();

    checkMainMenuFont(singleMenuTileWidth);
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
    
    //STORY-MODE
    if(getCellType(grid[2][additionalsfxwidth+1]) == PLAYER || (mousetouchY >=  -singleMenuTileWidth + transY && mousetouchY <= transY && mousetouchX >= transX - mainMenuFont.stringWidth("Story-mode") && mousetouchX <= transX)) {
        highlightedMainMenuPrintRightAligned("Story-mode", singleMenuTileWidth);
    } else {
        unhighlightedMainMenuPrintRightAligned("Story-mode", singleMenuTileWidth);
    }
    
    if(isMousePressed && (mousetouchY >=  -singleMenuTileWidth + transY && mousetouchY <= transY && mousetouchX >= transX - mainMenuFont.stringWidth("Story-mode") && mousetouchX <= transX)) {
        gotoYOption = 2;
    }
    if(getCellType(grid[2][additionalsfxwidth]) == PLAYER) {
        initMenu();
    }
    
    //ZEN-MODE
    ofTranslate(0,3*singleMenuTileWidth);
    transY += 3*singleMenuTileWidth;
    
    if(getCellType(grid[menulength/3][additionalsfxwidth+1]) == PLAYER || (mousetouchY >=  -singleMenuTileWidth + transY && mousetouchY <= transY && mousetouchX >= transX - mainMenuFont.stringWidth("Zen-mode") && mousetouchX <= transX)) {
        highlightedMainMenuPrintRightAligned("Zen-mode", singleMenuTileWidth);
    } else {
        unhighlightedMainMenuPrintRightAligned("Zen-mode", singleMenuTileWidth);
    }

    if(isMousePressed && (mousetouchY >=  -singleMenuTileWidth + transY && mousetouchY <= transY && mousetouchX >= transX - mainMenuFont.stringWidth("Zen-mode") && mousetouchX <= transX)) {
        gotoYOption = menulength/3;
    }
    if(getCellType(grid[menulength/3][additionalsfxwidth]) == PLAYER) {
        initMenu();
    }
    
    
    //CONTROLS
    ofTranslate(0,5*singleMenuTileWidth);
    transY += 5*singleMenuTileWidth;
    
    if(getCellType(grid[menulength/3*2][additionalsfxwidth+1]) == PLAYER || (mousetouchY >=  -singleMenuTileWidth + transY && mousetouchY <= transY && mousetouchX >= transX - mainMenuFont.stringWidth("Controls") && mousetouchX <= transX)) {
        highlightedMainMenuPrintRightAligned("Controls", singleMenuTileWidth);
    } else {
        unhighlightedMainMenuPrintRightAligned("Controls", singleMenuTileWidth);
    }
    if(isMousePressed && (mousetouchY >=  -singleMenuTileWidth + transY && mousetouchY <= transY && mousetouchX >= transX - mainMenuFont.stringWidth("Controls") && mousetouchX <= transX)) {
        gotoYOption = menulength/3*2;
    }
    if(getCellType(grid[menulength/3*2][additionalsfxwidth]) == PLAYER) {
        initControlChange();
    }
    
    //MAIN MENU
    ofTranslate(0,3*singleMenuTileWidth);
    transY += 3*singleMenuTileWidth;
    
    if(getCellType(grid[menulength-3][additionalsfxwidth+1]) == PLAYER || (mousetouchY >=  -singleMenuTileWidth + transY && mousetouchY <= transY && mousetouchX >= transX - mainMenuFont.stringWidth("Credits") && mousetouchX <= transX) ) {
        highlightedMainMenuPrintRightAligned("Credits", singleMenuTileWidth);
    } else {
        unhighlightedMainMenuPrintRightAligned("Credits", singleMenuTileWidth);
    }
    
    if(isMousePressed && (mousetouchY >=  -singleMenuTileWidth + transY && mousetouchY <= transY && mousetouchX >= transX - mainMenuFont.stringWidth("Credits") && mousetouchX <= transX)) {
        gotoYOption = menulength-3;
    }
    if(getCellType(grid[menulength-3][additionalsfxwidth]) == PLAYER) {
        initCredits();
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
    highlightedMainMenuPrintCentered("E r a v a d e", singleMenuTileWidth);
    
    ofTranslate(0, singleMenuTileWidth);
    unhighlightedMainMenuPrintCentered("Made by kdkdk & Baege", singleMenuTileWidth);
    
    ofTranslate(0,-5*singleMenuTileWidth);
    ofTranslate(-7.5*singleMenuTileWidth,(sfxlength-1.5)*singleMenuTileWidth);
    if(playerID == 2) {
        highlightedMainMenuPrintCentered("BGM Volume", singleMenuTileWidth);
    } else {
        unhighlightedMainMenuPrintCentered("BGM Volume", singleMenuTileWidth);
    }
    
    ofTranslate(15*singleMenuTileWidth,0);
    if(playerID == 3) {
        highlightedMainMenuPrintCentered("SFX Volume", singleMenuTileWidth);
    } else {
        unhighlightedMainMenuPrintCentered("SFX Volume", singleMenuTileWidth);
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
    
    
    
    ofPopMatrix();
    
}


void initCredits() {
    mode = CREDITS;
    assert(getCellType(2000000) == UNMOVABLE_ENEMY);
    if(renderMode == PARTIAL) {switchRenderMode(PARTIAL);}
}

void displayCredits() {
    ofFill();
    float singleMenuTileWidth = getMenuTileWidth();
    checkMainMenuFont(singleMenuTileWidth);
    
    ofPushMatrix();
    ofTranslate(getWidth()/2.-singleMenuTileWidth*3,singleMenuTileWidth*2);
    highlightedMainMenuPrintRightAligned("Developer 1", singleMenuTileWidth);
    ofTranslate(+singleMenuTileWidth*3,-singleMenuTileWidth);
    static ofImage kevinImg(locationOfResources + "imgs/kevin.jpg");
    kevinImg.draw(0,0,singleMenuTileWidth*4,singleMenuTileWidth*4);
    ofTranslate(-singleMenuTileWidth*3,+singleMenuTileWidth);
    ofTranslate(0,singleMenuTileWidth*1);
    unhighlightedMainMenuPrintRightAligned("Kevin Joël Philippe De Keyser (@kdkdkch)",singleMenuTileWidth);
    ofTranslate(0,singleMenuTileWidth*1);
    unhighlightedMainMenuPrintRightAligned("dekeyser.ch", singleMenuTileWidth);
    
    ofTranslate(singleMenuTileWidth*6, singleMenuTileWidth*grid.size()/4-2*singleMenuTileWidth);

    highlightedMainMenuPrintLeftAligned("Developer 2", singleMenuTileWidth);
    ofTranslate(0,singleMenuTileWidth*1);
    unhighlightedMainMenuPrintLeftAligned("Lukas Baege",singleMenuTileWidth);
    //ofTranslate(0,singleMenuTileWidth*1);
    //unhighlightedMainMenuPrintRightAligned("", singleMenuTileWidth);
    
    ofTranslate(-singleMenuTileWidth*6, singleMenuTileWidth*grid.size()/4-1*singleMenuTileWidth);
    highlightedMainMenuPrintRightAligned("BGM", singleMenuTileWidth);
    ofTranslate(+singleMenuTileWidth*3,-singleMenuTileWidth);
    static ofImage nightdriverImg(locationOfResources + "imgs/nightdriver.jpg");
    nightdriverImg.draw(0,0,singleMenuTileWidth*4,singleMenuTileWidth*4);
    ofTranslate(-singleMenuTileWidth*3,+singleMenuTileWidth);
    ofTranslate(0,singleMenuTileWidth*1);
    unhighlightedMainMenuPrintRightAligned("Night Driver",singleMenuTileWidth);
    ofTranslate(0,singleMenuTileWidth*1);
    unhighlightedMainMenuPrintRightAligned("nosoapradio.us",singleMenuTileWidth);
    
    ofTranslate(singleMenuTileWidth*6, singleMenuTileWidth*grid.size()/4-2*singleMenuTileWidth);
    highlightedMainMenuPrintLeftAligned("Font", singleMenuTileWidth);
    ofTranslate(0,singleMenuTileWidth*1);
    unhighlightedMainMenuPrintLeftAligned("Share by Carrois Apostrophe",singleMenuTileWidth);
    ofTranslate(0,singleMenuTileWidth*1);
    unhighlightedMainMenuPrintLeftAligned("carrois.com",singleMenuTileWidth);
    ofTranslate(0,singleMenuTileWidth*1);
    unhighlightedMainMenuPrintLeftAligned("fonts.google.com/specimen/Share",singleMenuTileWidth);
    ofPopMatrix();
}


void initControlChange() {
    mode = CONTROL_CHANGE;
    setRemapKey = false;
    remapKey = UNKNOWNKEYT;
    if(renderMode == PARTIAL) {switchRenderMode(PARTIAL);}
}

void displayKeyCode(string keyStr, keyType keyT, float singleMenuTileWidth, float & translationY) {
    ofFill();
    if(mousetouchY >= translationY && mousetouchY <= translationY + singleMenuTileWidth) {
        ofSetColor(scheme.colorUNMOVABLE_ENEMYSTROKE);
        ofDrawRectangle(-getWidth(),0,getWidth()*2,singleMenuTileWidth);
        if(isMousePressed) {
            setRemapKey = true;
            remapKey = keyT;
        }
    }
    
    if(remapKey == keyT && setRemapKey) {
        ofSetColor(scheme.colorENEMY);
        ofDrawRectangle(-getWidth(),0,getWidth()*2,singleMenuTileWidth);
    }
    
    ofTranslate(-singleMenuTileWidth*3,singleMenuTileWidth);
    unhighlightedMainMenuPrintRightAligned(keyStr,singleMenuTileWidth);
    string keycodesstr = "";
    for(auto k : keyMapper) if(k.second == keyT) {
        string kcstr = keycodeToStr(k.first);
        
        keycodesstr += (keycodesstr.size() != 0 ? "," : "") + to_string(k.first) + (kcstr.size() != 0 ? "(" : "") + kcstr +  (kcstr.size() != 0 ? ")" : "");
    }
    ofTranslate(+singleMenuTileWidth*6,0);
    unhighlightedMainMenuPrintLeftAligned(keycodesstr,singleMenuTileWidth);
    ofTranslate(-singleMenuTileWidth*3,0);
    translationY += singleMenuTileWidth;
    
}

void displayControlChange() {
    ofFill();
    float singleMenuTileWidth = getMenuTileWidth();
    checkMainMenuFont(singleMenuTileWidth);

    float translationY = 0;
    ofPushMatrix();
    ofTranslate(getWidth()/2.,singleMenuTileWidth*2);
    translationY += singleMenuTileWidth*2;
    highlightedMainMenuPrintCentered("Change controls", singleMenuTileWidth);
    ofTranslate(0,singleMenuTileWidth);
    translationY += singleMenuTileWidth;
    unhighlightedMainMenuPrintCentered("by clicking on a movement and pressing the key to remap", singleMenuTileWidth);
    ofTranslate(-singleMenuTileWidth*3,singleMenuTileWidth*3);
    translationY += singleMenuTileWidth*3;
    highlightedMainMenuPrintRightAligned("KEY", singleMenuTileWidth);
    ofTranslate(singleMenuTileWidth*6,0);
    highlightedMainMenuPrintLeftAligned("MAP CODES", singleMenuTileWidth);
    ofTranslate(-singleMenuTileWidth*3,0);
    
    displayKeyCode("Left",LEFT, singleMenuTileWidth, translationY);
    displayKeyCode("Right",RIGHT, singleMenuTileWidth, translationY);
    displayKeyCode("Up",UP, singleMenuTileWidth, translationY);
    displayKeyCode("Down",DOWN, singleMenuTileWidth, translationY);
    displayKeyCode("Change player",PLAYER_CHANGE, singleMenuTileWidth, translationY);
    displayKeyCode("Undo",UNDO, singleMenuTileWidth, translationY);
    displayKeyCode("Restart",RESTART, singleMenuTileWidth, translationY);
    displayKeyCode("Toggle toolbar",TOGGLE_TOOLBAR, singleMenuTileWidth, translationY);
    
    ofTranslate(0,singleMenuTileWidth*2);
    translationY += singleMenuTileWidth*2;
    highlightedMainMenuPrintCentered("LEVEL EDITOR KEYS", singleMenuTileWidth);
    
    displayKeyCode("Change to PLAYER",CHANGE_TO_PLAYER, singleMenuTileWidth, translationY);
    displayKeyCode("Change to MOVABLE BLOCK",CHANGE_TO_ENEMY, singleMenuTileWidth, translationY);
    displayKeyCode("Change to UNMOVABLE BLOCK",CHANGE_TO_UNMOVABLE_ENEMY, singleMenuTileWidth, translationY);
    displayKeyCode("Change to CONNECT BLOCK",CHANGE_TO_UNMOVABLE_ENEMY, singleMenuTileWidth, translationY);
    displayKeyCode("Change to RIGHT MONSTER MOUTH",CHANGE_TO_MONSTERMOUTH, singleMenuTileWidth, translationY);
    displayKeyCode("Change to RIGHT MONSTER EYE",CHANGE_TO_MONSTEREYE, singleMenuTileWidth, translationY);
    displayKeyCode("Change to DELETE TILE",CHANGE_TO_AIR, singleMenuTileWidth, translationY);
    displayKeyCode("Change to DELETE STRUCTURE",CHANGE_TO_SUPERAIR, singleMenuTileWidth, translationY);
    displayKeyCode("Clear level",CLEAR, singleMenuTileWidth, translationY);

    
    ofPopMatrix();
}
#endif /* mainmenu_h */
