#include "MyDatabase.h"
#include <iostream>

// SQLite3 database connection
sqlite3* db = nullptr;

// Function to initialize the SQLite database connection
bool InitDatabase(const char* dbName) {
    int rc = sqlite3_open(dbName, &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    else {
        std::cout << "Opened database successfully" << std::endl;
        return true;
    }
}

// Function to execute an SQL query in the database
void ExecuteQuery(const char* query) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, query, nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else {
        std::cout << "Query executed successfully" << std::endl;
    }
}

// Function to close the SQLite database connection
void CloseDatabase() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}




































//#include "MyDatabase.h"
//#include <iostream>
//
//sqlite3* db;
//
//bool InitDatabase(const char* dbName) {
//    int rc = sqlite3_open(dbName, &db);
//    if (rc != SQLITE_OK) {
//        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
//        return false;
//    }
//    else {
//        std::cout << "Opened database successfully" << std::endl;
//        return true;
//    }
//    
//}
//
//void ExecuteQuery(const char* query) {
//    char* errMsg = nullptr;
//    int rc = sqlite3_exec(db, query, nullptr, nullptr, &errMsg);
//
//    if (rc != SQLITE_OK) {
//        std::cerr << "SQL error: " << errMsg << std::endl;
//        sqlite3_free(errMsg);
//    }
//    else {
//        std::cout << "Query executed successfully" << std::endl;
//    }
//}
//
//// Optional function to close the database
//void CloseDatabase() {
//    if (db) {
//        sqlite3_close(db);
//        db = nullptr;
//    }
//}