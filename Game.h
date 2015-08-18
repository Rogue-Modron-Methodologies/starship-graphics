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

class Game{
private:
	Player *P1, *P2, *cPlyr;
	Universe *universe;
	sf::RenderWindow gWindow;
	sf::Vector2u screenSize;
	ResourceManager<sf::Texture> txtMgr;
	sf::Font font;
	int actionNum;
	int cPhase;						//  Current Phase Num
	sf::Text phaseNameString;			//  Phase Name Text String
	sf::Text specialString;				//  For End of Phase Messages (And Sector Selection)
	sf::Text errorString;				//  Error Text String
	std::string statusUpdate;			//  Catches errors from called functions
	sf::Text infoString;				//  Info Text String
	sf::Text cPlanet;					//  Current Planet Text String
	Icon tradeMenuIcons[4];				//  Icons for the Trade Menu
	int errorTimer;
	Icon flightDie;
	int combatDie[6];
	bool phaseSetupComplete;				//  Flag 
	bool gainProductionResource;			//  Flag for enabling free colony resource
	bool displayFlightPath;				//  Flag for displaying flightPath (so it isn't displayed when focusing on the starship)
	bool displaySectors;				//  Flag for displaying Sectors (so it isn't displayed when focusing on the starship)
	bool sectorSelected;				//  Flag for whether a sector has been chosen this turn
	bool phaseComplete;					//  Flag 
	bool displayFlightMenu;				//  Flag
	bool tradeComplete;					//  Flag
	bool justTraded;					//  Flag

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
	Player* getP1() const
	{	return P1;  }
	Player* getP2() const
	{	return P2;  }
	Universe* getUniverse() const
	{	return universe;	}


	int rollCombatDie()
	{	return combatDie[rand() % 6];	}
	void startGame()
	{	gameLoop();	};

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
	void flightPhaseSectorSelectionListener(sf::RenderWindow &gWindow, int &tempType);
	void tradePhaseListener(sf::RenderWindow &gWindow);
	void buildPhaseListener(sf::RenderWindow &gWindow);
	void tradeMenu(sf::RenderWindow &gWindow, int tempType);
	void drawFlightMenu(sf::RenderWindow &gWindow);
	void updateFlightMenu(sf::RenderWindow &gWindow);
	void drawFlightPath(sf::RenderWindow &gWindow);
	void drawCurrentPlanet(sf::RenderWindow &gWindow);
	void updateTradeMenu(sf::RenderWindow &gWindow, int tempType);

};

#endif // BOARDGAME_H
