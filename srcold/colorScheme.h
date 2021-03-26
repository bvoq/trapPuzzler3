
//
//  colorScheme.h
//  trapStory
//
//  Created by kdkdk on 28/12/15.
//
//

#ifndef compiledWithoutOpenframeworks
#ifndef colorScheme_h
#define colorScheme_h

#include "macros.h"

struct colorScheme {
    ofColor colorPLAYERSELECTED, colorPLAYERUNSELECTED, colorENEMY, colorENEMYSTROKE, colorUNMOVABLE_ENEMY, colorUNMOVABLE_ENEMYSTROKE, colorLOVE, colorLOVESTROKE, colorGRAVITYMONSTER, colorGRAVITYMONSTERSTROKE, colorBACKGROUND, colorBACKGROUND_LIGHT, colorBACKGROUND_SHADED, colorBACKGROUND_VOID, colorLEVELSELECT, colorLEVELSELECT_LIGHT, colorMESSAGE, colorMESSAGE_SHADED, colorTOOLBAR, colorTOOLBARBUTTON, colorTOOLBARBUTTON_LIGHT, colorTOOLBARBUTTON_SELECTED, colorTOOLBARBUTTON_SELECTED_LIGHT, colorIDE_BACKGROUND, colorIDE_TEXT, colorIDE_CURSOR, colorPENCILCOLOR_LOWERBASE, colorPENCILCOLOR_BASE, colorPENCILCOLOR_BODY, colorPENCILCOLOR_HEAD, colorPENCILCOLOR_FRAME;
    
    colorScheme(int _colorPLAYERSELECTED, int _colorPLAYERUNSELECTED, int _colorENEMY, int _colorENEMYSTROKE, int _colorUNMOVABLE_ENEMY, int _colorUNMOVABLE_ENEMYSTROKE, int _colorLOVE, int _colorLOVESTROKE, int _colorGRAVITYMONSTER, int _colorGRAVITYMONSTERSTROKE, int _colorBACKGROUND, int _colorBACKGROUND_LIGHT, int _colorBACKGROUND_SHADED, int _colorBACKGROUND_VOID, int _colorLEVELSELECT, int _colorLEVELSELECT_LIGHT, int _colorMESSAGE, int _colorMESSAGE_SHADED, int _colorTOOLBAR, int _colorTOOLBARBUTTON, int _colorTOOLBARBUTTON_LIGHT, int _colorTOOLBARBUTTON_SELECTED, int _colorTOOLBARBUTTON_SELECTED_LIGHT, int _colorIDE_BACKGROUND, int _colorIDE_TEXT, int _colorIDE_CURSOR, int _colorPENCILCOLOR_LOWERBASE, int _colorPENCILCOLOR_BASE, int _colorPENCILCOLOR_BODY, int _colorPENCILCOLOR_HEAD, int _colorPENCILCOLOR_FRAME) {
        
        colorPLAYERSELECTED.setHex(_colorPLAYERSELECTED);
        colorPLAYERUNSELECTED.setHex(_colorPLAYERUNSELECTED);
        colorENEMY.setHex(_colorENEMY);
        colorENEMYSTROKE.setHex(_colorENEMYSTROKE);
        colorUNMOVABLE_ENEMY.setHex(_colorUNMOVABLE_ENEMY);
        colorUNMOVABLE_ENEMYSTROKE.setHex(_colorUNMOVABLE_ENEMYSTROKE);
        colorLOVE.setHex(_colorLOVE);
        colorLOVESTROKE.setHex(_colorLOVESTROKE);
        colorGRAVITYMONSTER.setHex(_colorGRAVITYMONSTER);
        colorGRAVITYMONSTERSTROKE.setHex(_colorGRAVITYMONSTERSTROKE);
        colorBACKGROUND.setHex(_colorBACKGROUND);
        colorBACKGROUND_LIGHT.setHex(_colorBACKGROUND_LIGHT);
        colorBACKGROUND_SHADED.setHex(_colorBACKGROUND_SHADED);
        colorBACKGROUND_VOID.setHex(_colorBACKGROUND_VOID);
        colorLEVELSELECT.setHex(_colorLEVELSELECT);
        colorLEVELSELECT_LIGHT.setHex(_colorLEVELSELECT_LIGHT);
        colorMESSAGE.setHex(_colorMESSAGE, 0); //add transperancy
        colorMESSAGE_SHADED.setHex(_colorMESSAGE_SHADED, 0); //add transperancy
        colorTOOLBAR.setHex(_colorTOOLBAR);
        colorTOOLBARBUTTON.setHex(_colorTOOLBARBUTTON);
        colorTOOLBARBUTTON_LIGHT.setHex(_colorTOOLBARBUTTON_LIGHT);
        colorTOOLBARBUTTON_SELECTED.setHex(_colorTOOLBARBUTTON_SELECTED);
        colorTOOLBARBUTTON_SELECTED_LIGHT.setHex(_colorTOOLBARBUTTON_SELECTED_LIGHT);
        colorIDE_BACKGROUND.setHex(_colorIDE_BACKGROUND);
        colorIDE_TEXT.setHex(_colorIDE_TEXT);
        colorIDE_CURSOR.setHex(_colorIDE_CURSOR);
        colorPENCILCOLOR_LOWERBASE.setHex(_colorPENCILCOLOR_LOWERBASE);
        colorPENCILCOLOR_BASE.setHex(_colorPENCILCOLOR_BASE);
        colorPENCILCOLOR_BODY.setHex(_colorPENCILCOLOR_BODY);
        colorPENCILCOLOR_HEAD.setHex(_colorPENCILCOLOR_HEAD);
        colorPENCILCOLOR_FRAME.setHex(_colorPENCILCOLOR_FRAME);
        
    }
    
};


extern colorScheme scheme;
extern colorScheme scheme0;
extern colorScheme scheme1;

#endif
#endif
