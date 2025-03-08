#include "RESPUtils.h"

bool RESPUtils::consumeCRLF(std::istream& stream) {
    char c1 = stream.get();
    char c2 = stream.get();
    return c1 == '\r' && c2 == '\n';
}

int RESPUtils::readSizeFromStream(istream& stream) {
    string size;

    while (isdigit(stream.peek())) {  
        size += stream.get();  
    }

    if (size.empty() || !RESPUtils::consumeCRLF(stream)) {
        return -1;  // Indicate failure
    }

    return stoi(size);
}

string RESPUtils::readLine(istream &stream){
    string line;
    getline(stream, line, '\r');
    if(stream.peek() == '\n') stream.get(); // consume '\n'
    return line;
}
