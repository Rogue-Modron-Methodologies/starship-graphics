//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#ifndef PLAYER_H
#define PLAYER_H

#include "Starship.h"
#include "LinkedList.h"
#include "ColonyCard.h"

enum Icons{ carbon, fuel, ore, science, tradeGood, wheat, player, astro, vicPt, frdPt, fmPt };
const int ICNNUM = 11;
const std::string ICNFLE = "resources/board/icons.png";		//  Source file name for trade/colony ships
const std::string SYM1FLE = "resources/board/symbols.png";		//  Source file for Victory/Fame/Friendship Icons
const std::string SY21FLE = "resources/board/symbols2.png";		//  Source file for Hero/Friend of the People
const std::string RICNFLE = "resources/board/ResourceIcons.png";	//  Source file for Resource File Icons
const sf::Vector2f CSPOS = sf::Vector2f(30, 550);				//  Screen Position for Small Scale Colony Ico
const sf::Vector2f TSPOS = sf::Vector2f(130, 550);			//  Screen Position for Small Scale Trade Ico
const sf::Vector2f CLPOS = sf::Vector2f(30, 610);				//  Screen Position for Large Scale Colony Ico
const sf::Vector2f TLPOS = sf::Vector2f(180, 610);			//  Screen Position for Large Scale Trade Ico

class Player 
{
private:	
	Starship* starship;
	LinkedList<Card>* ColonyZone;		//  Colony Zone 
	sf::Text cZoneString;			//  Colony Zone Text String
	LinkedList<Card>* TradeZone;		//  Trade Zone 
	sf::Text tZoneString;			//  Trade Zone Text String
	Ico statistics[ICNNUM];			//  Array for the statistic Icons

public:
	Player(ResourceManager<sf::Texture> &txtMgr, ResourceManager<sf::Font> &fntMgr, std::string name = "EMPTY", int num = -99);
	~Player();
	// getters and setters
	Starship* getStarship() const {  return starship;  }
	LinkedList<Card>* getColonyZone() const {	return ColonyZone;	}
	LinkedList<Card>* getTradeZone() const 	{	return TradeZone;	}
	int getAstro() const  { return statistics[astro].ico->getQty(); }
	void update();
	void draw(sf::RenderWindow &gWindow);
	void drawCPlyrStats(sf::RenderWindow &gWindow);
	void updateIcon(int type);
	void expandColonyZone();
	void expandTradeZone();
	void makeBig();
	void makeSmall();
	bool canAfford(int num, std::string &statusUpdate)
	{
		if (num <= statistics[astro].ico->getQty())
			return true;
		statusUpdate = "Can not afford to trade ";
		return false;
	}
	void subAstro(int num)
	{
		statistics[astro].ico->setQty(statistics[astro].ico->getQty() - num);
		statistics[astro].text.setString(std::to_string(statistics[astro].ico->getQty()));
	}
	void addAstro(int num)
	{
		statistics[astro].ico->setQty(statistics[astro].ico->getQty() + num);
		statistics[astro].text.setString(std::to_string(statistics[astro].ico->getQty()));
	}
	

};
#endif // PLAYER_H
