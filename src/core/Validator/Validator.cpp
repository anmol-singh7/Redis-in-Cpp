#include "Validator.h"
using namespace std;



CommandType Validator::mapCommandType(const std::string& commandType) {
    if (commandType == "PING") return CommandType::PING;
    if (commandType == "ECHO") return CommandType::ECHO;
    return CommandType::UNKNOWN;
}

bool Validator::containsOnlyAlphabets(string& command,int start,int szOfFirstElement){

    if(start >= command.size() || start + szOfFirstElement >= command.size() ) return false;

    for (size_t i = 0; i < szOfFirstElement; ++i) {
        char c = command[start + i];
        if (!isalpha(static_cast<unsigned char>(c))) {
            return false;
        }
    }

    return true;
}





bool Validator::isValidCommand(char* cmd,int sz_Command){
    string command(cmd, sz_Command);
    // when ever ptr used check its < sz_Command 
    int ptr = 0;

    char firstChar = command[ptr++];

    if(firstChar != '*') return false;

    string numberStr = "";

    while(isdigit(commnad[ptr])){
        numberStr += command[ptr++];
    }

    int numberOfElements = stoi(numberStr);
    ptr += 2;

     

    if(numberOfElements < 1) return false;

    bool isFirstElementBulkString =  (command[ptr++] == '$');
    ptr += 2;

    if(!isFirstElementBulkString) return false;

    string sizeStr = "";
    while (isdigit(command[ptr])) {
        sizeStr += command[ptr++];
    }
    int szOfFirstElement = stoi(sizeStr);
    
    if(!containsOnlyAlphabets(command, ptr, szOfFirstElement)) return false;
    
    string commandType = command.substr(ptr, szOfFirstElement);
    ptr += szOfFirstElement;
    ptr += 2;

    CommandType cmdType = mapCommandType(commandType);
    auto commandObj = CommandFactory::createCommand(cmdType);

    bool isValid = commandObj->validate(command,ptr);


    return isValid;
}


