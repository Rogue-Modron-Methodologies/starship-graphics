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
	Object *image;					//  Clickable image 

public:
	Icon(){};
	//  Constructor for initializing the Ico (preferred)
	Icon(const sf::Texture &texture, sf::Vector2f pos, int num = 1, sf::Vector2u srcSize, sf::Vector2u srcPos = { 0, 0 })
	{
		image = new Object(texture, pos, num, srcSize, srcPos);
	}
	//  Constructor for initializing the text (only used when Ico is not being used.)
	Icon(sf::Font &font, std::string words, sf::Vector2f pos)
	{
		text.setFont(font);
		text.setString(words);
		text.setPosition(pos);
	}
	~Icon() 
	{
		delete image;
	}

	// Getters and Setters
	void setString()
	{

	}
	void setIcon()
	{

	}



};
#endif // ICON_H
