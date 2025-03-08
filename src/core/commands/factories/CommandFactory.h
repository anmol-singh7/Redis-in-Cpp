#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include "../Command.h"
#include "../CommandTypes.h"
#include <memory>

using namespace std;

class CommandFactory {

    public:

    static CommandType determineCommandType(string cmdType);
   
    static unique_ptr<Command> createCommand(CommandType cmdType);
};

#endif