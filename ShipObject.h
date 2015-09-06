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
const std::string ARWFILE = "resources/arrows.png";		//  Source File name for resource arrows
const std::string BSTFILE = "resources/boosters.png";		//  Source file name for boosters
const std::string LSRFILE = "resources/lasers.png";		//  Source file name for lasers
const std::string SHPFILE = "resources/ships.png";		//  Source file name for trade/colony

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
	virtual bool loseItem(std::string &error){ std::cout << "shipObject loseItem Function Called"; return false; }
	virtual bool gainItem(std::string &error){ std::cout << "shipObject gainItem Function Called"; return false; }
	virtual bool gainItem(int type, std::string &error){ std::cout << "shipObject gainItem Function Called"; return false; }
	virtual int getType() const { std::cout << "shipObject getType Function Called\n"; return -1; }
	virtual int getRCap() const  { "shipObject getRCap Function Called\n"; return -1; }
	virtual bool isMaxed() const { "shipObject isMaxed Function Called\n"; return false; }
	virtual void setSrcPos(sf::Vector2u source) { this->srcPos = source; updateTextRect(); }
	virtual void updateTextRect()
	{
		srcPos.x = qty - 1;
		sprite->setTextureRect(sf::IntRect(srcPos.x * srcSize.x, srcPos.y * srcSize.y, srcSize.x, srcSize.y));
	}
};

#endif // SHIPOBJECT_H