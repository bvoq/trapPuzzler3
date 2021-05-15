//
//  saves.h
//  trapPuzzler3
//
//  Created by Kivifreak on 23/01/16.
//
//

#ifndef trapPuzzler3_saves_h
#define trapPuzzler3_saves_h

void loadSaveData() {
    createLevels();
    cout << "Loading user data from " << locationOfSavesLevels << "saves/saveState1" << endl;
    if (!ofFile::doesFileExist(locationOfSavesLevels + "saves/saveState1")) {
        cout << "Did not find file, trying to create it." << endl;
        //create file in case it doesn't exist.
        /*
        ofstream ofstr(locationOfSavesLevels + "saves/saveState1");
        ofstr << levels.size() << endl;
        for (int i = 0; i < levels.size(); ++i) {
            ofstr << false << endl;
        }
        ofstr << 6 << endl; //musicaudio
        ofstr << 6 << endl; //sfxaudio
        ofstr.close();*/
        
        ofBuffer ofbuf; //iPad
        // fill the buffer with something important
        ofbuf.append(to_string(levels.size())+"\n");
        for(int i = 0; i < beaten.size(); ++i) {
            ofbuf.append(to_string(false)+"\n");
        }
        ofbuf.append("6\n");
        ofbuf.append("6\n");
        ofbuf.append("1\n");
        bool fileWritten = ofBufferToFile(locationOfSavesLevels + "saves/saveState1", ofbuf); //iPad
        
    }
    vector<string> lines = ofSplitString(ofBufferFromFile(locationOfSavesLevels + "saves/saveState1"), "\n");
    if (lines.size() <= 0) {
        cout << "WARNING: Empty save file at " << (locationOfSavesLevels + "saves/saveState1") << ", attempting to overwrite the save file with a new blank one." << endl;
        ofFile::removeFile(locationOfSavesLevels + "saves/saveState1");
        loadSaveData();
    }

    int lengthOfBeatenLevels = stoi(lines[0]);
    for (int i = 1; i <= lengthOfBeatenLevels; ++i) {
        beaten.push_back(lines[i][0] == '1');
    }
    musicaudiolevel = stoi(lines[lengthOfBeatenLevels + 1]);
    cout << "Loaded musicaudiolevel: " << musicaudiolevel << endl;
    if (!(musicaudiolevel >= 0 && musicaudiolevel <= 12)) {
        cout << "WARNING: Music audio levels should be between [0-12], but received " << musicaudiolevel << ", you probably have a corrupted savefile. Setting audio to 6." << endl;
        musicaudiolevel = 6;
    }
    sfxaudiolevel = stoi(lines[lengthOfBeatenLevels + 2]);
    if (!(sfxaudiolevel >= 0 && sfxaudiolevel <= 12)) {
        cout << "WARNING: Music audio levels should be between [0-12], but received " << musicaudiolevel << ", you probably have a corrupted savefile. Setting audio to 6." << endl;
        musicaudiolevel = 6;
    }
    updateVolume();
    lightmode = stoi(lines[lengthOfBeatenLevels + 3]);
    loadColorScheme();

    cout << "Loaded sfxaudiolevel: " << sfxaudiolevel << endl;
    while(beaten.size() < levels.size()) beaten.push_back(false);
}

void saveSaveData() {
    cout << "Saving user data to " << locationOfSavesLevels << "saves/saveState1" << endl;
    
    if(ofFile::doesFileExist(locationOfSavesLevels+"saves/saveState1")) ofFile::removeFile(locationOfSavesLevels+"saves/saveState1");
    
    //ofFile file;
    //file.open(ofToDataPath("saves/saveState1"), ofFile::ReadWrite, false);
    
    ofBuffer ofbuf; //iPad
    // fill the buffer with something important
    ofbuf.append(to_string(beaten.size())+"\n");
    for(int i = 0; i < beaten.size(); ++i) {
        ofbuf.append(to_string(beaten[i])+"\n");
    }
    ofbuf.append(to_string(musicaudiolevel)+"\n");
    ofbuf.append(to_string(sfxaudiolevel)+"\n");
    ofbuf.append(to_string(lightmode)+"\n");
    bool fileWritten = ofBufferToFile(locationOfSavesLevels+"saves/saveState1", ofbuf); //iPad
    
    /*
    ofstream ofstr(locationOfSavesLevels+"saves/saveState1");
    ofstr << beaten.size() << endl;
    for(int i = 0; i < beaten.size(); ++i) {
        ofstr << beaten[i] << endl;
    }
    ofstr << musicaudiolevel << endl;
    cout << "Loaded musicaudiolevel: " << musicaudiolevel << endl;
    ofstr << sfxaudiolevel << endl;
    cout << "Loaded sfxaudiolevel: " << sfxaudiolevel << endl;
    ofstr.close();
    */
}

#endif