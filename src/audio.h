#ifndef audio_h
#define audio_h


vector<ofSoundPlayer> titles, walks;
int currentTitle = -1;
void initAudio() {
    for(int i = 0; i < 1; ++i) {
        ofSoundPlayer temp;
        temp.load(locationOfResources + "audio/title"+to_string(i)+".mp3");
        temp.setLoop(true);
        titles.push_back(temp);
    }
    
    for(int i = 0; i < 1; ++i) {
        ofSoundPlayer temp;
        temp.load(locationOfResources + "audio/walk"+to_string(i)+".wav");
        temp.setLoop(false);
        walks.push_back(temp);
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
    int pos = rand() % walks.size();
    walks[pos].play();
}



#endif /* audio_h */
