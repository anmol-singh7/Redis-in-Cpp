

#include "SetCommand.h"
#include <unordered_set>

const string ERROR_MSG = "-ERR wrong type of arguments for 'set' command\r\n";

struct CommandParams {
    bool hasSyntaxError = false;
    bool hasExpiryOption = false;
    int64_t expiryTime = -2;
    string expiryOption;
    bool hasGetOption = false;
    RESPValue oldValue = nullptr;
    bool hasSetCondition = false;
    string setCondition;
};

unordered_set<string> validExpiryOptions = {"ex", "px", "exat", "pxat"};

int64_t getExpiryTimeMs(const string& option, int64_t expiryTime) {
    if (option == "ex") return expiryTime * 1000;
    if (option == "px") return expiryTime;
    
    int64_t nowMs = chrono::duration_cast<chrono::milliseconds>(
        chrono::system_clock::now().time_since_epoch()).count();
    return (option == "exat" ? expiryTime * 1000 : expiryTime) - nowMs;
}

void parseOptions(const RESPVarArray& args, int& index, CommandParams& params, const string& key, Database& db) {
    while (index < args.size()) {
        if (!holds_alternative<string>(args[index]->value)) {
            params.hasSyntaxError = true;
            return;
        }
        
        string option = get<string>(args[index++]->value);

        cout<<option<<"  :  "<<index-1<<endl;

        if (option == "nx" || option == "xx") {
            if (params.hasSetCondition) {cout<<1<<endl; params.hasSyntaxError = true; return; }
            params.hasSetCondition = true;
            params.setCondition = option;
        } else if (option == "get") {
            if (!db.exists(key)) {cout<<2<<endl; params.hasSyntaxError = true; return; }
            params.hasGetOption = true;
            params.oldValue = db.get(key);
        } else if (validExpiryOptions.count(option)) {
            if (params.hasExpiryOption || index >= args.size() || !holds_alternative<string>(args[index]->value)) {
                cout<<3<<endl;
                params.hasSyntaxError = true;
                return;
            }
            int64_t expiryTime = stoll(get<string>(args[index++]->value));
            if (expiryTime < 0) {cout<<4<<endl; params.hasSyntaxError = true; return; }
            params.expiryOption = option;
            params.expiryTime = getExpiryTimeMs(option, expiryTime);
            params.hasExpiryOption = true;
        } else if (option == "keepttl") {
            if (params.hasExpiryOption) { cout<<5<<endl; params.hasSyntaxError = true; return; }
            params.expiryOption = option;
            params.expiryTime = db.ttl(key);
            params.hasExpiryOption = true;
        } else {
            cout<<6<<endl;
            params.hasSyntaxError = true;

            return;
        }
    }
}

string SetCommand::execute(const RESPValue& args) {
    Database& db = Database::getInstance();
    if (!holds_alternative<RESPVarArray>(args->value)) return ERROR_MSG;
    
    const RESPVarArray& cmdArgs = get<RESPVarArray>(args->value);
    if (cmdArgs.size() < 3) return "-ERR wrong number of arguments for 'set' command\r\n";
    
    int index = 1;
    if (!holds_alternative<string>(cmdArgs[index]->value)) return ERROR_MSG;
    string key = get<string>(cmdArgs[index++]->value);
    if (!holds_alternative<string>(cmdArgs[index]->value)) return ERROR_MSG;
    string value = get<string>(cmdArgs[index++]->value);

    cout<<"key :"<<key<<"value : "<<value<<endl;

    CommandParams params;
    parseOptions(cmdArgs, index, params, key, db);
    if (params.hasSyntaxError) return ERROR_MSG;
    
    string response = params.hasGetOption ? "$" + to_string(get<string>(params.oldValue->value).size()) + "\r\n" + get<string>(params.oldValue->value) + "\r\n" : "+OK\r\n";
    if (params.hasExpiryOption && params.expiryTime <= 0) return response;
    
    if (params.hasSetCondition) {
        if ((params.setCondition == "nx" && !db.exists(key)) || (params.setCondition == "xx" && db.exists(key))) {
            db.set(key, RESPValueStruct::create(value), params.expiryTime);
        }
        return response;
    }
    
    db.set(key, RESPValueStruct::create(value), params.expiryTime);
    return response;
}
