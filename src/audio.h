#ifndef audio_h
#define audio_h


vector<ofSoundPlayer> titles, walksfx, undosfx, blockingsfx;
float musicvolume = 0.75, sfxvolume = 1.0;
int currentTitle = -1;
void initAudio() {
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
}

void playAudio(int title) {
    if(currentTitle != title) {
        if(currentTitle != -1) titles[title].stop();
        titles[title].play();
        currentTitle = title;
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


void playGravity() {
    
}

#endif /* audio_h */
