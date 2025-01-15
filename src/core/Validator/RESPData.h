#ifndef RESPDATA_H
#define RESPDATA_H

#include <string>

class RESPData {

    public:
    virtual bool validate(const std::string& data) = 0;

    virtual ~RESPData() = default;
};