#ifndef RESPFACTORY_H
#define RESPFACTORY_H

#include <memory>
#include "../RESPData.h"
#include "../types/RESPElement.h"

using namespace std;

class RESPFactory {
    public:
    static unique_ptr<RESPElement> createRESPElement(RESPTypes type);

    static RESPTypes determineRESPType(char prefix);

    static bool consumeCRLF(const string& data, size_t& ptr);

    
};

#endif