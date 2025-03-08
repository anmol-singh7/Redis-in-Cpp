#include "RESPInteger.h"

//need to handle both positive nad negative integer 
//:[<+|->]<value>\r\n  integer may contain +/- symbol
bool RESPInteger::validate(istream& stream){

    return true;
}

RESPValue RESPInteger::parseElement(istream &stream){
    return RESPValue();
}
