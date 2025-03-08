#include "Database.h"

void Database::set(const string& key, const RESPValue& value, int64_t milliseconds) {
    storage[key] = value;

    if (milliseconds > 0) {
        expiry[key] = chrono::steady_clock::now() + chrono::milliseconds(static_cast<int64_t>(milliseconds));
    } else {
        expiry.erase(key);
    }
}


RESPValue Database::get(const string& key) {
    // Check if key exists
    auto it = storage.find(key);
    if (it == storage.end()) {
        return nullptr;  // ✅ Fix: Return nullptr instead of nullptr_t
    }

    // Check if key has expired
    auto exp_it = expiry.find(key);
    if (exp_it != expiry.end() && chrono::steady_clock::now() > exp_it->second) {
        storage.erase(it);  // Removes both key and its expiry
        expiry.erase(exp_it);
        return nullptr;  // ✅ Fix: Return nullptr instead of nullptr_t
    }

    return it->second;
}



void Database::del(const string &key){
    expiry.erase(key);
    storage.erase(key);
}

bool Database::exists(const string &key){
    return storage.find(key) != storage.end();
}

bool Database::expire(const string &key, int64_t milliseconds) {
    if (storage.find(key) != storage.end()) {
        expiry[key] = chrono::steady_clock::now() + chrono::milliseconds(milliseconds);
        return true;
    }
    return false;
}


int64_t Database::ttl(const string &key) {
    auto it = expiry.find(key);
    if (it == expiry.end()) return -2; // -2 means key does not exist in expiry map

    auto now = chrono::steady_clock::now();
    auto expirationTime = it->second;

    if (now >= expirationTime) {
        return -2; // Key has already expired
    }

    return chrono::duration_cast<chrono::milliseconds>(expirationTime - now).count();
}

