#include "RESPArray.h"
#include <string>
#include <cctype>
#include <vector>
#include "../factories/RESPFactory.h"

using namespace std;

bool RESPArray::validate(istream& stream) {

    int numberOfElements = RESPUtils::readSizeFromStream(stream);

    if(numberOfElements < 0) return false;
    
    for (int i = 0; i < numberOfElements; i++) {
        if (stream.eof()) return false;

        char prefix = stream.get();
     
        RESPType elementType = RESPFactory::determineRESPType(prefix);

        unique_ptr<RESPElement> respElement = RESPFactory::createRESPElement(elementType);

        if (!respElement || !respElement->validate(stream)) {
            return false;
        }
    }

    return true;
}

RESPValue RESPArray::parseElement(istream &stream) {

    int numberOfElements = RESPUtils::readSizeFromStream(stream);

    RESPVarArray elements; // This is a vector<RESPValue>

    for (int i = 0; i < numberOfElements; i++) {
        if (stream.eof()) return nullptr;

        char prefix = stream.get();
        RESPType elementType = RESPFactory::determineRESPType(prefix);
        unique_ptr<RESPElement> respElement = RESPFactory::createRESPElement(elementType);

        if (!respElement) return nullptr;
        
        RESPValue parsedValue = respElement->parseElement(stream);
        elements.push_back(parsedValue);
    }

    return RESPValueStruct::create(elements);
}
