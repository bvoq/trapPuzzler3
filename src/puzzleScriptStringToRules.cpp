#include "puzzleScriptStringToRules.h"

static string replaceStrForever(string str, string from, string to) {
    size_t start_pos;
    while((start_pos = str.find(from) ) != string::npos) {
        str.replace(start_pos, from.size(), to);
    }
    return str;
}

static string replaceStrOnce(string str, string from, string to) {
    size_t start_pos;
    for(int i=0;i+from.size()<str.size();++i) {
        if(str.substr(i,from.size()) == from) {
            str = str.substr(0,i) + to + str.substr(i+from.size());
            i += to.size()-1;
        }
    }

    return str;
}

static vector<string> keywords_directions = {">","<","^","v","up","down","left","right","moving","horizontal","vertical","orthogonal","action"}; //UNSUPPORTED: "stationary","no","randomdir","random","perpendicular","parallel",
static vector<string> keywords_commandwords = {"sfx0","sfx1","sfx2","sfx3","sfx4","sfx5","sfx6","sfx7","sfx8","sfx9","sfx10","cancel","checkpoint","restart","win","message","again"};


/*
var relativeDirs = ['^','v','<','>','parallel','perpendicular'];//used to index the following
var relativeDict = {
    'right': ['up', 'down', 'left', 'right','horizontal','vertical'],
    'up': ['left', 'right', 'down', 'up','vertical','horizontal'],
    'down': ['right', 'left', 'up', 'down','vertical','horizontal'],
    'left': ['down', 'up', 'right', 'left','horizontal','vertical']
};*/


/*
enum DIRECTION {
    UP=0x00001,DOWN=0x00010,LEFT=0x00100,RIGHT=0x01000
}*/

void logError(string errorMsg, string str, int lineno) {
    cerr << "Parse issue [" << lineno << "] " << " on string " << str << endl;
    cerr << errorMsg << endl;
}

//returns empty rules if failed
vector<Rule> toRule(vector<string> strs, vector<string> keywords_names) {
    //Lower-case keyword_names
    for (string & str : keywords_names)
        for(char & c : str)
            if(c >= 'A' && c <= 'Z') c += 'a'-'A';
    
    
    vector<Rule> crules;
    vector<Rule> emptyRules; //returned on error
    
    int groupNumber = 0;
    
    for(int lineno=0;lineno<strs.size();++lineno) {
        string str = strs[lineno];
        cout << "parsing " << str << endl;
        
        //Lower-case
        for(char & c : str) {
            if(c >= 'A' && c <= 'Z') c += 'a'-'A';
        }
        
        
        //TOKENIZE
        str = replaceStrOnce(str, "->"," -> ");
        str = replaceStrOnce(str, "|"," | ");
        str = replaceStrOnce(str, "["," [ ");
        str = replaceStrOnce(str, "]"," ] ");

        vector<string> tokens;
        string curstr = "";
        for(int i=0;i<=str.size();++i) {
            if(i == str.size() || isspace(str[i])) {
                if(curstr.size() > 0) {
                    tokens.push_back(curstr);
                    curstr.clear();
                }
            } else curstr.push_back(str[i]);
        }
        
        
        if(tokens.size() == 0) {
            DEB("Spoopy empty token rule.");
            continue;
        }
        
        //PARSE
        /*
        STATE
        0 - scanning for initial directions
            LHS
        1 - reading cell contents LHS
        2 - reading cell contents RHS
        */
        int parseState = 0;
        Rule crule;
        crule.lineNumber = lineno;
        crule.groupNumber = lineno; //Assume it's a single standing group. updated if different
        
        vector<string> ccell = {};
        vector<vector<string> > ccellrow = {};
        bool incellrow = false;
        
        for(int tokenno=0;tokenno<tokens.size();++tokenno) {
            string token = tokens[tokenno];
            if(parseState == 0) {
                if(token == "+") {
                    if(tokenno == 0) {
                        logError("The '+' symbol, for joining a rule with the group of the previous rule, must be the first symbol on the line.",str,lineno);
                        return emptyRules;
                    } else if(crules.size() == 0) {
                        logError("The '+' symbol, for joining a rule with the group of the previous rule, needs a previous rule to be applied to.", str, lineno);
                        return emptyRules;
                    } else {
                        crule.groupNumber = crules.back().groupNumber;
                    }
                } else if(token == "left" || token == "right" || token == "up" || token == "down") {
                    crule.directions.push_back(token);
                } else if(token == "horizontal") {
                    crule.directions.push_back("left");crule.directions.push_back("right");
                } else if(token == "vertical") {
                    crule.directions.push_back("up");crule.directions.push_back("down");
                } else if(token == "orthogonal") {
                    crule.directions.push_back("up");crule.directions.push_back("down");
                    crule.directions.push_back("left");crule.directions.push_back("right");
                } else if(token == "late") {
                    crule.late = true;
                } else if(token == "rigid") {
                    crule.rigid = true;
                } else if(token == "random") {
                    crule.randomRule = true;
                } else if(token == ">"||token=="<"||token=="v"||token=="^") {
                    logError("You cannot use relative directions (\"^v<>\") to indicate in which direction(s) a rule applies.  Use absolute directions indicators (Up, Down, Left, Right, Horizontal, or Vertical, for instance), or, if you want the rule to apply in all four directions, do not specify directions", str, lineno);
                    return emptyRules;
                } else if (token == "[") {
                    if (crule.directions.size() == 0) {
                        crule.directions.push_back("up");crule.directions.push_back("down");
                        crule.directions.push_back("left");crule.directions.push_back("right");
                    }
                    parseState = 1;
                    tokenno--;
                }
            }
            else if(parseState == 1 || parseState == 2) {
                if(token == "[") {
                    if (ccell.size() > 0) {
                        logError("Error, malformed cell rule - encountered a '[' before previous bracket was closed", str, lineno);
                        return emptyRules;
                    }
                    incellrow = true;
                    ccell.clear();
                } else if(find(keywords_directions.begin(),keywords_directions.end(),token) != keywords_directions.end()) {
                    if (ccell.size() % 2 == 1) {
                        logError("Error, an item can only have one direction/action at a time, but you're looking for several at once!", str, lineno);
                        return emptyRules;
                    } else if (!incellrow) {
                        logError("Invalid syntax. Directions should be placed at the start of a rule.", str,lineno);
                        return emptyRules;
                    } else {
                        ccell.push_back(token);
                    }
                } else if (token == "|") {
                    if (ccell.size() % 2 == 1) {
                        logError("In a rule, if you specify a force, it has to act on an object.", str, lineno);
                        return emptyRules;
                    } else {
                        ccellrow.push_back(ccell);
                        ccell.clear();
                    }
                } else if(token == "]") {
                    if (ccell.size() % 2 == 1) {
                        if (ccell[0]=="...") {
                            logError("Cannot end a rule with ellipses.", str, lineno);
                            return emptyRules;
                        } else {
                            logError("In a rule, if you specify a force, it has to act on an object.", str, lineno);
                            return emptyRules;
                        }
                    } else {
                        ccellrow.push_back(ccell);
                        ccell.clear();
                    }
                    
                    if (parseState == 1) //lhs
                        crule.lhs.push_back(ccellrow);
                    else if(parseState == 2) //rhs
                        crule.rhs.push_back(ccellrow);
                    
                    ccellrow.clear();
                    incellrow = false;
                } else if(token == "->") {
                    if (parseState != 1) {
                        logError("Error, you can only use '->' once in a rule; it\'s used to separate before and after states.", str, lineno);
                        return emptyRules;
                    } if (ccellrow.size() > 0) {
                        logError("Encountered an unexpected '->' inside square brackets.  It\'s used to separate states, it has no place inside them >:| .", str, lineno);
                        return emptyRules;
                    } else {
                        parseState = 2;
                    }
                }  else if(find(keywords_names.begin(),keywords_names.end(),token) != keywords_names.end()) {
                    if(!incellrow) {
                        logError("Invalid token: '"+token+"'. Object names should only be used within cells (square brackets).", str, lineno);
                        return emptyRules;
                    } else if(ccell.size() % 2 == 0) {
                        ccell.push_back("");
                        ccell.push_back(token);
                    } else if(ccell.size() % 2 == 1){
                        ccell.push_back(token);
                    }
                } else if(token == "...") {
                    logError("Ellipses are not supported currently!", str, lineno);
                    return emptyRules;
                    if (!incellrow) {
                        logError("Invalid syntax, ellipses should only be used within cells (square brackets).", str, lineno);
                        return emptyRules;
                    } else {
                        ccell.push_back(token);
                        ccell.push_back(token);
                    }
                } else if (find(keywords_commandwords.begin(),keywords_commandwords.end(),token) != keywords_commandwords.end()) {
                    if (parseState != 2) {
                        logError("Commands cannot appear on the left-hand side of the arrow.",str, lineno);
                        return emptyRules;
                    }
                    if (token=="message") {
                        //we have to find the original message before tokenizing.
                        size_t index = strs[lineno].find(token);
                        if (index!=string::npos)
                            crule.commands.push_back("message:"+strs[lineno].substr(index)); //handled slightly differently than in puzzlescript engine
                        
                        tokenno = (int)tokens.size();
                    } else {
                        crule.commands.push_back(token);
                    }
                }
            }
        }
        crules.push_back(crule);
    }

    return crules;
}



//   _______DI_blockid__blockno_________
//   000000_00_00000000_0000000000000000

//2^32 2^16
//
// dir, block.
