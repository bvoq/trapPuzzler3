#ifndef audio_h
#define audio_h


vector<ofSoundPlayer> titles;
int currentTitle = -1;
void initAudio() {
    for(int i = 0; i < 1; ++i) {
        ofSoundPlayer temp;
        temp.load(locationOfResources + "audio/title0.mp3");
        temp.setLoop(true);
        titles.push_back(temp);
    }
}

void playAudio(int title) {
    if(currentTitle != title) {
        if(currentTitle != -1) titles[title].stop();
        titles[title].play();
        currentTitle = title;
    }
}




#endif /* audio_h */
