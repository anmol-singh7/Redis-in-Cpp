#ifndef RESPDEFINITIONS_H
#define RESPDEFINITIONS_H

#include <variant>
#include <string>
#include <vector>
#include <map>
#include <cstdint>
using namespace std;

// Enum class for RESP3 data types
enum class RESPType {
    SIMPLE_STRING,
    INTEGER,
    BULK_STRING,
    ARRAY,
    ERROR,
    NULL_VALUE,
    BOOLEAN,
    DOUBLE,
    SET,
    MAP,
    ATTRIBUTE,
    VERBATIM_STRING
};

// Define RESPValue as a variant of all possible RESP3 types
using RESPValue = variant<
    int64_t,                                        // Integer
    double,                                         // Double
    string,                                         // Simple String, Bulk String, or Verbatim String
    bool,                                           // Boolean
    nullptr_t,                                       // Null
    vector<variant<int64_t, double, string, bool, nullptr_t>>, // Array or Set
    map<string, variant<int64_t, double, string, bool, nullptr_t>> // Map
>;

#endif 
