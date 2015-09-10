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
#include <iostream>

enum Icons{ science, ore, fuel, tradeGood, wheat, carbon, astro, player, vicPt, frdPt, fmPt };
const int STATNUM = 11;
const std::string ICNFLE = "resources/playerIcons.png";		//  Source file name for trade/colony ships
const std::string SYM1FLE = "resources/symbolsSmall.png";	//  Source file for Victory/Fame/Friendship Icons
const std::string FRIENDHERO = "resources/FriendHeroIcons.png";		//  Source file for Hero/Friend of the People
const std::string SYMBFLE = "resources/symbolsBig.png";
const std::string RICNFLE = "resources/ResourceIcons.png";	//  Source file for Resource File Icons
const sf::Vector2f CSPOS = sf::Vector2f(20, 550);				//  Screen Position for Small Scale Colony Icon
const sf::Vector2f TSPOS = sf::Vector2f(130, 550);			//  Screen Position for Small Scale Trade Icon
const sf::Vector2f CLPOS = sf::Vector2f(20, 610);				//  Screen Position for Large Scale Colony Icon
const sf::Vector2f TLPOS = sf::Vector2f(170, 610);			//  Screen Position for Large Scale Trade Icon

class Player 
{
private:	
	Starship* starship;
	Zone<ColonyCard> *colonyZone;		//  Colony Zone 
	Zone<TradeCard> *tradeZone;		//  Trade Zone 
	Zone<Pirate> *pirateZone;		//  Zone to hold Pirates that have been defeated  (to be used to create logs.)	
	Zone<AdventureCard> *advZone;		//  Zone to hold Adventures that have been completed (to be used later.)
	Object** statistics;			//  Array for the statistic Icons
	bool smallDisplay;
	bool friendOfThePeople;
	bool heroOfThePeople;

public:
	Player(ResourceManager<sf::Texture> &txtMgr, ResourceManager<sf::Font> &fntMgr, std::string name, int num);
	~Player();

	// getters and setters
	Starship* getStarship() const {  return starship;  }
	Zone<ColonyCard>* getColonyZone() const {	return colonyZone;	}
	Zone<TradeCard>* getTradeZone() const 	{	return tradeZone;	}
	Zone<Pirate>* getPirateZone() const { return pirateZone; }
	Zone<AdventureCard>* getAdventureZone() const { return advZone; }
	int getStatQty(int num){ return statistics[num]->getQty(); }
	void setAstro(int num){ statistics[astro]->setQty(num); }
	
	//  Misc Inline Functions
	void updatePlayerIcon();
	void draw(sf::RenderWindow &gWindow);
	int getPlyrNum() const { return statistics[player]->getQty(); }
	bool isHero() const { return heroOfThePeople; }
	bool isFriend() const { return friendOfThePeople; }
	
	void addFmPt(int num = 1){ statistics[fmPt]->setQty(statistics[fmPt]->getQty() + num ); }
	void addFrdPt(int num = 1){ statistics[frdPt]->setQty(statistics[frdPt]->getQty() + num ); }
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

	void addVicPt(int num = 1)
	{
		statistics[vicPt]->setQty(statistics[vicPt]->getQty() + num ); 
		if (statistics[vicPt]->getQty() >= 10)
			std::cout << "If it is this player's turn (will check later) they are the winner!!!!!!!!!!!!\n";

	}
	void toggleFriend(bool toggle)
	{ 
		friendOfThePeople = toggle; 
		if (toggle)
			statistics[vicPt]->setQty(statistics[vicPt]->getQty() + 1);
		else
			statistics[vicPt]->setQty(statistics[vicPt]->getQty() - 1);
	}
	void toggleHero(bool toggle)
	{ 
		heroOfThePeople = toggle; 
		if (toggle)
			statistics[vicPt]->setQty(statistics[vicPt]->getQty() + 1);
		else
			statistics[vicPt]->setQty(statistics[vicPt]->getQty() - 1);
	}
	
};
#endif // PLAYER_H
