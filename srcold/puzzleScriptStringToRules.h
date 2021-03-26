//
//  puzzleScriptStringToRules.hpp
//  trapPuzzler3
//
//  Created by kdkdk on 20.03.19.
//

#ifndef puzzleScriptStringToRules_h
#define puzzleScriptStringToRules_h

#include "macros.h"

/* JAVASCRIPT Rule as a reference
 var rule_line = {
 directions: directions,
 lhs: lhs_cells,
 rhs: rhs_cells,
 lineNumber: lineNumber,
 late: late,
 rigid: rigid,
 groupNumber: groupNumber,
 commands: commands,
 randomRule: randomRule
 };
 */

struct Rule {
    vector<string> directions; //UP=0x00001,DOWN=0x00010,LEFT=0x00100,RIGHT=0x01000
    vector<vector<vector<string> > > lhs = {}, rhs = {};
    
    bool late = false;
    // unsupported
    bool rigid = false;
    bool randomRule = false;
    
    int lineNumber = -1;
    int groupNumber = -1;
    vector<string> commands = {}; //potentially executed if empty
    
};


extern vector<Rule> toRule(vector<string> strs, vector<string> keywords_names);


#endif /* puzzleScriptStringToRules_hpp */
