//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#ifndef ADVENTURECARD_H
#define ADVENTURECARD_H

#include "Card.h"
#include <iostream>

class AdventureCard : public Card
{
private:	
	std::string mission;		// mission name
	int req1Qty;				// Requirement 1 Quantity
	int req1Type;				// Requirement 1 Type
	int req2Qty;				// Requirement 2 Quantity
	int req2Type;				// Requirement 2 Type
	int recRcvd;				// resources received	
	int astroPts;				// astros received
	int fmPts;				// fame points
	int vicPts;				// victory points
	bool available;			// flag to see if adv is available

public:
	AdventureCard(const sf::Texture &texture, sf::Vector2u srcPos, int num, std::string name, int type, std::string mission, 
		int req1Qty, int req1Type, int req2Qty, int req2Type, int resource, int astro, int fmPts, int vicPts)
		: Card(texture, srcPos, type, num, name)
	{
		this->mission = mission;
		this->req1Qty = req1Qty;
		this->req1Type = req1Type;
		this->req2Qty = req2Qty;
		this->req2Type = req2Type;
		this->recRcvd = resource;
		this->astroPts = astro;
		this->fmPts = fmPts;
		this->vicPts = vicPts;
		available = false;
	}
	~AdventureCard() {}
	// Getters and Setters
	std::string getMission() const
	{	return mission;	}
	int getRecRcvd() const
	{	return recRcvd;	}
	int getAstros() const
	{	return astroPts;	}
	int getFame() const
	{	return fmPts;	}
	int getVicPts() const
	{	return vicPts;	}
	bool isAvailable()
	{	return available;	}
	void setAvailable(bool toggle)
	{	available = toggle;	}

};
#endif // ADVENTURECARD_H
