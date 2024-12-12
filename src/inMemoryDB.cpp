// inMemoryDB.cpp

#include "inMemoryDB.h"

int InMemoryDB::get(string key)
{
    if (this->db.find(key) == this->db.end())
    {
        // assume normal transaction can't be negative
        return -1;
    }

    return this->db[key];
}

void InMemoryDB::put(string key, int value)
{
    if (!transacting)
    {
        cerr << "Error: No transaction in place" << endl;
        return;
    }

    this->actions.push({key, value});
}

void InMemoryDB::begin_transaction()
{
    if (this->transacting)
    {
        cerr << "Error: Another transaction is already in place" << endl;
        return;
    }

    this->transacting = true;
}

void InMemoryDB::commit()
{
    if (!transacting)
    {
        cerr << "Error: No transaction in place" << endl;
        return;
    }

    while (!this->actions.empty())
    {
        auto action = this->actions.front();
        this->db[action.first] = action.second;
        this->actions.pop();
    }

    this->transacting = false;
}

void InMemoryDB::rollback()
{
    if (!transacting)
    {
        cerr << "Error: No transaction in place" << endl;
        return;
    }

    while (!this->actions.empty())
    {
        this->actions.pop();
    }

    this->transacting = false;
}
