//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#ifndef ZONE_H
#define ZONE_H

#include "Icon.h"
#include "Card.h"

template <class T>
class Zone
{
private:
	std::vector<T*> zone;
	Icon	*zoneIcon;
	bool	showIconOnly;					

public:
	Zone(ResourceManager<sf::Texture> &txtMgr, ResourceManager<sf::Font> &fntMgr, std::string name)
	{
		zoneIcon = new Icon(txtMgr.getResource("resources/cards/CardBackground.png"), CLPOS, 10, sf::Vector2u(200, 300));
		zoneIcon->setScale(CRDZNSCL);
		if (name == "Colony")
			zoneIcon->initString(fntMgr.getResource(FNTFLE), { CLPOS.x, CLPOS.y - 35}, name);
		else
			zoneIcon->initString(fntMgr.getResource(FNTFLE), { TLPOS.x, TLPOS.y - 35 }, name);
		showIconOnly = true;
	}

	~Zone()
	{
		for (int i = 0; i < zone.size(); i++)
			delete zone[i];
	}

	// getters and setters
	bool getIconOnly() const { return showIconOnly; }
	bool getSmallDisplay() const { return smallDisplay; }
	sf::Vector2f getPosition() const { return zoneIcon->getIconPosition(); }
	sf::Vector2f getScale() const { return zoneIcon->getScale(); }



	//  Misc Inline Functions
	bool isIconTargeted(sf::RenderWindow &gWindow) { 	return zoneIcon->isTargeted(gWindow); }
	
	template<class T>
	void push_back(T* item) 
	{ 
		zone.push_back(item); 
		sortZone();
	}

	//
	void draw(sf::RenderWindow &gWindow)
	{
		if (showIconOnly)
			zoneIcon->draw(gWindow);
		else
		{
			gWindow.draw(zoneIcon->getText());
			if (zone.empty())
				return;
			for (int i = 0; i < zone.size(); i++)
				zone[i]->draw(gWindow);
		}
	}

	//  Updates the ColonyZone based on given pos and scale 
	void updateZone(sf::Vector2f pos, sf::Vector2f scale, bool toggle)
	{
		showIconOnly = toggle;
		zoneIcon->setIconPosition(pos);
		zoneIcon->setScale(scale);
		zoneIcon->setTextPosition({pos.x, pos.y - 35});
		if (zone.empty())
			return;

		zoneIcon->setTexture(*(zone[0]->getTexture()));
		zoneIcon->setSrcPos(zone[0]->getSrcPos());
		zoneIcon->updateTextRect();

		int cardCnt = 0;

		for (int i = 0; i < zone.size(); i++)			
		{
			zone[i]->setScale(scale);
			zone[i]->setPosition(pos + sf::Vector2f{ 150.0f * cardCnt, 0 });
			cardCnt++;
		}
	}

	// Checks to see if any card in the vector has been targeted   
	bool isZoneTargeted(sf::RenderWindow &gWindow, int &resource) const
	{
		for (int i = 0; i < zone.size(); i++)
		{
			if (zone[i]->isTargeted(gWindow))
			{
				resource = zone[i]->getResource();
				return true;
			}
		}
		return false;
	}

	// Checks to see
	bool resourceMatchesActNum(int resource, int actNum)
	{
		bool flag = false;

		for (int i = 0; i < zone.size(); i++)
		{
			if ( zone[i]->getActNum() == actNum && zone[i]->getResource() == resource )
				return true;
		}
		return false;
	}

	//  Checks to see if num is in the list                         
	bool findResource(int num, int resAvail[])
	{
		bool flag = false;

		for (int i = 0; i < zone.size(); i++)
		{
			if (zone[i]->getActNum() == num)
			{
				resAvail[zone[i]->getResource()] = 1;
				flag = true;
			}
				
		}
		return flag;
	}

private:
	void sortZone()
	{
		typedef bool(*comparer_t)(const T*, const T*);
		comparer_t cmp = &sortBy;
		std::sort(zone.begin(), zone.end(), cmp);
	}

};

#endif

