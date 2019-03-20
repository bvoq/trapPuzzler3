#include "levelEditorIDE.h"

#include "ofMain.h"

#include "globals.h"
#include "colorScheme.h"
#include "keyMap.h"

using namespace std;

bool activeIDE = false;
float ideFactor = 3./7; //how much of the screen should be IDE

vector<string> ideString = {
    "[ > Player | Crate ] -> [ > Player | > Crate ]",
    "[ > Player | Crate ] -> [ > Player | > Crate ]",
    "[ > Player | Crate ] -> [ > Player | > Crate ]"};

static pair<int,int> cursorPos;
static float ideWidth = -1, prevIdeWidth = -2;
static int ideLongestSentence = -1, prevIdeLongestSentence = -2;

static ofTrueTypeFont ideFont; //License see 1.4 http://theleagueof.github.io/licenses/ofl-faq.html

void initLevelEditorIDE() {
    activeIDE = false;
    cursorPos = {1,4};
}

void switchToIDE() {
    activeIDE = true;
}

void displayLevelEditorIDE() {
    ideWidth = ofGetWidth() * ideFactor;
    ideLongestSentence = 72;
    for(const auto & t : ideString) ideLongestSentence = MAX(ideLongestSentence, t.size() + 15);
    
    if(prevIdeWidth != ideWidth || prevIdeLongestSentence != ideLongestSentence) {
        //load a font relative to the width of the display editor (might change later)
        cout << "Loading font: " << locationOfResources + "font/Inconsolata/Inconsolata-Regular.ttf" << " of size " << ideWidth * 1./46*1./72 * ideLongestSentence << endl;
        ideFont.load(locationOfResources + "font/Inconsolata/Inconsolata-Regular.ttf",ideWidth * 1./46 * 72/ideLongestSentence);
        prevIdeWidth = ideWidth;
        prevIdeLongestSentence = ideLongestSentence;
    }
    
    int lineHeight = ideFont.getLineHeight();
    ofFill();
    ofSetColor(scheme.colorIDE_BACKGROUND);
    ofDrawRectangle(ofGetWidth()-ideWidth,0,ideWidth,ofGetHeight());
    ofNoFill();
    ofSetColor(scheme.colorIDE_TEXT);
    for(int i = 0; i < ideString.size();++i) {
        ideFont.drawString(ideString[i], ofGetWidth()-ideWidth,ofGetHeight()/24+i*lineHeight);
    }
    
    if(activeIDE) {
        string stringToGetWidth = ideString[cursorPos.first].substr(0,cursorPos.second);
        for(int i=stringToGetWidth.size()-1;i>=0;i--) if(stringToGetWidth[i] == ' ') stringToGetWidth[i] = '_';
        
        int widthOfStringUntilCursor = ideFont.stringWidth(stringToGetWidth);
        int widthOfCharacterOnCursor = ideFont.stringWidth("W"); //getGlyphBBox().getWidth();
        
        int heightBetween0lineAndNextLine = (ideFont.stringHeight("q")- ideFont.stringHeight("a"))*2./3;
        
        ofFill();
        ofSetColor(scheme.colorIDE_CURSOR, 0x90);
        
        if(ofGetElapsedTimeMicros() % 1000000 < 750000)
            ofDrawRectangle(ofGetWidth()-ideWidth + widthOfStringUntilCursor, ofGetHeight()/24+cursorPos.first*lineHeight - lineHeight + heightBetween0lineAndNextLine, widthOfCharacterOnCursor, lineHeight);
        ofSetColor(0xAAAAAA,0x90);
        ofDrawRectangle(0,0,ofGetWidth()-ideWidth,ofGetHeight());
    } else {
        ofFill();
        ofSetColor(0xAAAAAA,0x90);
        ofDrawRectangle(ofGetWidth()-ideWidth,0,ideWidth,ofGetHeight());
    }
}

void ideKeyPressed(int key, bool isSuperKey) {
    cout << key << endl;
    if(!isSuperKey && key >= 32 && key <= 126) {
        ideString[cursorPos.first] = ideString[cursorPos.first].substr(0, cursorPos.second) + (char)key + ideString[cursorPos.first].substr(cursorPos.second);
        cursorPos.second++;
    } else {
        switch(key) {
            case 13: // enter macOS
            {
                string str1 = ideString[cursorPos.first].substr(0,cursorPos.second);
                string str2 = ideString[cursorPos.first].substr(cursorPos.second);
                
                ideString.insert(ideString.begin()+cursorPos.first+1, str2);
                ideString[cursorPos.first] = str1;
                cursorPos.first++;
                cursorPos.second = 0;
            }
                break;
            case 8: // delete macOS
                if(cursorPos.first == 0 && cursorPos.second == 0) {}
                else if(cursorPos.second == 0) {
                    cursorPos.second = ideString[cursorPos.first-1].size();
                    ideString[cursorPos.first-1] += ideString[cursorPos.first];
                    ideString.erase(ideString.begin()+cursorPos.first);
                    cursorPos.first--;
                }
                else {
                    ideString[cursorPos.first] = ideString[cursorPos.first].substr(0,cursorPos.second-1) + ideString[cursorPos.first].substr(cursorPos.second);
                    cursorPos.second--;
                }
                break;
                
            case 356: //left windows
            case 57356: //left macOS
                if(cursorPos.second > 0)
                    cursorPos.second--;
                else if(cursorPos.first > 0)
                    cursorPos.second = ideString[--cursorPos.first].size();
                
                break;
                
            case 357: //up windows
            case 57357: //up macOS
                if(cursorPos.first == 0) cursorPos = {0,0};
                if(cursorPos.first > 0) {
                    cursorPos.first--;
                    if(ideString[cursorPos.first].size() <= cursorPos.second) cursorPos.second = ideString[cursorPos.first].size();
                }
                break;
                
                
            case 358: //right windows
            case 57358: //right macOS
                if(cursorPos.second < ideString[cursorPos.first].size())
                    cursorPos.second++;
                else if(cursorPos.first+1 < ideString.size()){
                    cursorPos.first++;
                    cursorPos.second = 0;
                }
                break;
                
                
            case 359: //down windows
            case 57359: //down macOS
                if(cursorPos.first+1 == ideString.size()) cursorPos = {cursorPos.first,ideString[cursorPos.first].size()};
                else if(cursorPos.first+1 < ideString.size()) {
                    cursorPos.first++;
                    if(ideString[cursorPos.first].size() <= cursorPos.second) cursorPos.second = ideString[cursorPos.first].size();
                }
                break;
                
            case 118: //paste macOS if command is pressed (i think 22 if control is pressed)
            {
                string cmd = "pbpaste";
                FILE* pipe = popen(cmd.c_str(), "r");
                if (!pipe) break;
                char buffer[128];
                string result = "";
                while(!feof(pipe))
                {
                    if(fgets(buffer, 128, pipe) != NULL)
                    {
                        result += buffer;
                    }
                }
                pclose(pipe);
                for(char c : result) ideKeyPressed(c, false);
            }
                break;
            default:;
                cout << "unknown keytype " << keyMapper[key] << endl;
        }
    }
}
