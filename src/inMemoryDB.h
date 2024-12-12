// inMemoryDB.h

#include <iostream>
#include <string>
#include <queue>
#include <utility>
#include <unordered_map>

using namespace std;

class InMemoryDB
{
private:
    unordered_map<string, int> db;
    queue<pair<string, int>> actions;
    bool transacting;

public:
    InMemoryDB() : transacting(false) {};
    int get(string key);
    void put(string key, int value);
    void begin_transaction();
    void commit();
    void rollback();
};