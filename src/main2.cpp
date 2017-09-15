//POSSIBLE COMPILATION FLAGS: -frename-registers -funroll-loops -march=native

//ALSO RUN USING PGO: -fprofile-generate
//AFTER RUNNING RECOMPILE USING: -fprofile-use -fprofile-correction

//
//  main2.cpp
//  trapPuzzler3
//
//  Created by kdkdk on 11.09.17.
//
//

#include <algorithm>
#include <deque>
#include <iostream>
#include <queue>
#include <random>
#include <set>
#include <vector>
#include <ctime>
#include <cassert>
#include <mutex>
#include <thread>
#include <climits>
#include <string>
#include <map>
using namespace std;

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define islevelgen
//#include "ofMain.h"
#define ddd deque<deque<int> >
#include "globals.h"
#include "keyMap.h"
#include "grid.h"
#include "eyes.h"
#include "movement.h"
#include "levelGen.h"
#include "puzzleSolver.h"
//#include "keyEvent.h"
#include "parallelLevelCreation.h"
#include "winningAnimation.h"


int main() {
    int maxSize = 4096*16;
    
    srand(time(0)); //seed only needs to be loaded once, every thread should execute something different.
    // rand not thread safe, but shouldn't matter.
    thread threads[threadCount];
    cout << "Executing with: " << threadCount << " threads and one main thread for a total of "<< threadCount+1<<"." << endl;
    int size = 10; //!!!
    for(int i = 0; i < threadCount; ++i) {
        threads[i] = thread(runThread,i,size,false,maxSize);
    }
    runThread(1000,size,false,maxSize); //1000=main thread
    threads[0].join(); //probs not necessairy
    return 0;
}
