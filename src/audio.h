#ifndef audio_h
#define audio_h


vector<ofSoundPlayer> titles, walksfx, undosfx;
int currentTitle = -1;
void initAudio() {
    for(int i = 0; i <= 0; ++i) {
        ofSoundPlayer temp;
        temp.load(locationOfResources + "audio/title"+to_string(i)+".mp3");
        temp.setLoop(true);
        titles.push_back(temp);
    }
    
    for(int i = 0; i <= 3; ++i) {
        ofSoundPlayer temp;
        temp.load(locationOfResources + "audio/walk"+to_string(i)+".wav");
        temp.setLoop(false);
        walksfx.push_back(temp);
    }
    
    for(int i = 0; i <= 3; ++i) {
        ofSoundPlayer temp;
        temp.load(locationOfResources + "audio/undo"+to_string(i)+".wav");
        temp.setLoop(false);
        undosfx.push_back(temp);
    }
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
    //walksfx[pos].play();
}

void playUndoSound() {
    int pos = rand() % undosfx.size();
    //undosfx[pos].play();
}




#endif /* audio_h */
