//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "TradeCard.h"
#include "ColonyCard.h"		
#include "Pirate.h"
#include "AdventureCard.h"

enum menuOptions {trdW, colIt, conFly, endFl };
const int MENUSIZE = 4;
const int CARDLISTSIZE = 71;					//  number of cards in the deck
const std::string CARDLIST = "starship.csv";
const std::string CARDIMAGES = "resources/cards/universeCards.png";
const std::string ADVENTURELIST = "starship2.csv";

class Universe{
private:
	sf::Font font;
	Object *board;
	Icon **menu;
	Icon flightSector[MENUSIZE];
	Card **S1;				//  Sector 1
	Card **S2;				//  Sector 2
	Card **S3;				//  Sector 3
	Card **S4;				//  Sector 4
	Card **SE;				//  Extra Cards waiting to be put into Sectors
	Card **AD;				//  Adventure Deck
	Card **cAdv;				//  Current Adventure????
	int currentMove;
	int sectorNum;
	int ExtraDeckPtr;
	int advPtr;

public:
	Universe(ResourceManager<sf::Texture> &txtMgr);
	~Universe();
	// Getters and Setters
	Card** getSector(int num);
	Card** getCurrentSector(){ return getSector(sectorNum);}
	Icon* getMenuItem(int num) { return menu[num]; }
	Card* getAdvCard(int i);
	Object *getBoard() const { return board; }
	int getCurrentMove(){ return currentMove; }
	Card* getCurrentPlanet(){ return getSector(sectorNum)[currentMove - 1]; }
	void printCurrentAdventure(sf::RenderWindow &gWindow);
	void drawSectors(sf::RenderWindow &gWindow);
	bool sectorsTargeted(sf::RenderWindow &gWindow, int &num);
	bool flightPathTargeted(sf::RenderWindow &gWindow, int &num);
	void initializeFlightPath(int tempType);
	bool menuOptionTargeted(sf::RenderWindow &gWindow, int &num);
	void continueFlight(){ currentMove++; }


private:
	void universeSetup(ResourceManager<sf::Texture> &txtMgr);
	void adventureDeckSetup();
	void addCardtoAdvDeck(int i);		
	void shuffleDeck(Card* list[], int size);
	void addCardtoSector(int secNum, int i);
	Icon getFlightSector() const { return flightSector[0]; }
	void setSector(Card* nCard, int sNum, int cNum);

};
#endif // UNIVERSE_H
