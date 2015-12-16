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

enum BuildIcons{ BLVL1, BLVL2, LLVL1, LLVL2, COLSHIP, TRDSHIP };
enum tradeIcons{ plus, minus, check, cancel };
enum menuOptions { trdW, estTP, colIt, conFly, endFl, adv };
enum pirateIcons{ pay, fight };

class Menu
{
private:
	std::vector<Object*> menu;
	sf::Text updateText;			
	bool active;

public:
	Menu(ResourceManager<sf::Font> &fntMgr)
	{
		active = false;
		updateText.setFont(fntMgr.getResource(FNTFLE));
		updateText.setPosition({ 200, 820 });
		updateText.setString("");
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
	void greyItem(int pos){ menu[pos]->greyOut(); }
	void unGreyItem(int pos){ menu[pos]->unGreyOut(); }
	int getItemQty(int i) const { return menu[i]->getQty(); }
	void setItemQty(int i, int qty) { menu[i]->setQty(qty); }
	void setItemString(int i, std::string text) { menu[i]->setString(text); }
	int size() const { return (int)menu.size(); }
	void hideItem(int pos) {	menu[pos]->hide(); }
	void unhideItem(int pos)	{ menu[pos]->unhide(); }
	bool isItemTargeted(sf::RenderWindow & gWindow, int pos)
	{ return active && menu[pos]->isTargeted(gWindow); }
	//  Menu is active but all Icons get hidden
	void hideAll()
	{
		for (int i = 0; i < menu.size(); ++i)
			menu[i]->hide();
	}
	//  Menu is active and all Icons get unhidden
	void unhideAll()
	{
		for (int i = 0; i < menu.size(); ++i)
			menu[i]->unhide();
	}
	//  Menu is drawn if active
	void draw(sf::RenderWindow &gWindow)
	{
		if (active)
		{
			for (int i = 0; i < menu.size(); ++i)
				menu[i]->draw(gWindow);
			gWindow.draw(updateText);
		}
	}
	//  Menu is checked for targeted if active
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
};

#endif // MENU_H
