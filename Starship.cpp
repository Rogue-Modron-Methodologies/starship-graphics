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
//  Constructor: Calls the Object Constructor
//		
//		
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
Starship::Starship(TextureManager &txtMgr, sf::Vector2f pos, sf::Vector2f scale) : Object(txtMgr.getTexture(SRCFILE), pos, scale)
{
	resources = new Resource*[5];
	resources[Science] = new Resource(txtMgr.getTexture(ARWFILE), sf::Vector2f{ 243, 59 }, sf::Vector2u(65, 65), 1, "ScienceResource");
	resources[Ore] = new Resource(txtMgr.getTexture(ARWFILE), sf::Vector2f{ 555, 59 }, sf::Vector2u(65, 65), 1, "OreResource");
	resources[Fuel] = new Resource(txtMgr.getTexture(ARWFILE), sf::Vector2f{ 713, 59 }, sf::Vector2u(65, 65), 1, "FuelResource");
	resources[TradeGood] = new Resource(txtMgr.getTexture(ARWFILE), sf::Vector2f{ 243, 374 }, sf::Vector2u(65, 65), 1, "TradeGoodResource");
	resources[Wheat] = new Resource(txtMgr.getTexture(ARWFILE), sf::Vector2f{ 555, 374 }, sf::Vector2u(65, 65), 1, "WheatResource");
	resources[Carbon] = new Resource(txtMgr.getTexture(ARWFILE), sf::Vector2f{ 712, 374 }, sf::Vector2u(65, 65), 1, "CarbonResource");

	boosters = new Object*[3];
	boosters[B1] = new Object(txtMgr.getTexture(BSTFILE), sf::Vector2f{ 0, 125 }, sf::Vector2f(1, 1), sf::Vector2u(125, 75), sf::Vector2u(0, 0), 1, "B1");
	boosters[B2] = new Object(txtMgr.getTexture(BSTFILE), sf::Vector2f{ 0, 210 }, sf::Vector2f(1, 1), sf::Vector2u(125, 75), sf::Vector2u(0, 0), 0, "B2");
	boosters[B3] = new Object(txtMgr.getTexture(BSTFILE), sf::Vector2f{ 0, 295 }, sf::Vector2f(1, 1), sf::Vector2u(125, 75), sf::Vector2u(0, 0), 1, "B3");
	
	lasers = new Object*[3];
	lasers[L1] = new Object(txtMgr.getTexture(LSRFILE), sf::Vector2f{ 908, 125 }, sf::Vector2f(1, 1), sf::Vector2u(125, 75), sf::Vector2u(0, 0), 0, "L1");
	lasers[L2] = new Object(txtMgr.getTexture(LSRFILE), sf::Vector2f{ 908, 210 }, sf::Vector2f(1, 1), sf::Vector2u(125, 75), sf::Vector2u(0, 0), 1, "L2");
	lasers[L3] = new Object(txtMgr.getTexture(LSRFILE), sf::Vector2f{ 908, 295 }, sf::Vector2f(1, 1), sf::Vector2u(125, 75), sf::Vector2u(0, 0), 0, "L3");

	shipHold = new Object*[2];
	shipHold[H1] = new Object(txtMgr.getTexture(SHPFILE), sf::Vector2f{ 160, 190 }, sf::Vector2f(1, 1), sf::Vector2u(100, 60), sf::Vector2u(0, 0), 1, "H1");
	shipHold[H2] = new Object(txtMgr.getTexture(SHPFILE), sf::Vector2f{ 160, 250 }, sf::Vector2f(1, 1), sf::Vector2u(100, 60), sf::Vector2u(1, 0), 1, "H2");

	maxActions = 2;
}	

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Destructor - 
//		
//		
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
Starship::~Starship()
{
	delete resources[Carbon];
	delete resources[Fuel];
	delete resources[Ore];
	delete resources[Science];
	delete resources[TradeGood];
	delete resources[Wheat];
//	delete [] resources;
	delete boosters[B1];
	delete boosters[B2];
	delete boosters[B3];
//	delete [] boosters;
	delete shipHold[H1];
	delete shipHold[H2];
//	delete [] shiphold;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Draws the starship to the screen
//		Draws the components of the ships to scale with the ship.
//		
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Starship::draw(sf::RenderWindow &gWindow) 
{ 
	gWindow.draw(*sprite);					// draws the ship sprite
	for (int i = 0; i < 6; i++)
	{
		if (resources[i]->getNum() > 0)		// only draws the resource's arrows to the screen if the cargo hold contains resources. 
			resources[i]->draw(gWindow);
	}

	for (int i = 0; i < 3; i++)
	{
		if (lasers[i]->getNum() > 0)			// only draws the lasers to the screen if the lvl is above zero
			lasers[i]->draw(gWindow);
		if (boosters[i]->getNum() > 0)		// only draws the boosters to the screen if the lvl is above zero
			boosters[i]->draw(gWindow);
	}

	if (shipHold[H1]->getNum() > 0)			// only draws the ship to the screen if the qty is above zero
		shipHold[H1]->draw(gWindow);			
	if (shipHold[H2]->getNum() > 0)
		shipHold[H2]->draw(gWindow);

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
	update(resources[Science], LRGSCL);
	update(resources[Ore], LRGSCL);
	update(resources[Fuel], LRGSCL);
	update(resources[TradeGood], LRGSCL);
	update(resources[Wheat], LRGSCL);
	update(resources[Ore], LRGSCL);
	update(resources[Carbon], LRGSCL);
	update(lasers[L1], LRGSCL);
	update(lasers[L2], LRGSCL);
	update(lasers[L3], LRGSCL);
	update(boosters[B1], LRGSCL);
	update(boosters[B2], LRGSCL);
	update(boosters[B3], LRGSCL);
	update(shipHold[H1], LRGSCL);
	update(shipHold[H2], LRGSCL);
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
	update(resources[Science], SMLSCL);
	update(resources[Ore], SMLSCL);
	update(resources[Fuel], SMLSCL);
	update(resources[TradeGood], SMLSCL);
	update(resources[Wheat], SMLSCL);
	update(resources[Carbon], SMLSCL);
	update(lasers[L1], SMLSCL);
	update(lasers[L2], SMLSCL);
	update(lasers[L3], SMLSCL);
	update(boosters[B1], SMLSCL);
	update(boosters[B2], SMLSCL);
	update(boosters[B3], SMLSCL);
	update(shipHold[H1], SMLSCL);
	update(shipHold[H2], SMLSCL);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Checks all ship objects for mouse selection
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Starship::bigLeftClicked(sf::RenderWindow &gWindow, std::string &statusUpdate)
{
	if (resources[Science]->isTargeted(gWindow))
		resources[Science]->gainResource(statusUpdate);
	else if (resources[Ore]->isTargeted(gWindow))
		resources[Ore]->gainResource(statusUpdate);
	else if (resources[Fuel]->isTargeted(gWindow))
		resources[Fuel]->gainResource(statusUpdate);
	else if (resources[TradeGood]->isTargeted(gWindow))
		resources[TradeGood]->gainResource(statusUpdate);
	else if (resources[Wheat]->isTargeted(gWindow))
		resources[Wheat]->gainResource(statusUpdate);
	else if (resources[Carbon]->isTargeted(gWindow))
		resources[Carbon]->gainResource(statusUpdate);
	else if (boosters[B1]->isTargeted(gWindow))
		addBooster(B1, statusUpdate);
	else if (boosters[B2]->isTargeted(gWindow))
		addBooster(B2, statusUpdate);
	else if (boosters[B3]->isTargeted(gWindow))
		addBooster(B3, statusUpdate);
	else if (lasers[L1]->isTargeted(gWindow))
		addLaser(L1, statusUpdate);
	else if (lasers[L2]->isTargeted(gWindow))
		addLaser(L2, statusUpdate);
	else if (lasers[L3]->isTargeted(gWindow))
		addLaser(L3, statusUpdate);
	else if (shipHold[H1]->isTargeted(gWindow)) ////////////////////////////////////////////////////
		std::cout << H1;
	else if (shipHold[H2]->isTargeted(gWindow)) //////////////////////////////////////////////////// 
		std::cout << H2;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Checks all ship objects for mouse selection
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Starship::bigRightClicked(sf::RenderWindow &gWindow, std::string &statusUpdate)
{
	if (resources[Science]->isTargeted(gWindow))
		resources[Science]->loseResource(statusUpdate);
	else if (resources[Ore]->isTargeted(gWindow))
		resources[Ore]->loseResource(statusUpdate);
	else if (resources[Fuel]->isTargeted(gWindow))
		resources[Fuel]->loseResource(statusUpdate);
	else if (resources[TradeGood]->isTargeted(gWindow))
		resources[TradeGood]->loseResource(statusUpdate);
	else if (resources[Wheat]->isTargeted(gWindow))
		resources[Wheat]->loseResource(statusUpdate);
	else if (resources[Carbon]->isTargeted(gWindow))
		resources[Carbon]->loseResource(statusUpdate);
	else if (shipHold[H1]->isTargeted(gWindow)) ////////////////////////////////////////////////////
		std::cout << H1;
	else if (shipHold[H2]->isTargeted(gWindow)) ////////////////////////////////////////////////////
		std::cout << H2;

}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Adds or upgrades a laser if allowed
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Starship::addLaser(int pos, std::string &statusUpdate)
{
	if (lasers[pos]->getNum() < 2)
	{
		if (lasers[pos]->getNum() == 0)
		{
			lasers[pos]->setNum(lasers[pos]->getNum() + 1);
			lasers[pos]->setSrcPos({ 0, 0 });
			lasers[pos]->updateTextRect();
		}
		else if(lasers[L1]->getNum() >= 1 && lasers[L2]->getNum() >= 1 && lasers[L3]->getNum() >= 1)
		{
			lasers[pos]->setNum(lasers[pos]->getNum() + 1);
			lasers[pos]->setSrcPos({ 1, 0 });
			lasers[pos]->updateTextRect();
		}
		else
			statusUpdate = "All Lasers must be upgraded to Level 1!";
	}
	else
		statusUpdate = "Laser is already at maximum!";
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Adds or upgrades a booster if allowed
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Starship::addBooster(int pos, std::string &statusUpdate)
{
	if (boosters[pos]->getNum() < 2)
	{
		if (boosters[pos]->getNum() == 0)
		{
			boosters[pos]->setNum(boosters[pos]->getNum() + 1);
			boosters[pos]->setSrcPos({ 0, 0 });
			boosters[pos]->updateTextRect();
		}
		else if(boosters[B1]->getNum() >= 1 && boosters[B2]->getNum() >= 1 && boosters[B3]->getNum() >= 1)
		{
			boosters[pos]->setNum(boosters[pos]->getNum() + 1);
			boosters[pos]->setSrcPos({ 1, 0 });
			boosters[pos]->updateTextRect();
		}
		else
			statusUpdate = "All Boosters must be upgraded to Level 1!";
	}
	else
		statusUpdate = "Booster is already at maximum!";
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Updates position and scale of objects relative to the ship
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Starship::update(Object *o, sf::Vector2f scale)
{
	o->getSprite()->setScale(scale);
	o->getSprite()->setPosition((sprite->getPosition() + sf::Vector2f(o->getRelPos().x * scale.x, o->getRelPos().y * scale.y)));
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Calls individual resource gainResource function
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Starship::gainResource(int type, std::string &statusUpdate)
{ 
	if (resources[type]->gainResource(statusUpdate))
		return true;
	else
		return false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Calls individual resource loseResource function
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Starship::loseResource(int type, std::string &statusUpdate)
{
	if (resources[type]->loseResource(statusUpdate))
		return true;
	else
		return false;
}

