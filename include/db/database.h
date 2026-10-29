#pragma once

#include <string>
#include <sqlite3.h>

class Database {
public:
    Database(const std::string& path);
    ~Database();

    // prevent copy / copy assignment
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    bool initialize();
    sqlite3* getConnection() const;

private:
    sqlite3* db;
};