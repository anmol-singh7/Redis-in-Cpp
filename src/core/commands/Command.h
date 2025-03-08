#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <string>
#include "CommandTypes.h"
#include "../respEngine/RESPDefinitions.h"
#include "../storage/Database.h"

using namespace std;
class Command {

    public:
    virtual ~Command() = default;
    virtual string execute(const RESPValue& args) = 0;


};

#endif