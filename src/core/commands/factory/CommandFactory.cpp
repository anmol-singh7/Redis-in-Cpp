#include "CommandFactory.h"
#include "../PingCommand.h"
#include "../EchoCommand.h"
#include "../UnknownCommand.h"

using namespace std;

unique_ptr<Command> CommandFactory::createCommand(CommandType cmdType){
    switch(cmdTpye){
        case CommandType::PING:
            return make_unique<PingCommand>();
        case CommandType::ECHO:
            return make_unique<EchoCommand>();
        default:
            return make_unique<UnknownCommand>();
    }
}