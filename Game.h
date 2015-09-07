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
const int FLIGHTACTIONS = 10;

enum phases{ production, flight, tradeBuild };
enum combatParties{ply, prt};

const int BUILDICONSIZE = 6;
enum BuildIcons{ BLVL1, BLVL2, LLVL1, LLVL2, COLSHIP, TRDSHIP };

const int TRADEMENUSIZE = 4;
enum tradeIcons{plus, minus, check, cancel};

const int FMENUSIZE = 5;
enum menuOptions { trdW, colIt, conFly, endFl, adv };

const int PMENUSIZE = 2;
enum pirateIcons{pay, fight};

const int FLAGNUM = 17;
enum flagTypes
{
	phaseSetupComplete,				//  Flag:  Phase Setup Complete
	gainResource,					//  Flag:  Choose one resource
	showFlightPath,				//  Flag:  Display flightPath
	sectorSelected,				//  Flag:  Sector Selection Complete
	phaseComplete,					//  Flag:  Phase Complete
	showflightMenu,				//  Flag:	 Display Flight Menu
	choosingResource,				//  Flag;  In process of choosing Resource
	resourceChosen,				//  Flag:  Resource Chosen
	tradeInProgress,				//  Flag:  Trade in Progress
	justActed,					//  Flag:  Performed and action on this planet
	pirateChoice,					//  Flag:  Choice to Pay or Fight Pirate
	pirateAttack,					//  Flag:  Currently Being Attacked by Pirate
	pirateResult,					//  Flag:  Lost to pirate and losing something
	buildTradeBegin,				//  Flag:  Beginning of Trading during build phase
	buildTradeEnd,					//  Flag:  End of Trading during build phase
	adventureAvailable,				//  Flag:  Current Planet is an adventure planet and adventure is available.
	adventureReward				//  Flag:  Adventure Resource Granted
};

class Game{
private:
	Player *P1, *P2, *cPlyr;
	Universe *universe;
	sf::RenderWindow gWindow;
	sf::Vector2u screenSize;
	sf::Event event;
	ResourceManager<sf::Texture> txtMgr;
	ResourceManager<sf::Font> fntMgr;
	bool flag[FLAGNUM];					//  Will hold an array of flags for game decisions	
	Object **tradeSaveState;				//  Saves value of all six resources and astro in case of cancel 
	Object **tradeMenuIcons;				//  Icons for the Trade Menu
	Object *flightDie;					//  Production/Flight Die
	Object **combatDie;					//  Combat Die for Player and Pirate
	Object cPlanetIcon;					//  Current Planet Icon
	TradeCard cPlanetInfo;				//  Placeholder for current trade 
	Object **flightMenuIcons;				//  FlightMenu  
	Object **pirateMenuIcons;				//  PirateMenu
	Object **flightPathActions;			//  Displays actions by the Current Player during flight
	Object **buildMenuIcons;				//  Clickable objects for build phase
	Object friendPeople;
	Object heroPeople;
	std::string statusUpdate;			//  Catches errors from called functions
	sf::Text phaseNameString;			//  Phase Name Text String
	sf::Text endPhaseString;				//  For End of Phase Messages
	sf::Text specialString;				//  For special instructions
	sf::Text infoString;				//  Info Text String
	sf::Text errorString;				//  Error Text String	
	sf::Text flightEventString;			//  In Progress/Complete/Cancelled	
	int actionNum;						//  Current Action Num
	int cPhase;						//  Current Phase Num
	int errorTimer;
	int cTradeResource;					//  Current Traded Resource
	int cTradeNum;						//  Current Number of Trades
	int numPlntsTrd;
	int curAdv;

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
		for (int i = 0; i < FLIGHTACTIONS; i++)
			delete flightPathActions[i];
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
		for (int i = 0; i < BUILDICONSIZE; i++)
			delete buildMenuIcons[i];
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
	void phaseSetup();
	void drawGameWindow();
	void endPhase();
	void rollSpeedDie();
	void rollCombatDie(int party);
	void productionPhaseListener();
	void flightPhaseListener(int tempType);
	void preFlightListener(int &tempType);
	void tradeBuildPhaseListener(int &tempNum);
	void tradeMenuListener();
	void updateFlightMenu();
	void initTradeMenu(int &tempType, int tempPos = -1);
	bool tradeIconsTargeted();
	bool buildIconsTargeted(int &tempType);
	bool flightMenuOptionTargeted(int &num);
	bool anyResourcesInListAvailable(int resAvail[]);
	bool allRequirementsMet(int requirements[], int size = 6);
	bool areAnyResourcesAvailable();
	bool gainOneResource(int cost = 0);
	void updateFriendOfThePeople();
	void updateHeroOfThePeople();
	void initPirateMenu();
	void pirateMenuListener();
	void adventureListener(int tempType);
	bool buildShipObject(int item);
	std::string getAdvReqString();
	bool startAdventure();
	void adventureRewards();
	std::string getAdvRewardsString(int res, int astro, int fame, int vic);


};

#endif // BOARDGAME_H
