#include <importing/cardparser.h>
#include <card.h>
#include <nlohmann/json.hpp>

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

    card.colors = parseColor(json.at("colors"));
    
    auto [types, subtypes] = parseTypeLine(json.at("type_line").get<std::string>());
    card.types = std::move(types);
    card.subtypes = std::move(subtypes);

    card.oracle_text = json.at("oracle_text").get<std::string>();

    if (json.contains("power")) {
        card.power = json.at("power").get<std::string>();
    }
    if (json.contains("toughness")) {
        card.toughness = json.at("toughness").get<std::string>();
    }

    // using small image url
    card.image_url = json.at("image_uris").at("small").get<std::string>();

    return card;
}

//
// helper functions for parsing
// 

rarity CardParser::parseRarity(const std::string& r) {
    if (r == "common") return rarity::common;
    if (r == "uncommon") return rarity::uncommon;
    if (r == "rare") return rarity::rare;
    if (r == "mythic") return rarity::mythic;

    throw std::invalid_argument("Unknown rarity: " + r);
}

color_flags CardParser::parseColor(const nlohmann::json& colors) {
    color_flags res{};

    if (colors.empty()) return res;

    for (const auto& colorValue : colors) {
        std::string c = colorValue.get<std::string>();

        if (c == "W") res |= static_cast<color_flags>(color::White);
        else if (c == "U") res |= static_cast<color_flags>(color::Blue);
        else if (c == "B") res |= static_cast<color_flags>(color::Black);
        else if (c == "R") res |= static_cast<color_flags>(color::Red);
        else if (c == "G") res |= static_cast<color_flags>(color::Green);
    }

    return res;
}

// returns the types, subtypes pair
std::pair<std::vector<std::string>, std::vector<std::string>> 
CardParser::parseTypeLine(const std::string& typeLine) {
    std::vector<std::string> types;
    std::vector<std::string> subtypes;

    size_t dash = typeLine.find("—");

    std::stringstream typeStream(typeLine.substr(0, dash));
    std::string word;

    while (typeStream >> word) {
        types.push_back(word);
    }

    if (dash != std::string::npos) {
        std::stringstream subtypeStream(typeLine.substr(dash + std::string("—").length()));

        while (subtypeStream >> word) {
            subtypes.push_back(word);
        }
    }

    return {types, subtypes};
}


