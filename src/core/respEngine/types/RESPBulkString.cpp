#include "RESPBulkString.h"

bool RESPBulkString::validate(istream& stream) {
    string strSize;
    char ch;
    while (stream.get(ch) && isdigit(ch)) {
        strSize += ch;
    }

    if (strSize.empty() || !RESPFactory::consumeCRLF(stream)) {
        return false;
    }

    int length = stoi(strSize);
    for (int i = 0; i < length; i++) {
        if (stream.get() == EOF) return false;
    }

    return RESPFactory::consumeCRLF(stream);
}