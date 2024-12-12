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
    int put(string key, int value);
    int begin_transaction();
    int commit();
    int rollback();
};