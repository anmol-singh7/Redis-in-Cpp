#ifndef RESPDATAFACTORY_H
#define RESPDATAFACTORY_H


#include "./RESPData.h"
#include <memory>

using namespace std;

enum class DataType {
    SIMPLE_STRING,
    INTEGER,
    BULK_STRING,
    ARRAY,
    ERROR
};

class RESPDataFactory {
    public:
    unique_ptr<RESPData> createRESPDataObject(DataType dataType);
};

#endif