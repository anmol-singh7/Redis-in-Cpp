#include "Validator.h"
#include "respEngine/types/RESPTypes.h"
#include "respEngine/factories/RESPFactory.h"
#include "respEngine/RESPElement.h"
#include <string>
using namespace std;


bool Validator::isValidCommand(char* cmd,int sz_Command){
    try{
        string command(cmd, sz_Command);
        if(sz_Command < 1) return false;

        size_t ptr = 0;

        char prefix = command[ptr++];

        if(prefix != '*') return false;    

        RESPTypes elementType = RESPFactory::determineRESPType(prefix);
        unique_ptr<RESPElement> respElement = RESPFactory::createRESPElement(elementType);

        return respElement->validate(command,ptr);
    }
    catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
    
    return false;
}


