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

enum Phases{ production, flight, trades, build };
enum tradeIcons{plus, minus, check, cancel};

const int FLAGNUM = 9;
enum flagTypes{
	phaseSetupComplete,				//  Flag:  Phase Setup Complete
	gainResource,					//  Flag:  Choose one resource
	visFlightPath,					//  Flag:  Display flightPath
	visSectors,					//  Flag:  Display Sectors
	sectorSelected,				//  Flag:  Sector Selection Complete
	phaseComplete,					//  Flag:  Phase Complete
	visFlightMenu,					//  Flag:	 Display Flight Menu
	tradeInProgress,				//  Flag:  Trade in Progress
	justTraded					//  Flag:  Traded Already
};

class Game{
private:
	Player *P1, *P2, *cPlyr;
	Universe *universe;
	sf::RenderWindow gWindow;
	sf::Vector2u screenSize;
	ResourceManager<sf::Texture> txtMgr;
	bool flag[9];						//  Will hold an array of flags for game decisions
	sf::Font font;						//  Font for Texts
	sf::Text phaseNameString;			//  Phase Name Text String
	sf::Text specialString;				//  For End of Phase Messages (And Sector Selection)
	sf::Text infoString;				//  Info Text String
	sf::Text cPlanet;					//  Current Planet Text String
	sf::Text errorString;				//  Error Text String
	std::string statusUpdate;			//  Catches errors from called functions	
	Icon tradeMenuIcons[4];				//  Icons for the Trade Menu
	Icon flightDie;
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
		delete flightDie.icon;
		for (int i = 0; i < 4; i++)
			delete tradeMenuIcons[i].icon;
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

};

#endif // BOARDGAME_H
