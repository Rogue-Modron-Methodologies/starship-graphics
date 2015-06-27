//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#include "Resource.h"	

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Copy Constructor
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
Resource::Resource(Resource &right, int num, std::string name)
{
	this->name = name;
	this->num = num;
	this->srcSize = right.srcSize;
	this->srcPos = right.srcPos;
	this->texture = right.texture;
	this->sprite = new sf::Sprite;
	sprite->setTexture(texture);
	sprite->setTextureRect(sf::IntRect(srcPos.x * srcSize.y, srcPos.y * srcSize.y, srcSize.y, srcSize.y));
	rCap = 4;			///////////////////////  SB 2  (science is always 4)
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Sets Arrow to position indicated by number of resources
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Resource::update()
{
	srcPos.x = num - 1;
	sprite->setTextureRect(sf::IntRect(srcPos.x * srcSize.y, srcPos.y * srcSize.y, srcSize.y , srcSize.y));
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Attemps to use a resource
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Resource::loseResource(std::string &statusUpdate)
{
	if (num > 0)		// num: current resource quantity
	{
		num--;
		update();
		return true;
	}
	statusUpdate = name + " hold is empty!";
	return false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Attemps to gain a resource
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Resource::gainResource(std::string &statusUpdate)
{
	if (num < rCap)	// num: current resource quantity
	{
		num++;
		update();
		return true;
	}
	statusUpdate = name + " hold is full!";
	return false;
}
