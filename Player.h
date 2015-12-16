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

#include <SFML/Graphics.hpp>

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

#include "Starship.h"
#include "Zone.h"
#include "Menu.h"
#include <iostream>

class Player 
{
private:	
	Starship* starship;
	Zone<ColonyCard> *colonyZone;		//  Colony Zone 
	Zone<TradeCard> *tradeZone;		//  Trade Zone 
	Zone<Pirate> *pirateZone;		//  Zone to hold Pirates that have been defeated  (to be used to create logs.)	
	Zone<AdventureCard> *advZone;		//  Zone to hold Adventures that have been completed (to be used later.)
	Menu statistics;
	bool smallDisplay;
	bool friendOfThePeople;
	bool heroOfThePeople;

public:
	Player(ResourceManager<sf::Texture> &txtMgr, ResourceManager<sf::Font> &fntMgr, std::string name, int num);
	~Player();

	// getters and setters
	Starship* getStarship() const {  return starship;  }
	Zone<ColonyCard>* getColonyZone() const { return colonyZone; }
	Zone<TradeCard>* getTradeZone() const 	{ return tradeZone;	}
	Zone<Pirate>* getPirateZone() const { return pirateZone; }
	Zone<AdventureCard>* getAdventureZone() const { return advZone; }
	int getStatQty(int num){ return statistics.getItemQty(num); }
	void setAstro(int num){ statistics.setItemQty(astro, num); }
	
	//  Misc Inline Functions
	void draw(sf::RenderWindow &gWindow);
	int getPlyrNum() const { return statistics.getItemQty(player); }
	bool isHero() const { return heroOfThePeople; }
	bool isFriend() const { return friendOfThePeople; }
	//void updatePlayerIcon() { statistics[player]->setSrcPosX(statistics[player]->getQty() - 1); }
	bool zonesSmall(){ return smallDisplay; }	

	//  Prototypes
	void updateIcon(int type);
	void expandColonyZone();
	void expandTradeZone();
	void makeBig();
	void makeSmall();
	void addFmPt(int num = 1);
	void addFrdPt(int num = 1);
	void subAstro(int num);
	void addAstro(int num);
	bool canAfford(int num, std::string &statusUpdate);
	void addVicPt(int num = 1);
	void toggleFriend(bool toggle);
	void toggleHero(bool toggle);
	void fillHolds();
	void createSectorMenu(ResourceManager<sf::Texture> &txtMgr, ResourceManager<sf::Font> &fntMgr, std::string name, int num);
};

#endif // PLAYER_H
