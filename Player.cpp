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
Player::Player(TextureManager &txtMgr, std::string name, int num)
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

	player.icon = new Object(txtMgr.getTexture(ICNFLE), { 10, 820 }, { .75f, .75f }, { 100, 100 }, { 0, 0 }, num);
	player.text.setFont(font);
	player.text.setString(name);
	player.text.setPosition({ 90, 820 });

	vicPt.icon = new Object(txtMgr.getTexture(SYM1FLE), { 180, 860 }, { .35f, .35f }, { 100, 100 }, { 0, 0 }, 1, "VicPtIcon");		// sb 1
	vicPt.text.setFont(font);
	vicPt.text.setString(std::to_string(vicPt.icon->getNum()));
	vicPt.text.setPosition({ 220, 855 });

	frdPt.icon = new Object(txtMgr.getTexture(SYM1FLE), { 260, 860 }, { .35f, .35f }, { 100, 100 }, { 1, 0 }, 1, "frPtIcon");			// sb 0
	frdPt.text.setFont(font);
	frdPt.text.setString(std::to_string(frdPt.icon->getNum()));
	frdPt.text.setPosition({ 300, 855 });

	fmPt.icon = new Object(txtMgr.getTexture(SYM1FLE), { 340, 860 }, { .35f, .35f }, { 100, 100 }, { 2, 0 }, 1, "fmPtIcon");			// sb 0
	fmPt.text.setFont(font);
	fmPt.text.setString(std::to_string(fmPt.icon->getNum()));
	fmPt.text.setPosition({ 380, 855 });

	astro.icon = new Object(txtMgr.getTexture(SYM1FLE), { 90, 860 }, { .35f, .35f }, { 100, 100 }, { 3, 0 }, 25, "astroIcon");			// sb 25
	astro.text.setFont(font);
	astro.text.setString(std::to_string(astro.icon->getNum()));
	astro.text.setPosition({ 130, 855 });

	science.icon = new Object(txtMgr.getTexture(RICNFLE), { 420, 860 }, { .35f, .35f }, { 100, 100 }, { 0, 0 }, 1, "Ore Icon");
	science.text.setFont(font);
	science.text.setString(std::to_string(science.icon->getNum()));
	science.text.setPosition({ 460, 855 });

	ore.icon = new Object(txtMgr.getTexture(RICNFLE), { 500, 860 }, { .35f, .35f }, { 100, 100 }, { 5, 0 }, 1, "Science Icon");
	ore.text.setFont(font);
	ore.text.setString(std::to_string(ore.icon->getNum()));
	ore.text.setPosition({ 540, 855 });

	fuel.icon = new Object(txtMgr.getTexture(RICNFLE), { 580, 860 }, { .35f, .35f }, { 100, 100 }, { 1, 0 }, 1, "Fuel Icon");
	fuel.text.setFont(font);
	fuel.text.setString(std::to_string(fuel.icon->getNum()));
	fuel.text.setPosition({ 620, 855 });

	tradeGood.icon = new Object(txtMgr.getTexture(RICNFLE), { 660, 860 }, { .35f, .35f }, { 100, 100 }, { 4, 0 }, 1, "TradeGood Icon");
	tradeGood.text.setFont(font);
	tradeGood.text.setString(std::to_string(tradeGood.icon->getNum()));
	tradeGood.text.setPosition({ 700, 855 });

	wheat.icon = new Object(txtMgr.getTexture(RICNFLE), { 740, 860 }, { .35f, .35f }, { 100, 100 }, { 2, 0 }, 1, "Wheat Icon");
	wheat.text.setFont(font);
	wheat.text.setString(std::to_string(wheat.icon->getNum()));
	wheat.text.setPosition({ 780, 855 });

	carbon.icon = new Object(txtMgr.getTexture(RICNFLE), { 820, 860 }, { .35f, .35f }, { 100, 100 }, { 3, 0 }, 1, "Carbon Icon");
	carbon.text.setFont(font);
	carbon.text.setString(std::to_string(carbon.icon->getNum()));
	carbon.text.setPosition({ 860, 855 });
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
	delete player.icon;
	delete vicPt.icon;
	delete frdPt.icon;
	delete fmPt.icon;
	delete astro.icon;
	delete science.icon;
	delete ore.icon;
	delete fuel.icon;
	delete tradeGood.icon;
	delete wheat.icon;
	delete carbon.icon;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::update()
{
	player.icon->setSrcPosX(player.icon->getNum() - 1);
	player.icon->updateTextRect();
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
	player.icon->draw(gWindow);
	gWindow.draw(player.text);
	astro.icon->draw(gWindow);
	gWindow.draw(astro.text);
	vicPt.icon->draw(gWindow);
	gWindow.draw(vicPt.text);
	frdPt.icon->draw(gWindow);
	gWindow.draw(frdPt.text);
	fmPt.icon->draw(gWindow);
	gWindow.draw(fmPt.text);
	science.icon->draw(gWindow);
	gWindow.draw(science.text);
	ore.icon->draw(gWindow);
	gWindow.draw(ore.text);
	fuel.icon->draw(gWindow);
	gWindow.draw(fuel.text);
	tradeGood.icon->draw(gWindow);
	gWindow.draw(tradeGood.text); 
	wheat.icon->draw(gWindow);
	gWindow.draw(wheat.text);
	carbon.icon->draw(gWindow);
	gWindow.draw(carbon.text);
	gWindow.draw(carbon.text);
	gWindow.draw(cZoneString);
	gWindow.draw(tZoneString);

}