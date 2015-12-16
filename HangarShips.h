//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#ifndef HANGARSHIPS_H
#define HANGARSHIPS_H

#include "ShipObject.h"

enum hShips{colonyShip, tradeShip };

class HangarShips : public ShipObject
{
private:
	int type;

public:
	HangarShips(const sf::Texture &texture, sf::Vector2f pos, sf::Vector2u srcSize, int num, int type, sf::Vector2u srcPos = sf::Vector2u{ 0, 0 })
		: ShipObject(texture, pos, num, srcSize, srcPos)
	{
		this->type = type;
	}

	int getType() const { return type; }
	void setSrcPos(sf::Vector2u source) { this->srcPos = source; updateTextRect(); }

	void updateTextRect()
	{
		sprite->setTextureRect(sf::IntRect(srcPos.x * srcSize.x, srcPos.y * srcSize.y, srcSize.x, srcSize.y));
	}

	bool loseItem(std::string &error)
	{
		qty = 0;
		return true;
	}

	bool gainItem(int type, std::string &error)
	{
		qty = 1;
		srcPos.x = type;
		this->type = type;
		this->updateTextRect();
		return true;
	}
	bool isMaxed() const { return qty >= 1; }
};

#endif // HANGARSHIPS_H

