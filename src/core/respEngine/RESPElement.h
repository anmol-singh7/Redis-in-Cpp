#ifndef RESPELEMENT_H
#define RESPELEMENT_H

#include <iostream>
#include <string>
#include <cctype>
#include "RESPDefinitions.h"
#include <sstream>
#include "../utils/RESPUtils.h"
using namespace std;

class RESPElement {  

    public:
        virtual bool validate(istream& stream) = 0;
        
        virtual RESPValue parseElement(istream& stream) = 0;
        
        virtual ~RESPElement() = default;
};

#endif