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

//enum Icons{player, astro, vicPt, frdPt, fmPt, science, ore, fuel, tradeGood, wheat, carbon};

const std::string ICNFLE = "resources/board/icons.png";		//  Source file name for trade/colony ships
const std::string FNTFLE = "resources/board/unique.ttf";		//  Source file name for Font
const std::string SYM1FLE = "resources/board/symbols.png";		//  Source file for Victory/Fame/Friendship Icons
const std::string SY21FLE = "resources/board/symbols2.png";		//  Source file for Hero/Friend of the People
const std::string RICNFLE = "resources/board/ResourceIcons.png";	//  Source file for Resource File Icons
const sf::Vector2f CSPOS = sf::Vector2f(30, 550);				//  Screen Position for Small Scale Colony Icon
const sf::Vector2f TSPOS = sf::Vector2f(130, 550);			//  Screen Position for Small Scale Trade Icon
const sf::Vector2f CLPOS = sf::Vector2f(30, 610);				//  Screen Position for Large Scale Colony Icon
const sf::Vector2f TLPOS = sf::Vector2f(180, 610);			//  Screen Position for Large Scale Trade Icon

struct Icon						// For When an object needs to be paired with displayable text
{
	sf::Text text;					//  Text String
	Object *icon;					//  Icon 
};

class Player 
{
private:	
	Starship* starship;
	sf::Font font;
	LinkedList<Card>* ColonyZone;		//  Colony Zone 
	sf::Text cZoneString;			//  Colony Zone Text String
	LinkedList<Card>* TradeZone;		//  Trade Zone 
	sf::Text tZoneString;			//  Trade Zone Text String
	//Icon statistics[11];			//  Array for Below Icons  /////////////////////////   ADD THE ICONS TO THE ARRAY  - WITH AN ENUM
	Icon player;					//  Player Icon 
	Icon astro;					//  Astro Icon
	Icon vicPt;					//  Victory Point Icon
	Icon frdPt;					//  Friend Point Icon (for friend of the people)
	Icon fmPt;					//  Fame Point Icon (for hero of the people)
	Icon science;					//  Science Resource Icon
	Icon ore;						//  Ore Resource Icon
	Icon fuel;					//  Fuel Resource Icon
	Icon tradeGood;				//  TradeGood Resource Icon
	Icon wheat;					//  Wheat Resource Icon
	Icon carbon;					//  Carbon Resource Icon

public:
	Player(std::string name = "EMPTY", int num = -99);
	~Player();
	// getters and setters
	Starship* getStarship() const {  return starship;  }
	LinkedList<Card>* getColonyZone() const {	return ColonyZone;	}
	LinkedList<Card>* getTradeZone() const 	{	return TradeZone;	}
	int getAstro() const  { return astro.icon->getNum(); }
	void update();
	void draw(sf::RenderWindow &gWindow);
	void drawCPlyrStats(sf::RenderWindow &gWindow);
	void expandColonyZone();
	void expandTradeZone();
	void makeBig();
	void makeSmall();
	

};
#endif // PLAYER_H
