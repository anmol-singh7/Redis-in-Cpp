#include "RESPFactory.h"
#include "../types/RESPSimpleString.h"
#include "../types/RESPInteger.h"
#include "../types/RESPBulkString.h"
#include "../types/RESPArray.h"
#include "../types/RESPError.h"
#include "../types/RESPTypes.h"
#include <stdexcept>
using namespace std;



unique_ptr<RESPElement> RESPFactory::createRESPElement(RESPTypes type)
{
    switch(type)
    {
        case RESPTypes::SIMPLE_STRING:
            return make_unique<RESPSimpleString>();
        case RESPTypes::INTEGER:
            return make_unique<RESPInteger>();
        case RESPTypes::BULK_STRING:
            return make_unique<RESPBulkString>();
        case RESPTypes::ARRAY:
            return make_unique<RESPArray>();
        case RESPTypes::ERROR:
            return make_unique<RESPError>();
        default:
            throw std::invalid_argument("Unsupported RESP data type");
    }

    return unique_ptr<RESPElement>();
}

RESPTypes RESPFactory::determineRESPType(char prefix)
{
    switch(prefix)
    {
        case '+': return RESPTypes::SIMPLE_STRING;
        case ':': return RESPTypes::INTEGER;
        case '$': return RESPTypes::BULK_STRING;
        case '*': return RESPTypes::ARRAY;
        case '-': return RESPTypes::ERROR;
        default: throw std::invalid_argument("Invalid RESP type prefix");
    }
    return RESPTypes();
}

bool RESPFactory::consumeCRLF(const string &data, size_t &ptr)
{
    if(ptr + 1 >= data.size() || data[ptr] != '\r' || data[ptr + 1] != '\n')
    {
        return false;
    }

    ptr += 2;
    return false;
}
