#include "ofApp.h"
#include "includes.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cout << "You must run this code from the folder in which the binary is contained." << endl;
    ofDisableDataPath();
    //ofSetDataPathRoot(locationOfResources); //this is for future use!!
    //SEE ALSO OFAPP.CPP AT THE SETUP
    
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
        if(mode == CONTROL_CHANGE && setRemapKey) {
            keyMapper[key] = remapKey;
        }
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
    for(auto & a : keyPressedDown)
    {
        if(timeWaitForRepress.count(a.first) == 0) timeWaitForRepress[a.first] = false;
        if(a.first == UP || a.first == DOWN || a.first == LEFT || a.first == RIGHT || a.first == PLAYER_CHANGE) {
            if(movements.size() == 0 && (timeWaitForRepress[a.first] || (timeWaitForRepress[a.first]==false && ofGetElapsedTimeMicros() > a.second.first + timeForKeypressWait) )) {
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
