#ifndef RESP_DEFINITIONS_H
#define RESP_DEFINITIONS_H

#include <variant>
#include <vector>
#include <map>
#include <string>
#include <cstdint>
#include <memory>  // For shared_ptr

using namespace std;


// Enum to define different RESP types
enum class RESPType {
    INTEGER,
    DOUBLE,
    SIMPLE_STRING,
    BULK_STRING,
    VERBATIM_STRING,
    BOOLEAN,
    RESP_NULL,
    ARRAY,
    MAP,
    ERROR
};

// Forward declaration
struct RESPValueStruct;

// Define a shared pointer to allow recursive types
using RESPValue = shared_ptr<RESPValueStruct>;


// Struct to hold the actual RESP value
struct RESPValueStruct {
    variant<
        int64_t,                        // Integer
        double,                         // Double
        string,                         // Simple String, Bulk String, Verbatim String
        bool,                           // Boolean
        nullptr_t,                      // Null
        vector<RESPValue>,              // ✅ Nested Arrays (RESPVarArray)
        map<string, RESPValue>          // ✅ Nested Maps (RESPVarMap)
    > value;

    // Constructors for easy assignment  
    template <typename T>
    RESPValueStruct(T v) : value(move(v)) {}

    // Factory method for creating shared_ptr instances
    template <typename T>
    static RESPValue create(T v) {
        return make_shared<RESPValueStruct>(move(v));
    }
};

// Aliases for better readability
using RESPVarArray = vector<RESPValue>;
using RESPVarMap = map<string, RESPValue>;

#endif // RESP_DEFINITIONS_H
