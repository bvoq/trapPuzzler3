#include "ofMain.h"
#include "ofApp.h"

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    cout << "windows" << endl;
        //ofAppGlutWindow window;
    //window.setGlutDisplayString("rgba double samples>=4");
    ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
    ShowWindow (GetConsoleWindow(), SW_HIDE);

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
}
#else // _WIN32
//========================================================================
int main( ){
    //ofAppGlutWindow window;
    //window.setGlutDisplayString("rgba double samples>=4");
    ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());

}
#endif
