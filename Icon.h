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

	//  Constructor for initializing the Icon
	Icon(const sf::Texture &texture, sf::Vector2f pos, int num = 1, sf::Vector2u srcSize = { 0, 0 }, sf::Vector2u srcPos = { 0, 0 })
	{ icon = new Object(texture, pos, num, srcSize, srcPos); }

	~Icon() {	delete icon; }

	// Getters and Setters
	sf::Text getText(){ return text; }
	int getQty() const { return icon->getQty(); }
	void setQty(int num, bool changeQty = true) 
	{
		icon->setQty(num);  
		if (changeQty)
			refreshStringQty();
	}
	bool isVisible() const { return icon->isVisible(); }
	void setVisible(bool toggle){ icon->setVisible(toggle); }

	//  Misc Inline Functions
	void setString(std::string words) { text.setString(words); 	}				//  Sets text field with a string
	void setString(int num) { text.setString(std::to_string(num)); }				//  Sets text field with an int
	void setScale(sf::Vector2f scale) { icon->setScale(scale); }
	void setIconPosition(sf::Vector2f pos) { icon->setPosition(pos); }			//  Sets the position of the icon
	void setTextPosition(sf::Vector2f pos) { text.setPosition(pos); }			//  Sets the position of the text
	void setTextScale(sf::Vector2f scale){ text.setScale(scale); }
	void setTextColor(sf::Color color) { text.setColor(color); }
	void setSrcPos(sf::Vector2u source) { icon->setSrcPos(source); }
	void setSrcPosX(unsigned num){ icon->setSrcPosX(num); }
	void setPosition(sf::Vector2f pos) { icon->setPosition(pos); }
	sf::Vector2f getPosition(){ return icon->getPosition(); }
	//void setColor(sf::Color color = sf::Color::White){ icon->setColor(color); }
	void clear(){ text.setString(""); }
	const sf::Texture* getTexture() { return icon->getTexture(); }
	void setTexture(const sf::Texture &texture){ icon->setTexture(texture); }
	sf::Vector2f getIconPosition() const { return icon->getPosition(); }
	sf::Vector2f getScale() const { return icon->getScale(); }
	void unGreyOut(){ icon->unGreyOut(); }
	void greyOut(){ icon->greyOut(); }
	void hide(){ icon->hide(); }
	void unhide(){ icon->unhide(); }


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
		icon->draw(window); 		
		if (icon->isVisible() && !text.getString().isEmpty())
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
