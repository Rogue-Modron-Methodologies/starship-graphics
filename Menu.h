//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#ifndef MENU_H
#define MENU_H

#include "Object.h"

const int BUILDICONSIZE = 6;
enum BuildIcons{ BLVL1, BLVL2, LLVL1, LLVL2, COLSHIP, TRDSHIP };

const int TRADEMENUSIZE = 4;
enum tradeIcons{ plus, minus, check, cancel };

const int FMENUSIZE = 6;
enum menuOptions { trdW, estTP, colIt, conFly, endFl, adv };

const int PMENUSIZE = 2;
enum pirateIcons{ pay, fight };

class Menu
{
private:
	std::vector<Object*> menu;
	bool active;

public:
	Menu()
	{
		active = false;
	}

	~Menu()
	{
		for (int i = 0; i < menu.size(); ++i)
			delete menu[i];
	}

	void push_back(Object* item) 	{  menu.push_back(item); }
	bool isActive() const { return active; }
	void setActive(bool toggle){ active = toggle; }
	void setPositionOfItem(int i, sf::Vector2f pos ){ menu[i]->setPosition(pos); }

	bool isItemTargeted(sf::RenderWindow & gWindow, int pos)
	{
		return active && menu[pos]->isTargeted(gWindow);
	}

	bool isMenuTargeted(sf::RenderWindow &gWindow, int &pos)
	{
		if (active)
		{
			for (int i = 0; i < menu.size(); ++i)
			{
				if (menu[i]->isTargeted(gWindow))
				{
					pos = i;
					return true;
				}
			}
		}
		return false;
	}
	//  Menu is active but all Icons get hidden
	void hideAll()
	{
		for (int i = 0; i < menu.size(); ++i)
			menu[i]->hide();
	}

	void hideItem(int pos)
	{
		menu[pos]->hide();
	}
	
	void unhideAll()
	{
		for (int i = 0; i < menu.size(); ++i)
			menu[i]->unhide();
	}

	void unhideItem(int pos)
	{
		menu[pos]->unhide();
	}

	void draw(sf::RenderWindow &gWindow)
	{
		if (active)
		{
			for (int i = 0; i < menu.size(); ++i)
				menu[i]->draw(gWindow);
		}
	}
};
#endif // ADVENTURECARD_H
