#ifndef RESPBULKSTRING_H
#define RESPBULKSTRING_H

#include <iostream>
#include <string> 
#include "../RESPElement.h" 
#include "../factories/RESPFactory.h"
#include <cctype>
using namespace std;

class RESPBulkString : public RESPElement {
public:

    bool validate(istream& stream) override;

    RESPValue parseElement(istream& stream) override;

};

#endif