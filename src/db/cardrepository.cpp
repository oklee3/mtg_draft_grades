#include <sqlite3.h>
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
       )
       VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);
    )";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(
        db.getConnection(), sql, -1, &stmt, nullptr
    ) != SQLITE_OK) {
        return false;
    }

    // convert / bind parameters from card
    sqlite3_bind_text(stmt, 1, card.id.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, card.oracle_id.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, card.set_code.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, card.collector_number.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, Card::rarityToString(card.rarity).c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 6, card.mana_cost.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 7, card.cmc);
    
    std::string typeLine;
    for (const auto& type : card.types) {
        if (!typeLine.empty()) {
            typeLine += " ";
        }
        typeLine += type;
    }
    sqlite3_bind_text(stmt, 8, typeLine.c_str(), -1, SQLITE_TRANSIENT);
    
    std::string subtypeLine;
    for (const auto& subtype: card.subtypes) {
        if (!subtypeLine.empty()) {
            subtypeLine += " ";
        }
        subtypeLine += subtype;
    }
    sqlite3_bind_text(stmt, 8, subtypeLine.c_str(), -1, SQLITE_TRANSIENT);

    if (card.power.has_value()) {
        sqlite3_bind_int(stmt, 10, card.power.value());
    } else {
        sqlite3_bind_null(stmt, 10);
    }
    if (card.toughness.has_value()) {
        sqlite3_bind_int(stmt, 11, card.toughness.value());
    } else {
        sqlite3_bind_null(stmt, 11);
    }

    sqlite3_bind_text(stmt, 12, card.oracle_text.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 13, card.colors);
    sqlite3_bind_text(stmt, 14, card.image_url.c_str(), -1, SQLITE_TRANSIENT);
    
    // Implement cardFaces eventually, maybe with another table
    
    bool exists = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return exists;
}

/*
std::vector<Card> CardRepository::getCardsBySet(const std::string& set_code) {

}
*/
