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

const sf::Vector2f CRDSIZE = { 500, 500 };
const sf::Vector2u CSRCSZE = { 250, 385 };
const sf::Vector2f CRDSSCL = sf::Vector2f(.35f, .35f);		//  Card Small Scale
const sf::Vector2f CRDLSCL = sf::Vector2f(.5f, .5f);		//  Card Large Scale
class Card : public Object
{
private:
	int type;	    // card type

public:
	Card(int num = 0, std::string name = "", int type = 0)
	{
		this->num = num;
		this->string = string;
		this->type = type;
	}

	Card(std::string fileName, sf::Vector2f pos, sf::Vector2f scale, sf::Vector2u srcPos = { 0, 0 }, int num = 0, std::string name = "", int type = 0)
		: Object(fileName, pos, scale, CSRCSZE, srcPos, num, name)
	{
		this->num = num;
		this->string = string;
		this->type = type;
	}
	virtual Card* operator= (Card* right)
	{
		this->num = right->num;
		this->string = right->string;
		this->type = right->type;
		return this;
	}
	~Card() {}
	// Getters and Setters
	void setDeckNum(int num)
	{  this->num = num;  }
	void setName(std::string name)
	{	this->string = name;}
	void setType(int type)
	{	this->type = type;	}
	int getDeckNum() const
	{  return num; 	}
	std::string getName() const
	{	return string;}
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
			tempName = "Carbon";
			break;
		case 1:
			tempName = "Fuel";
			break;
		case 2:
			tempName = "Ore";
			break;
		case 3:
			tempName = "Science";
			break;
		case 4:
			tempName = "TradeGood";
			break;
		case 5:
			tempName = "Wheat";
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
	void displayCard(sf::RenderWindow &gWindow){
		draw(gWindow);
	}
};
#endif // CARD_H
