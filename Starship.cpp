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
Starship::Starship(std::string fileName, sf::Vector2f size, sf::Vector2f pos, sf::Vector2f scale) : Object(fileName, size, pos, scale)
{
	resources = new Resource*[5];
	resources[Science] = new Resource(ARWFILE, STDSZE, (sprite->getPosition() + sf::Vector2f(1130 * STDSCL.x, 280 * STDSCL.y)), STDSCL, sf::Vector2u(250, 250), 1, "Science");
	resources[Science]->setName("Science");
	resources[Ore] = new Resource(*resources[Science], (sprite->getPosition() + sf::Vector2f(2530 * STDSCL.x, 280 * STDSCL.y)), 1, "Ore");
	resources[Fuel] = new Resource(*resources[Science], (sprite->getPosition() + sf::Vector2f(3240 * STDSCL.x, 280 * STDSCL.y)), 1, "Fuel");
	resources[TradeGood] = new Resource(*resources[Science], (sprite->getPosition() + sf::Vector2f(1130 * STDSCL.x, 1700 * STDSCL.y)), 1, "TradeGood");
	resources[Wheat] = new Resource(*resources[Science], (sprite->getPosition() + sf::Vector2f(2530 * STDSCL.x, 1700 * STDSCL.y)), 1, "Wheat");
	resources[Carbon] = new Resource(*resources[Science], (sprite->getPosition() + sf::Vector2f(3240 * STDSCL.x, 1700 * STDSCL.y)), 1, "Carbon");
	
	boosters = new Object*[3];
	boosters[B1] = new Object(BSTFILE, STDSZE, (sprite->getPosition() + sf::Vector2f(90 * STDSCL.x, 580 * STDSCL.y)), STDSCL, sf::Vector2u(500, 500), 1);
	boosters[B2] = new Object(*boosters[L1], (sprite->getPosition() + sf::Vector2f(90 * STDSCL.x, 980 * STDSCL.y)), 0);
	boosters[B3] = new Object(*boosters[L1], (sprite->getPosition() + sf::Vector2f(90 * STDSCL.x, 1370 * STDSCL.y)), 1);
	
	lasers = new Object*[3];
	lasers[L1] = new Object(LSRFILE, STDSZE, (sprite->getPosition() + sf::Vector2f(4100 * STDSCL.x, 580 * STDSCL.y)), STDSCL, sf::Vector2u(500, 500), 0);
	lasers[L2] = new Object(*lasers[L1], (sprite->getPosition() + sf::Vector2f(4100 * STDSCL.x, 980 * STDSCL.y)), 1);
	lasers[L3] = new Object(*lasers[L1], (sprite->getPosition() + sf::Vector2f(4100 * STDSCL.x, 1370 * STDSCL.y)), 0);

	shipHold = new Object*[2];
	shipHold[H1] = new Object(SHPFILE, STDSZE, (sprite->getPosition() + sf::Vector2f(660 * STDSCL.x, 815 * STDSCL.y)), STDSCL, sf::Vector2u(1000, 500), 1);
	shipHold[H2] = new Object(*shipHold[H1], (sprite->getPosition() + sf::Vector2f(660 * STDSCL.x, 1115 * STDSCL.y)));

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
	if (resources[Science]->getNum() > 0)		// only draws the resource's arrows to the screen if the cargo hold contains resources. 
		resources[Science]->draw(gWindow);		
	if (resources[Ore]->getNum() > 0)
		resources[Ore]->draw(gWindow);
	if (resources[Fuel]->getNum() > 0)
		resources[Fuel]->draw(gWindow);
	if (resources[TradeGood]->getNum() > 0)
		resources[TradeGood]->draw(gWindow);
	if (resources[Wheat]->getNum() > 0)
		resources[Wheat]->draw(gWindow);
	if (resources[Carbon]->getNum() > 0)
		resources[Carbon]->draw(gWindow);
	if (lasers[L1]->getNum() > 0)				// only draws the lasers to the screen if the lvl is above zero
		lasers[L1]->draw(gWindow);			
	if (lasers[L2]->getNum() > 0)
		lasers[L2]->draw(gWindow);
	if (lasers[L3]->getNum() > 0)
		lasers[L3]->draw(gWindow);
	if (boosters[B1]->getNum() > 0)			// only draws the boosters to the screen if the lvl is above zero
		boosters[B1]->draw(gWindow);			 
	if (boosters[B2]->getNum() > 0)
		boosters[B2]->draw(gWindow);
	if (boosters[B3]->getNum() > 0)
		boosters[B3]->draw(gWindow);		
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
	resources[Science]->setScale(LRGSCL);
	resources[Science]->setPos((sprite->getPosition() + sf::Vector2f(1120 * LRGSCL.x, 280 * LRGSCL.y)));
	resources[Ore]->setScale(LRGSCL);
	resources[Ore]->setPos((sprite->getPosition() + sf::Vector2f(2520 * LRGSCL.x, 280 * LRGSCL.y)));
	resources[Fuel]->setScale(LRGSCL);
	resources[Fuel]->setPos((sprite->getPosition() + sf::Vector2f(3230 * LRGSCL.x, 280 * LRGSCL.y)));
	resources[TradeGood]->setScale(LRGSCL);
	resources[TradeGood]->setPos((sprite->getPosition() + sf::Vector2f(1120 * LRGSCL.x, 1700 * LRGSCL.y)));
	resources[Wheat]->setScale(LRGSCL);
	resources[Wheat]->setPos((sprite->getPosition() + sf::Vector2f(2520 * LRGSCL.x, 1700 * LRGSCL.y)));
	resources[Carbon]->setScale(LRGSCL);
	resources[Carbon]->setPos((sprite->getPosition() + sf::Vector2f(3230 * LRGSCL.x, 1700 * LRGSCL.y)));
	lasers[L1]->setScale(LRGSCL);
	lasers[L1]->setPos((sprite->getPosition() + sf::Vector2f(4100 * LRGSCL.x, 585 * LRGSCL.y)));
	lasers[L2]->setScale(LRGSCL);
	lasers[L2]->setPos((sprite->getPosition() + sf::Vector2f(4100 * LRGSCL.x, 985 * LRGSCL.y)));
	lasers[L3]->setScale(LRGSCL);
	lasers[L3]->setPos((sprite->getPosition() + sf::Vector2f(4100 * LRGSCL.x, 1370 * LRGSCL.y)));
	boosters[B1]->setScale(LRGSCL);
	boosters[B1]->setPos((sprite->getPosition() + sf::Vector2f(90 * LRGSCL.x, 580 * LRGSCL.y)));
	boosters[B2]->setScale(LRGSCL);
	boosters[B2]->setPos((sprite->getPosition() + sf::Vector2f(90 * LRGSCL.x, 980 * LRGSCL.y)));
	boosters[B3]->setScale(LRGSCL);
	boosters[B3]->setPos((sprite->getPosition() + sf::Vector2f(90 * LRGSCL.x, 1370 * LRGSCL.y)));
	shipHold[H1]->setScale(LRGSCL);
	shipHold[H1]->setPos((sprite->getPosition() + sf::Vector2f(660 * LRGSCL.x, 815 * LRGSCL.y)));
	shipHold[H2]->setScale(LRGSCL);
	shipHold[H2]->setPos((sprite->getPosition() + sf::Vector2f(660 * LRGSCL.x, 1115 * LRGSCL.y)));
}


// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Changes Starship Scale to standard for more board space
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Starship::makeSmall()
{
	smallDisplay = true;
	sprite->setScale(STDSCL);
	sprite->setPosition(STDPOS);
	resources[Science]->setScale(STDSCL);
	resources[Science]->setPos((sprite->getPosition() + sf::Vector2f(1130 * STDSCL.x, 280 * STDSCL.y)));
	resources[Ore]->setScale(STDSCL);
	resources[Ore]->setPos((sprite->getPosition() + sf::Vector2f(2530 * STDSCL.x, 280 * STDSCL.y)));
	resources[Fuel]->setScale(STDSCL);
	resources[Fuel]->setPos((sprite->getPosition() + sf::Vector2f(3240 * STDSCL.x, 280 * STDSCL.y)));
	resources[TradeGood]->setScale(STDSCL);
	resources[TradeGood]->setPos((sprite->getPosition() + sf::Vector2f(1130 * STDSCL.x, 1700 * STDSCL.y)));
	resources[Wheat]->setScale(STDSCL);
	resources[Wheat]->setPos((sprite->getPosition() + sf::Vector2f(2530 * STDSCL.x, 1700 * STDSCL.y)));
	resources[Carbon]->setScale(STDSCL);
	resources[Carbon]->setPos((sprite->getPosition() + sf::Vector2f(3240 * STDSCL.x, 1700 * STDSCL.y)));
	lasers[L1]->setScale(STDSCL);
	lasers[L1]->setPos((sprite->getPosition() + sf::Vector2f(4100 * STDSCL.x, 585 * STDSCL.y)));
	lasers[L2]->setScale(STDSCL);
	lasers[L2]->setPos((sprite->getPosition() + sf::Vector2f(4100 * STDSCL.x, 985 * STDSCL.y)));
	lasers[L3]->setScale(STDSCL);
	lasers[L3]->setPos((sprite->getPosition() + sf::Vector2f(4100 * STDSCL.x, 1370 * STDSCL.y)));
	boosters[B1]->setScale(STDSCL);
	boosters[B1]->setPos((sprite->getPosition() + sf::Vector2f(0 * STDSCL.x, 580 * STDSCL.y)));
	boosters[B2]->setScale(STDSCL);
	boosters[B2]->setPos((sprite->getPosition() + sf::Vector2f(0 * STDSCL.x, 980 * STDSCL.y)));
	boosters[B3]->setScale(STDSCL);
	boosters[B3]->setPos((sprite->getPosition() + sf::Vector2f(0 * STDSCL.x, 1370 * STDSCL.y)));
	shipHold[H1]->setScale(STDSCL);
	shipHold[H1]->setPos((sprite->getPosition() + sf::Vector2f(660 * STDSCL.x, 815 * STDSCL.y)));
	shipHold[H2]->setScale(STDSCL);
	shipHold[H2]->setPos((sprite->getPosition() + sf::Vector2f(660 * STDSCL.x, 1115 * STDSCL.y)));
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
//  Gains a resource of a chosen type
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Starship::gainResource(int type, std::string &statusUpdate)
{
	resources[type]->gainResource(statusUpdate);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Loses a resource of a chosen type
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Starship::loseResource(int type, std::string &statusUpdate)
{
	resources[type]->loseResource(statusUpdate);
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
			lasers[pos]->getSprite()->setTextureRect(sf::IntRect(lasers[pos]->getSrcPos().x * lasers[pos]->getSrcSze().y, lasers[pos]->getSrcPos().y * lasers[pos]->getSrcSze().y, lasers[pos]->getSrcSze().x, lasers[pos]->getSrcSze().y));
		}
		else if(lasers[L1]->getNum() >= 1 && lasers[L2]->getNum() >= 1 && lasers[L3]->getNum() >= 1)
		{
			lasers[pos]->setNum(lasers[pos]->getNum() + 1);
			lasers[pos]->setSrcPos({ 1, 0 });
			lasers[pos]->getSprite()->setTextureRect(sf::IntRect(lasers[pos]->getSrcPos().x * lasers[pos]->getSrcSze().y, lasers[pos]->getSrcPos().y * lasers[pos]->getSrcSze().y, lasers[pos]->getSrcSze().x, lasers[pos]->getSrcSze().y));
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
			boosters[pos]->getSprite()->setTextureRect(sf::IntRect(boosters[pos]->getSrcPos().x * boosters[pos]->getSrcSze().y, boosters[pos]->getSrcPos().y * boosters[pos]->getSrcSze().y, boosters[pos]->getSrcSze().x, boosters[pos]->getSrcSze().y));
		}
		else if(boosters[B1]->getNum() >= 1 && boosters[B2]->getNum() >= 1 && boosters[B3]->getNum() >= 1)
		{
			boosters[pos]->setNum(boosters[pos]->getNum() + 1);
			boosters[pos]->setSrcPos({ 1, 0 });
			boosters[pos]->getSprite()->setTextureRect(sf::IntRect(boosters[pos]->getSrcPos().x * boosters[pos]->getSrcSze().y, boosters[pos]->getSrcPos().y * boosters[pos]->getSrcSze().y, boosters[pos]->getSrcSze().x, boosters[pos]->getSrcSze().y));
		}
		else
			statusUpdate = "All Boosters must be upgraded to Level 1!";
	}
	else
		statusUpdate = "Booster is already at maximum!";
}