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
Player::Player(std::string name, int num) 
{
	starship = new Starship();
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

	plyIcon = new Object(ICNFLE, STDSZE, { 10, 820 }, { .3f, .3f }, { 500, 250 }, num);
	plyIcon->getSprite()->setTextureRect(sf::IntRect(plyIcon->getSrcPos().x * plyIcon->getSrcSze().y, plyIcon->getSrcPos().y * plyIcon->getSrcSze().y, plyIcon->getSrcSze().y, plyIcon->getSrcSze().y));
	nameString.setFont(font);
	nameString.setString(name);
	nameString.setPosition({ 90, 820 });	

	astroIcon = new Object(ASTFLE, STDSZE, { 90, 860 }, { .15f, .15f }, { 200, 200 }, 25);	// sb 25
	astroString.setFont(font);
	astroString.setString(std::to_string(astroIcon->getNum()));
	astroString.setPosition({ 130, 855 });

	vPtIcon = new Object(SYM1FLE, STDSZE, { 180, 860 }, { .21f, .21f }, { 150, 150 }, 1);		// sb 1
	vPtIcon->getSprite()->setTextureRect(sf::IntRect(vPtIcon->getSrcPos().x * vPtIcon->getSrcSze().y, vPtIcon->getSrcPos().y * vPtIcon->getSrcSze().y, vPtIcon->getSrcSze().y, vPtIcon->getSrcSze().y));
	vPtString.setFont(font);
	vPtString.setString(std::to_string(vPtIcon->getNum()));
	vPtString.setPosition({ 220, 855 });
	
	frPtIcon = new Object(vPtIcon, { 260, 860 }, 1);			// sb 0
	frPtIcon->setSrcPos({ 1 , 0 });
	frPtIcon->getSprite()->setTextureRect(sf::IntRect(frPtIcon->getSrcPos().x * frPtIcon->getSrcSze().y, frPtIcon->getSrcPos().y * frPtIcon->getSrcSze().y, frPtIcon->getSrcSze().y, frPtIcon->getSrcSze().y));
	frPtString.setFont(font);
	frPtString.setString(std::to_string(frPtIcon->getNum()));
	frPtString.setPosition({ 300, 855 });

	fmPtIcon = new Object(vPtIcon, { 340, 860 }, 1);			// sb 0
	fmPtIcon->setSrcPos({ 2, 0 });
	fmPtIcon->getSprite()->setTextureRect(sf::IntRect(fmPtIcon->getSrcPos().x * fmPtIcon->getSrcSze().y, fmPtIcon->getSrcPos().y * fmPtIcon->getSrcSze().y, fmPtIcon->getSrcSze().y, fmPtIcon->getSrcSze().y));
	fmPtString.setFont(font);
	fmPtString.setString(std::to_string(fmPtIcon->getNum()));
	fmPtString.setPosition({ 380, 855 });

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
	delete plyIcon;
	delete vPtIcon;
	delete frPtIcon;
	delete fmPtIcon;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::update()
{
	plyIcon->setSrcPosX(plyIcon->getNum() - 1);
	plyIcon->getSprite()->setTextureRect(sf::IntRect(plyIcon->getSrcPos().x * plyIcon->getSrcSze().y, plyIcon->getSrcPos().y * plyIcon->getSrcSze().y, plyIcon->getSrcSze().y, plyIcon->getSrcSze().y));
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
	cZoneString.setPosition(COLLPOS - sf::Vector2f(0, 35));
	ColonyZone->setIconOnly(true);
	ColonyZone->updateList(COLLPOS, CRDLSCL);
	tZoneString.setPosition(TRDLPOS - sf::Vector2f(0, 35));
	TradeZone->setIconOnly(true);
	TradeZone->updateList(TRDLPOS, CRDLSCL);
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
	cZoneString.setPosition(COLSPOS - sf::Vector2f(0, 35));
	ColonyZone->updateList(COLSPOS, CRDSSCL);
	tZoneString.setPosition(TRDSPOS - sf::Vector2f(0, 35));
	TradeZone->setIconOnly(true);
	TradeZone->updateList(TRDSPOS, CRDSSCL);

}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  Expands the Colony Zone and moves Trade to the far right
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Player::expandColonyZone()
{
	cZoneString.setPosition(COLLPOS - sf::Vector2f(0, 35));
	ColonyZone->updateList(COLLPOS, CRDLSCL);
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
	tZoneString.setPosition(COLLPOS - sf::Vector2f(0, 35));
	TradeZone->updateList(COLLPOS, CRDLSCL);
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
	plyIcon->draw(gWindow);
	gWindow.draw(nameString);
	astroIcon->draw(gWindow);
	gWindow.draw(astroString);
	vPtIcon->draw(gWindow);
	gWindow.draw(vPtString);
	frPtIcon->draw(gWindow);
	gWindow.draw(frPtString);
	fmPtIcon->draw(gWindow);
	gWindow.draw(fmPtString);
	gWindow.draw(cZoneString);
	gWindow.draw(tZoneString);

}