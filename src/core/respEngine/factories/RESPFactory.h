#ifndef RESPFACTORY_H
#define RESPFACTORY_H

#include <memory>
#include "../RESPElement.h"
#include "../RESPDefinitions.h"
#include <sstream> 
using namespace std;

class RESPFactory {
    public:
    static unique_ptr<RESPElement> createRESPElement(RESPType type);

    static RESPType determineRESPType(char prefix);

    // static bool consumeCRLF(istream& stream);
};

#endif