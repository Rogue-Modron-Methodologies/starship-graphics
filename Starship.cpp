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
	shipObjects[Ore] = new Resource(txtMgr.getResource(ARWFILE), sf::Vector2f{ 472, 51 }, sf::Vector2u(55, 55), 1, "Ore");
	shipObjects[Fuel] = new Resource(txtMgr.getResource(ARWFILE), sf::Vector2f{ 606, 51 }, sf::Vector2u(55, 55), 1, "Fuel");
	shipObjects[TradeGood] = new Resource(txtMgr.getResource(ARWFILE), sf::Vector2f{ 207, 318 }, sf::Vector2u(55, 55), 1, "TradeGood");
	shipObjects[Wheat] = new Resource(txtMgr.getResource(ARWFILE), sf::Vector2f{ 472, 318 }, sf::Vector2u(55, 55), 1, "Wheat");
	shipObjects[Carbon] = new Resource(txtMgr.getResource(ARWFILE), sf::Vector2f{ 606, 318 }, sf::Vector2u(55, 55), 1, "Carbon");

	shipObjects[B1] = new BoosterLaser(txtMgr.getResource(BSTFILE), sf::Vector2f{ 0, 110 }, 1, sf::Vector2u(105, 63));
	shipObjects[B2] = new BoosterLaser(txtMgr.getResource(BSTFILE), sf::Vector2f{ 0, 180 }, 0, sf::Vector2u(105, 63));
	shipObjects[B3] = new BoosterLaser(txtMgr.getResource(BSTFILE), sf::Vector2f{ 0, 250 }, 1, sf::Vector2u(105, 63));

	shipObjects[L1] = new BoosterLaser(txtMgr.getResource(LSRFILE), sf::Vector2f{ 770, 110 }, 0, sf::Vector2u(105, 63));
	shipObjects[L2] = new BoosterLaser(txtMgr.getResource(LSRFILE), sf::Vector2f{ 770, 180 }, 1, sf::Vector2u(105, 63));
	shipObjects[L3] = new BoosterLaser(txtMgr.getResource(LSRFILE), sf::Vector2f{ 770, 250 }, 0, sf::Vector2u(105, 63));

	shipObjects[H1] = new ShipObject(txtMgr.getResource(SHPFILE), sf::Vector2f{ 131, 161 }, 1, sf::Vector2u(85, 50));
	shipObjects[H2] = new ShipObject(txtMgr.getResource(SHPFILE), sf::Vector2f{ 131, 212 }, 1, sf::Vector2u(85, 50), sf::Vector2u(1, 0));
	
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
bool Starship::gainItem(int pos, std::string &statusUpdate)
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
			else{
				statusUpdate = "All Lasers must be upgraded to Level 1!";
				return false;
			}
		}
		statusUpdate = "Laser already at maximum!";
		return false;
		break;
	case H1:
	case H2:
		return true;
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
bool Starship::loseItem(int pos, std::string &statusUpdate)
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
		return true;
		break;
	default:
		return false;
	}
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