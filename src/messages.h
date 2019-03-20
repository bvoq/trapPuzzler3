//
//  messages.h
//  trapPuzzler3
//
//  Created by kdkdk on 21.08.16.
//
//

#ifndef messages_h
#define messages_h

#include "macros.h"

extern deque<pair<vector<string>, long long> > message;

extern ofTrueTypeFont fontMessage; extern int previousWindowWidth; //License see 1.4 http://theleagueof.github.io/licenses/ofl-faq.html

extern long long dynamicTime;
extern void gradientFilledRect(float, float, float, float, ofColor, ofColor, ofColor, ofColor);
extern int messageSize, prevMessageSize;

extern vector<string> prevMessage;
extern void displayMessage();

extern void addMessage(vector<string> strMessage, int durationInSeconds);

#endif /* messages_h */
