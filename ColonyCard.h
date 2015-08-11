//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#ifndef COLONYCARD_H
#define COLONYCARD_H

#include "Card.h"
#include <iostream>
//enum cTypes{ trade, colony, pirate, adventure, lost };
//enum ResourcesAvailable { Carbon, Fuel, Ore, Science, TradeGood, Wheat, Any };
const std::string STRFILE = "resources/cards/colonystarter.png";		//  Source file name for starter colonies
class ColonyCard : public Card
{
private:
	int resource;			// type of resource
	int actNum;			// activation number
	int vicPts;

public:
	ColonyCard(int num, std::string name, int type, int resource, int actNum, int vicPts)
	{
		this->resource = resource;
		this->actNum = actNum;
		this->vicPts = vicPts;
	}

	ColonyCard(int num, std::string name, int type, int resource, int actNum, int vicPts, const sf::Texture &texture, sf::Vector2f pos, sf::Vector2u srcPos = { 0, 0 })
		: Card(texture, pos, type, srcPos, num, name)
	{
		this->resource = resource;
		this->actNum = actNum;
		this->vicPts = vicPts;
	}
	~ColonyCard() {}
	// Getters and Setters
	int getResource() const
	{	return resource;	}
	int getActNum() const
	{	return actNum;	}
	int getPts() const
	{  return vicPts;  }

};
#endif // COLONYCARD_H
