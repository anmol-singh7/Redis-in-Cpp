#ifndef RESPERROR_H
#define RESPERROR_H

#include <string> 
#include "../RESPElement.h" 

class RESPError : public RESPElement {
public:

    bool validate(istream& stream) override;

    RESPValue parseElement(istream& stream) override;
};

#endif