//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#ifndef TRADEMANAGER_H
#define TRADEMANAGER_H

#include "Menu.h"
#include "Player.h"

const int NUMRESOURCES = 7;
const std::string SDIEFLE = "resources/flightdie.png";
const std::string CDIEFLE = "resources/combatdie.png";
const std::string TRDICN = "resources/TradeMenuIcons.png";

class TradeManager
{
private:
	bool active;
	bool choosingRes;
	bool resChosen;
	bool productionGain;
	int cResource;
	int cTradeNum;
	int cost;
	int limit;
	int resAvail[NUMRESOURCES];	
	Menu resourceMenu;				//  Menu:  Used for resource choice and save states
	Menu tradeMenu;				//  Menu:  Trade Options
	std::string transaction;

public:
	TradeManager(ResourceManager<sf::Texture> &txtMgr);

	//  Getters/Setters
	void setChoosingResource(bool toggle) { choosingRes = toggle;}
	void setResourceChosen(bool toggle) { resChosen = toggle; }
	bool choosingResource() { return choosingRes; }
	bool resourceChosen() { return resChosen; }
	void setTradedResource(int num){ cResource = num; }
	int getTradedResource(){ return cResource; }
	void setLimit(int lim) { limit = lim; }
	void setCost(int co) { cost = co; }	
	int getCost(){ return cost; }
	bool isActive() const { return active; }
	void setTransaction(std::string trans) { transaction = trans; }
	
	//  Misc Inline Functions
	bool checkTargeted(sf::RenderWindow &gWindow)
		{ return tradeMenu.isItemTargeted(gWindow, check); }
	bool cancelTargeted(sf::RenderWindow &gWindow)
		{ return tradeMenu.isItemTargeted(gWindow, cancel);}
	bool plusTargeted(sf::RenderWindow &gWindow)
		{ return tradeMenu.isItemTargeted(gWindow, plus); }
	bool minusTargeted(sf::RenderWindow &gWindow)
		{return tradeMenu.isItemTargeted(gWindow, minus); }

	//  Prototypes
	void tradNumPlusOne(){ cTradeNum++; }
	void setActive(bool toggle);
	void saveResources(Player *cPlyr);
	void restoreResources(Player *cPlyr);
	void greyAllButChosesnResources();
	void greyUnavailResources(Player *cPlyr);
	void updateTradeIcons(Player *cPlyr);
	bool resourceTargeted(sf::RenderWindow &gWindow, int &pos);
	bool iconsTargeted(sf::RenderWindow &gWindow);
	void draw(sf::RenderWindow &gWindow);
	void setAvailableResources(int resAvail[]);


private:
	void createResourceMenu(ResourceManager<sf::Texture> &txtMgr);
	void createTradeMenu(ResourceManager<sf::Texture> &txtMgr);
};



#endif // TRADEMANAGER_H

