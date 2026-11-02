#pragma once

#include <db/database.h>
#include <card.h>

#include <string>
#include <vector>

// implements database operations with cards
class CardRepository {
public:
	explicit CardRepository(Database& db);

	bool cardExists(const std::string& id);
	bool insertCard(const Card& card);
	std::vector<Card> getCardsBySet(const std::string& set_code);

	// add more when needed

private:
	// cardrepositories refer to existing database connections
	Database& db;
};