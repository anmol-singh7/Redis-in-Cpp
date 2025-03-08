#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <string>
#include "CommandTypes.h"

using namespace std;

class Command {

    public:
    virtual ~Command() = default;
    virtual bool validate(string& command, int ptr)  = 0;

};

#endif