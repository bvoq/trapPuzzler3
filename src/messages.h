//
//  messages.h
//  trapPuzzler3
//
//  Created by kdkdk on 21.08.16.
//
//

#ifndef messages_h
#define messages_h

#include "bitsstdc.h"
#include "macros.h"

extern std::deque<std::pair<std::vector<string>, long long> > message;

extern ofTrueTypeFont fontMessage; extern int previousWindowWidth; //License see 1.4 http://theleagueof.github.io/licenses/ofl-faq.html

extern long long dynamicTime;
extern void gradientFilledRect(float, float, float, float, ofColor, ofColor, ofColor, ofColor);
extern int messageSize, prevMessageSize;

extern std::vector<std::string> prevMessage;
extern void displayMessage();

extern void addMessage(std::vector<std::string> strMessage, int durationInSeconds);

#endif /* messages_h */
