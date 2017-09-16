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
    cout << "Loading user data from " << locationOfResources << "saves/saveState1" << endl;
    if(!ofFile::doesFileExist(locationOfResources+"saves/saveState1")) {
        ofstream ofstr(locationOfResources+"saves/saveState1");
        ofstr << levels.size() << endl;
        for(int i = 0; i < levels.size(); ++i) {
            ofstr << false << endl;
        }
        ofstr.close();
    }
    vector<string> lines = ofSplitString(ofBufferFromFile(locationOfResources+"saves/saveState1"), "\n");
    for(int i = 1; i < lines.size(); ++i) {
        beaten.push_back(lines[i] == "1");
    }
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
    ofstr.close();
}

#endif
