#include "PingCommand.h"

string PingCommand::execute(const RESPValue& args) {

    if (!holds_alternative<RESPVarArray>(args->value)) {
        return "-ERR wrong type of arguments for 'ping' command\r\n";
    }

    const RESPVarArray& cmdArgs = get<RESPVarArray>(args->value);
    int numArgs = cmdArgs.size();

    if (numArgs == 1)  return "+PONG\r\n";

    if (numArgs > 2)   return "-ERR wrong number of arguments for 'ping' command\r\n";

    if (!holds_alternative<string>(cmdArgs[1]->value)) return "-ERR wrong type of arguments for 'ping' command\r\n";

    string message = get<string>(cmdArgs[1]->value);
    
    return "+" + message + "\r\n";
}
