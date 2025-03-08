#include "CommandFactory.h"
#include "../PingCommand.h"
#include "../EchoCommand.h"
#include "../UnknownCommand.h"
#include "../SetCommand.h"
#include "../GetCommand.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>

using namespace std;

CommandType CommandFactory::determineCommandType(string cmdType)
{
    transform(cmdType.begin(), cmdType.end(), cmdType.begin(),[](unsigned char c) { return tolower(c); });
    if(cmdType == "ping") return CommandType::PING;
    else if(cmdType == "echo") return CommandType::ECHO;
    else if(cmdType == "set") return CommandType::SET;
    else if(cmdType == "get") return CommandType::GET;
    else return CommandType::UNKNOWN;
    return CommandType();
}

unique_ptr<Command> CommandFactory::createCommand(CommandType cmdType){
    switch(cmdType){
        case CommandType::PING:
            return make_unique<PingCommand>();
        case CommandType::ECHO:
            return make_unique<EchoCommand>();
        case CommandType::SET:
            return make_unique<SetCommand>();
        case CommandType::GET:  
            return make_unique<GetCommand>();
        default:
            return make_unique<UnknownCommand>();
    }
    return unique_ptr<Command>();
}