#include "RESPArray.h"
using namespace std;

bool RESPArray::validate(const string& data, size_t& ptr){

    string numElements = "";

    while(ptr < data.size() && isdigit(data[ptr])){
        numElements += data[ptr++];
    }

    if(numElements.empty()){
        return false;
    }

    if(!RESPFactory::consumeCRLF(data, ptr)){
        return false;
    }

    int numberOfElements = stoi(numElements);

    for(int i = 0;i < numberOfElements; i++){
        if(ptr >= data.size()){
            return false;
        }
        
        char prefix = data[ptr++];
        RESPTypes elementType = RESPFactory::determineRESPType(prefix);
        unique_ptr<RESPElement> respElement = RESPFactory::createRESPElement(elementType);
        
        if(respElement->validate(data, ptr)){
            return false;
        }

    }


    return true;
}