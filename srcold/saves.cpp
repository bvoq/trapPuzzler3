#include "saves.h"

#include "ofMain.h"

#include "audio.h"
#include "globals.h"
#include "levels.h"

void loadSaveData() {
    createLevels();
    cout << "Loading user data from " << locationOfResources << "saves/saveState1" << endl;
    if (!ofFile::doesFileExist(locationOfResources + "saves/saveState1")) {
        cout << "Did not find file, trying to create it." << endl;
        //create file in case it doesn't exist.
        ofstream ofstr(locationOfResources + "saves/saveState1");
        ofstr << levels.size() << endl;
        for (int i = 0; i < levels.size(); ++i) {
            ofstr << false << endl;
        }
        ofstr << 6 << endl; //musicaudio
        ofstr << 6 << endl; //sfxaudio
        
        ofstr.close();
    }
    vector<string> lines = ofSplitString(ofBufferFromFile(locationOfResources + "saves/saveState1"), "\n");
    if (lines.size() <= 0) {
        cout << "WARNING: Empty save file at " << (locationOfResources + "saves/saveState1") << ", attempting to overwrite the save file with a new blank one." << endl;
        ofFile::removeFile(locationOfResources + "saves/saveState1");
        loadSaveData();
    }
    
    int lengthOfBeatenLevels = stoi(lines[0]);
    for (int i = 1; i <= lengthOfBeatenLevels; ++i) {
        beaten.push_back(lines[i][0] == '1');
    }
    audio::musicaudiolevel = stoi(lines[lengthOfBeatenLevels + 1]);
    cout << "Loaded musicaudiolevel: " << audio::musicaudiolevel << endl;
    if (!(audio::musicaudiolevel >= 0 && audio::musicaudiolevel <= 12)) {
        cout << "WARNING: Music audio levels should be between [0-12], but received " << audio::musicaudiolevel << ", you probably have a corrupted savefile. Setting audio to 6." << endl;
        audio::musicaudiolevel = 6;
    }
    audio::sfxaudiolevel = stoi(lines[lengthOfBeatenLevels + 2]);
    if (!(audio::sfxaudiolevel >= 0 && audio::sfxaudiolevel <= 12)) {
        cout << "WARNING: Music audio levels should be between [0-12], but received " << audio::musicaudiolevel << ", you probably have a corrupted savefile. Setting audio to 6." << endl;
        audio::musicaudiolevel = 6;
    }
    updateVolume();
    cout << "Loaded sfxaudiolevel: " << audio::sfxaudiolevel << endl;
    while(beaten.size() < levels.size()) beaten.push_back(false);
}

void saveSaveData() {
    cout << "Saving user data to " << locationOfResources << "saves/saveState1" << endl;
    if(ofFile::doesFileExist(locationOfResources+"saves/saveState1")) ofFile::removeFile(locationOfResources+"saves/saveState1");
    ofstream ofstr(locationOfResources+"saves/saveState1");
    ofstr << beaten.size() << endl;
    for(int i = 0; i < beaten.size(); ++i) {
        ofstr << beaten[i] << endl;
    }
    ofstr << audio::musicaudiolevel << endl;
    cout << "Loaded musicaudiolevel: " << audio::musicaudiolevel << endl;
    ofstr << audio::sfxaudiolevel << endl;
    cout << "Loaded sfxaudiolevel: " << audio::sfxaudiolevel << endl;
    ofstr.close();
}
