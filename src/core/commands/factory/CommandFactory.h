#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include "../Command.h"
#include <memory>

using namespace std;

enum class CommandType {
    PING,
    ECHO
};

class CommandFactory {
    static unique_ptr<Command> createCommand(CommandType cmdType);
};

#endif