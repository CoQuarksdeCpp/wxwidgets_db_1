#pragma once

#include <sqlite3.h>

// Declare db as an extern variable so it can be shared between files
extern sqlite3* db;

// Function to initialize the SQLite database connection
bool InitDatabase(const char* dbName);

// Function to execute a query in the SQLite3 database
void ExecuteQuery(const char* query);

// Function to close the database connection
void CloseDatabase();









//#pragma once
//
//#include <sqlite3.h>
//
//// Function to initialize the database connection
//bool InitDatabase(const char* dbName);
//
//
//void ExecuteQuery(const char* query);
//
//// Optional: Function to close the database connection if needed
//void CloseDatabase();
