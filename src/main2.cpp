//
//  main2.cpp
//  trapPuzzler3
//
//  Created by kdkdk on 11.09.17.
//
//

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
    thread threads[threadCount];
    cout << "Executing with: " << threadCount << " threads." << endl;
    int size = 10;
    for(int i = 0; i < threadCount; ++i) {
        threads[i] = thread(runThread,i,size,false);
    }
    threads[0].join(); //wait forever
    return 0;
}
