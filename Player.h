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
#include "Zone.h"
#include "ColonyCard.h"
#include "TradeCard.h"

enum Icons{ science, ore, fuel, tradeGood, wheat, carbon, astro, player, vicPt, frdPt, fmPt };
const int STATNUM = 11;
const std::string ICNFLE = "resources/board/icons.png";		//  Source file name for trade/colony ships
const std::string SYM1FLE = "resources/board/symbolsSmall.png";	//  Source file for Victory/Fame/Friendship Icons
const std::string SY21FLE = "resources/board/symbols2.png";		//  Source file for Hero/Friend of the People
const std::string RICNFLE = "resources/board/ResourceIcons.png";	//  Source file for Resource File Icons
const sf::Vector2f CSPOS = sf::Vector2f(20, 550);				//  Screen Position for Small Scale Colony Icon
const sf::Vector2f TSPOS = sf::Vector2f(130, 550);			//  Screen Position for Small Scale Trade Icon
const sf::Vector2f CLPOS = sf::Vector2f(20, 610);				//  Screen Position for Large Scale Colony Icon
const sf::Vector2f TLPOS = sf::Vector2f(170, 610);			//  Screen Position for Large Scale Trade Icon

class Player 
{
private:	
	Starship* starship;
	Zone<ColonyCard> *colonyZone;		//  Colony Zone 
	Zone<TradeCard>* tradeZone;		//  Trade Zone 
	Icon** statistics;				//  Array for the statistic Icons
	bool smallDisplay;

public:
	Player(ResourceManager<sf::Texture> &txtMgr, ResourceManager<sf::Font> &fntMgr, std::string name = "EMPTY", int num = -99);
	~Player();

	// getters and setters
	Starship* getStarship() const {  return starship;  }
	Zone<ColonyCard>* getColonyZone() const {	return colonyZone;	}
	Zone<TradeCard>* getTradeZone() const 	{	return tradeZone;	}
	int getStatQty(int num){ return statistics[num]->getQty(); }
	void setStatQty(int stat, int num){ statistics[stat]->setQty(num); }


	//  Misc Inline Functions
	void updatePlayerIcon();
	void draw(sf::RenderWindow &gWindow);
	void updateIcon(int type);
	void expandColonyZone();
	void expandTradeZone();
	void makeBig();
	void makeSmall();
	bool zonesSmall(){ return smallDisplay; }
	void subAstro(int num) {	statistics[astro]->setQty(statistics[astro]->getQty() - num); }
	void addAstro(int num) { statistics[astro]->setQty(statistics[astro]->getQty() + num); }
	bool canAfford(int num, std::string &statusUpdate)
	{
		if (num <= statistics[astro]->getQty())
			return true;
		statusUpdate = "Can not afford ";
		return false;
	}	
	
};
#endif // PLAYER_H
