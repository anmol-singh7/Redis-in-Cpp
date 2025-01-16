#ifndef RESPINTEGER_H
#define RESPINTEGER_H

#include <string> 
#include "../RESPElement.h" 

class RESPInteger : public RESPElement {
public:

    bool validate(string& data, size_t& ptr) override;

};

#endif