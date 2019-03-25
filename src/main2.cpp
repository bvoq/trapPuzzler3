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

#define compiledWithoutOpenframeworks //THIS CAN BE COMPILED WITHOUT OPENFRAMEWORKS!
#define nogetvertices

#include "macros.h" // include all preprocessor libraries, etc.

#include "parallelLevelCreation.h"

#include "puzzleScriptStringToRules.h"


//#include "globals.h"
//#include "keyMap.h"
//#include "grid.h"
//#include "eyes.h"
//#include "movement.h"
//#include "levelGen.h"
//#include "puzzleSolver.h"
//#include "parallelLevelCreation.h"
//#include "winningAnimation.h"

deque<deque<int> > spiralGen(int n) {
    deque<deque<int> > grid (n, deque<int>(n,0));
    
    int i = 0, j = 0;
    int x = 1, y = 0;
    int upto = n-2;
    while(upto > 0) {
        for(int c = 0; c < upto; ++c) {
            grid[i][j] = 2000000;
            i+=y;
            j+=x;
        }
        if(x==1&&y==0) {
            x=0; y=1;
            upto-=2;

        }
        else if(x==0&&y==1) {
            x=-1;
            y=0;
        }
        else if(x==-1&&y==0) {
            x=0;
            y=-1;
            upto-=2;
        }
        else if(y==-1&&x==0) {
            x=1;
            y=0;
        }
    }
    return grid;
}

int main() {
    /*
    deque<deque<int> > splevel = spiralGen(12);
    cout << "{";
    for(int i = 0; i < splevel.size(); ++i) {
        cout << "{";
        for(int j = 0; j < splevel[i].size(); ++j) {
            cout << splevel[i][j] << (j+1 < splevel[i].size()?",":"");
        }
        cout << "}" << (i+1 < splevel.size()?",":"");
    }
    cout << "}" << endl;
    return 0;
    */
    
    vector<string> puzzleScriptRules =
    {
        "[ >  Player | Crate ] -> [  >  Player | > Crate  ]",
        "[ >  Crate | Crate ] -> [  >  Crate | > Crate  ]"
    };
    
    toRule(puzzleScriptRules, {"Player","Crate"});
    
    
    return 0;
    
    
    int maxSize = 4096*16;
    
    //srand(time(0)); //seed only needs to be loaded once, every thread should execute something different.
    srand(time(0));
    // rand not thread safe, but shouldn't matter.
    thread threads[threadCount];
    cout << "Executing with: " << threadCount << " threads and one main thread for a total of "<< threadCount+1<<"." << endl;
    int size = 10; //!!!
    for(int i = 0; i < threadCount; ++i) {
        threads[i] = thread(runThread,i,size,false,true,maxSize);
    }
    runThread(1000,size,false,true,maxSize); //1000=main thread
    threads[0].join(); //probs not necessairy
    return 0;
}
