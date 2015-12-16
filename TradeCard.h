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

class TradeCard : public Card
{
private:
	int resource;				// type of resource
	int cost;					// cost of resource
	std::string transaction;
	int limit;
	int pts;

public:

	TradeCard(const sf::Texture &texture, sf::Vector2u srcPos, int num, std::string name, int type, int resource, int cost, 
		std::string transaction, int limit, int pts) : Card(texture, srcPos, type, num, name)
	{
		this->resource = resource;
		this->cost = cost;
		this->transaction = transaction;
		this->limit = limit;
		this->pts = pts;
	}
	~TradeCard() {}
	
	friend bool sortBy(const TradeCard *lhs, const TradeCard *rhs){ return lhs->resource < rhs->resource; }

	// Getters and Setters
	int getResource() const {  return resource; }
	int getCost() const {  return cost;  }
	std::string getTransaction() const {	return transaction;  }
	int getLimit() const {	return limit;  }
	int getPts() const 	{  return pts;  }
	void setResource(int r) { resource = r; }
	void setCost(int c)  { cost = c; }
	void setTransaction(std::string tr)  { transaction = tr; }
	void setLimit(int l)  { limit = l; }
	void setPts(int p) { pts = p; }
	void copyData(TradeCard *right)
	{
		this->srcPos = right->srcPos;
		this->resource = right->resource;
		this->cost = right->cost;
		this->limit = right->limit;
		this->transaction = right->transaction;
		this->pts = right->pts;
		this->setType(right->getType());
		this->setName(right->getName());
		this->setVisible(right->isVisible());
	}
};

#endif // TRADECARD_H
