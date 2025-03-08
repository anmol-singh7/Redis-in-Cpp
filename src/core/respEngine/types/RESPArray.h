#ifndef RESPARRAY_H
#define RESPARRAY_H

#include <iostream>
#include <string> 
#include "../RESPElement.h" 

using namespace std;

class RESPArray : public RESPElement {
public:

    bool validate(istream& stream) override;

    RESPValue parseElement(istream& stream) override;
};

#endif