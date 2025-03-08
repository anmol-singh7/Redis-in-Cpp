#include "CommandHandler.h"
#include "Parser.h"
#include "respEngine/RESPDefinitions.h"
#include "commands/factories/CommandFactory.h"
#include "Validator.h"

string CommandHandler::handleCommand(char *cmd, int sz_Command){
   
    Parser parser;
    Validator validator;

    string command(cmd,sz_Command);
    cout<<"Command received: " + command << endl;
    bool isValid = validator.isValidCommand(command);
    cout<<"Command is valid: " + to_string(isValid) << endl;

    string errorMsg  = "-Error: Invalid input command\r\n";
    if(!isValid){
        cout<< "Invalid command received from client" << endl;
        // throw error
        return errorMsg;
    }

    RESPValue cmdArgs = parser.parseCommand(command);
    
    if(!cmdArgs || !holds_alternative<RESPVarArray>(cmdArgs->value)){
        //throw and error 
        cerr<<"CmdArgs is not a vetore\n";
        return errorMsg;
    }

    RESPVarArray& args = get<RESPVarArray>(cmdArgs->value);

    if(args.empty() || !holds_alternative<string>(args[0]->value)){
        cerr<< "Problem with Args\n";
        return errorMsg;
    }

    

    string cmdType = get<string>(args[0]->value);

    CommandType type = CommandFactory::determineCommandType(cmdType);

    unique_ptr<Command> commandEle =  CommandFactory::createCommand(type);

    string response = commandEle->execute(RESPValueStruct::create(args));
    cout<<"Response : " + response<<endl;
    return response;
}