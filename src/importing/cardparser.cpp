#include <importing/cardparser.h>
#include <card.h>
#include <nlohmann/json.hpp>

#include <vector>
#include <string>

using json = nlohmann::json;

// create card objects from single card json
Card CardParser::parseCard(const nlohmann::json& json) {
    Card card;

    card.id = json.at("id").get<std::string>();
    card.oracle_id = json.at("oracle_id").get<std::string>();
    card.set_code = json.at("set").get<std::string>();
    card.collector_number = json.at("collector_number").get<std::string>();
    card.rarity = parseRarity(json.at("rarity").get<std::string>());
    card.name = json.at("name").get<std::string>();
    card.mana_cost = json.at("mana_cost").get<std::string>();
    card.cmc = json.at("cmc").get<double>();

    // colors next, use helper function 
}

//
// helper functions for parsing
// 

Rarity CardParser::parseRarity(const std::string& r) {
    if (r == "common") return Rarity::common;
    if (r == "uncommon") return Rarity::uncommon;
    if (r == "rare") return Rarity::rare;
    if (r == "mythic") return Rarity::mythic;

    throw std::invalid_argument("Unknown rarity: " + r);
}
