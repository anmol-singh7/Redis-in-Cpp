#include "RESPDataFactory.h"
#include "../types/RESPSimpleString.h"
#include "../types/RESPInteger.h"
#include "../types/RESPBulkString.h"
#include "../types/RESPArray.h"
#include "../types/RESPError.h"

using namespace std;

unique_ptr<RESPData> RESPDataFactory::createRESPDataObject(DataType dataType)
{
    switch(dataType){
        case DataType::SIMPLE_STRING:
            return make_unique<SimpleString>();
        case DataType::INTEGER:
            return make_unique<Integer>();
        case DataType::BULK_STRING:
            return make_unique<BulkString>();
        case DataType::ARRAY:
            return make_unique<Array>();
        case DataType::ERROR:
            return make_unique<Error>();
    }

    return unique_ptr<RESPData>();
}
