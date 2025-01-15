#ifndef RESPELEMENT_H
#define RESPELEMENT_H

#include <string>
using namespace std;

class RESPElement {

    public:
    virtual bool validate(const string& data) = 0;

    virtual ~RESPElement() = default;
};