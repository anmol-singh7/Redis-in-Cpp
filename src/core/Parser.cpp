#include "Parser.h"
#include "respEngine/factories/RESPFactory.h"
#include "respEngine/RESPElement.h"
using namespace std;

RESPValue Parser::parseCommand(string& command){   
    
    int sz_Command =  command.size();
    if(sz_Command < 1) return RESPValue();

    istringstream stream(command);

    char prefix = stream.get();

    if(prefix != '*') return RESPValue();

    RESPType elementType = RESPFactory::determineRESPType(prefix);

    unique_ptr<RESPElement> respElement = RESPFactory::createRESPElement(elementType);
    
    return respElement->parseElement(stream);
}



