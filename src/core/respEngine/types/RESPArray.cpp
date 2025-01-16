#include "RESPArray.h"
#include <cctype>
#include "../factories/RESPFactory.h"
using namespace std;

bool RESPArray::validate(istream& stream){
    string numElements;
    char ch;
    while (stream.get(ch) && isdigit(ch)) {
        numElements += ch;
    }

    if (numElements.empty() || !RESPFactory::consumeCRLF(stream)) {
        return false;
    }

    int numberOfElements = stoi(numElements);
    for (int i = 0; i < numberOfElements; i++) {
        char prefix = stream.get();
        RESPType elementType = RESPFactory::determineRESPType(prefix);
        unique_ptr<RESPElement> respElement = RESPFactory::createRESPElement(elementType);

        if (!respElement->validate(stream)) {
            return false;
        }
    }

    return true;
}