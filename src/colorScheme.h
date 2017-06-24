
//
//  colorScheme.h
//  trapStory
//
//  Created by Kivifreak on 28/12/15.
//
//

#ifndef trapPuzzler3_colorScheme_h
#define trapPuzzler3_colorScheme_h

struct colorScheme {
    ofColor colorPLAYERSELECTED, colorPLAYERUNSELECTED, colorENEMY, colorENEMYSTROKE, colorUNMOVABLE_ENEMY, colorUNMOVABLE_ENEMYSTROKE, colorBACKGROUND, colorBACKGROUND_LIGHT, colorBACKGROUND_SHADED, colorBACKGROUND_VOID, colorLEVELSELECT, colorLEVELSELECT_LIGHT, colorMESSAGE, colorMESSAGE_SHADED, colorTOOLBAR, colorTOOLBARBUTTON, colorTOOLBARBUTTON_LIGHT, colorTOOLBARBUTTON_SELECTED, colorTOOLBARBUTTON_SELECTED_LIGHT;
    
    colorScheme(int _colorPLAYERSELECTED, int _colorPLAYERUNSELECTED, int _colorENEMY, int _colorENEMYSTROKE, int _colorUNMOVABLE_ENEMY, int _colorUNMOVABLE_ENEMYSTROKE, int _colorBACKGROUND, int _colorBACKGROUND_LIGHT, int _colorBACKGROUND_SHADED, int _colorBACKGROUND_VOID, int _colorLEVELSELECT, int _colorLEVELSELECT_LIGHT, int _colorMESSAGE, int _colorMESSAGE_SHADED, int _colorTOOLBAR, int _colorTOOLBARBUTTON, int _colorTOOLBARBUTTON_LIGHT, int _colorTOOLBARBUTTON_SELECTED, int _colorTOOLBARBUTTON_SELECTED_LIGHT) {
        
        colorPLAYERSELECTED.setHex(_colorPLAYERSELECTED);
        colorPLAYERUNSELECTED.setHex(_colorPLAYERUNSELECTED);
        colorENEMY.setHex(_colorENEMY);
        colorENEMYSTROKE.setHex(_colorENEMYSTROKE);
        colorUNMOVABLE_ENEMY.setHex(_colorUNMOVABLE_ENEMY);
        colorUNMOVABLE_ENEMYSTROKE.setHex(_colorUNMOVABLE_ENEMYSTROKE);
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
    }
    
};

//colorScheme blue (0x1240AB, 0x4671D5, 0x6C8CD5, 0x06266F);
colorScheme scheme0 (
                    0xF9FA00, //PLAYERSELECTED
                    0xFFFF99, //PLAYERUNSELECTED
                    0xFF6400, //ENEMY
                    0xFF0000, //ENEMYSTROKE
                    0x646464, //UNMOVABLE_ENEMY
                    0x000000, //UNMOVABLE_ENEMYSTROKE
                    0xC8C8C8, //BACKGROUND
                    0xDBDBDB, //BACKGROUND_LIGHT
                    0x666666, //BACKGROUND_SHADED
                    0x000000, //BACKGROUND_VOID
                    0x0000FF, //LEVELSELECT
                    0x5555FF, //LEVELSELECT_LIGHT
                    0x646464, //MESSAGE
                    0x000000, //MESSAGE_SHADED
                    0x646464, //TOOLBAR
                    0x000000, //TOOLBAR_BUTTON
                    0x2f2f2f, //TOOLBARBUTTON_LIGHT
                    0xf3ffac, //TOOLBARBUTTON_SELECTED
                    0xfcffe8 //TOOLBARBUTTON_SELECTED_LIGHT
);

colorScheme scheme1(
	0x00EB2E, //PLAYERSELECTED
	0x8AFFA1, //PLAYERUNSELECTED
	0xFF5555, //ENEMY
	0xFF0000, //ENEMYSTROKE
	0x000000, //UNMOVABLE_ENEMY
	0x646464, //UNMOVABLE_ENEMYSTROKE
	0x94FAFF, //BACKGROUND
	0xAFFBFF, //BACKGROUND_LIGHT
	0x666666, //BACKGROUND_SHADED
	0x000000, //BACKGROUND_VOID
	0x0000FF, //LEVELSELECT
	0x5555FF, //LEVELSELECT_LIGHT
	0x646464, //MESSAGE
	0x000000, //MESSAGE_SHADED
	0x646464, //TOOLBAR
	0x000000, //TOOLBAR_BUTTON
	0x2f2f2f, //TOOLBARBUTTON_LIGHT
	0xf3ffac, //TOOLBARBUTTON_SELECTED
	0xfcffe8 //TOOLBARBUTTON_SELECTED_LIGHT

);
//colorScheme scheme1 (0xFFFF00/*0xF9FA00*/, 0xFF2265, 0x5B2031, 0x556C62, 0xC2D7CD);
//colorScheme scheme2 (0xF9FA00, 0xFF6400, 0x5B2031, 0x556C62, 0xC2D7CD);
//Current scheme
colorScheme scheme = scheme1;
//ALTERNATIVE SCHEMES
//COLOR_1 = 0xFF2A00, COLOR_2 = 0x3016B0, COLOR_3 = 0x00A287, COLOR_4 = 0xA66A00
#endif
