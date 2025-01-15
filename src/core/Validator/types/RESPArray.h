#ifndef RESPARRAY_H
#define RESPARRAY_H

#include <string> 
#include <iostream>
#include "../RESPElement.h" 

class RESPArray : public RESPElement {
public:

    bool validate(string& data, size_t& ptr) override;

    
};

#endif