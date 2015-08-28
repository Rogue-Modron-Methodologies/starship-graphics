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
#include "ColonyCard.h"
#include "Pirate.h"
#include "TradeCard.h"
#include "AdventureCard.h"

template <class T>
class Zone
{
private:
	std::vector<T*> zone;
	Icon	*zoneIcon;
	Icon *beginArrow;
	Icon *endArrow;
	bool	showIconOnly;
	bool begArwVis;
	bool endArwVis;


public:
	Zone(ResourceManager<sf::Texture> &txtMgr, ResourceManager<sf::Font> &fntMgr, std::string name)
	{
		zoneIcon = new Icon(txtMgr.getResource(UNIVERSECARDIMAGES), CLPOS, 10, sf::Vector2u(200, 300), {4, 13});
		zoneIcon->setScale(CRDZNSCL);
		if (name == "Colony")
			zoneIcon->initString(fntMgr.getResource(FNTFLE), { CLPOS.x, CLPOS.y - 35}, name);
		else
			zoneIcon->initString(fntMgr.getResource(FNTFLE), { TLPOS.x, TLPOS.y - 35 }, name);
		showIconOnly = true;
		begArwVis = false;
		endArwVis = false;
		beginArrow = new Icon(txtMgr.getResource(SYMBFLE), { CLPOS.x + 175, CLPOS.y - 60 }, 0, { 50, 50 }, { 7, 0 });
		endArrow = new Icon(txtMgr.getResource(SYMBFLE), { CLPOS.x + 250, CLPOS.y - 60 }, 3, { 50, 50 }, { 8, 0 });
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
	void push_back(T* item) 	{ 
		zone.push_back(item); 
		sortZone();
	}

	//
	void draw(sf::RenderWindow &gWindow){
		if (showIconOnly)
			zoneIcon->draw(gWindow);
		else	{
			gWindow.draw(zoneIcon->getText());
			if (zone.empty())
				return;
			if (begArwVis)
				beginArrow->draw(gWindow);
			if (endArwVis)
				endArrow->draw(gWindow);

			for (int i = beginArrow->getQty(); i <= endArrow->getQty() && i < zone.size(); i++)
				zone[i]->draw(gWindow);
		}
	}

	//  Updates the ColonyZone based on given pos and scale 
	void updateZone(sf::Vector2f pos, sf::Vector2f scale, bool toggle){
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

		for (int i = beginArrow->getQty(); i <= endArrow->getQty() && i < zone.size(); i++){
			zone[i]->setScale(scale);
			zone[i]->setPosition(pos + sf::Vector2f{ 150.0f * cardCnt, 0 });
			cardCnt++;
		}
		updateArrows();
	}

	// Checks to see if any card in the vector has been targeted   
	bool isZoneTargeted(sf::RenderWindow &gWindow, int &resource){
		for (int i = beginArrow->getQty(); i <= endArrow->getQty() && i < zone.size(); i++){
			if (zone[i]->isTargeted(gWindow)){
				resource = zone[i]->getResource();
				return true;
			}
		}
		if (begArwVis && beginArrow->isTargeted(gWindow)){
			beginArrow->setQty(beginArrow->getQty() - 1);
			endArrow->setQty(endArrow->getQty() - 1);
			updateZone(CLPOS, CRDZNSCL, false);
			return true;
		}
		if (endArwVis && endArrow->isTargeted(gWindow)){
			beginArrow->setQty(beginArrow->getQty() + 1);
			endArrow->setQty(endArrow->getQty() + 1);
			updateZone(CLPOS, CRDZNSCL, false);
			return true;
		}
				
		return false;
	}

	// Checks to see
	bool resourceMatchesActNum(int resource, int actNum){
		bool flag = false;

		for (int i = 0; i < zone.size(); i++){
			if ( zone[i]->getActNum() == actNum && zone[i]->getResource() == resource )
				return true;
		}
		return false;
	}

	//  Checks to see if num is in the list                         
	bool findResource(int num, int resAvail[]){
		bool flag = false;

		for (int i = 0; i < zone.size(); i++){
			if (zone[i]->getActNum() == num){
				resAvail[zone[i]->getResource()] = 1;
				flag = true;
			}			
		}
		return flag;
	}

private:
	void sortZone(){
		typedef bool(*comparer_t)(const T*, const T*);
		comparer_t cmp = &sortBy;
		std::sort(zone.begin(), zone.end(), cmp);
	}

	void updateArrows(){
		if (beginArrow->getQty() > 0)
			begArwVis = true;
		else
			begArwVis = false;
		if (endArrow->getQty() < zone.size() - 1)
			endArwVis = true;
		else
			endArwVis = false;
	}

};

#endif

