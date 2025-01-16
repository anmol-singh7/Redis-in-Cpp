#ifndef RESPSIMPLESTRING_H
#define RESPSIMPLESTRING_H

#include <string> 
#include "../RESPElement.h" 

class RESPSimpleString : public RESPElement {
public:

    bool validate(string& data, size_t& ptr) override;

};

#endif