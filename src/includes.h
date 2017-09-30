
//
//  includes.h
//  trapStory2
//
//  Created by Kivifreak on 25/12/15.
//
//

#ifndef trapPuzzler3_includes_h
#define trapPuzzler3_includes_h

//For compability
//#define nogetvertices

//in %s at line %d
//Enormously useful for debugging:
//#define switchRenderMode printf("Calling switchRenderMode from %s at line %d in file %s.\n",__FUNCTION__,__LINE__,__FILE__);DEBUGswitchRenderModeDEBUG
//needs to overwrite the function and forward declarations using this method.

#include "globals.h"

#include "timeTaker.h"

#include "audio.h"
#include "keyMap.h"
#include "colorScheme.h"
#include "grid.h"
#include "eyes.h"
#include "levels.h"
#include "movement.h"
#include "displayLevel.h"
#include "levelEditor.h"
#include "toolbar.h"
#include "messages.h"
#include "updateGrid.h"
#include "saves.h"
#include "levelGen.h"
#include "puzzleSolver.h"
#include "keyEvent.h"
#include "menu.h"
#include "mouseTouchEvent.h"
#include "winningAnimation.h"
#include "screenShake.h"

#include "mainmenucredits.h"


#include "setupDrawEvent.h"


#endif
