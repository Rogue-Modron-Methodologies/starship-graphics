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

const std::string SDIEFLE = "resources/flightdie.png";
const std::string CDIEFLE = "resources/combatdie.png";
const std::string TRDICN = "resources/TradeMenuIcons.png";
const int NUMRESOURCES = 7;

enum phases{ production, flight, tradeBuild };
enum combatParties{ply, prt};

const int TRADEMENUSIZE = 4;
enum tradeIcons{plus, minus, check, cancel};

const int FMENUSIZE = 4;
enum menuOptions { trdW, colIt, conFly, endFl };

const int PMENUSIZE = 2;
enum pirateIcons{pay, fight};

const int FLAGNUM = 14;
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
	justColonized,					//  Flag:	 Colonized/Established Post
	pirateChoice,					//  Flag:  Choice to Pay or Fight Pirate
	pirateAttack,					//  Flag:  Currently Being Attacked by Pirate
	pirateResult					//  Flag:  Lost to pirate and losing something
};

class Game{
private:
	Player *P1, *P2, *cPlyr;
	Universe *universe;
	sf::RenderWindow gWindow;
	sf::Vector2u screenSize;
	ResourceManager<sf::Texture> txtMgr;
	ResourceManager<sf::Font> fntMgr;
	bool flag[FLAGNUM];					//  Will hold an array of flags for game decisions	
	Icon **tradeSaveState;				//  Saves value of all six resources and astro in case of cancel 
	Icon **tradeMenuIcons;				//  Icons for the Trade Menu
	Icon *flightDie;					//  Production/Flight Die
	Icon **combatDie;					//  Combat Die for Player and Pirate
	Icon *phaseNameString;				//  Phase Name Text String
	Icon *endPhaseString;				//  For End of Phase Messages
	Icon *specialString;				//  For special instructions
	Icon *infoString;					//  Info Text String
	Icon cPlanet;						//  Current Planet 
	Icon *errorString;					//  Error Text String
	Icon *flightEventString;				//  In Progress/Complete/Cancelled
	Icon **flightMenuIcons;				//  FlightMenu  
	Icon **pirateMenuIcons;				//  PirateMenu
	Icon *friendPeople;
	Icon *heroPeople;
	std::string statusUpdate;			//  Catches errors from called functions
	int errorTimer;
	int actionNum;						//  Current Action Num
	int cPhase;						//  Current Phase Num


public:
	Game();
	~Game()
	{
		delete P1;
		delete P2;
		delete universe;
		delete flightDie;
		delete combatDie[ply];
		delete combatDie[prt];
		delete combatDie;
		delete phaseNameString;
		delete flightEventString;
		delete endPhaseString;
		delete specialString;
		delete infoString;
		delete errorString;
		delete heroPeople;
		delete friendPeople;
		for (int i = 0; i < TRADEMENUSIZE; i++)
			delete tradeMenuIcons[i];
		delete [] tradeMenuIcons;
		for (int i = 0; i < NUMRESOURCES; i++)
			delete tradeSaveState[i];
		delete [] tradeSaveState;
		for (int i = 0; i < FMENUSIZE; i++)
			delete flightMenuIcons[i];
		delete[] flightMenuIcons;
		for (int i = 0; i < PMENUSIZE; i++)
			delete pirateMenuIcons[i];
		delete[] pirateMenuIcons;
	}

	// getters and setters
	Player* getP1() const { return P1; }
	Player* getP2() const { return P2; }
	Universe* getUniverse() const { return universe; }

	//  Misc Inline Functions
	void startGame() { gameLoop(); };

private:	
	void gameLoop();
	void playerSetup();	
	void phaseSetup();
	void updateDrawGameWindow();
	void endPhase();
	void rollSpeedDie();
	void rollCombatDie(int party);
	void productionPhaseListener();
	void flightPhaseListener(int tempType);
	void preFlightListener(int &tempType);
	void tradeBuildPhaseListener();
	void tradeMenuListener(int tempType);
	void updateFlightMenu();
	void initTradeMenu(int tempType);
	bool tradeIconsTargeted();
	bool menuOptionTargeted(int &num);
	bool resourcesAvailable(int resAvail[]);
	void gainOneResource();
	void updateFriendOfThePeople();
	void updateHeroOfThePeople();
	void initPirateMenu();
	void pirateMenuListener();


};

#endif // BOARDGAME_H
