//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#ifndef OBJECT_H
#define OBJECT_H

#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include "ResourceManager.h"

enum direction { Down, Left, Right, Up };
enum cTypes{ trade, colony, pirate, adventure, lost };

class Object 
{
private: 
	
protected:
	int qty;
	sf::Sprite *sprite;
	sf::Vector2u srcSize;		// file source size
	sf::Vector2u srcPos;		// file source position
	bool smallDisplay;

public:
	Object(){};
	Object(const sf::Texture &texture, sf::Vector2f pos, int num = 1, sf::Vector2u srcSize = { 0, 0 }, sf::Vector2u srcPos = { 0, 0 });
	~Object() { delete sprite; };

	//  Getters/Setters
	void setScale(sf::Vector2f scale) { sprite->setScale(scale); }
	void setPosition(sf::Vector2f pos) { sprite->setPosition(pos); }
	void setSrcPos(sf::Vector2u source) { this->srcPos = source; }
	void setSrcPosX(unsigned num){ this->srcPos.x = num; }	
	void setSrcPosY(unsigned num){ this->srcPos.y = num; }
	void setQty(int num){ this->qty = num; }
	int getQty() const { return qty; }

	// Misc Inline Functions
	bool isSmall() const  { return smallDisplay; }

	// Prototypes
	virtual void updateTextRect();
	virtual void draw(sf::RenderWindow &window) { window.draw(*sprite); }
	bool isTargeted(sf::RenderWindow &gWindow);	
	sf::Vector2f convertCoord(sf::RenderWindow &gWindow);
};

#endif  // OBJECT_H