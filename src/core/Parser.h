#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include "respEngine/RESPDefinitions.h"
#include <sstream>
using namespace std;

class Parser {
    public:
    RESPValue parseCommand(string& command);

};


#endif