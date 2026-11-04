#pragma once

#include <nlohmann/json.hpp>
#include <db/cardrepository.h>

class CardParser {
public:
    static Card parseCard(const nlohmann::json& json);

private:
    static Rarity parseRarity(const std::string& rarity);
};
