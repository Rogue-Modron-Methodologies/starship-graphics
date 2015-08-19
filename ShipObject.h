//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#ifndef SHIPOBJECT_H
#define SHIPOBJECT_H

#include "Object.h"

enum ShipComponents { Science, Ore, Fuel, TradeGood, Wheat, Carbon, B1, B2, B3, L1, L2, L3, H1, H2 };
enum Ships { empty, tradeShip, colonyShip };
const std::string ARWFILE = "resources/board/arrows.png";		//  Source File name for resource arrows
const std::string BSTFILE = "resources/board/boosters.png";		//  Source file name for boosters
const std::string LSRFILE = "resources/board/lasers.png";		//  Source file name for lasers
const std::string SHPFILE = "resources/board/ships.png";		//  Source file name for trade/colony

class ShipObject : public Object
{
private:
	sf::Vector2f relPos;		// relative position to starship Orgin 

public:
	ShipObject(const sf::Texture &texture, sf::Vector2f pos, int num = 1, sf::Vector2u srcSize = { 0, 0 }, sf::Vector2u srcPos = { 0, 0 })
		: Object(texture, pos, num, srcSize, srcPos)
	{
		relPos = pos;
	}
	~ShipObject() {};
	sf::Vector2f getRelPos() const { return relPos; }
	virtual bool loseItem(std::string &error){ error = "shipObject loseItem Function Called"; return false; }
	virtual bool gainItem(std::string &error){ error = "shipObject gainItem Function Called"; return false; }
	virtual void updateTextRect()
	{
		srcPos.x = qty - 1;
		sprite->setTextureRect(sf::IntRect(srcPos.x * srcSize.x, srcPos.y * srcSize.y, srcSize.x, srcSize.y));
	}
};

#endif // SHIPOBJECT_H