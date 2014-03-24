/**
 * @file    Statement_test.cpp
 * @ingroup tests
 * @brief   Test of a SQLiteCpp Statement.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Statement.h>

#include <gtest/gtest.h>

#include <cstdio>


TEST(Statement, invalid) {
    remove("test.db3");
    {
        // Create a new database
        SQLite::Database db("test.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);

        // Compile a SQL query, but without any table in the database
        EXPECT_THROW(SQLite::Statement query(db, "SELECT * FROM test"), SQLite::Exception);

        EXPECT_EQ(0, db.exec("CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT)"));
        
        // Compile a SQL query with no parameter
        SQLite::Statement   query(db, "SELECT * FROM test");
        EXPECT_STREQ("SELECT * FROM test", query.getQuery().c_str());
        EXPECT_EQ(2, query.getColumnCount ());
        EXPECT_EQ(false, query.isOk());
        EXPECT_EQ(false, query.isDone());
        EXPECT_THROW(query.isColumnNull(-1), SQLite::Exception);
        EXPECT_THROW(query.isColumnNull(0), SQLite::Exception);
        EXPECT_THROW(query.isColumnNull(1), SQLite::Exception);
        EXPECT_THROW(query.isColumnNull(2), SQLite::Exception);
        EXPECT_THROW(query.getColumn(-1), SQLite::Exception);
        EXPECT_THROW(query.getColumn(0), SQLite::Exception);
        EXPECT_THROW(query.getColumn(1), SQLite::Exception);
        EXPECT_THROW(query.getColumn(2), SQLite::Exception);

        query.reset();
        EXPECT_EQ(false, query.isOk());
        EXPECT_EQ(false, query.isDone());

        query.exec();
        EXPECT_EQ(false, query.isOk());
        EXPECT_EQ(true,  query.isDone());
        query.reset();
        EXPECT_EQ(false, query.isOk());
        EXPECT_EQ(false, query.isDone());

        query.reset();
        EXPECT_THROW(query.bind(-1, 123), SQLite::Exception);
        EXPECT_THROW(query.bind(0, 123), SQLite::Exception);
        EXPECT_THROW(query.bind(1, 123), SQLite::Exception);
        EXPECT_THROW(query.bind(2, 123), SQLite::Exception);
        EXPECT_THROW(query.bind(0, "abc"), SQLite::Exception);
        EXPECT_THROW(query.bind(0), SQLite::Exception);

        query.exec();
        EXPECT_THROW(query.isColumnNull(0), SQLite::Exception);
        EXPECT_THROW(query.getColumn(0), SQLite::Exception);

    } // Close DB test.db3
    remove("test.db3");
}
