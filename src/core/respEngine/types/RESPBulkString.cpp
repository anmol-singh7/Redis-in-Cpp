#include "RESPBulkString.h"

bool RESPBulkString::validate(istream& stream) {
    
    int size = RESPUtils::readSizeFromStream(stream);

    if(size < 0) return false;
    
    for (int i = 0; i < size; i++) {
        if (stream.get() == EOF) return false;
    }

    return RESPUtils::consumeCRLF(stream);
}

RESPValue RESPBulkString::parseElement(istream& stream) {
    string strSize = RESPUtils::readLine(stream); //comsuming the line

    string str = RESPUtils::readLine(stream); // Read the actual string
    return RESPValueStruct::create(str); // Return the string as a RESPValue
}
