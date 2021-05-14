//
//  messages.h
//  trapPuzzler3
//
//  Created by kdkdk on 21.08.16.
//
//

#ifndef messages_h
#define messages_h

#include "displayLevel.h"
#include "toolbar.h"

deque<pair<vector<string>, long long> > message;

ofTrueTypeFont font; int previousWindowWidth = -1; //License see 1.4 http://theleagueof.github.io/licenses/ofl-faq.html

long long dynamicTime = 0;
void gradientFilledRect(float, float, float, float, ofColor, ofColor, ofColor, ofColor);
int prevMessageSize = 0;
vector<string> prevMessage = {""};
void displayMessage() {
    if(getWidth() != previousWindowWidth) {
        //mainMenuFont.load(locationOfResources + "font/Share/Share-Italic.ttf",singleMenuTileWidth/1.75);

        font.load(locationOfResources + "font/Share/Share-Regular.ttf",getWidth()/36);
        previousWindowWidth = getWidth();
    }
    
    while(message.size() > 0 && time(0) >= message.front().second) {
        message.pop_front();
        //TODO: Redraw everything since rescaling might be an issue.
        //Redraw message box if another message is still there, elsewise init message off.
        
        messageSize = 0;
        dynamicTime = getAdjustedTime();
        prevMessage = {""};
    }
    
    
    
    if(message.size() > 0) {
        messageSize = font.stringHeight("Tg") * (message.front().first.size()+1.5);
        prevMessageSize = messageSize;
        messageBlockingToolbar = true;
        if(renderMode == PARTIAL && message.front().first != prevMessage) { //might be a new textbox all around
            ofFill();
            ofSetColor(scheme.colorBACKGROUND);
            ofDrawRectangle(0, ofGetHeight() - messageSize, getWidth(), messageSize);
            
            if(!lightmode) ofSetColor(255,255,255);
            else ofSetColor(0);
            for(int i = message.front().first.size() - 1; i >= 0; --i) {
                font.drawString(message.front().first[i], getWidth()/2 - font.stringWidth(message.front().first[i])/2, ofGetHeight() - font.stringHeight("Tg") * (message.front().first.size() - i));
            }
        }
        else {
            if(!lightmode) ofSetColor(255,255,255);
            else ofSetColor(0);
            for(int i = message.front().first.size() - 1; i >= 0; --i) {
                font.drawString(message.front().first[i], getWidth()/2 - font.stringWidth(message.front().first[i])/2, ofGetHeight() - font.stringHeight("Tg") * (message.front().first.size() - i));
            }
        }
        prevMessage = message.front().first;
        messageSize = font.stringHeight("Tg") * (message.front().first.size()+1.5);
    }
    /*
    else if(dynamicTime > getAdjustedTime() - 500000) { //dynamic frame update
        messageBlockingToolbar = false;
        float scaleY = (getHeight()-toolbarSize) / (MAX(grid.size() + 2, MIN_CELL_SIZE) * 1.);
        messageSize = toolbarSize + scaleY + (prevMessageSize-toolbarSize-scaleY) * ( 1.0 - ( (getAdjustedTime() - dynamicTime)/500000.0 ) );
        cout << "Dynamically resizing " << toolbarSize << " " << rand() << endl;
        if(renderMode == PARTIAL) {switchRenderMode(PARTIAL);} //refresh window during change of toolbar from message.
        //TODO: Set message size dynamically AND update the frame if PARTIAL.
    } */else {
        messageBlockingToolbar = false;
        toolbarOrientation = BOTTOMTOOLBAR;
        if(renderMode == PARTIAL) {switchRenderMode(PARTIAL);}
        //switchRenderMode(FULL);
    }
    //cout << time(0) << " " << until << endl;
}

void addMessage(vector<string> strMessage, int durationInSeconds) {
    long long currentTime = time(0);
    if(message.size() > 0) currentTime = message.back().second;
    long long until = currentTime + durationInSeconds;
    message.push_back({strMessage, until});
    toolbarSize = (ofGetHeight()/20.);
}

#endif /* messages_h */
