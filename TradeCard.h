//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#ifndef TRADECARD_H
#define TRADECARD_H

#include "Card.h"
//enum cTypes{ trade, colony, pirate, adventure, lost };
//enum ResourcesAvailable { Carbon, Fuel, Ore, Science, TradeGood, Wheat, Any };
class TradeCard : public Card
{
private:
	int resource;				// type of resource
	int cost;					// cost of resource
	std::string transaction;
	int limit;
	int pts;

public:

	TradeCard(const sf::Texture &texture, sf::Vector2u srcPos, int num, std::string name, int type, int resource, int cost, std::string transaction, int limit, int pts) : Card(texture, srcPos, type, num, name)
	{
		this->resource = resource;
		this->cost = cost;
		this->transaction = transaction;
		this->limit = limit;
		this->pts = pts;
	}
	Card* operator= (Card* right)
	{
		setDeckNum(right->getDeckNum());
		setName(right->getName());
		setType(right->getType());
		this->resource = resource;
		this->cost = cost;
		this->transaction = transaction;
		this->limit = limit;
		this->pts = pts;		
		return this;
	}
	~TradeCard() {}
	// Getters and Setters
	int getResource() const
		{  return resource; }
	int getCost() const
		{  return cost;  }
	std::string getTransaction() const
		{	return transaction;  }
	int getLimit() const
		{	return limit;  }
	int getPts() const
		{  return pts;  }

};
#endif // TRADECARD_H
