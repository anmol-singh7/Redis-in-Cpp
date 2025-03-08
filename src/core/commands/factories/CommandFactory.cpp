#include "CommandFactory.h"
#include "../PingCommand.h"
#include "../EchoCommand.h"
#include "../UnknownCommand.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>

using namespace std;

CommandType CommandFactory::determineCommandType(string cmdType)
{
    // transform(cmdType.begin(), cmdType.end(), cmdType.begin(),[](unsigned char c) { return tolower(c); });
    // switch(cmdType){
    //     case "ping":
    //         return CommandType::PING;
    //     case "echo":
    //         return CommandType::ECHO;
    //     default:
    //         return CommandType::UNKNOWN;
    // }
    return CommandType();
}

unique_ptr<Command> CommandFactory::createCommand(CommandType cmdType)
{
    switch(cmdType){
        case CommandType::PING:
            return make_unique<PingCommand>();
        case CommandType::ECHO:
            return make_unique<EchoCommand>();
        default:
            return make_unique<UnknownCommand>();
    }
}