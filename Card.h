//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#ifndef CARD_H
#define CARD_H

#include "Object.h"

const std::string UNIVERSECARDIMAGES = "resources/UniverseCards.png";
const sf::Vector2u CSRCSZE = { 200, 300 };
const sf::Vector2f CRDSSCL = sf::Vector2f(.45f, .45f);		//  Card Small Scale for Icons
const sf::Vector2f CRDZNSCL = sf::Vector2f(.70f, .70f);	//  Card Scale for when in Colony or Trade Zone
const sf::Vector2f CRDLSCL = sf::Vector2f(1.0f, 1.0f);		//  Card Large Scale for when in the Universe

class Card : public Object
{
private:
	int type;	    // card type
	std::string name;

public:
	Card(int num = 0, std::string name = "", int type = 0)
	{
		this->qty = num;
		this->name = name;
		this->type = type;
	}
	Card(const sf::Texture &texture, sf::Vector2u srcPos, int type = 0, int num = 0, std::string name = "", sf::Vector2f pos= { 0, 0 }) : Object(texture, pos, num, CSRCSZE, srcPos)
	{
		this->qty = num;
		this->name = name;
		this->type = type;
	}

	~Card() {}
	// Getters and Setters
	void setDeckNum(int num)
	{
		this->qty = num;
	}
	void setName(std::string name)
	{
		this->name = name;
	}
	void setType(int type)
	{	this->type = type;	}
	int getDeckNum() const
	{
		return qty;
	}
	std::string getName() const
	{
		return name;
	}
	int getType() const
	{	return type;	}
	virtual std::string getRequirement() const
	{	return "This should never print.";	}
	virtual int getActNum() const
	{	return 0;	}
	virtual int getResource() const
	{	return -100;	}
	virtual int getPts() const
	{	return -100;  }
	virtual int getCost() const
	{	return -100;	}
	virtual int getCannons() const
	{	return -100;	}
	virtual int getLimit() const
	{	return -100;	}
	virtual std::string getTransaction() const
	{	return "This should never print.";	}
	virtual std::string getResult() const
	{	return "This should never print.";	}
	std::string getResName(int type)
	{
		std::string tempName;
		switch (type)
		{
		case 0:
			tempName = "Science";
			break;
		case 1:
			tempName = "Ore";
			break;
		case 2:
			tempName = "Fuel";
			break;
		case 3:
			tempName = "Trade Goods";
			break;
		case 4:
			tempName = "Wheat";
			break;
		case 5:
			tempName = "Carbon";
			break;
		default:
			tempName = "Any";
		}
		return tempName;
	}
	virtual int getRecRcvd() const
	{	return -100;	}
	virtual int getAstros() const
	{	return -100;	}
	virtual int getFame() const
	{	return -100;	}
	virtual int getVicPts() const
	{	return -100;	}

};
#endif // CARD_H
