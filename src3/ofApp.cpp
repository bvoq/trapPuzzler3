#include "ofApp.h"
#include "includes.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cout << "You must run this code from the folder in which the binary is contained." << endl;
    ofDisableDataPath(); //uncomment this for iPad
    //ofSetDataPathRoot(locationOfResources); //this is for future use!!
    //SEE ALSO OFAPP.CPP AT THE SETUP
    
    //for ios use the Documents directory:
    //char *home = getenv("HOME");
    
    
    /* OSX 
    char *home = getenv("HOME");
    cout << string(home) << endl;
    
    string subdir = "/Library/Application Support/trappuzzler/";
    
    locationOfSavesLevels = string(home) + subdir;
    cout << "locationOfSavesLevels: "  << locationOfSavesLevels << endl;
    std::filesystem::path pathToSaveFile = locationOfSavesLevels;
    ofDirectory iosdocuments(pathToSaveFile);
    ofDirectory saves("saves");
    ofDirectory lvls("levels");
    ofDirectory savesdir(iosdocuments.getAbsolutePath()+"/saves");
    if(!savesdir.exists()) {
        iosdocuments.createDirectory("");
        saves.copyTo(iosdocuments.getAbsolutePath()+"/saves");
        lvls.copyTo(iosdocuments.getAbsolutePath()+"/levels");
    }*/
    
    /* IOS
    char *home = getenv("HOME");
    //for ios:
    string subdir = "/Library/Documents/"; //for osx: "/Library/Application Support/trappuzzler/"
    
    locationOfSavesLevels = string(home) + subdir;
    cout << "locationOfSavesLevels: "  << locationOfSavesLevels << endl;
    ofDirectory iosdocuments(locationOfSavesLevels);
    ofDirectory saves("saves");
    ofDirectory lvls("levels");
    ofDirectory savesdir(iosdocuments.getAbsolutePath()+"/saves");
    if(!savesdir.exists()) {
        iosdocuments.createDirectory("");
        saves.copyTo(iosdocuments.getAbsolutePath()+"/saves");
        lvls.copyTo(iosdocuments.getAbsolutePath()+"/levels");
    }
    */
    initAudio();
    initDefaultKeyMapping();
    ofSetEscapeQuitsApp(false); //Disable quit on escape key press.

    createLevels();
    loadSaveData();
    //loadLevel();

    //Will change when accessing the menu.
    if(!beautifulGraphics) switchRenderMode(PARTIAL);
    else switchRenderMode(FULL);
    //initMenu();
    initMainMenu();

    //generateFancyMeshes();
    //initLevelEditor(currentLevel);
    //generateSomeCoolLevels();

    playAudio(0);
}

//--------------------------------------------------------------
void testForRekeyPress();
void ofApp::update(){
    testForRekeyPress();
    updateEvent();
}

//--------------------------------------------------------------
void ofApp::draw(){
    mousetouchY = ofGetAppPtr()->mouseY;
    mousetouchX = ofGetAppPtr()->mouseX;
    drawEventWithScreenShake();
}

//--------------------------------------------------------------

void ofApp::keyPressed(int key){
    if(keyMapper.count(key) != 0) {
        if(keyPressedDown.count(keyMapper[key]) == 0 || keyPressedDown[keyMapper[key] ].second == false) {
            keyPressedDown[keyMapper[key] ] = {ofGetElapsedTimeMicros(),true};
            keyEvent(keyMapper[key]);
        }
    }
    if(mode == CONTROL_CHANGE && setRemapKey) {
        if(keyMapper.count(key) == 0 || keyMapper[key] != remapKey) keyMapper[key] = remapKey;
        else keyMapper[key] = UNKNOWNKEYT;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    if(keyMapper.count(key) != 0) {
        if(keyPressedDown.count(keyMapper[key]) != 0) {
            keyPressedDown[keyMapper[key]] = {LLONG_MAX,false};
            timeWaitForRepress[keyMapper[key]] = false;
        }
    }
    DEB("Released key: " << key);
}

void testForRekeyPress() {
    for(auto & a : keyPressedDown) {
        //Fast level scrolling can be fixed by checking
        if(timeWaitForRepress.count(a.first) == 0) timeWaitForRepress[a.first] = false;
        if(a.first == UP || a.first == DOWN || a.first == LEFT || a.first == RIGHT || a.first == PLAYER_CHANGE || a.first == UNDO) {
            if(movements.size() == 0 && ( (timeWaitForRepress[a.first]==true && ofGetElapsedTimeMicros() > a.second.first + timeForAnotherKeypressWait) || (timeWaitForRepress[a.first]==false && ofGetElapsedTimeMicros() > a.second.first + timeForKeypressWait) )) {
                a.second = {ofGetElapsedTimeMicros(),true};
                timeWaitForRepress[a.first] = true;
                keyEvent(a.first);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    mouseTouchMoved(y,x,button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mouseTouchDown(y, x, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    mouseTouchUp(y,x,button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    isWindowResized = 10;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

/*
void ofBaseApp::exit() {
    cout << "Exiting..." << endl;
    if(mode == LEVEL_EDITOR || mode == LEVEL_EDITOR_PLAYING) saveLevelData();
}
*/
