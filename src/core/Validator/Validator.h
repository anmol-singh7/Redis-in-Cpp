#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <../commands/factory/CommandFactory.h>

using namespace std;

class Validator {
    private:
    bool containsOnlyAlphabets(string &command,int start,int szOfFirstElement);
   
    CommandType mapCommandType(const string& commandType);

    public:
    bool isValidCommand(char* cmd,int sz_Command);

};


#endif