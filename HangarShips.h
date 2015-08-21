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

enum hShips{tradeShip, colonyShip };

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
	bool loseItem(std::string &error){
		qty = 0;
		return true;
	}
	bool gainItem(std::string &error){
		qty = 0;
		return true;
	}

};

#endif // HANGARSHIPS_H

