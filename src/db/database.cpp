#include "db/database.h"
#include <iostream>

// creates or opens a database obj, should only have 1 at a time
Database::Database(const std::string& path) {
	db = nullptr;

	int res = sqlite3_open(path.c_str(), &db);

	if (res != SQLITE_OK) {
		std::cerr << "Failed to open database: "
			<< sqlite3_errmsg(db) << "\n";
	}
}

Database::~Database()
{
	if (db != nullptr) {
		sqlite3_close(db);
	}
}

bool initialize() {
	// pointer to c-style string sql commands
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS sets (
            code TEXT PRIMARY KEY,
            name TEXT NOT NULL,
            release_date TEXT,
            card_count INTEGER
        );

        CREATE TABLE IF NOT EXISTS cards (
            id TEXT PRIMARY KEY,
            oracle_id TEXT,
            name TEXT NOT NULL,
            set_code TEXT NOT NULL,
            collector_number TEXT,
            rarity TEXT,
            mana_cost TEXT,
            cmc REAL,
            type_line TEXT,
            oracle_text TEXT,
            colors TEXT,
            color_identity TEXT,
            image_url TEXT,
            artist TEXT,

            FOREIGN KEY (set_code) REFERENCES sets(code)
        );

        CREATE INDEX IF NOT EXISTS idx_cards_set_code
        ON cards(set_code);

        CREATE INDEX IF NOT EXISTS idx_cards_oracle_id
        ON cards(oracle_id);

        CREATE INDEX IF NOT EXISTS idx_cards_name
        ON cards(name);
    )";

    char* errorMessage = nullptr;

    int res = sqlite3_exec(
        db,
        sql,
        nullptr,
        nullptr,
        &errorMessage
    );

    if (res != SQLITE_OK) {
        std::cerr << "Failed to initialize database: "
            << errorMessage << '\n';

        sqlite3_free(errorMessage);
        return false;
    }

    return true;
}

sqlite3* Database::getConnection() const
{
    return db;
}