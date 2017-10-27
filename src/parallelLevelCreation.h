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
long long threadCount = 46; //48 is max core count i think, so utilising 47 with threadCount = 46 makes sense.

long long globalBiggestSolved = 0;
long long globalBiggestSolvedDepth = 0;

long long sufficientDepth = 25;
long long sufficientBreadth = 40000;

long long atleastdepth = 25;

ddd improveLevel(deque<deque<int> > oldLevel, bool hasGravity, int tries, int maxBreadth);
int newSolver(ddd gridtosolve, bool hasGravity, vector<keyType> & solution, int maxComputationFields);
void runThread(int threadID, int size, bool symmetric, bool gravitymonsterlevel, int maxComputationFields) {
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
        bool hasGravity = gravitymonsterlevel;
        deque<deque<int> > field;
        if(!symmetric && !gravitymonsterlevel) field = initField(fieldSize, fieldSize);
        else if(symmetric && !gravitymonsterlevel) field = initSymmetricField(symFieldSize, symFieldSize);
        else if(!symmetric && gravitymonsterlevel) field = initGravityField(symFieldSize, symFieldSize);
        else assert(false);
        
        vector<keyType> solution;
        int hasSolved = newSolver(field, hasGravity, solution, maxComputationFields);
        int depthSolved = solution.size();
        if(hasSolved == -1) trapCount++;
        else if(hasSolved == -2) {tooLongCount++;}
        else if(hasSolved < 0) cout << "UNKNOWN RES " << hasSolved << endl;
        else{
			
			int improvementTries = 5;
			vector< ddd > improvedFields(improvementTries, ddd ());
			for(int i = 0; i < improvementTries; ++i){
				improvedFields[i] = improveLevel(field, false, 10, 4096*16);
			}
			
			vector<keyType> tempSol;
			int best = 0;
			for(int i = 0; i < improvementTries; ++i){
				int depth = newSolver(improvedFields[i], false, tempSol, 4096*16);
				if(depth > best){
					best = depth;
					field = improvedFields[i];
				}
			}
		}
        //cout << hasSolved << endl;
        //cout << i << " " << hasSolved << endl;
        if(/*hasSolved >= enough ||*/ hasSolved >= biggestSolved || depthSolved >= biggestSolvedDepth) {
            if(hasSolved > biggestSolved) biggestSolved = hasSolved;
            if(depthSolved > biggestSolvedDepth) biggestSolvedDepth = depthSolved;
            
            synchronized(m_mutex) {
                if(depthSolved >= 2 && (hasSolved >= globalBiggestSolved || depthSolved >= globalBiggestSolvedDepth || hasSolved >= sufficientBreadth || depthSolved >= sufficientDepth)) {
                    globalCount++;
                    
                    if(hasSolved > globalBiggestSolved) globalBiggestSolved = hasSolved;
                    if(depthSolved > globalBiggestSolvedDepth) globalBiggestSolvedDepth = depthSolved;
                    
                    levelExport(cout, field);
                    cout  << ";" << endl;
                    cout << "//#" << globalCount << " breadth: " << hasSolved << " depth: " << depthSolved  << " traps l.: " << trapCount << " toolong l.: " << tooLongCount << " total l.: " << i << " thread: " << threadID << endl;
                    cout << endl;
                }
            }
        }
    }
}

#endif /* parallelLevelCreation_h */
