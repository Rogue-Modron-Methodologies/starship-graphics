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
#include "Resource.h"
#include "BoosterLaser.h"
#include "HangarShips.h"
#include "ShipObject.h"
#include "Icon.h"
#include "Module.h"
#include "Card.h"

const sf::Vector2f SMLPOS = sf::Vector2f(20, 700);		//  Screen Position for Standard Scale Starship
const sf::Vector2f SMLSCL = sf::Vector2f(.25f, .25f);		//  Standard Scale for Starship;
const sf::Vector2f LRGPOS = sf::Vector2f(40, 100);		//  Screen Position for Large Scale Starship
const sf::Vector2f LRGSCL = sf::Vector2f(1.0f, 1.0f);		//  Large Scale for Starship
const std::string SRCFILE = "resources/board/ship.png";	//  Source File name for StarShip
const int CLKNUM = 14;								//  Number of clickable objects on the starship


class Starship : public Object
{
private:
	ShipObject** shipObjects;		//  Array of all clickable ship objects
	int maxActions;				//  Max actions in the flight phase
	int maxMovement;				//  Max movement in the flight phase


public:
	Starship(ResourceManager<sf::Texture> &txtMgr, ResourceManager<sf::Font> &fntMgr, sf::Vector2f pos = SMLPOS);
	~Starship();

	//  Getters/Setters
	int getMaxDistance() const  { return 10 /* maxMovement*/; } ///////////////////////////// debugging ONLY
	int getMaxActions() const  { return maxActions; }
	int getShipObjectQty(int type){ return shipObjects[type]->getQty(); }
	void setShipObjectQty(int type, int num){ shipObjects[type]->setQty(num); }

	//  Misc Inline Functions
	void calcMaxDistance(int dieRoll)  { maxMovement = (dieRoll + totalBoosters()); }	
	int totalLasers() { return shipObjects[L1]->getQty() + shipObjects[L2]->getQty() + shipObjects[L3]->getQty(); }			// used in combat
	int totalBoosters()  { return shipObjects[B1]->getQty() + shipObjects[B2]->getQty() + shipObjects[B3]->getQty(); }			// called by calcMaxDistance and events	
	bool shipAvailable(int type, int &hanger, std::string &error);
	bool holdFull(int resource) { return shipObjects[resource]->getQty() >= shipObjects[resource]->getRCap(); }

	//  Prototypes
	void draw(sf::RenderWindow &window);
	void makeSmall();
	void makeBig();
	bool bigLeftClicked(sf::RenderWindow &window, std::string &statusUpdate, int &tempNum);
	bool bigRightClicked(sf::RenderWindow &window, std::string &statusUpdate, int &tempNum);
	void update(ShipObject *o, sf::Vector2f scale = { 1, 1 });	
	bool gainItem(int type, std::string &statusUpdate);
	bool loseItem(int type, std::string &statusUpdate);
	void updateShipIcons();
	
};

#endif // STARSHIP_H