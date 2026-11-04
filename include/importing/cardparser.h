#pragma once

#include <nlohmann/json.hpp>
#include <db/cardrepository.h>

#include <sstream>
#include <utility>

class CardParser {
public:
    static Card parseCard(const nlohmann::json& json);

private:
    static Rarity parseRarity(const std::string& rarity);

    static color_flags parseColor(const nlohmann::json& colors);

    // return types and subtypes from json type_line
    static std::pair<std::vector<std::string>, std::vector<std::string>> 
    parseTypeLine(const std::string& typeLine);
};
