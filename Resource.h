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


using namespace std;

class Resource : public Object
{
private:
	std::string name;
	int rCap;
	
public:
	Resource(std::string fileName, sf::Vector2f size, sf::Vector2f pos, sf::Vector2f scale, sf::Vector2u srcSize = { 0, 0 }, int num = 1,
		std::string name = "bad") : Object(fileName, size, pos, scale, srcSize, num, name)
	{
		rCap = 4;			///////////////////////  SB 2
	}

	Resource(Resource &right, sf::Vector2f pos, int num, string name)
	{
		this->name = name;
		this->num = num;
		this->srcSize = right.srcSize;
		this->srcPos = right.srcPos;
		this->texture = right.texture;
		this->sprite = new sf::Sprite;
		sprite->setTexture(texture);
		sprite->setTextureRect(sf::IntRect(srcPos.x * srcSize.y, srcPos.y * srcSize.y, srcSize.y, srcSize.y));
		sprite->setScale(right.getScale());
		sprite->setPosition(pos);
		rCap = 4;			///////////////////////  SB 2
	}
	void update();
	void setName(std::string name){ this->name = name; }
	std::string getName() const { return name; }
	bool loseResource(std::string &error);
	bool gainResource(std::string &error);
	
};

#endif // RESOURCE_H