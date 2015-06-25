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
	std::string requirement;		// requirements	
	int recRcvd;			// resources received	
	int astroPts;			// astros received
	int fmPts;			// fame points
	int vicPts;			// victory points

public:
	AdventureCard(int num, std::string name, int type, std::string mission, std::string requirement, int resource, int astro, int fmPts, int vicPts)
		: Card(num, name, type)
	{
		this->mission = mission;
		this->requirement = requirement;
		this->recRcvd = resource;
		this->astroPts = astro;
		this->fmPts = fmPts;
		this->vicPts = vicPts;
	}
	~AdventureCard() {}
	// Getters and Setters
	std::string getMission() const
	{	return mission;	}
	std::string getRequirement() const
	{	return requirement;	}
	int getRecRcvd() const
	{	return recRcvd;	}
	int getAstros() const
	{	return astroPts;	}
	int getFame() const
	{	return fmPts;	}
	int getVicPts() const
	{	return vicPts;	}

};
#endif // ADVENTURECARD_H
