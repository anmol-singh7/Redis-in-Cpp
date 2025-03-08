#include "RESPError.h"

bool RESPError::validate(istream& stream){

    return true;
}

RESPValue RESPError::parseElement(istream &stream){
    return RESPValue();
}
