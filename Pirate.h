//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#ifndef PIRATE_H
#define PIRATE_H

#include "Card.h"
#include <iomanip>

class Pirate : public Card
{
private:
	std::string result;			// lose result
	int cost;					// cost of to bribe
	int cannons;				// number of cannons
	int pts;					// num of hero points

public:
	Pirate(const sf::Texture &texture, sf::Vector2u srcPos, int num, std::string name, int type, int cost, int cannons, std::string result, int pts) : Card(texture, srcPos, type, num, name)
	{
		this->cost = cost;
		this->cannons = cannons;
		this->result = result;
		this->pts = pts;
	}
	~Pirate() {}

	friend bool sortBy(const Pirate *lhs, const Pirate *rhs){ return lhs->cannons < rhs->cannons; }

	// Getters and Setters
	std::string getResult() const
	{	return result;	}
	int getCost() const
	{	return cost;	}
	int getCannons() const
	{	return cannons;		}
	int getPts() const
	{	return pts;		}
	void displayCard(sf::RenderWindow &gWindow){
		draw(gWindow);
	}
};

#endif // PIRATE_H
