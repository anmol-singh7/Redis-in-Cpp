#ifndef RESPELEMENT_H
#define RESPELEMENT_H

#include <iostream>
#include <string>
#include <cctype>
#include "RESPDefinitions.h"
#include <sstream>
using namespace std;

    
class RESPElement {

    public:
    virtual bool validate(istream& stream) = 0;
    
    virtual ~RESPElement() = default;
};

#endif