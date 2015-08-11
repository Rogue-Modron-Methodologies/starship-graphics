//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include "Object.h"

class Resource : public Object
{
private:
	int rCap;
	std::string name;
	
public:
	Resource(const sf::Texture &texture, sf::Vector2f pos, sf::Vector2u srcSize, int num, std::string name, sf::Vector2u srcPos = sf::Vector2u{ 0, 0 })
		: Object(texture, pos, num, srcSize, srcPos)	
	{
		rCap = 4;			///////////////////////  SB 2 except for science which should be 4.
		this->name = name;
	}	
	int getRCap() const  { return rCap; }
	void update();
	void update(sf::Vector2f pos, sf::Vector2f scale);
	bool loseResource(std::string &error);
	bool gainResource(std::string &error);
	
};

#endif // RESOURCE_H

