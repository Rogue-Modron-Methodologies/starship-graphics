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

enum direction { Down, Left, Right, Up };
enum cTypes{ trade, colony, pirate, adventure, lost };
enum ResourcesAvailable { Carbon, Fuel, Ore, Science, TradeGood, Wheat, Any };

class Object : public sf::Drawable, public sf::Transformable
{
private: 
	
protected:
	int num;
	std::string string;
	sf::Sprite *sprite;
	sf::Texture texture;
	sf::Vector2u srcSize;
	sf::Vector2u srcPos;
	sf::Vector2f relPos;
	bool smallDisplay;

public:
	Object(std::string fileName = "EMPTY", int n = -99){ string = fileName; num = n; }
	Object(std::string fileName, sf::Vector2u srcSize, sf::Vector2u srcPos, int num, std::string name);
	Object(std::string fileName, sf::Vector2f pos, sf::Vector2f scale, sf::Vector2u srcSize = { 0, 0 }, sf::Vector2u srcPos = { 0, 0 }, int num = 1, std::string name = "bad");
	Object(Object &right, int num, std::string name);
	~Object();

	//  Getters/Setters
	void setTexture(sf::Texture texture) { this->texture = texture; }
	void setScale(sf::Vector2f scale) { sprite->setScale(scale); }
	void setPosition(sf::Vector2f pos) { sprite->setPosition(pos); }
	void setRelPos(sf::Vector2f pos) { relPos = pos; }
	void setSrcPos(sf::Vector2u source) { this->srcPos = source; }
	void setSrcPosX(unsigned num){ this->srcPos.x = num; }	
	void setNum(int num){ this->num = num; }	
	sf::Sprite *getSprite() const { return sprite; } 
	sf::Texture getTexture() const { return texture; }
	sf::Vector2f getScale() const { return sprite->getScale(); }
	sf::Vector2f getRelPos() const { return relPos; }	
	int getNum() const { return num; }

	// Misc Inline Functions
	bool isSmall() const  { return smallDisplay; }

	// Prototypes
	virtual void updateTextRect();
	virtual void draw(sf::RenderWindow &window) { window.draw(*sprite); }
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool isTargeted(sf::RenderWindow &gWindow);
};

#endif  // OBJECT_H