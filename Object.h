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
const std::string FNTFLE = "resources/unique.ttf";		//  Source file name for Font

class Object 
{
private: 
	
protected:
	int qty;
	sf::Sprite *sprite;
	sf::Vector2u srcSize;		// file source size
	sf::Vector2u srcPos;		// file source position
	bool smallDisplay;
	bool visible;
	bool clickable;

public:	
	Object(){};
	Object(const sf::Texture &texture, sf::Vector2f pos, int num = 1, sf::Vector2u srcSize = { 0, 0 }, sf::Vector2u srcPos = { 0, 0 });
	~Object() { delete sprite; };

	//  Getters/Setters
	void setScale(sf::Vector2f scale) { sprite->setScale(scale); }
	void setPosition(sf::Vector2f pos) { sprite->setPosition(pos); }
	void setSrcPos(sf::Vector2u source) { this->srcPos = source; updateTextRect(); }
	void setSrcPosX(unsigned num){ this->srcPos.x = num; updateTextRect(); }
	void setSrcPosY(unsigned num){ this->srcPos.y = num; updateTextRect(); }
	sf::Vector2u getSrcPos() const { return srcPos;  }
	void setQty(int num){ this->qty = num; }
	int getQty() const { return qty; }
	//void setColor(sf::Color color = sf::Color::White){ sprite->setColor(color); }
	const sf::Texture* getTexture() { return sprite->getTexture(); }
	void setTexture(const sf::Texture &texture){ sprite->setTexture(texture); }
	sf::Vector2f getPosition() const { return sprite->getPosition(); }
	sf::Vector2f getScale() const { return sprite->getScale(); }
	bool isVisible() const { return visible; }
	void setVisible(bool toggle){ visible = toggle; }


	// Misc Inline Functions
	bool isSmall() const  { 	return smallDisplay; }
	
	// Prototypes
	virtual void updateTextRect();
	virtual void draw(sf::RenderWindow &window) 
	{ if(visible) window.draw(*sprite); }
	bool isTargeted(sf::RenderWindow &gWindow);	
	sf::Vector2f convertCoord(sf::RenderWindow &gWindow);
	void unGreyOut();			//  Visible, unmuted and fully visible
	void greyOut();			//  Visible, muted and unclickable
	void hide();				//  Invisible and unclickable
	void unhide();				//  Visible and clickable
};

#endif  // OBJECT_H