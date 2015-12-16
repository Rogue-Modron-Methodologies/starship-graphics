//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#include "Player.h"

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Constructor
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
Player::Player(ResourceManager<sf::Texture> &txtMgr, ResourceManager<sf::Font> &fntMgr, std::string name, int num)
	: statistics(fntMgr)
{
	starship = new Starship(txtMgr, fntMgr);
	colonyZone = new Zone<ColonyCard>(txtMgr, fntMgr, "Colony");
	tradeZone = new Zone<TradeCard>(txtMgr, fntMgr, "Trade");
	pirateZone = new Zone<Pirate>(txtMgr, fntMgr, "Pirate");
	advZone = new Zone<AdventureCard>(txtMgr, fntMgr, "Adventure");
	createSectorMenu(txtMgr, fntMgr, name, num);
	bool friendOfThePeople = false;
	bool heroOfThePeople = false;
}
 
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)  
//  Destructor
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
Player::~Player()
{
	delete starship;
	delete colonyZone;
	delete tradeZone;
	delete pirateZone;
	delete advZone;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Updates an Icons Qty
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::updateIcon(int type)
{
	if (type < astro)	//  All the tradable resources
	{
		int tempNum = starship->getShipObjectQty(type);
		statistics.setItemQty(type, tempNum);
		statistics.setItemString(type, std::to_string(statistics.getItemQty(type)));
	}
	else if (type == astro)
		statistics.setItemString(astro, std::to_string(statistics.getItemQty(astro)));
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Draws the Member Zones and Menu
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::draw(sf::RenderWindow &gWindow)
{
	starship->draw(gWindow);
	colonyZone->draw(gWindow);
	tradeZone->draw(gWindow);
	statistics.draw(gWindow);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Expands StarShip, Colony Zone, and Trade Zone
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::makeBig()
{
	starship->makeBig();
	colonyZone->updateZone(CLPOS, CRDZNSCL, true);
	tradeZone->updateZone(TLPOS, CRDZNSCL, true);
	smallDisplay = false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Reduces StarShip, Colony Zone, and Trade Zone
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::makeSmall()
{
	starship->makeSmall();
	colonyZone->updateZone(CSPOS, CRDSSCL, true);
	tradeZone->updateZone(TSPOS, CRDSSCL, true);
	smallDisplay = true;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Expands the Colony Zone and moves Trade to the far right
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::expandColonyZone()
{
	colonyZone->updateZone(CLPOS, CRDZNSCL, false);
	tradeZone->updateZone(sf::Vector2f(1050, 610), CRDZNSCL, true);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Expands the Trade Zone and moves Colony to the far right
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::expandTradeZone()
{
	tradeZone->updateZone(CLPOS, CRDZNSCL, false);
	colonyZone->updateZone(sf::Vector2f(1050, 610), CRDZNSCL, true);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Fills the Holds to 4  (To be removed)
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::fillHolds()
{
	std::cout << "Cargo Holds Filled" << std::endl;
	for (int i = 0; i < 6; i++)
		starship->setShipObjectQty(i, 4);
	starship->updateShipIcons();
	for (int i = 0; i < 6; i++)
	{
		starship->setShipObjectQty(i, 4);
		updateIcon(i);
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
// Adds the indicated qty of Fame Points and updates the string
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::addFmPt(int num)
{
	statistics.setItemQty(fmPt, statistics.getItemQty(fmPt) + num);
	statistics.setItemString(fmPt, std::to_string(statistics.getItemQty(fmPt)));
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
// Adds the indicated qty of Friend Points and updates the string
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::addFrdPt(int num)
{
	statistics.setItemQty(frdPt, statistics.getItemQty(frdPt) + num);
	statistics.setItemString(frdPt, std::to_string(statistics.getItemQty(frdPt)));
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
// Subtracts the indicated qty of astro and updates the string
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::subAstro(int num)
{
	statistics.setItemQty(astro, statistics.getItemQty(astro) - num);
	statistics.setItemString(astro, std::to_string(statistics.getItemQty(astro)));
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
// Adds the indicated qty of astro and updates the string
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::addAstro(int num)
{
	statistics.setItemQty(astro, statistics.getItemQty(astro) + num);
	statistics.setItemString(astro, std::to_string(statistics.getItemQty(astro)));
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Tests to see if the astro qty is >= the passed number
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Player::canAfford(int num, std::string &statusUpdate)
{
	if (num <= statistics.getItemQty(astro))
		return true;
	statusUpdate = "Can not afford ";
	return false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Adds Victory Points and checks for a win 
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::addVicPt(int num )
{
	statistics.setItemQty(vicPt, statistics.getItemQty(vicPt) + num);
	statistics.setItemString(vicPt, std::to_string(statistics.getItemQty(vicPt)));
	if (statistics.getItemQty(vicPt) >= 10)
		std::cout << "If it is this player's turn (will check later) they are the winner!!!!!!!!!!!!\n";
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
// Toggles friend status and adds/removes the victory points
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::toggleFriend(bool toggle)
{
	friendOfThePeople = toggle;
	if (toggle)
		statistics.setItemQty(vicPt, statistics.getItemQty(vicPt) + 1);
	else
		statistics.setItemQty(vicPt, statistics.getItemQty(vicPt) - 1);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
// Toggles hero status and adds/removes the victory points
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::toggleHero(bool toggle)
{
	heroOfThePeople = toggle;
	if (toggle)
		statistics.setItemQty(vicPt, statistics.getItemQty(vicPt) + 1);
	else
		statistics.setItemQty(vicPt, statistics.getItemQty(vicPt) - 1);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Creates the Sector Menu and initializes it.
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::createSectorMenu(ResourceManager<sf::Texture> &txtMgr, ResourceManager<sf::Font> &fntMgr, std::string name, int num)
{
	Object* tempObject;

	tempObject = new Object(txtMgr.getResource(RICNFLE), { 420, 860 }, 1, { 35, 35 }, { 0, 0 });		// science 
	tempObject->initString(fntMgr.getResource(FNTFLE), { 460, 855 });
	statistics.push_back(tempObject);

	tempObject = new Object(txtMgr.getResource(RICNFLE), { 500, 860 }, 1, { 35, 35 }, { 1, 0 });		// ore
	tempObject->initString(fntMgr.getResource(FNTFLE), { 540, 855 });
	statistics.push_back(tempObject);

	tempObject = new Object(txtMgr.getResource(RICNFLE), { 580, 860 }, 1, { 35, 35 }, { 2, 0 });		// fuel
	tempObject->initString(fntMgr.getResource(FNTFLE), { 620, 855 });
	statistics.push_back(tempObject);

	tempObject = new Object(txtMgr.getResource(RICNFLE), { 660, 860 }, 1, { 35, 35 }, { 3, 0 });		// tradeGood
	tempObject->initString(fntMgr.getResource(FNTFLE), { 700, 855 });
	statistics.push_back(tempObject);

	tempObject = new Object(txtMgr.getResource(RICNFLE), { 740, 860 }, 1, { 35, 35 }, { 4, 0 });		// wheat
	tempObject->initString(fntMgr.getResource(FNTFLE), { 780, 855 });
	statistics.push_back(tempObject);

	tempObject = new Object(txtMgr.getResource(RICNFLE), { 820, 860 }, 1, { 35, 35 }, { 5, 0 });		// carbon
	tempObject->initString(fntMgr.getResource(FNTFLE), { 860, 855 });
	statistics.push_back(tempObject);
	
	tempObject = new Object(txtMgr.getResource(SYM1FLE), { 90, 860 }, 25, { 35, 35 }, { 3, 0 });		// astro
	tempObject->initString(fntMgr.getResource(FNTFLE), { 130, 855 });
	statistics.push_back(tempObject);	
	
	tempObject = new Object(txtMgr.getResource(ICNFLE), { 10, 820 }, num, { 75, 75 });				// Player
	tempObject->initString(fntMgr.getResource(FNTFLE), { 90, 820 }, name);
	statistics.push_back(tempObject);

	tempObject = new Object(txtMgr.getResource(SYM1FLE), { 180, 860 }, 1, { 35, 35 });				// vicPt
	tempObject->initString(fntMgr.getResource(FNTFLE), { 220, 855 });
	statistics.push_back(tempObject);

	tempObject = new Object(txtMgr.getResource(SYM1FLE), { 260, 860 }, 0, { 35, 35 }, { 1, 0 });		// frdPt
	tempObject->initString(fntMgr.getResource(FNTFLE), { 300, 855 });
	statistics.push_back(tempObject);

	tempObject = new Object(txtMgr.getResource(SYM1FLE), { 340, 860 }, 0, { 35, 35 }, { 2, 0 });		// fmPt
	tempObject->initString(fntMgr.getResource(FNTFLE), { 380, 855 });
	statistics.push_back(tempObject);

	statistics.setActive(true);
}
