include <sqlite3.h>
#include <db/cardrepository.h>

#include <string>
#include <vector>

CardRepository::CardRepository(Database& db)
	: db(db) {}

// doesn't currently distingiush between sqlite error and failure to find
bool CardRepository::cardExists(const std::string& id) {
    const char* sql = R"(
        SELECT 1 FROM cards
        WHERE id = ?
        LIMIT 1;
    )";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(
        db.getConnection(), sql, -1, &stmt, nullptr
    ) != SQLITE_OK) {
        return false;
    }

    if (sqlite3_bind_text(
        stmt, 1, id.c_str(), -1, SQLITE_TRANSIENT
    ) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return false;
    }

    bool exists = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return exists;
}

bool CardRepository::insertCard(const Card& card) {
    const char* sql = R"(
       INSERT INTO cards (
            id,
            oracle_id,
            set_code,
            collector_number,
            rarity,
            mana_cost,
            cmc,
            types,
            subtypes,
            power,
            toughness,
            oracle_text,
            colors,
            image_url,
            card_faces
       )
       VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);
    )";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(
        db.getConnection(), sql, -1, &stmt, nullptr
    ) != SQLITE_OK {
        return false;
    }

    // bind parameter
    
    bool exists = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return exists;
}

/*
std::vector<Card> CardRepository::getCardsBySet(const std::string& set_code) {

}
*/
