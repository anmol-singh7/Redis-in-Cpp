#include "Validator.h"
#include "respEngine/RESPDefinitions.h"
#include "respEngine/factories/RESPFactory.h"
#include "respEngine/RESPElement.h"
#include <string>
using namespace std;


bool Validator::isValidCommand(char* cmd,int sz_Command){
    try{
        if(sz_Command < 1) return false;

        string command(cmd, sz_Command);

        istringstream stream(command);

        char prefix = stream.get();
        if (prefix != '*') return false;

        RESPType elementType = RESPFactory::determineRESPType(prefix);
        unique_ptr<RESPElement> respElement = RESPFactory::createRESPElement(elementType);

        return respElement->validate(stream);
    }
    catch(const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return false;
    }
    
    return false;

}


