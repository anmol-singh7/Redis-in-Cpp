#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "../respEngine/RESPDefinitions.h"
#include <unordered_map>
#include <chrono>

using namespace std;

class Database {
private:
    unordered_map<string, RESPValue> storage;
    unordered_map<string, chrono::time_point<chrono::steady_clock>> expiry;

    // Private constructor to prevent direct instantiation
    Database() = default;

public:
    // Delete copy constructor and assignment operator to enforce singleton
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    // Corrected: Return reference to singleton instance
    static Database& getInstance() {
        static Database instance;
        return instance;
    }

    void set(const string& key, const RESPValue& value, int64_t milliseconds);

    RESPValue get(const string& key);

    void del(const string& key);

    bool exists(const string& key);

    bool expire(const string& key, int64_t milliseconds);

    int64_t ttl(const string& key);

};

#endif // DATABASE_H
