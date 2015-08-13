//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#ifndef BOOSTERLASER_H
#define BOOSTERLASER_H

#include "ShipObject.h"

class BoosterLaser : public ShipObject
{
private:

public:
	BoosterLaser(const sf::Texture &texture, sf::Vector2f pos, int num = 1, sf::Vector2u srcSize = { 0, 0 }, sf::Vector2u srcPos = { 0, 0 })
		: ShipObject(texture, pos, num, srcSize, srcPos){};

	bool loseItem(std::string &error)
	{ 
		if (qty > 0)
		{
			qty--;
			srcPos.x--;
			updateTextRect();
			return true;
		}
		error = "Nothing to lose";
		return false;
	}

	bool gainItem(std::string &error)
	{
		qty++;
		srcPos.x++;
		updateTextRect();
		return true;
	}
};

#endif // BOOSTERLASER_H

