//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#include "Object.h"



// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
// Constructor -
// Creates the sprite for the object.  
// Sets the inital scale, source position, and screen position.
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
Object::Object(const sf::Texture &texture, sf::Vector2f pos, int num, sf::Vector2u srcSize, sf::Vector2u srcPos)
{
	smallDisplay = true;
	this->srcSize = srcSize;
	this->srcPos = srcPos;
	this->relPos = pos;
	sprite = new sf::Sprite;
	sprite->setTexture(texture);
	if (srcSize != sf::Vector2u{ 0, 0 })
		updateTextRect();
	sprite->setPosition(pos);
	this->qty = num;
}


// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Check if Mouse Position is within bounds of Starship
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Object::isTargeted(sf::RenderWindow &gWindow)
{
	if (sf::Mouse::getPosition(gWindow).x <sprite->getPosition().x + sprite->getGlobalBounds().width
		&& sf::Mouse::getPosition(gWindow).y > sprite->getPosition().y
		&& sf::Mouse::getPosition(gWindow).x > sprite->getPosition().x
		&& sf::Mouse::getPosition(gWindow).y < sprite->getPosition().y + sprite->getGlobalBounds().height)
	{
		std::cout << sprite->getPosition().x << " " << sprite->getPosition().y << std::endl;
		return true;
	}
		
	else
		return false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
// Update Funtion -
// Currently updates the TextureRect to new position when called
// 
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Object::updateTextRect()
{
	sprite->setTextureRect(sf::IntRect(srcPos.x * srcSize.x, srcPos.y * srcSize.y, srcSize.x, srcSize.y));
}