//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#ifndef ICON_H
#define ICON_H

#include "Object.h"

class Icon : public Object
{
private:

	sf::Text text;					//  Text String
	Object *icon;					//  Clickable image 

public:
	Icon(){};
	//  Constructor for initializing the Icon (preferred)
	Icon(const sf::Texture &texture, sf::Vector2f pos, int num = 1, sf::Vector2u srcSize = { 0, 0 }, sf::Vector2u srcPos = { 0, 0 })
	{
		icon = new Object(texture, pos, num, srcSize, srcPos);
	}
	//  Constructor for initializing the text with a string
	Icon(const sf::Font &font, sf::Vector2f pos, std::string words, int style = sf::Text::Regular ) { initString(font, pos, words); }

	//  Constructor for initializing the text with a num
	Icon(const sf::Font &font, sf::Vector2f pos, int num, int style = sf::Text::Regular) { initString(font, pos, std::to_string(num)); }

	//  Constructor for initializing the text with default qty of icon
	Icon(const sf::Font &font, sf::Vector2f pos, int style = sf::Text::Regular) { initString(font, pos, std::to_string(icon->getQty())); }

	~Icon() {	delete icon; }

	// Getters and Setters
	int getQty() const { return icon->getQty(); }
	void setQty(int num, bool changeQty = true) 
	{
		icon->setQty(num);  
		if (changeQty)
			refreshStringQty();
	}

	//  Misc Inline Functions
	void setString(std::string words) { text.setString(words); 	}				//  Sets text field with a string
	void setString(int num) { text.setString(std::to_string(num)); }				//  Sets text field with an int
	void setScale(sf::Vector2f scale) { icon->setScale(scale); }
	void setIconPosition(sf::Vector2f pos) { icon->setPosition(pos); }			//  Sets the position of the icon
	void setTextPosition(sf::Vector2f pos) { text.setPosition(pos); }			//  Sets the position of the text
	void setTextScale(sf::Vector2f scale){ text.setScale(scale); }
	void setTextColor(sf::Color color) { text.setColor(color); }
	void setSrcPos(sf::Vector2u source) { icon->setSrcPos(source); }
	void setPosition(sf::Vector2f pos) { std::cout << "ERROR: Icon setPostion function should never be called\n"; }

	//  Initializes the string member variable	
	void initString(const sf::Font &font, sf::Vector2f pos, std::string words = "XXX", int style = sf::Text::Regular)
	{
		text.setFont(font);
		if (words == "XXX")
			text.setString(std::to_string(icon->getQty()));
		else
			text.setString(words);
		text.setPosition(pos);
		text.setStyle(style);
	}

	//  Draws to Window
	void draw(sf::RenderWindow &window) 
	{ 
		if (icon)
			icon->draw(window); 
		if (!text.getString().isEmpty())
			window.draw(text);
	}
	void updateTextRect()
	{
		icon->updateTextRect();
	}
	bool isTargeted(sf::RenderWindow &gWindow)
	{
		if (icon->isTargeted(gWindow))
			return true;
		else
			return false;
	}

private:
	void refreshStringQty() { text.setString(std::to_string(icon->getQty())); }	//  Sets text field with icon's qty



};
#endif // ICON_H
