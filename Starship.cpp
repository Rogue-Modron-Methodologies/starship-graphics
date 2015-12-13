//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#include "Starship.h"

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//	Constructor: Calls the Object Constructor	
//		
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
Starship::Starship(ResourceManager<sf::Texture> &txtMgr, ResourceManager<sf::Font> &fntMgr, sf::Vector2f pos) : Object(txtMgr.getResource(SRCFILE), pos)
{
	shipObjects = new ShipObject*[CLKNUM];			// will be higher once modules are included

	shipObjects[Science] = new Resource(txtMgr.getResource(ARWFILE), sf::Vector2f{ 207, 51 }, sf::Vector2u(55, 55), 1, "Science");
	shipObjects[Ore] = new Resource(txtMgr.getResource(ARWFILE), sf::Vector2f{ 472, 51 }, sf::Vector2u(55, 55), 0, "Ore");
	shipObjects[Fuel] = new Resource(txtMgr.getResource(ARWFILE), sf::Vector2f{ 606, 51 }, sf::Vector2u(55, 55), 0, "Fuel");
	shipObjects[TradeGood] = new Resource(txtMgr.getResource(ARWFILE), sf::Vector2f{ 207, 318 }, sf::Vector2u(55, 55), 1, "TradeGood");
	shipObjects[Wheat] = new Resource(txtMgr.getResource(ARWFILE), sf::Vector2f{ 472, 318 }, sf::Vector2u(55, 55), 0, "Wheat");
	shipObjects[Carbon] = new Resource(txtMgr.getResource(ARWFILE), sf::Vector2f{ 606, 318 }, sf::Vector2u(55, 55), 0, "Carbon");

	shipObjects[B1] = new BoosterLaser(txtMgr.getResource(BSTFILE), sf::Vector2f{ 0, 110 }, 1, sf::Vector2u(105, 63));
	shipObjects[B2] = new BoosterLaser(txtMgr.getResource(BSTFILE), sf::Vector2f{ 0, 180 }, 0, sf::Vector2u(105, 63));
	shipObjects[B3] = new BoosterLaser(txtMgr.getResource(BSTFILE), sf::Vector2f{ 0, 250 }, 1, sf::Vector2u(105, 63));

	shipObjects[L1] = new BoosterLaser(txtMgr.getResource(LSRFILE), sf::Vector2f{ 770, 110 }, 0, sf::Vector2u(105, 63));
	shipObjects[L2] = new BoosterLaser(txtMgr.getResource(LSRFILE), sf::Vector2f{ 770, 180 }, 1, sf::Vector2u(105, 63));
	shipObjects[L3] = new BoosterLaser(txtMgr.getResource(LSRFILE), sf::Vector2f{ 770, 250 }, 0, sf::Vector2u(105, 63));

	shipObjects[H1] = new HangarShips(txtMgr.getResource(SHPFILE), sf::Vector2f{ 131, 161 }, sf::Vector2u(85, 50), 1, colonyShip, sf::Vector2u(0, 0));	
	shipObjects[H2] = new HangarShips(txtMgr.getResource(SHPFILE), sf::Vector2f{ 131, 212 }, sf::Vector2u(85, 50), 1, tradeShip, sf::Vector2u(1, 0));	
	
	maxActions = 2;		
}	

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Destructor - 
//		
//		
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
Starship::~Starship()
{
	for (int i = 0; i < CLKNUM; i++)
		delete shipObjects[i];
	delete shipObjects;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Draws the starship to the screen
//		Draws the components of the ships to scale with the ship.
//		
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Starship::draw(sf::RenderWindow &gWindow) 
{ 
	gWindow.draw(*sprite);					// draws the ship sprite
	for (int i = 0; i < CLKNUM; i++)
	{
		if (shipObjects[i]->getQty() > 0)		// only draws the object to the screen if qty is above 0. 
			shipObjects[i]->draw(gWindow);
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Changes Starship Scale to large for better viewing
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Starship::makeBig()
{
	smallDisplay = false;
	sprite->setScale(LRGSCL);
	sprite->setPosition(LRGPOS);
	for (int i = 0; i < CLKNUM; i++)
		update(shipObjects[i]);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Changes Starship Scale to standard for more board space
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Starship::makeSmall()
{
	smallDisplay = true;
	sprite->setScale(SMLSCL);
	sprite->setPosition(SMLPOS);
	for (int i = 0; i < CLKNUM; i++)
		update(shipObjects[i], SMLSCL);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Checks availability of item and returns location number if true
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Starship::checkBuildItemAvailability(int &num, std::string &statusUpdate)
{
	int tempNum = num;
	num = -1;
	switch (tempNum)
	{
	case B1:
		if (shipObjects[B1]->getQty() == 0)
			num = B1;
		else if (shipObjects[B2]->getQty() == 0)
			num = B2;
		else if (shipObjects[B3]->getQty() == 0)
			num = B3;
		else
		{
			statusUpdate = "No available booster locations!";
			return false;
		}
		return true;
	case B2:		
		if (areBoostersMaxed())
		{
			statusUpdate = "Boosters are already at maximum!";
			return false;
		}
		else if (shipObjects[B1]->getQty() >= 1 && shipObjects[B2]->getQty() >= 1 && shipObjects[B3]->getQty() >= 1)
		{
			if (shipObjects[B1]->getQty() == 1)
				num = B1;
			else if (shipObjects[B2]->getQty() == 1)
				num = B2;
			else if (shipObjects[B3]->getQty() == 1)
				num = B3;
			return true;
		}
		else
			statusUpdate = "All lasers must be upgraded to Level 1!";
		return false;
	case L1:
		if (shipObjects[L1]->getQty() == 0)
			num = L1;
		else if (shipObjects[L2]->getQty() == 0)
			num = L2;
		else if (shipObjects[L3]->getQty() == 0)
			num = L3;
		else
		{
			statusUpdate = "No available laser locations!";
			return false;
		}
		return true;
	case L2:
		if (areLasersMaxed())
		{
			statusUpdate = "Lasers are already at maximum!";
			return false;
		}
		else if (shipObjects[L1]->getQty() >= 1 && shipObjects[L2]->getQty() >= 1 && shipObjects[L3]->getQty() >= 1)
		{
			if (shipObjects[L1]->getQty() == 1)
				num = L1;
			else if (shipObjects[L2]->getQty() == 1)
				num = L2;
			else if (shipObjects[L3]->getQty() == 1)
				num = L3;
			return true;
		}
		else
			statusUpdate = "All lasers must be upgraded to Level 1!";
		return false;
	case H1:
		if (!areHangersFull())
		{
			num = shipObjects[H1]->getQty() == 0 ? H1 : H2;
			return true;
		}
		statusUpdate = "Hangars are full!";
		return false;
	default:
		std::cout << "Check Availablility Default message:  THIS SHOULD NEVER PRINT!!\n";
		return false;
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Checks all ship objects for mouse selection
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Starship::bigLeftClicked(sf::RenderWindow &gWindow, std::string &statusUpdate, int &tempNum)
{
	for (int i = 0; i < CLKNUM; i++)
	{
		if (shipObjects[i]->isTargeted(gWindow) && gainItem(i, statusUpdate))
		{
			tempNum = i;
			return true;
		}		
	}	
	return false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Checks all ship objects for mouse selection
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Starship::bigRightClicked(sf::RenderWindow &gWindow, std::string &statusUpdate, int &tempNum)
{
	for (int i = 0; i < CLKNUM; i++)
	{
		if (shipObjects[i]->isTargeted(gWindow) && loseItem(i, statusUpdate))
		{
			tempNum = i;
			return true;			
		}
	}
	return false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Updates position and scale of objects relative to the ship
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Starship::update(ShipObject *o, sf::Vector2f scale)
{
	o->setScale(scale);
	o->setPosition((sprite->getPosition() + sf::Vector2f(o->getRelPos().x * scale.x, o->getRelPos().y * scale.y))); //////////////////////////////////////
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Calls individual resource gainResource function
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Starship::gainItem(int pos, std::string &statusUpdate, int type)
{ 
	switch (pos)
	{
	case Carbon:
	case Fuel:
	case Ore:
	case Science:
	case TradeGood:
	case Wheat:
		if (shipObjects[pos]->gainItem(statusUpdate))
			return true;
		else
			return false;
		break;
	case B1:
	case B2:
	case B3:
		if (shipObjects[pos]->getQty() < 2)
		{
			if (shipObjects[pos]->getQty() == 0)
			{
				shipObjects[pos]->gainItem(statusUpdate);
				return true;
			}
			else if (shipObjects[B1]->getQty() >= 1 && shipObjects[B2]->getQty() >= 1 && shipObjects[B3]->getQty() >= 1)
			{
				shipObjects[pos]->gainItem(statusUpdate);
				return true;
			}
			else{
				statusUpdate = "All boosters must be upgraded to Level 1!";
				return false;
			}
		}
		statusUpdate = "Booster already at maximum!";
		return false;
		break;
	case L1:
	case L2:
	case L3:
		if (shipObjects[pos]->getQty() < 2)
		{
			if (shipObjects[pos]->getQty() == 0)
			{
				shipObjects[pos]->gainItem(statusUpdate);
				return true;
			}
			else if (shipObjects[L1]->getQty() >= 1 && shipObjects[L2]->getQty() >= 1 && shipObjects[L3]->getQty() >= 1)
			{
				shipObjects[pos]->gainItem(statusUpdate);
				return true;
			}
			else
			{
				statusUpdate = "All Lasers must be upgraded to Level 1!";
				return false;
			}
		}
		statusUpdate = "Laser already at maximum!";
		return false;
		break;
	case H1:
	case H2:
		if (shipObjects[pos]->gainItem(type, statusUpdate))
			return true;
		else
			return false;
		break;
	default:
		return false;

	};
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Calls individual resource loseResource function
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Starship::loseItem(int pos, std::string &statusUpdate, int type)
{
	switch (pos)
	{
	case Carbon:
	case Fuel:
	case Ore:
	case Science:
	case TradeGood:
	case Wheat:
		if (shipObjects[pos]->loseItem(statusUpdate))
			return true;
		else
			return false;
		break;
	case B1:
	case B2:
	case B3:
		if (shipObjects[pos]->getQty() > 0)
		{
			shipObjects[pos]->loseItem(statusUpdate);
			return true;
		}
		statusUpdate = "No Booster to Lose!";
		return false;
		break;
	case L1:
	case L2:
	case L3:
		if (shipObjects[pos]->getQty() > 0)
		{
			shipObjects[pos]->loseItem(statusUpdate);
			return true;
		}
		statusUpdate = "No Laser to Lose!";
		return false;
		break;
	case H1:
	case H2:
		if (shipObjects[pos]->loseItem(statusUpdate))
			return true;
		else
			return false;
		break;
		break;
	default:
		return false;
	}
}

bool Starship::resourceAvailable(int type, int qty, std::string &statusUpdate) 
{ 
	if (qty <= shipObjects[type]->getQty())
		return true;
	statusUpdate = "Resource Requirement Not Met";
	return false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Restores shipObject quantities to a set value/position
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Starship::updateShipIcons()
{
	for (int i = 0; i < CLKNUM; i++)
		shipObjects[i]->updateTextRect();
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Checks to see if the proper ship is in the hangar 
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Starship::shipAvailabletoCompleteAction(int type, int &hanger, std::string &error)
{
	if (shipObjects[H1]->getType() == type && shipObjects[H1]->getQty() > 0)
	{
		hanger = H1;
		return true;
	}
	else if (shipObjects[H2]->getType() == type && shipObjects[H2]->getQty() > 0)
	{
		hanger = H2;
		return true;
	}
	error = "No ship in Hangar can complete this action!";
	return false;
}