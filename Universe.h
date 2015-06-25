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
#include "Object.h"

class Universe{
private:
	Object *board;
	Card* S1[10];
	Card* S2[10];
	Card* S3[10];
	Card* S4[10];
	Card* SE[28];
	Card* AD[9];
	Card* cAdv[3];
	int ExtraDeckPtr;
	int advPtr;

public:
	Universe()
	{
		board = new Object ("resources/board/starrynight.png", sf::Vector2f(1200, 900), sf::Vector2f(0, 0), sf::Vector2f(3.1f, 3.6f));
		universeSetup();
		adventureDeckSetup();
		ExtraDeckPtr = 0;
		advPtr = 0;
	}
	~Universe() 
	{	delete board;	}
	// Getters and Setters
	Card** getSector(int num);
	Card* getAdvCard(int i);
	Object *getBoard() const { return board; }
	void setSector(Card* nCard, int sNum, int cNum);
	void shuffleDeck(Card* list[], int size);
	void addCardtoSector(int secNum, int i);
	void addCardtoAdvDeck(int i);
	void printCurrentAdventure(sf::RenderWindow &gWindow);

private:
	void universeSetup();
	void adventureDeckSetup();
	
};
#endif // UNIVERSE_H
