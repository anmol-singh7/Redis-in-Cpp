#ifndef RESPSIMPLESTRING_H
#define RESPSIMPLESTRING_H

#include <string> 
#include "../RESPElement.h" 

class RESPSimpleString : public RESPElement {
public:

    bool validate(istream& stream) override;

    RESPValue parseElement(istream& stream) override;
};

#endif