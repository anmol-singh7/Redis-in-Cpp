#include "Validator.h"
#include "respEngine/RESPDefinitions.h"
#include "respEngine/factories/RESPFactory.h"
#include "respEngine/RESPElement.h"
#include <string>
using namespace std;

string respTypeToString(RESPType type) {
    switch (type) {
        case RESPType::INTEGER: return "INTEGER";
        case RESPType::DOUBLE: return "DOUBLE";
        case RESPType::SIMPLE_STRING: return "SIMPLE_STRING";
        case RESPType::BULK_STRING: return "BULK_STRING";
        case RESPType::VERBATIM_STRING: return "VERBATIM_STRING";
        case RESPType::BOOLEAN: return "BOOLEAN";
        case RESPType::ARRAY: return "ARRAY";
        case RESPType::MAP: return "MAP";
        case RESPType::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

bool Validator::isValidCommand(string& command){
    try{
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



