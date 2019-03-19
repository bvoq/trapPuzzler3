//
//  toolbar.h
//  trapPuzzler3
//
//  Created by kdkdk on 22.04.17.
//
//

#ifndef toolbar_h
#define toolbar_h

extern int toolbarX, toolbarY;

enum ToolbarOrientation {
    NOTOOLBAR=0, BOTTOMTOOLBAR=1
};

extern ToolbarOrientation toolbarOrientation;
extern bool messageBlockingToolbar; //maybe add this to message.h

extern int toolbarSize; //Will be dynamically overwritten, later in the code.

extern int getWidth();
extern int getHeight();
extern int getToolbarWidth();

extern void displayToolBar();

#endif /* toolbar_h */

