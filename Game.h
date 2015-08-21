//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Universe.h"
#include "Object.h"
#include <string>
#include <fstream>
#include <sstream>
#include "SFML/Graphics.hpp"

const std::string SDIEFLE = "resources/board/flightdie.png";
const std::string TRDICN = "resources/board/TradeMenuIcons.png";

enum menuOptions { trdW, colIt, conFly, endFl };
enum phases{ production, flight, trades, build };
enum tradeIcons{plus, minus, check, cancel};

const int FLAGNUM = 10;
enum flagTypes{
	phaseSetupComplete,				//  Flag:  Phase Setup Complete
	gainResource,					//  Flag:  Choose one resource
	visFlightPath,					//  Flag:  Display flightPath
	visSectors,					//  Flag:  Display Sectors
	sectorSelected,				//  Flag:  Sector Selection Complete
	phaseComplete,					//  Flag:  Phase Complete
	visFlightMenu,					//  Flag:	 Display Flight Menu
	tradeInProgress,				//  Flag:  Trade in Progress
	justTraded,					//  Flag:  Traded Already
	justColonized					//  Flag:	 Colonized/Established Post
};

class Game{
private:
	Player *P1, *P2, *cPlyr;
	Universe *universe;
	sf::RenderWindow gWindow;
	sf::Vector2u screenSize;
	ResourceManager<sf::Texture> txtMgr;
	ResourceManager<sf::Font> fntMgr;
	bool flag[9];						//  Will hold an array of flags for game decisions	
	Icon **tradeSaveState;				//  Saves value of all six resources and astro in case of cancel 
	Icon **tradeMenuIcons;				//  Icons for the Trade Menu
	Icon *flightDie;	
	Icon *phaseNameString;				//  Phase Name Text String
	Icon *endPhaseString;				//  For End of Phase Messages
	Icon *specialString;				//  For special instructions
	Icon *infoString;					//  Info Text String
	Icon *cPlanet;						//  Current Planet Text String
	Icon *errorString;					//  Error Text String
	Icon *tradeProgressString;			//  In Progress/Complete/Cancelled
	Icon **menu;						//  
	std::string statusUpdate;			//  Catches errors from called functions
	int errorTimer;
	int actionNum;						//  Current Action Num
	int cPhase;						//  Current Phase Num
	int combatDie[6];


public:
	Game();
	~Game()
	{
		delete P1;
		delete P2;
		delete universe;
		delete flightDie;
		delete phaseNameString;
		delete tradeProgressString;
		delete endPhaseString;
		delete specialString;
		delete infoString;
		delete errorString;
		delete cPlanet;
		for (int i = 0; i < 4; i++)
			delete tradeMenuIcons[i];
		delete [] tradeMenuIcons;
		for (int i = 0; i < 7; i++)
			delete tradeSaveState[i];
		delete [] tradeSaveState;
		for (int i = 0; i < MENUSIZE; i++)
			delete menu[i];
		delete[] menu;
	}

	// getters and setters
	Player* getP1() const { return P1; }
	Player* getP2() const { return P2; }
	Universe* getUniverse() const { return universe; }

	//  Misc Inline Functions
	int rollCombatDie() { return combatDie[rand() % 6]; }
	void startGame() { gameLoop(); };

private:	
	void gameLoop();
	void playerSetup();	
	void initCDie();
	void phaseSetup();
	void updateGameWindow(sf::RenderWindow &gWindow);
	void endPhase();
	void setError(std::string error);
	int rollSpeedDie();
	void productionPhaseListener(sf::RenderWindow &gWindow);
	void flightPhaseListener(sf::RenderWindow &gWindow, int tempType);
	void preFlightListener(sf::RenderWindow &gWindow, int &tempType);
	void tradePhaseListener(sf::RenderWindow &gWindow);
	void buildPhaseListener(sf::RenderWindow &gWindow);
	void tradeMenu(sf::RenderWindow &gWindow, int tempType);
	void drawFlightMenu(sf::RenderWindow &gWindow);
	void updateFlightMenu(sf::RenderWindow &gWindow);
	void drawFlightPath(sf::RenderWindow &gWindow);
	void drawCurrentPlanet(sf::RenderWindow &gWindow);
	void initTradeMenu(sf::RenderWindow &gWindow, int tempType);
	bool tradeIconsTargeted(sf::RenderWindow &gWindow);
	bool menuOptionTargeted(sf::RenderWindow &gWindow, int &num);

};

#endif // BOARDGAME_H
