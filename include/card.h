#pragma once

#include <string>
#include <vector>
#include <optional>

enum class rarity {
	Common,
	Uncommon,
	Rare,
	Mythic
};

enum class grade {
	F,
	D_minus,
	D,
	D_plus,
	C_minus,
	C,
	C_plus,
	B_minus,
	B,
	B_plus,
	A_minus,
	A,
	A_plus,
	S_minus,
	S,
	S_plus
};

enum class type {
	Legendary,
	Artifact,
	Battle,
	Creature,
	Kindred,
	Enchantment,
	Land,
	Planeswalker,
	Instant,
	Sorcery
};

struct cardFace {
    std::string name;
    std::string mana_cost;
    std::vector<type> types;
    std::vector<std::string> subtypes;
    std::string oracle_text;

    std::optional<int> power;
    std::optional<int> toughness;

    std::string image_url;
};

/*
use bits to represent colors since we can have multiple
when reading from json, combine values using | (bitwise OR)
getCardColors in cardutils.h using & to check for presence of each color
*/
enum class color {
	White = 1,  // 00001
	Blue = 2,  // 00010
	Black = 4,  // 00100
	Red = 8,  // 01000
	Green = 16  // 10000
};

// color_flags as the type for colors
using color_flags = unsigned int;

struct Card {
	// inherent attributes
	std::string id;
    std::string oracle_id;
    std::string set_code;
    int collector_number;
    rarity rarity;
	std::string name;
	std::string mana_cost;
	int cmc;
	color_flags colors = 0;
	std::vector<type> types;
	std::vector<std::string> subtypes;
	std::string oracle_text;
	std::optional<int> power;
	std::optional<int> toughness;
    std::string image_url;
    std::vector<cardFace> card_faces;

	// user created attributes
	grade grade;
	std::string notes;
};
