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
	ColonyZone = new LinkedList<Card>;
	TradeZone = new LinkedList<Card>;

	cZoneIcon = new Icon(fntMgr.getResource(FNTFLE), { 30, 515 }, "Colony");

	tZoneIcon = new Icon(fntMgr.getResource(FNTFLE), { 130, 515 }, "Trade");

	statistics = new Icon*[STATNUM];

	statistics[player] = new Icon(txtMgr.getResource(ICNFLE), { 10, 820 }, num, {75, 75 });
	statistics[player]->initString(fntMgr.getResource(FNTFLE), { 90, 820 }, name);

	statistics[vicPt] = new Icon(txtMgr.getResource(SYM1FLE), { 180, 860 }, 1, { 35, 35 });
	statistics[vicPt]->initString(fntMgr.getResource(FNTFLE), { 220, 855 });

	statistics[frdPt] = new Icon(txtMgr.getResource(SYM1FLE), { 260, 860 }, 0, { 35, 35 }, { 1, 0 });
	statistics[frdPt]->initString(fntMgr.getResource(FNTFLE), { 300, 855 });

	statistics[fmPt] = new Icon(txtMgr.getResource(SYM1FLE), { 340, 860 }, 0, { 35, 35 }, { 2, 0 });
	statistics[fmPt]->initString(fntMgr.getResource(FNTFLE), { 380, 855 });

	statistics[astro] = new Icon(txtMgr.getResource(SYM1FLE), { 90, 860 }, 25, { 35, 35 }, { 3, 0 });
	statistics[astro]->initString(fntMgr.getResource(FNTFLE), { 130, 855 });

	statistics[science] = new Icon(txtMgr.getResource(RICNFLE), { 500, 860 }, 1, { 35, 35 });
	statistics[science]->initString(fntMgr.getResource(FNTFLE), { 540, 855 });
	
	statistics[ore] = new Icon(txtMgr.getResource(RICNFLE), { 420, 860 }, 1, { 35, 35 }, { 5, 0 });
	statistics[ore]->initString(fntMgr.getResource(FNTFLE), { 460, 855 });

	statistics[fuel] = new Icon(txtMgr.getResource(RICNFLE), { 580, 860 }, 1, { 35, 35 }, { 1, 0 });
	statistics[fuel]->initString(fntMgr.getResource(FNTFLE), { 620, 855 });

	statistics[tradeGood] = new Icon(txtMgr.getResource(RICNFLE), { 660, 860 }, 1, { 35, 35 }, { 4, 0 });
	statistics[tradeGood]->initString(fntMgr.getResource(FNTFLE), { 700, 855 });

	statistics[wheat] = new Icon(txtMgr.getResource(RICNFLE), { 740, 860 }, 1, { 35, 35 }, { 2, 0 });
	statistics[wheat]->initString(fntMgr.getResource(FNTFLE), { 780, 855 });

	statistics[carbon] = new Icon(txtMgr.getResource(RICNFLE), { 820, 860 }, 1, { 35, 35 }, { 3, 0 });
	statistics[carbon]->initString(fntMgr.getResource(FNTFLE), { 860, 855 });
}
 
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Destructor
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
Player::~Player()
{
	delete starship;
	delete ColonyZone;
	delete TradeZone;
	for (int i = 0; i < STATNUM; i++)
		delete statistics[i];
	delete [] statistics;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Updates the Player Icon
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::update()
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
	drawCPlyrStats(gWindow);
	if (ColonyZone->showIconOnly())
		ColonyZone->displayHead(gWindow);
	else
		ColonyZone->displayList(gWindow);
	if (TradeZone->getCount())
	{
		if (TradeZone->showIconOnly())
			TradeZone->displayHead(gWindow);
		else
			TradeZone->displayList(gWindow);
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Expands StarShip, Colony Zone, and Trade Zone
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::makeBig()
{
	starship->makeBig();
	cZoneIcon->setTextPosition(CLPOS - sf::Vector2f(0, 35));
	ColonyZone->setIconOnly(true);
	ColonyZone->updateList(CLPOS, CRDZNSCL);
	tZoneIcon->setTextPosition(TLPOS - sf::Vector2f(0, 35));
	TradeZone->setIconOnly(true);
	TradeZone->updateList(TLPOS, CRDZNSCL);	
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Reduces StarShip, Colony Zone, and Trade Zone
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::makeSmall()
{
	starship->makeSmall();
	ColonyZone->setIconOnly(true);
	cZoneIcon->setTextPosition(CSPOS - sf::Vector2f(0, 35));
	ColonyZone->updateList(CSPOS, CRDSSCL);
	tZoneIcon->setTextPosition(TSPOS - sf::Vector2f(0, 35));
	TradeZone->setIconOnly(true);
	TradeZone->updateList(TSPOS, CRDSSCL);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Expands the Colony Zone and moves Trade to the far right
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::expandColonyZone()
{
	cZoneIcon->setTextPosition(CLPOS - sf::Vector2f(0, 35));
	ColonyZone->updateList(CLPOS, CRDZNSCL);
	ColonyZone->setIconOnly(false);
	tZoneIcon->setTextPosition(sf::Vector2f(1050, 575));
	TradeZone->updateList(sf::Vector2f(1050, 610), CRDZNSCL);
	TradeZone->setIconOnly(true);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Expands the Trade Zone and moves Colony to the far right
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::expandTradeZone()
{
	tZoneIcon->setTextPosition(CLPOS - sf::Vector2f(0, 35));
	TradeZone->updateList(CLPOS, CRDZNSCL);
	TradeZone->setIconOnly(false);
	cZoneIcon->setTextPosition(sf::Vector2f(1050, 575));
	ColonyZone->updateList(sf::Vector2f(1050, 610), CRDZNSCL);
	ColonyZone->setIconOnly(true);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  draws the icons and stats for current player
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::drawCPlyrStats(sf::RenderWindow &gWindow)
{
	for (int i = 0; i < STATNUM; i++)
		statistics[i]->draw(gWindow);
	cZoneIcon->draw(gWindow);
	tZoneIcon->draw(gWindow);
}