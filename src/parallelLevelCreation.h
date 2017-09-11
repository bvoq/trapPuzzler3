//
//  parallelLevelCreation.h
//  trapPuzzler3
//
//  Created by kdkdk on 11.09.17.
//
//

#ifndef parallelLevelCreation_h
#define parallelLevelCreation_h

#include <thread>
#define synchronized(m) \
for(std::unique_lock<std::recursive_mutex> lk(m); lk; lk.unlock())

std::recursive_mutex m_mutex;
int globalCount = 0;
long long threadCount = 45; //should use 1 thread less than the total number of available cores, since the main thread is not counted.
long long globalBiggestSolved = 0;
long long globalBiggestSolvedDepth = 0;

void runThread(int threadID, int size, bool symmetric) {
    srand(time(0));
    long long biggestSolved = 0;
    long long biggestSolvedDepth = 0;
    //deque<deque<int> > debugLevel = {{0,0,105,105,0,0,0,0,0,0},{0,0,0,0,0,0,0,102,0,0},{0,0,1002,1002,0,0,0,102,0,0},{0,0,0,0,0,0,101,1001,0,0},{0,0,0,0,0,0,101,0,1003,0},{0,0,0,0,0,0,0,0,1003,0},{0,0,0,0,0,0,0,0,0,0},{103,103,0,0,0,0,0,0,0,1},{1004,0,0,0,0,0,104,0,0,1},{1004,0,0,0,0,0,0,0,0,0}};
    //int hi = bfsSolve(debugLevel);
    //cout << "SOLVED: " << hi << endl;
    
    int incrSuccess = 10000000 * threadID;
    
    int trapCount = 0;
    int tooLongCount = 0;
    
    for(long long i = 0; i < 10000000000000000; ++i) {
        int symFieldSize = size;
        int fieldSize = size;
        bool hasGravity = false;
        deque<deque<int> > field;
        if(!symmetric) field = initField(fieldSize, fieldSize);
        else field = initSymmetricField(symFieldSize, symFieldSize);
        
        vector<keyType> solution;
        int hasSolved = newSolver(field, hasGravity, solution);

        int depthSolved = solution.size();
        if(trapCount == -1) trapCount++;
        else if(hasSolved == -2) tooLongCount++;
        //cout << hasSolved << endl;
        //cout << i << " " << hasSolved << endl;
        if(/*hasSolved >= enough ||*/ hasSolved >= biggestSolved || depthSolved >= biggestSolvedDepth) {
            if(hasSolved > biggestSolved) biggestSolved = hasSolved;
            if(depthSolved > biggestSolvedDepth) biggestSolvedDepth = depthSolved;
            
            synchronized(m_mutex) {
                if(hasSolved >= globalBiggestSolved || depthSolved >= globalBiggestSolvedDepth) {
                    globalCount++;
                    
                    if(hasSolved > globalBiggestSolved) globalBiggestSolved = hasSolved;
                    if(depthSolved > globalBiggestSolvedDepth) globalBiggestSolvedDepth = depthSolved;
                    
                    levelExport(cout, field);
                    cout  << ";" << endl;
                    cout << "#" << globalCount << " breadth: " << hasSolved << " depth: " << depthSolved  << " traps l.: " << trapCount << " toolong l.: " << tooLongCount << " total l.: " << i << " thread: " << threadID << endl;
                    cout << endl;
                }
            }
        }
    }
}

#endif /* parallelLevelCreation_h */