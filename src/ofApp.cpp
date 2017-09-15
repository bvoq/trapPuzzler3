#include "ofApp.h"
#include "includes.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableDataPath();
    //ofSetDataPathRoot(locationOfResources); //this is for future use!!
    //SEE ALSO OFAPP.CPP AT THE SETUP
    
    ofSetBackgroundAuto(false);

    
    initAudio();
    
    initDefaultKeyMapping();
    ofSetEscapeQuitsApp(false); //Disable quit on escape key press.
    
    createLevels();
    loadSaveData();
    //loadLevel();
    
    
    initMenu();
    
    //generateFancyMeshes();
    //initLevelEditor(currentLevel);
    //generateSomeCoolLevels();
        
    playAudio(0);
}

//--------------------------------------------------------------
void ofApp::update(){
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
        if(keyPressedDown.count(keyMapper[key]) == 0 || keyPressedDown[keyMapper[key] ] == false) keyEvent(keyMapper[key]);
        keyPressedDown[keyMapper[key] ] = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    if(keyMapper.count(key) != 0) {
        if(keyPressedDown.count(keyMapper[key]) != 0) keyPressedDown[keyMapper[key]] = false;
    }
    DEB("Released key: " << key);
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
