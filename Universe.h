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

const int CARDLISTSIZE = 71;							//  number of cards in the universe deck
const std::string CARDLIST = "starship.csv";
const std::string BOARDFILE = "resources/starrynight.png";

class Universe
{
private:
	Object *board;
	Card **S1;				//  Sector 1
	Card **S2;				//  Sector 2
	Card **S3;				//  Sector 3
	Card **S4;				//  Sector 4
	Card **SE;				//  Extra Cards waiting to be put into Sectors
	AdventureCard **AD;			//  Adventure Deck (Extra Cards)
	AdventureCard **cAdv;		//  Available Adventures (will be three of them)
	Object **flightSector;
	int currentMove;
	int sectorNum;
	int ExtraDeckPtr;
	int advPtr;

public:
	Universe(ResourceManager<sf::Texture> &txtMgr, ResourceManager<sf::Font> &fntMgr);
	~Universe();
	// Getters and Setters
	Card** getSector(int num);
	int getCurrentSectorNum(){ return sectorNum; }
	Card** getCurrentSector(){ return getSector(sectorNum);}
	AdventureCard* getAdvCard(int i);
	Object *getBoard() const { return board; }
	int getCurrentMove(){ return currentMove; }
	Card* getCurrentPlanet(){ return getSector(sectorNum)[currentMove - 1]; }
	Card* getFlightPathPlanet(int num){ return getSector(sectorNum)[num]; }
	bool isCurrentAdventureTargeted(sf::RenderWindow &gWindow, int &temp);
	void drawCurrentAdventures(sf::RenderWindow &gWindow);
	void hideSectors();
	void unhideSectors();
	void drawSectors(sf::RenderWindow &gWindow);
	bool sectorsTargeted(sf::RenderWindow &gWindow, int &num);
	bool flightPathTargeted(sf::RenderWindow &gWindow, int &num);
	void initializeFlightPath(int tempType);
	void continueFlight(){ currentMove++; }
	void replaceCurrentPlanet();
	void makeAdventuresAvailable();
	bool atAdventurePlanet();
	bool atCurrentAdventurePlanet(int num);
	void addCardtoAdvDeck(int i);	

private:
	void universeSetup(ResourceManager<sf::Texture> &txtMgr);
	void shuffleDeck(Card* list[], int size);
	void addCardtoSector(int secNum, int i);
	Object* getFlightSector() const { return flightSector[0]; }
	void setSector(Card* nCard, int sNum, int cNum);

};
#endif // UNIVERSE_H
