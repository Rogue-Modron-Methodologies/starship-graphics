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
//  
//  Constructor
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
Player::Player(ResourceManager<sf::Texture> &txtMgr, ResourceManager<sf::Font> &fntMgr, std::string name, int num)
{
	starship = new Starship(txtMgr, fntMgr);
	colonyZone = new Zone<ColonyCard>(txtMgr, fntMgr, "Colony");
	tradeZone = new Zone<TradeCard>(txtMgr, fntMgr, "Trade");
	pirateZone = new Zone<Pirate>(txtMgr, fntMgr, "Pirate");

	statistics = new Icon*[STATNUM];

	statistics[player] = new Icon(txtMgr.getResource(ICNFLE), { 10, 820 }, num, {75, 75 });
	statistics[player]->initString(fntMgr.getResource(FNTFLE), { 90, 820 }, name);

	statistics[astro] = new Icon(txtMgr.getResource(SYM1FLE), { 90, 860 }, 25, { 35, 35 }, { 3, 0 });
	statistics[astro]->initString(fntMgr.getResource(FNTFLE), { 130, 855 });
	
	statistics[vicPt] = new Icon(txtMgr.getResource(SYM1FLE), { 180, 860 }, 1, { 35, 35 });
	statistics[vicPt]->initString(fntMgr.getResource(FNTFLE), { 220, 855 });
	
	statistics[frdPt] = new Icon(txtMgr.getResource(SYM1FLE), { 260, 860 }, 0, { 35, 35 }, { 1, 0 });
	statistics[frdPt]->initString(fntMgr.getResource(FNTFLE), { 300, 855 });

	statistics[fmPt] = new Icon(txtMgr.getResource(SYM1FLE), { 340, 860 }, 0, { 35, 35 }, { 2, 0 });
	statistics[fmPt]->initString(fntMgr.getResource(FNTFLE), { 380, 855 });

	statistics[science] = new Icon(txtMgr.getResource(RICNFLE), { 420, 860 }, 1, { 35, 35 }, { 0, 0 });
	statistics[science]->initString(fntMgr.getResource(FNTFLE), { 460, 855 });
		
	statistics[ore] = new Icon(txtMgr.getResource(RICNFLE), { 500, 860 }, 1, { 35, 35 }, { 1, 0 });
	statistics[ore]->initString(fntMgr.getResource(FNTFLE), { 540, 855 });
	
	statistics[fuel] = new Icon(txtMgr.getResource(RICNFLE), { 580, 860 }, 1, { 35, 35 }, { 2, 0 });
	statistics[fuel]->initString(fntMgr.getResource(FNTFLE), { 620, 855 });

	statistics[tradeGood] = new Icon(txtMgr.getResource(RICNFLE), { 660, 860 }, 1, { 35, 35 }, { 3, 0 });
	statistics[tradeGood]->initString(fntMgr.getResource(FNTFLE), { 700, 855 });

	statistics[wheat] = new Icon(txtMgr.getResource(RICNFLE), { 740, 860 }, 1, { 35, 35 }, { 4, 0 });
	statistics[wheat]->initString(fntMgr.getResource(FNTFLE), { 780, 855 });

	statistics[carbon] = new Icon(txtMgr.getResource(RICNFLE), { 820, 860 }, 1, { 35, 35 }, { 5, 0 });
	statistics[carbon]->initString(fntMgr.getResource(FNTFLE), { 860, 855 });

	bool friendOfThePeople = false;
	bool heroOfThePeople = false;
}
 
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Destructor
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
Player::~Player()
{
	delete starship;
	delete colonyZone;
	delete tradeZone;
	delete pirateZone;
	for (int i = 0; i < STATNUM; i++)
		delete statistics[i];
	delete [] statistics;
}



// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Updates the Player Icon
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::updatePlayerIcon()
{
	statistics[player]->setSrcPosX(statistics[player]->getQty() - 1);
	statistics[player]->updateTextRect();
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Updates an Icons Qty
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::updateIcon(int type)
{
	if (type < 6)
	{
		int tempNum = starship->getShipObjectQty(type);
		statistics[type]->setQty(tempNum);
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::draw(sf::RenderWindow &gWindow)
{
	starship->draw(gWindow);
	colonyZone->draw(gWindow);
	tradeZone->draw(gWindow);
	for (int i = 0; i < STATNUM; i++)
		statistics[i]->draw(gWindow);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Expands StarShip, Colony Zone, and Trade Zone
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::makeBig()
{
	starship->makeBig();
	colonyZone->updateZone(CLPOS, CRDZNSCL, true);
	tradeZone->updateZone(TLPOS, CRDZNSCL, true);
	smallDisplay = false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Reduces StarShip, Colony Zone, and Trade Zone
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::makeSmall()
{
	starship->makeSmall();
	colonyZone->updateZone(CSPOS, CRDSSCL, true);
	tradeZone->updateZone(TSPOS, CRDSSCL, true);
	smallDisplay = true;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Expands the Colony Zone and moves Trade to the far right
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::expandColonyZone()
{
	colonyZone->updateZone(CLPOS, CRDZNSCL, false);
	tradeZone->updateZone(sf::Vector2f(1050, 610), CRDZNSCL, true);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Expands the Trade Zone and moves Colony to the far right
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::expandTradeZone()
{
	tradeZone->updateZone(CLPOS, CRDZNSCL, false);
	colonyZone->updateZone(sf::Vector2f(1050, 610), CRDZNSCL, true);
}



