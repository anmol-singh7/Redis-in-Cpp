#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include "RESPData.h"

using namespace std;

class Validator {

    public:
    bool isValidCommand(char* cmd,int sz_Command);

};


#endif