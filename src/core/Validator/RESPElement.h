#ifndef RESPELEMENT_H
#define RESPELEMENT_H

#include <string>
using namespace std;

class RESPElement {

    public:
    virtual bool validate(string& data, size_t& ptr) = 0;

    virtual ~RESPElement() = default;
};

#endif