//
//  movement.h
//  trapStory2
//
//  Created by kdkdk on 28/12/15.
//
//

#ifndef trapPuzzler3_movement_h
#define trapPuzzler3_movement_h

#include "bitsstdc.h"
#include "macros.h"

#include "globals.h"
#include "keyMap.h"

extern void checkForMerge(ddd &, int &);
extern void recheckGrid();

extern float easeInElastic(float t, float b, float c, float d);
extern float easeOutElastic(float t, float b, float c, float d);
extern float easeOutBounce(float t, float b, float c, float d);
extern float easeInBounce (float t, float b, float c, float d);
extern float easeInQuad (float t, float b, float c, float d);
extern float easeOutQuad(float t, float b, float c, float d);
extern float easeInOutQuad(float t, float b, float c, float d);
extern float easeInOutTripple(float t, float b, float c, float d);
extern float easeInOutQuint(float t, float b, float c, float d);
extern float easeInOutElastic(float t, float b, float c, float d);
extern float easeInSine (float t, float b, float c, float d);
extern float easeOutSine (float t, float b, float c, float d);
extern float easeInOutSine(float t, float b, float c, float d);


#ifndef islevelgen
#include "ofMain.h"
enum MusicType {
    NONEMT=0, NORMALMT=1, UNDOMT=2, PLAYER_CHANGEMT = 3, SUCK0MT=100, SUCK1MT=101, SUCK2MT=102,SUCK3MT=103,SLURP0MT = 200, SLURP1MT = 201, SLURP2MT = 202, SLURP3MT = 203, RSUCK0MT=300, RSUCK1MT=301, RSUCK2MT=302, RSUCK3MT=303, RSLURP0MT = 400, RSLURP1MT = 401, RSLURP2MT = 402, RSLURP3MT = 403,
};

extern void screenShake(long long, keyType, float);
struct movement {
    long long timeWhenStarted;
    deque<deque<int> > newGrid, oldGrid, newEyeGrid, oldEyeGrid;
    keyType movementDirection;
    set<int> hasMoved;
    bool isUndoMove;
    int movementTime;
    int oldPlayerID;
    int newPlayerID; //will be overwritten.
    bool gravityMove;
    bool gravitySound;
    MusicType audioOnMove;
    
    movement(deque<deque<int> > _nG, deque<deque<int> > _oG, deque<deque<int> > _nEG, deque<deque<int> > _oEG,
             keyType _mD, set<int> _hM, bool _isUndoMove, int _movementTime, bool _gravityMove, MusicType _audioOnMove) {
        newGrid = _nG;
        oldGrid = _oG;
        newEyeGrid = _nEG;
        oldEyeGrid = _oEG;
        movementDirection = _mD;
        hasMoved = _hM;
        timeWhenStarted = getAdjustedTime();
        isUndoMove = _isUndoMove;
        movementTime = _movementTime;
        oldPlayerID = playerID;
        newPlayerID = playerID; //can be overwritten.
        gravityMove = _gravityMove;
        audioOnMove = _audioOnMove;
    }
    
    void changeGrid();
    float getDelay();
    
    bool isUsed = false;
    float linearIncr();
    float quadInOutIncr();
    float upDownSine();
    ofRectangle calculatePosition(int i, int j);
};

extern deque<movement> movements;
extern vector<movement> previousMovements;

extern void checkMovement();

extern void undoMovement(long long maxtime);
#endif

extern int moveTile(ddd & moveGrid, ddd & moveEyeGrid, int elementId, keyType& input, set<int>& checked, ddd & tempGrid, set<pair<int, int> >& eyesToChange, bool solver);

//returns a set with the blocks affected by gravity. currentlychecking makes sure no infinite loops happen.
extern bool affectGravity(ddd & moveGrid, ddd & moveEyeGrid, int elementId, keyType& gravityDirection, set<int>& checked, set<int>& currentlyChecking, set<int> &
                          affectedByGravity, set<pair<int,int> > & affectedEyes, bool solver);

extern void screenShake(long long duration, keyType keytype, float intensity);

//WILL NOT CALL THE GLOBAL MOVEGRID or playerID so it can be used with the solver!
extern bool move(ddd & moveGrid, ddd & moveEyeGrid, int & playerID, keyType input, long long timeAllowed, bool solver, bool possibleGravity);

#ifndef islevelgen
extern void changePlayerId(int i);
#endif

extern int changePlayerIdDeterministic(deque<deque<int> > & moveGrid, int playerID, bool solver);

extern void checkForMerge(deque<deque<int> > & moveGrid, int & playerID);

#endif
