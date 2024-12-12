// test.cpp

#include <iostream>
#include <vector>
#include <string>
#include "src/inMemoryDB.h"
#include <gtest/gtest.h>

TEST(BasicTests, PutAndGetValues1)
{
    InMemoryDB db;
    EXPECT_EQ(db.begin_transaction(), 0);

    db.put("key1", 1);
    db.put("key2", 2);
    db.put("key3", 3);

    EXPECT_EQ(db.commit(), 0);

    EXPECT_EQ(db.get("key1"), 1);
    EXPECT_EQ(db.get("key2"), 2);
    EXPECT_EQ(db.get("key3"), 3);
}

TEST(BasicTests, PutAndGetValues2)
{
    InMemoryDB db;
    EXPECT_EQ(db.put("key1", 2), -1);

    EXPECT_EQ(db.begin_transaction(), 0);

    db.put("key1", 1);
    db.put("key2", 2);
    db.put("key3", 3);

    EXPECT_EQ(db.get("key1"), -1);
    EXPECT_EQ(db.get("key2"), -1);
    EXPECT_EQ(db.get("key3"), -1);

    EXPECT_EQ(db.commit(), 0);

    EXPECT_EQ(db.get("key1"), 1);
    EXPECT_EQ(db.get("key2"), 2);
    EXPECT_EQ(db.get("key3"), 3);
}

TEST(BasicTests, PutAndGetValues3)
{
    InMemoryDB db;
    EXPECT_EQ(db.get("A"), -1);
    EXPECT_EQ(db.put("A", 5), -1);
    EXPECT_EQ(db.get("A"), -1);
}

TEST(BasicTests, Rollback1)
{
    InMemoryDB db;
    db.begin_transaction();
    
    vector<int> expectedValues = { 5, 4, 3};
    vector<int> results;
    results.push_back(db.put("A", 5));
    results.push_back(db.put("B", 4));
    results.push_back(db.put("C", 3));
    EXPECT_EQ(results, expectedValues);
    
    db.rollback();
    
    EXPECT_EQ(db.get("A"), -1);
    EXPECT_EQ(db.get("B"), -1);
    EXPECT_EQ(db.get("C"), -1);
}

TEST(AdvancedTests, Rollback2)
{
    InMemoryDB db;
    EXPECT_EQ(db.rollback(), -1);
    
    db.begin_transaction();
    
    db.put("A", 5);
    db.put("B", 4);
    db.put("C", 3);
    
    db.rollback();
    
    EXPECT_EQ(db.get("A"), -1);
    EXPECT_EQ(db.get("B"), -1);
    EXPECT_EQ(db.get("C"), -1);    

    EXPECT_EQ(db.put("A", 7), -1);
    EXPECT_EQ(db.put("B", 8), -1);
    EXPECT_EQ(db.put("C", 9), -1);
    
    EXPECT_EQ(db.rollback(), -1);
    
    db.begin_transaction();
    
    EXPECT_EQ(db.put("A", 7), 7);
    EXPECT_EQ(db.put("B", 8), 8);
    EXPECT_EQ(db.put("C", 9), 9);    
    
    db.commit();
    
    EXPECT_EQ(db.get("A"), 7);
    EXPECT_EQ(db.get("B"), 8);
    EXPECT_EQ(db.get("C"), 9);
}

TEST(AdvancedTests, MultiTransaction)
{
    InMemoryDB db;
    db.begin_transaction();
    db.commit();
    
    EXPECT_EQ(db.get("A"), -1);
    EXPECT_EQ(db.rollback(), -1);
    
    db.begin_transaction();
    
    db.put("A", 5);
    db.put("A", 6);
    
    db.commit();
    
    EXPECT_EQ(db.get("A"), 6);
    
    db.begin_transaction();
    
    db.put("B", 7);
    db.rollback();
    
    EXPECT_EQ(db.commit(), -1);
    EXPECT_EQ(db.get("B"), -1);
    
    db.begin_transaction();
    
    db.put("C", 8);
    db.commit();
    
    EXPECT_EQ(db.put("A", 10), -1);
    
    EXPECT_EQ(db.get("A"), 6);
    EXPECT_EQ(db.get("C"), 8);
}