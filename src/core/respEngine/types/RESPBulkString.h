#ifndef RESPBULKSTRING_H
#define RESPBULKSTRING_H

#include <string> 
#include "../RESPElement.h" 
#include "../factories/RESPFactory.h"
#include <cctype>

class RESPBulkString : public RESPElement {
public:

    bool validate(istream& stream) override;

};

#endif