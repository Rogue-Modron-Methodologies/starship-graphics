//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#ifndef STARSHIP_H
#define STARSHIP_H

#include <iostream>
#include <iomanip>
#include <string>
#include "Object.h"
#include "Resource.h"
#include "Module.h"
#include "Card.h"

enum Booster {B1, B2, B3};
enum Laser {L1, L2, L3};
enum ShipHold {H1, H2};
enum Ships {empty, tradeShip, colonyShip};
const sf::Vector2f STDPOS = sf::Vector2f(20, 700);		//  Screen Position for Standard Scale Starship
const sf::Vector2f STDSZE = sf::Vector2f(600, 450);		//  Standard Size for StarShip
const sf::Vector2f STDSCL = sf::Vector2f(.05f, .05f);		//  Standard Scale for Starship;
const sf::Vector2f LRGPOS = sf::Vector2f(40, 100);		//  Screen Position for Large Scale Starship
const sf::Vector2f LRGSCL = sf::Vector2f(.2f, .2f);		//  Large Scale for Starship
const std::string SRCFILE = "resources/board/ship.png";		//  Source File name for StarShip
const std::string ARWFILE = "resources/board/arrows.png";		//  Source File name for resource arrows
const std::string BSTFILE = "resources/board/boosters.png";		//  Source file name for boosters
const std::string LSRFILE = "resources/board/lasers.png";		//  Source file name for lasers
const std::string SHPFILE = "resources/board/ships.png";		//  Source file name for trade/colony


class Starship : public Object
{
private:
	Resource **resources;			//  Array of the 5 resources in the game
	Object **lasers;				//  Pointer to array of three lasers
	Object **boosters;				//  Pointer to array of three lasers
	Object **shipHold;				//  Pointer to array of two ships (Trade/Colony)
	int rCap;						//  Max resources a player may have in a hold
	int maxActions;				//  Max actions in the flight phase
	int maxMovement;				//  Max movement in the flight phase


public:
	Starship(std::string fileName = SRCFILE, sf::Vector2f size = STDSZE, sf::Vector2f pos = STDPOS, sf::Vector2f scale = STDSCL);
	~Starship();
	//Getters and Setters
	int getRCap() const  { return rCap;	}
//	int getResQty(int type)  { return resource[type];	}

	// Misc Inline Functions
	//bool haveShip(char type)	 { return (getH1() == type || getH2() == type); }
	//char getShip(int num) const  { return shipHold[num]; }
	//char getH1()  { return shipHold[H1]; }
	//char getH2()  { return shipHold[H2]; }
	//void setH1(char type)  { shipHold[H1] = type; }
	//void setH2(char type)  { shipHold[H2] = type; }
	//void removeTradeShip()  { getH1() == 'T' ? setH1(' ') : setH2(' '); }
	//void removeColonyShip()  { getH1() == 'C'? setH1(' ') : setH2(' '); }
//	void setMaxActions(int num)  { this->maxActions = num;	}						// called by a module
	void calcMaxDistance(int dieRoll)  { maxMovement = (dieRoll + totalBoosters()); }	// called in Flight Phase
	int getMaxDistance() const  { return maxMovement;	}
//	int getMaxActions() const  { return maxActions; }
	int totalBoosters()  { return boosters[B1]->getNum() + boosters[B2]->getNum() + boosters[B3]->getNum(); }			// called by calcMaxDistance and events	
//	int totalLasers()  { return laser[0] + laser[1] + laser[2];	}					// called by events and combat 
	// Prototypes
	void draw(sf::RenderWindow &window);
	void addLaser(int pos, std::string &statusUpdate);
	void addBooster(int pos, std::string &statusUpdate);
	bool modAstro(int num);
	std::string getResName(int type);
	bool modResource(int num, int type, int cost = 0);
	void makeSmall();
	void makeBig();
	void bigLeftClicked(sf::RenderWindow &window, std::string &statusUpdate);
	void bigRightClicked(sf::RenderWindow &window, std::string &statusUpdate); 
	void gainResource(int type, std::string &statusUpdate);
	void loseResource(int type, std::string &statusUpdate);
	
	
};

#endif // STARSHIP_H