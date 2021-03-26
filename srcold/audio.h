#ifndef compiledWithoutOpenframeworks
#ifndef audio_h
#define audio_h

#include "macros.h"

namespace audio {
    extern vector<ofSoundPlayer> titles, walksfx, undosfx, blockingsfx, gravitysucksfx, gravityslurpsfx, reversegravitysucksfx, reversegravityslurpsfx;
    extern float musicvolume, sfxvolume;
    
    extern int musicaudiolevel, sfxaudiolevel; //0-13 as set in menu.
    extern int currentTitle;
};

extern void updateVolume();
extern void initAudio();
extern void playAudio(int title);
extern void playMoveSound();
extern void playUndoSound();
extern void playBlocking();
extern void playGravitySuck(int gravityIntensity);
extern void playGravitySlurp(int gravityIntensity);
extern void playReverseGravitySuck(int gravityIntensity);
extern void playReverseGravitySlurp(int gravityIntensity);

#endif
#endif
