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
	sf::Text text;				// Text String
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
	sf::Text getText(){ return text; }
	void setScale(sf::Vector2f scale) { sprite->setScale(scale); }
	void setPosition(sf::Vector2f pos) { sprite->setPosition(pos); }
	virtual void setSrcPos(sf::Vector2u source) { this->srcPos = source; updateTextRect(); }
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
	void setString(std::string words) { text.setString(words); }				//  Sets text field with a string
	void setString(int num) { text.setString(std::to_string(num)); }				//  Sets text field with an int
	void clear(){ text.setString(""); }
	void setTextPosition(sf::Vector2f pos) { text.setPosition(pos); }			//  Sets the position of the text
	void setTextScale(sf::Vector2f scale){ text.setScale(scale); }
	void setTextColor(sf::Color color) { text.setColor(color); }


	// Misc Inline Functions
	bool isSmall() const  { 	return smallDisplay; }
	
	// Prototypes
	virtual void updateTextRect();
	//virtual void draw(sf::RenderWindow &window) 
	//{ if(visible) window.draw(*sprite); }
	bool isTargeted(sf::RenderWindow &gWindow);	
	sf::Vector2f convertCoord(sf::RenderWindow &gWindow);
	void unGreyOut();			//  Visible, unmuted and fully visible
	void greyOut();			//  Visible, muted and unclickable
	void hide();				//  Invisible and unclickable
	void unhide();				//  Visible and clickable

	//  Initializes the string member variable	
	void initString(const sf::Font &font, sf::Vector2f pos, std::string words = "XXX", int style = sf::Text::Regular)
	{
		text.setFont(font);
		if (words == "XXX")
			text.setString(std::to_string(qty));
		else
			text.setString(words);
		text.setPosition(pos);
		text.setStyle(style);
	}

	//  Draws to Window
	void draw(sf::RenderWindow &window)
	{
		if (visible)
		{
			window.draw(*sprite);
			window.draw(text);
		}
	}
};

#endif  // OBJECT_H

//  Old ICON CODE IN CASE IT'S NEEDED
//  Constructor for initializing the Icon
//	Icon(const sf::Texture &texture, sf::Vector2f pos, int num = 1, sf::Vector2u srcSize = { 0, 0 }, sf::Vector2u srcPos = { 0, 0 })
//	{ icon = new Object(texture, pos, num, srcSize, srcPos); }
//
//	~Icon() {	delete icon; }
//
//	// Getters and Setters
//	sf::Text getText(){ return text; }
//	int getQty() const { return icon->getQty(); }
//	void setQty(int num, bool changeQty = true) 
//	{
//		icon->setQty(num);  
//		if (changeQty)
//			refreshStringQty();
//	}
//	bool isVisible() const { return icon->isVisible(); }
//	void setVisible(bool toggle){ icon->setVisible(toggle); }
//
//	//  Misc Inline Functions
//	void setString(std::string words) { text.setString(words); 	}				//  Sets text field with a string
//	void setString(int num) { text.setString(std::to_string(num)); }				//  Sets text field with an int
//	void setScale(sf::Vector2f scale) { icon->setScale(scale); }
//	void setIconPosition(sf::Vector2f pos) { icon->setPosition(pos); }			//  Sets the position of the icon
//	void setTextPosition(sf::Vector2f pos) { text.setPosition(pos); }			//  Sets the position of the text
//	void setTextScale(sf::Vector2f scale){ text.setScale(scale); }
//	void setTextColor(sf::Color color) { text.setColor(color); }
//	void setSrcPos(sf::Vector2u source) { icon->setSrcPos(source); }
//	void setSrcPosX(unsigned num){ icon->setSrcPosX(num); }
//	void setPosition(sf::Vector2f pos) { icon->setPosition(pos); }
//	sf::Vector2f getPosition(){ return icon->getPosition(); }
//	//void setColor(sf::Color color = sf::Color::White){ icon->setColor(color); }
//	void clear(){ text.setString(""); }
//	const sf::Texture* getTexture() { return icon->getTexture(); }
//	void setTexture(const sf::Texture &texture){ icon->setTexture(texture); }
//	sf::Vector2f getIconPosition() const { return icon->getPosition(); }
//	sf::Vector2f getScale() const { return icon->getScale(); }
//	void unGreyOut(){ icon->unGreyOut(); }
//	void greyOut(){ icon->greyOut(); }
//	void hide(){ icon->hide(); }
//	void unhide(){ icon->unhide(); }
//
//
//	//  Initializes the string member variable	
//	void initString(const sf::Font &font, sf::Vector2f pos, std::string words = "XXX", int style = sf::Text::Regular)
//	{
//		text.setFont(font);
//		if (words == "XXX")
//			text.setString(std::to_string(icon->getQty()));
//		else
//			text.setString(words);
//		text.setPosition(pos);
//		text.setStyle(style);
//	}
//
//	//  Draws to Window
//	void draw(sf::RenderWindow &window)
//	{ 
//		icon->draw(window); 		
//		if (icon->isVisible() && !text.getString().isEmpty())
//				window.draw(text);
//	}
//	void updateTextRect()
//	{
//		icon->updateTextRect();
//	}
//	bool isTargeted(sf::RenderWindow &gWindow)
//	{
//		if (icon->isTargeted(gWindow))
//			return true;
//		else
//			return false;
//	}
//
//private:
//	void refreshStringQty() { text.setString(std::to_string(icon->getQty())); }	//  Sets text field with icon's qty