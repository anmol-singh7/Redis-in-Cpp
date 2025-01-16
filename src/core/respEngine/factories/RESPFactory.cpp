#include "RESPFactory.h"
#include "../types/RESPSimpleString.h"
#include "../types/RESPInteger.h"
#include "../types/RESPBulkString.h"
#include "../types/RESPArray.h"
#include "../types/RESPError.h"
#include <stdexcept>
using namespace std;

unique_ptr<RESPElement> RESPFactory::createRESPElement(RESPType type)
{
    switch(type)
    {
        case RESPType::SIMPLE_STRING:
            return make_unique<RESPSimpleString>();
        case RESPType::INTEGER:
            return make_unique<RESPInteger>();
        case RESPType::BULK_STRING:
            return make_unique<RESPBulkString>();
        case RESPType::ARRAY:
            return make_unique<RESPArray>();
        case RESPType::ERROR:
            return make_unique<RESPError>();
        default:
            throw std::invalid_argument("Unsupported RESP data type");
    }

    return unique_ptr<RESPElement>();
}

RESPType RESPFactory::determineRESPType(char prefix)
{
    switch(prefix)
    {
        case '+': return RESPType::SIMPLE_STRING;
        case ':': return RESPType::INTEGER;
        case '$': return RESPType::BULK_STRING;
        case '*': return RESPType::ARRAY;
        case '-': return RESPType::ERROR;
        default: throw std::invalid_argument("Invalid RESP type prefix");
    }
    return RESPType();
}

bool RESPFactory::consumeCRLF(istream& stream) {
    char c1 = stream.get();
    char c2 = stream.get();
    return c1 == '\r' && c2 == '\n';
}