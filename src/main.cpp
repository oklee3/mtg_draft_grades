#include <iostream>
#include <sqlite3.h>
#include <nlohmann/json.hpp>

#include "db/database.h"
#include "db/cardrepository.h"
#include "importing/cardparser.h"

int main() {
    std::cout << "Ponder is running!" << std::endl;
    // 1. Create the JSON input
    nlohmann::json thaliaJson = nlohmann::json::parse(R"(
    {
        "id": "c9f8b8fb-1cd8-450e-a1fe-892e7a323479",
        "oracle_id": "9b7f1d05-707c-4ed3-9f0e-8ced1232c2ee",
        "name": "Thalia, Guardian of Thraben",
        "set": "vow",
        "set_name": "Innistrad: Crimson Vow",
        "released_at": "2021-11-19",
        "collector_number": "38",
        "rarity": "rare",
        "mana_cost": "{1}{W}",
        "cmc": 2.0,
        "type_line": "Legendary Creature — Human Soldier",
        "oracle_text": "First strike\nNoncreature spells cost {1} more to cast.",
        "power": "2",
        "toughness": "1",
        "colors": ["W"],
        "image_uris": {
            "small": "https://cards.scryfall.io/small/front/c/9/c9f8b8fb-1cd8-450e-a1fe-892e7a323479.jpg?1783924909"
        }
    }
    )");

    // 2. Parse JSON into a Card object
    Card card = CardParser::parseCard(thaliaJson);

    std::cout << "Parsed card: " << card.name << '\n';

    // 3. Initialize database
    Database db("ponder.db");
    db.initialize();

    CardRepository repository(db);

    // 4. Insert the set first (required by the foreign key)
    const char* setSQL = R"(
        INSERT OR IGNORE INTO sets
        (code, name, release_date, card_count)
        VALUES ('vow', 'Innistrad: Crimson Vow', '2021-11-19', 0);
    )";

    char* errorMessage = nullptr;

    int setResult = sqlite3_exec(
        db.getConnection(),
        setSQL,
        nullptr,
        nullptr,
        &errorMessage
    );

    if (setResult != SQLITE_OK) {
        std::cerr << "Set insertion failed: "
                  << errorMessage << '\n';

        sqlite3_free(errorMessage);
        return 1;
    }

    // 5. Insert the card
    bool inserted = repository.insertCard(card);

    if (inserted) {
        std::cout << "Card inserted successfully.\n";
    } else {
        std::cout << "Card insertion failed.\n";
    }

    // 6. Check whether the card exists
    bool exists = repository.cardExists(card.id);

    std::cout << "Card exists: "
              << (exists ? "YES" : "NO") << '\n';

    return 0;
}
