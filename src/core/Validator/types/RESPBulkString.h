#ifndef RESPBULKSTRING_H
#define RESPBULKSTRING_H

#include <string> 
#include "../RESPElement.h" 

class RESPBulkString : public RESPElement {
public:

    bool validate(string& data, size_t& ptr) override;

};

#endif