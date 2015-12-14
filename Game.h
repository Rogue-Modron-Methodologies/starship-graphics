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

#include "Universe.h"
#include "Menu.h"
#include "TradeManager.h"
#include <string>
#include <fstream>
#include <sstream>
#include "SFML/Graphics.hpp"


const int FLIGHTACTIONS = 10;

enum phases{ production, flight, tradeBuild };
enum combatParties{ply, prt};

const int FLAGNUM = 10;
enum flagTypes
{
	phaseSetupComplete,				//  Flag:  Phase Setup Complete
	flightPathActive,				//  Flag:  flightPath, flightActionPath, and Adventures
	phaseComplete,					//  Flag:  Phase Complete
	justActed,					//  Flag:  Performed and action on this planet
	pirateResult,					//  Flag:  Lost to pirate and losing something
	buildTradeBegin,				//  Flag:  Beginning of Trading during build phase
	buildTradeEnd,					//  Flag:  End of Trading during build phase
	adventureAvailable,				//  Flag:  Current Planet is an adventure planet and adventure is available.
	adventureReward,				//  Flag:  Adventure Resource Granted
	cPlanetActive					//  Flag:  Show the Current Planet Icon
};

class Game
{
private:
	ResourceManager<sf::Texture> txtMgr;
	ResourceManager<sf::Font> fntMgr;	
	TradeManager trdMgr;	
	bool flag[FLAGNUM];						//  Hold an array of flags for game decisions	
	sf::RenderWindow gWindow;
	sf::Vector2u screenSize;
	sf::Event event;
	Universe *universe;
	Player		*P1, 
				*P2, 
				*cPlyr;				
	Menu			flightMenu,				//  Menu:  Flight Phase Actions
				buildMenu,				//  Menu:  Build Phase Actions
				pirateMenu,				//  Menu:  Pirate Options
				sectorMenu;				//  Menu:  Sector Selection
	Object		**flightPathActions,		//  Displays actions by the Current Player during flight				
				**combatDie,				//  Combat Die for Player and Pirate		 
				flightDie,				//  Production/Flight Die
				friendPeople,				//  Worth 1 Vic Point
				heroPeople;				//  Worth 1 Vic Point
	TradeCard		currentPlanet;				//  Current Planet Icon	
	std::string	statusUpdate;				//  Catches errors from called functions
	sf::Text		phaseNameString,			//  Phase Name Text String
				endPhaseString,			//  For End of Phase Messages
				specialString,				//  For special instructions
				infoString,				//  Info Text String
				errorString,				//  Error Text String	
				flightEventString;			//  In Progress/Complete/Cancelled	
	int actionNum;							//  Current Action Num
	int cPhase;							//  Current Phase Num
	int errorTimer;						//  Controls error string fade
	int numPlntsTrd;
	int curAdv;

public:
	Game();
	~Game()
	{
		delete P1;
		delete P2;
		delete universe;
		delete combatDie[ply];
		delete combatDie[prt];
		delete combatDie;
		for (int i = 0; i < FLIGHTACTIONS; i++)
			delete flightPathActions[i];
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
	void rollFlightDie();
	void rollCombatDie(int party);
	void productionPhaseListener();
	void flightPhaseListener(int tempType);
	void preFlightListener(int &tempType);
	void buildPhaseListener(int &tempNum);
	void tradeMenuListener();
	void updateFlightMenu();
	void initTradeMenu(int tempPos = -1);
	bool anyResourcesInListAvailable(int resAvail[]);
	bool allRequirementsMet(int requirements[], int size = 6);
	bool anyResAvail();
	void gainOneResource();
	void updateFriendOfThePeople();
	void updateHeroOfThePeople();
	void pirateMenuListener();
	void endPiratePhase();
	void endAdventerPhase();
	void adventureListener(int tempType);
	bool buildShipObject(int item);
	std::string getAdvReqString();
	bool startAdventure();
	void adventureRewards();
	std::string getAdvRewardsString(int res, int astro, int fame, int vic);
	void drawCurrentPlanet();
	bool isCPlanetTargeted();
	void showFlightPath();
	void createFlightMenu();
	void createBuildMenu();
	void createPirateMenu();
	void createSectorMenu();

};

#endif // BOARDGAME_H
