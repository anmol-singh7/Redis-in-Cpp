#include "GetCommand.h"

string GetCommand::execute(const RESPValue &args){
    
    Database &db = Database::getInstance();

    if (!holds_alternative<RESPVarArray>(args->value)) {
        return "-ERR wrong type of arguments for 'ping' command\r\n";
    }

    const RESPVarArray& cmdArgs = get<RESPVarArray>(args->value);

    if(cmdArgs.size() < 2){
        return "-ERR wrong number of arguments for 'get' command";
    }

    if(!holds_alternative<string>(cmdArgs[1]->value)){
        return "-ERR wrong type of arguments for 'get' command";
    }

    string key = get<string>(cmdArgs[1]->value);

    RESPValue val = db.get(key);

    if(val == nullptr){
        return "$-1\r\n";
    }

    string response = get<string>(val->value);
    response = "$" + to_string(response.size()) + "\r\n" + response + "\r\n";

    return response;
}