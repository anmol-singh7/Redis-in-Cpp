#ifndef RESPERROR_H
#define RESPERROR_H

#include <string> 
#include "../RESPElement.h" 

class RESPError : public RESPElement {
public:

    bool validate(string& data, size_t& ptr) override;

};

#endif