// inMemoryDB.cpp

#include "inMemoryDB.h"

int InMemoryDB::get(string key)
{
    if (this->db.find(key) == this->db.end())
        // assume normal transaction can't be negative
        return -1;

    return this->db[key];
}

int InMemoryDB::put(string key, int value)
{
    if (!transacting)
        return -1;

    this->actions.push({key, value});
    return value;
}

int InMemoryDB::begin_transaction()
{
    if (this->transacting)
        return -1;

    this->transacting = true;
    return 0;
}

int InMemoryDB::commit()
{
    if (!transacting)
        return -1;

    while (!this->actions.empty())
    {
        auto action = this->actions.front();
        this->db[action.first] = action.second;
        this->actions.pop();
    }

    this->transacting = false;
    return 0;
}

int InMemoryDB::rollback()
{
    if (!transacting)
        return -1;

    while (!this->actions.empty())
    {
        this->actions.pop();
    }

    this->transacting = false;
    return 0;
}
