#include "ofApp.h"
#include "includes.h"

//--------------------------------------------------------------
void ofApp::setup(){	
    cout << "You must run this code from the folder in which the binary is contained." << endl;
    //ofDisableDataPath();
    //ofSetDataPathRoot("data"); //this is for future use!!
    //SEE ALSO OFAPP.CPP AT THE SETUP
    
    //for ios use the Documents directory:
    char *home = getenv("HOME");
    string subdir = "/Library/Documents/";
    
    locationOfSavesLevels = string(home) + subdir;
    ofDirectory iosdocuments(locationOfSavesLevels);
    ofDirectory saves("saves");
    ofDirectory lvls("levels");
    ofDirectory savesdir(iosdocuments.getAbsolutePath()+"/saves");
    if(!savesdir.exists()) {
        iosdocuments.createDirectory("");
        saves.copyTo(iosdocuments.getAbsolutePath()+"/saves");
        lvls.copyTo(iosdocuments.getAbsolutePath()+"/levels");
    }
    //populate the directory object
    /*
    dir2.listDir();
    cout << "main path: " << dir2.getAbsolutePath() << endl;
    for(const auto & file : dir2.getFiles()) {
        cout << file.getAbsolutePath() << endl;
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
void ofApp::exit(){

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
void ofApp::touchDown(ofTouchEventArgs & touch){
    mousetouchY = touch.y;
    mousetouchX = touch.x;
    mouseTouchDown(touch.y, touch.x, 1);
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){
    mousetouchY = touch.y;
    mousetouchX = touch.x;
    mouseTouchMoved(touch.y,touch.x,1);
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){
    mousetouchY = touch.y;
    mousetouchX = touch.x;
    mouseTouchUp(touch.y,touch.x,1);
}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){
    mousetouchY = touch.y;
    mousetouchX = touch.x;
}

//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs & touch){
    mousetouchY = touch.y;
    mousetouchX = touch.x;
}

//--------------------------------------------------------------
void ofApp::lostFocus(){

}

//--------------------------------------------------------------
void ofApp::gotFocus(){

}

//--------------------------------------------------------------
void ofApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation){

}
