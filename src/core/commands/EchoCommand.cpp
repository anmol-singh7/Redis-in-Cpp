#include "EchoCommand.h"

string EchoCommand::execute(const RESPValue& args) {
   
    if (!holds_alternative<RESPVarArray>(args->value)) {
        return "-ERR wrong type of arguments for command\r\n";
    }

    const RESPVarArray& cmdArgs = get<RESPVarArray>(args->value);
    int numArgs = cmdArgs.size();
   
    if (numArgs != 2) {
        return "-ERR wrong number of arguments for command\r\n";
    }

    if (!holds_alternative<string>(cmdArgs[1]->value)) {
        return "-ERR wrong type of arguments for command\r\n";
    }

    string message = get<string>(cmdArgs[1]->value);

    string response = "$" + to_string(message.size()) + "\r\n" + message + "\r\n";

    return response;
}
