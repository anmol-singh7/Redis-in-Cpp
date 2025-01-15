#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <string>

class Command {

    public:
    virtual ~Command() = default;
    virtual bool validate(string& command, int ptr) const = 0;

};

#endif