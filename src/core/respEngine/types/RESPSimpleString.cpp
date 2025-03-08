#include "RESPSimpleString.h"

bool RESPSimpleString::validate(istream& stream){

    return true;
}

RESPValue RESPSimpleString::parseElement(istream &stream){
    return RESPValue();
}
