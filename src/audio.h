#ifndef audio_h
#define audio_h


vector<ofSoundPlayer> titles, walksfx, undosfx, blockingsfx, gravitysucksfx, gravityslurpsfx, reversegravitysucksfx, reversegravityslurpsfx;
float musicvolume = 0.75, sfxvolume = 1.0;
int currentTitle = -1;
void initAudio() {
    cout << "Attempting to load audio files in folder " << locationOfResources + "audio/" << endl;
    for(int i = 0; i <= 0; ++i) {
        ofSoundPlayer temp;
        temp.load(locationOfResources + "audio/title"+to_string(i)+".mp3");
        temp.setLoop(true);
        temp.setVolume(musicvolume);
        titles.push_back(temp);
    }
    
    for(int i = 0; i <= 3; ++i) {
        ofSoundPlayer temp;
        temp.load(locationOfResources + "audio/walk"+to_string(i)+".wav");
        temp.setLoop(false);
        temp.setVolume(sfxvolume);
        walksfx.push_back(temp);
    }
    
    for(int i = 0; i <= 3; ++i) {
        ofSoundPlayer temp;
        temp.load(locationOfResources + "audio/undo"+to_string(i)+".wav");
        temp.setLoop(false);
        temp.setVolume(sfxvolume);
        undosfx.push_back(temp);
    }
    
    for(int i = 0; i <= 0; ++i) {
        ofSoundPlayer temp;
        temp.load(locationOfResources + "audio/blocking"+to_string(i)+".wav");
        temp.setLoop(false);
        temp.setVolume(sfxvolume);
        blockingsfx.push_back(temp);
    }
    
    for(int i = 0; i <= 3; ++i) {
        ofSoundPlayer temp;
        temp.load(locationOfResources + "audio/gravity/gravitysuck"+to_string(i)+".wav");
        temp.setLoop(false);
        temp.setVolume(sfxvolume);
        gravitysucksfx.push_back(temp);
    }
    for(int i = 0; i <= 3; ++i) {
        ofSoundPlayer temp;
        temp.load(locationOfResources + "audio/gravity/gravityslurp"+to_string(i)+".wav");
        temp.setLoop(false);
        temp.setVolume(sfxvolume);
        gravityslurpsfx.push_back(temp);
    }
    
    for(int i = 0; i <= 3; ++i) {
        ofSoundPlayer temp;
        temp.load(locationOfResources + "audio/gravity/reversegravitysuck"+to_string(i)+".wav");
        temp.setLoop(false);
        temp.setVolume(sfxvolume);
        reversegravitysucksfx.push_back(temp);
    }
    for(int i = 0; i <= 3; ++i) {
        ofSoundPlayer temp;
        temp.load(locationOfResources + "audio/gravity/reversegravityslurp"+to_string(i)+".wav");
        temp.setLoop(false);
        temp.setVolume(sfxvolume);
        reversegravityslurpsfx.push_back(temp);
    }
    cout << "Done loading audio files." << endl;
    
}

void playAudio(int title) {
    if(currentTitle != title) {
        //if(currentTitle != -1) titles[title].stop();
        //titles[title].play();
        //currentTitle = title;
    }
}


void playMoveSound() {
    int pos = rand() % walksfx.size();
    walksfx[pos].play();
}

void playUndoSound() {
    int pos = rand() % undosfx.size();
    undosfx[pos].play();
}

void playBlocking() {
    int pos = rand() % blockingsfx.size();
    blockingsfx[pos].play();
}

void playGravitySuck(int gravityIntensity) {
    assert(gravityIntensity >= 0 && gravityIntensity <= 3);
    gravitysucksfx[gravityIntensity].play();
}

void playGravitySlurp(int gravityIntensity) {
    assert(gravityIntensity >= 0 && gravityIntensity <= 3);
    gravityslurpsfx[gravityIntensity].play();
}

void playReverseGravitySuck(int gravityIntensity) {
    assert(gravityIntensity >= 0 && gravityIntensity <= 3);
    reversegravitysucksfx[gravityIntensity].play();
}

void playReverseGravitySlurp(int gravityIntensity) {
    assert(gravityIntensity >= 0 && gravityIntensity <= 3);
    reversegravityslurpsfx[gravityIntensity].play();
}

#endif /* audio_h */
