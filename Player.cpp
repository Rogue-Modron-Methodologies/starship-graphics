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
Player::Player(ResourceManager<sf::Texture> &txtMgr, std::string name, int num)
{
	starship = new Starship(txtMgr);
	ColonyZone = new LinkedList<Card>;
	TradeZone = new LinkedList<Card>;
	if (!font.loadFromFile(FNTFLE)){
		std::cout << "Font not Loaded" << std::endl;
	}
	cZoneString.setFont(font);
	cZoneString.setString("Colony");
	cZoneString.setPosition({ 30, 515 });

	tZoneString.setFont(font);
	tZoneString.setString("Trade");
	tZoneString.setPosition({ 130, 515 });

	statistics[player].icon = new Object(txtMgr.getResource(ICNFLE), { 10, 820 }, num, {75, 75 });
	statistics[player].text.setFont(font);
	statistics[player].text.setString(name);
	statistics[player].text.setPosition({ 90, 820 });

	statistics[vicPt].icon = new Object(txtMgr.getResource(SYM1FLE), { 180, 860 }, 1, { 35, 35 });		// sb 1
	statistics[vicPt].text.setFont(font);
	statistics[vicPt].text.setString(std::to_string(statistics[vicPt].icon->getQty()));
	statistics[vicPt].text.setPosition({ 220, 855 });

	statistics[frdPt].icon = new Object(txtMgr.getResource(SYM1FLE), { 260, 860 }, 1, { 35, 35 }, { 1, 0 });			// sb 0
	statistics[frdPt].text.setFont(font);
	statistics[frdPt].text.setString(std::to_string(statistics[frdPt].icon->getQty()));
	statistics[frdPt].text.setPosition({ 300, 855 });

	statistics[fmPt].icon = new Object(txtMgr.getResource(SYM1FLE), { 340, 860 }, 1, { 35, 35 }, { 2, 0 });			// sb 0
	statistics[fmPt].text.setFont(font);
	statistics[fmPt].text.setString(std::to_string(statistics[fmPt].icon->getQty()));
	statistics[fmPt].text.setPosition({ 380, 855 });

	statistics[astro].icon = new Object(txtMgr.getResource(SYM1FLE), { 90, 860 }, 25, { 35, 35 }, { 3, 0 });			// sb 25
	statistics[astro].text.setFont(font);
	statistics[astro].text.setString(std::to_string(statistics[astro].icon->getQty()));
	statistics[astro].text.setPosition({ 130, 855 });

	statistics[science].icon = new Object(txtMgr.getResource(RICNFLE), { 420, 860 }, 1, { 35, 35 });
	statistics[science].text.setFont(font);
	statistics[science].text.setString(std::to_string(statistics[science].icon->getQty()));
	statistics[science].text.setPosition({ 460, 855 });

	statistics[ore].icon = new Object(txtMgr.getResource(RICNFLE), { 500, 860 }, 1, { 35, 35 }, { 5, 0 });
	statistics[ore].text.setFont(font);
	statistics[ore].text.setString(std::to_string(statistics[ore].icon->getQty()));
	statistics[ore].text.setPosition({ 540, 855 });

	statistics[fuel].icon = new Object(txtMgr.getResource(RICNFLE), { 580, 860 }, 1, { 35, 35 }, { 1, 0 });
	statistics[fuel].text.setFont(font);
	statistics[fuel].text.setString(std::to_string(statistics[fuel].icon->getQty()));
	statistics[fuel].text.setPosition({ 620, 855 });

	statistics[tradeGood].icon = new Object(txtMgr.getResource(RICNFLE), { 660, 860 }, 1, { 35, 35 }, { 4, 0 });
	statistics[tradeGood].text.setFont(font);
	statistics[tradeGood].text.setString(std::to_string(statistics[tradeGood].icon->getQty()));
	statistics[tradeGood].text.setPosition({ 700, 855 });

	statistics[wheat].icon = new Object(txtMgr.getResource(RICNFLE), { 740, 860 }, 1, { 35, 35 }, { 2, 0 });
	statistics[wheat].text.setFont(font);
	statistics[wheat].text.setString(std::to_string(statistics[wheat].icon->getQty()));
	statistics[wheat].text.setPosition({ 780, 855 });

	statistics[carbon].icon = new Object(txtMgr.getResource(RICNFLE), { 820, 860 }, 1, { 35, 35 }, { 3, 0 });
	statistics[carbon].text.setFont(font);
	statistics[carbon].text.setString(std::to_string(statistics[carbon].icon->getQty()));
	statistics[carbon].text.setPosition({ 860, 855 });
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
	for (int i = 0; i < ICNNUM; i++)
		delete statistics[i].icon;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Updates the Player Icon
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::update()
{
	statistics[player].icon->setSrcPosX(statistics[player].icon->getQty() - 1);
	statistics[player].icon->updateTextRect();
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
	cZoneString.setPosition(CLPOS - sf::Vector2f(0, 35));
	ColonyZone->setIconOnly(true);
	ColonyZone->updateList(CLPOS, CRDLSCL);
	tZoneString.setPosition(TLPOS - sf::Vector2f(0, 35));
	TradeZone->setIconOnly(true);
	TradeZone->updateList(TLPOS, CRDLSCL);
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
	cZoneString.setPosition(CSPOS - sf::Vector2f(0, 35));
	ColonyZone->updateList(CSPOS, CRDSSCL);
	tZoneString.setPosition(TSPOS - sf::Vector2f(0, 35));
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
	cZoneString.setPosition(CLPOS - sf::Vector2f(0, 35));
	ColonyZone->updateList(CLPOS, CRDLSCL);
	ColonyZone->setIconOnly(false);
	tZoneString.setPosition(sf::Vector2f(1050, 575));
	TradeZone->updateList(sf::Vector2f(1050,610), CRDLSCL);
	TradeZone->setIconOnly(true);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Expands the Trade Zone and moves Colony to the far right
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::expandTradeZone()
{
	tZoneString.setPosition(CLPOS - sf::Vector2f(0, 35));
	TradeZone->updateList(CLPOS, CRDLSCL);
	TradeZone->setIconOnly(false);
	cZoneString.setPosition(sf::Vector2f(1050, 575));
	ColonyZone->updateList(sf::Vector2f(1050, 610), CRDLSCL);
	ColonyZone->setIconOnly(true);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  draws the icons and stats for current player
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::drawCPlyrStats(sf::RenderWindow &gWindow)
{
	for (int i = 0; i < ICNNUM; i++)
	{
		statistics[i].icon->draw(gWindow);
		gWindow.draw(statistics[i].text);
	}
	gWindow.draw(cZoneString);
	gWindow.draw(tZoneString);

}