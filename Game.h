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

const int CARDLISTSIZE = 71;					//  number of cards in the deck
const std::string CARDLIST = "starship.csv";
const std::string ADVENTURELIST = "starship2.csv";
const std::string SDIEFLE = "resources/board/flightdie.png";

enum Phases{ production, flight, trades, build };

class Game{
private:
	Player *P1, *P2;
	Player *cPlyr;
	Universe *universe;
	sf::View view;
	sf::RenderWindow gWindow;
	sf::Vector2u screenSize;
	sf::FloatRect visibleArea;
	sf::Font font;
	int cPhase;						//  Current Phase Num
	sf::Text phaseNameString;			//  Phase Name Text String
	sf::Text errorString;				//  Error Text String
	std::string statusUpdate;			//  Catches errors from called functions
	sf::Text infoString;				//  Info Text String
	int errorTimer;
	Icon flightDie;
	int combatDie[6];
	bool phaseSetupComplete;				//  Flag 
	bool gainProductionResource;			//  Flag for enabling free colony resource
	bool phaseComplete;					//  Flag

public:
	Game();
	~Game()
	{
		delete P1;
		delete P2;
		delete universe;
		delete flightDie.icon;
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

};

#endif // BOARDGAME_H

//  THIS IS TEMP HOLDING SPOT UNTIL I MAKE SURE THE CHANGES I MAD TO GAME.CPP AREN"T BREAKING ANYTHING -----------------------------  will be deleted
//while (gWindow.isOpen())
//{
//	if (!phaseSetupComplete)
//		phaseSetup();
//	switch (cPhase)
//	{
//	case production:
//		while (gWindow.pollEvent(event))		// the event loop
//		{
//			switch (event.type) {
//			case sf::Event::Closed:
//				gWindow.close();
//				break;
//			case sf::Event::KeyPressed:
//				if (event.key.code == sf::Keyboard::Escape)
//					gWindow.close();
//				if (event.key.code == sf::Keyboard::Return && phaseComplete)
//					endPhase();
//				break;
//			case sf::Event::MouseButtonPressed:
//				// Colony Zone (Large Icon) is clicked
//				if (!cPlyr->getColonyZone()->isSmall() && cPlyr->getColonyZone()->showIconOnly() && cPlyr->getColonyZone()->isIconTargeted(gWindow))
//				{
//					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//						cPlyr->expandColonyZone();
//					else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
//						cPlyr->makeBig();
//				}
//				else if (!cPlyr->getTradeZone()->isSmall() && cPlyr->getTradeZone()->showIconOnly() && cPlyr->getTradeZone()->isIconTargeted(gWindow))
//				{
//					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//						cPlyr->expandTradeZone();
//					else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
//						cPlyr->makeBig();
//				}
//				// Colony Zone (Large List) is clicked and player is entitled to a production resource
//				else if (!cPlyr->getColonyZone()->isSmall() && !cPlyr->getColonyZone()->showIconOnly() && cPlyr->getColonyZone()->isZoneTargeted(gWindow, tempType))
//				{
//					if (gainProductionResource && sf::Mouse::isButtonPressed(sf::Mouse::Left))
//						if (cPlyr->getStarship()->gainResource(tempType, statusUpdate))
//						{
//							phaseComplete = true;
//							gainProductionResource = false;
//							infoString.setString("Press Enter to End Phase");
//						}
//				}
//			}
//		}
//		break;
//	case flight:
//		while (gWindow.pollEvent(event))
//		{
//			switch (event.type) {
//			case sf::Event::Closed:
//				gWindow.close();
//				break;
//			case sf::Event::Resized:
//
//			case sf::Event::KeyPressed:
//				if (event.key.code == sf::Keyboard::Escape)
//					gWindow.close();
//				if (event.key.code == sf::Keyboard::Return)
//					endPhase();
//				break;
//			}
//		}
//		break;
//	case trades:
//		while (gWindow.pollEvent(event))
//		{
//			switch (event.type) {
//			case sf::Event::Closed:
//				gWindow.close();
//				break;
//			case sf::Event::KeyPressed:
//				if (event.key.code == sf::Keyboard::Escape)
//					gWindow.close();
//				if (event.key.code == sf::Keyboard::Return)
//					endPhase();
//				break;
//			}
//		}
//		break;
//	case build:
//		while (gWindow.pollEvent(event))
//		{
//			switch (event.type) {
//			case sf::Event::Closed:
//				gWindow.close();
//				break;
//			case sf::Event::KeyPressed:
//				if (event.key.code == sf::Keyboard::Escape)
//					gWindow.close();
//				if (event.key.code == sf::Keyboard::Return)
//					endPhase();
//				break;
//
//			case sf::Event::MouseMoved:
//				std::cout << std::endl;
//				if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall())
//				{
//					std::cout << "P1 Ship Glows" << std::endl;
//				}
//				break;
//			case sf::Event::MouseButtonPressed:
//				// Starship (Small) is clicked
//				if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall())
//				{
//					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//						cPlyr->makeBig();
//				}
//				// Starship (Large) is clicked
//				else if (cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall())
//				{
//					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//						cPlyr->getStarship()->bigLeftClicked(gWindow, statusUpdate);
//					else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
//						cPlyr->getStarship()->bigRightClicked(gWindow, statusUpdate);
//				}
//				// Colony Zone (Large Icon) is clicked
//				else if (!cPlyr->getColonyZone()->isSmall() && cPlyr->getColonyZone()->showIconOnly() && cPlyr->getColonyZone()->isIconTargeted(gWindow))
//				{
//					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//						cPlyr->expandColonyZone();
//					else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
//						cPlyr->makeBig();
//				}
//				else if (!cPlyr->getTradeZone()->isSmall() && cPlyr->getTradeZone()->showIconOnly() && cPlyr->getTradeZone()->isIconTargeted(gWindow))
//				{
//					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//						cPlyr->expandTradeZone();
//					else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
//						cPlyr->makeBig();
//				}
//				// Colony Zone (Large List) is clicked
//				else if (!cPlyr->getColonyZone()->isSmall() && !cPlyr->getColonyZone()->showIconOnly() && cPlyr->getColonyZone()->isZoneTargeted(gWindow, tempType))
//				{
//					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//						cPlyr->getStarship()->gainResource(tempType, statusUpdate);
//					else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
//						cPlyr->getStarship()->loseResource(tempType, statusUpdate);
//				}
//				// Trade Zone (Large List) is clicked
//				else if (!cPlyr->getTradeZone()->isSmall() && !cPlyr->getTradeZone()->showIconOnly() && cPlyr->getTradeZone()->isZoneTargeted(gWindow, tempType))
//				{
//					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//						cPlyr->getStarship()->gainResource(tempType, statusUpdate);
//					else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
//						cPlyr->getStarship()->loseResource(tempType, statusUpdate);
//				}
//				//  Starship (Large) && Empty Space is clicked
//				else if (!cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall())
//				{
//					cPlyr->makeSmall();
//				}
//			}
//		}
//		break;
//	}
//
//	gWindow.clear();
//	updateGameWindow(gWindow);
//	gWindow.display();
//}
//}