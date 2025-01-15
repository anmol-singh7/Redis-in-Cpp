#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <string>

using namespace std;

class Command {

    public:
    virtual ~Command() = default;
    virtual bool validate(string& command, int ptr)  = 0;

};

#endif