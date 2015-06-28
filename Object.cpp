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
// Creates the texture and sprite for the object.  
// Sets the inital scale, source position, and screen position.
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
Object::Object(std::string fileName, sf::Vector2f pos, sf::Vector2f scale, sf::Vector2u srcSize, sf::Vector2u srcPos, int num, std::string name)
{
	smallDisplay = true;
	if (!texture.loadFromFile(fileName))
		std::cout << fileName << " failed to open!\n";	
	this->srcSize = srcSize;
	this->srcPos = srcPos;
	sprite = new sf::Sprite;
	sprite->setTexture(texture);
	if (srcSize != sf::Vector2u{0,0})
		updateTextRect();
	sprite->setScale(scale);
	sprite->setPosition(pos);
	this->num = num;
	this->string = name;
};

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
// Constructor -
// Creates the texture and sprite for the object.  
// Sets source size and source position.
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
Object::Object(std::string fileName, sf::Vector2u srcSize, sf::Vector2u srcPos, int num, std::string name)
{
	smallDisplay = true;
	if (!texture.loadFromFile(fileName))
		std::cout << fileName << " failed to open!\n";
	this->srcSize = srcSize;
	this->srcPos = srcPos;
	sprite = new sf::Sprite;
	sprite->setTexture(texture);
	if (srcSize != sf::Vector2u{ 0, 0 })
		updateTextRect();
	this->num = num;
	this->string = name;
}


// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Copy Constructor - 
//  For When Objects want to share the same texture.
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
Object::Object(Object & right, int num, std::string name)
{
	this->smallDisplay = right.smallDisplay;
	this->srcSize = right.srcSize;
	this->srcPos = right.srcPos;
	this->texture = right.texture;
	sprite = new sf::Sprite;
	sprite->setTexture(texture);
	updateTextRect();
	sprite->setScale(right.getScale());
	this->num = num;
	string = name;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Destructor - 
//  
//  
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
Object::~Object()
{
	delete sprite;
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
		return true;
	else
		return false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
// Draw -
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the entity's transform -- combine it with the one that was passed by the caller
	//states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

	// apply the texture
//	states.texture = &m_texture;

	// you may also override states.shader or states.blendMode if you want

	// draw the vertex array
	//target.draw(m_vertices, states);
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