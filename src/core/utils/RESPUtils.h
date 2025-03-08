#ifndef RESP_UTILS_H
#define RESP_UTILS_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class RESPUtils {
public:
    static bool consumeCRLF(istream& stream);

    static int readSizeFromStream(istream& stream);

    static string readLine(istream &stream);
};

#endif
