#include <sqlite3.h>
#include <db/cardrepository.h>

#include <string>
#include <vector>

CardRepository::CardRepository(Database& db)
	: db(db) {}

bool CardRepository::cardExists(const std::string& set_code) {

}

bool CardRepository::insertCard(const Card& card) {

}

std::vector<Card> CardRepository::getCardsBySet(const std::string& set_code) {

}