//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#include "Game.h"

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//
//  Player Name Setup
//
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
Game::Game()
{
	if (!font.loadFromFile(FNTFLE)){
		std::cout << "Font not Loaded" << std::endl;
	}

	flightDie.icon = new Object(txtMgr.getResource(SDIEFLE), sf::Vector2f{ 350, 525 }, 1, sf::Vector2u(200, 200));
	flightDie.icon->setScale({ .4f, .4f });
	flightDie.text.setFont(font);
	flightDie.text.setStyle(sf::Text::Bold);
	flightDie.text.setPosition({ 440, 545 });		
	P1 = new Player(txtMgr, "Player1", 1);		// Default names for bugtesting
	P2 = new Player(txtMgr, "Player2", 2);		// Default names for bugtesting
	universe = new Universe(txtMgr);
	screenSize = sf::Vector2u(1200, 900);
	gWindow.create(sf::VideoMode(screenSize.x, screenSize.y), "Starship Game");
	phaseSetupComplete = false;
	phaseComplete = false;
	gainProductionResource = false;
	displayFlightPath = true;
	displaySectors = true;
	sectorSelected = false;
	cPhase = production;

	cPlanet.setFont(font);
	cPlanet.setString("Current Planet");
	cPlanet.setPosition(835, 480);

	phaseNameString.setFont(font);
	phaseNameString.setString("Production Phase");
	phaseNameString.setPosition({ 200, 820 });		 
	
	errorString.setFont(font);
	errorString.setStyle(sf::Text::Bold);
	errorString.setPosition({ 550, 820 });   
	errorTimer = 255;
	
	infoString.setFont(font);
	infoString.setStyle(sf::Text::Bold);
	infoString.setPosition({ 40, 30 });	
	
	specialString.setFont(font);
	specialString.setString("End of Phase\n(Press Enter)");
	specialString.setStyle(sf::Text::Bold);
	specialString.setScale(2, 2);
	specialString.setColor(sf::Color::Red);
	specialString.setPosition({ 825, 25 });
	
	cPlyr = P2;
	playerSetup();
	initCDie();
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//
//  Player Name Setup
//
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::playerSetup()
{	
	/*     -------------------These commented parts will be readded when I'm further along... 
	string tempName;
	cout << "Please enter Player 1 Name. \n";
	getline(cin, tempName);
	P1->setName(tempName);
	cout << "Please enter Player 2 Name. \n";
	getline(cin, tempName);
	P2->setName(tempName);
	*/
	//ColonyCard(int num, string name, int type, int resource, int actNum, int vicPts) 
	Card* tempCard;
	//M		colony	Carbon	1	N/A	0	1	Colony: Alioth VIII
	tempCard = new ColonyCard(txtMgr.getResource(STRFILE), {0, 0}, -1, "Colony: Alioth VIII", colony, Carbon, 1, 1);
	tempCard->setScale(CRDZNSCL);
	tempCard->updateTextRect();
	P1->getColonyZone()->insertNode(tempCard);

	///////////////////////   BEGIN TEST STUFF
	tempCard = new ColonyCard(txtMgr.getResource(STRFILE), { 0, 0 }, -1, "Colony: Alioth VIII", colony, Carbon, 1, 1);
	tempCard->setScale(CRDZNSCL);
	tempCard->updateTextRect();
	P1->getColonyZone()->insertNode(tempCard);

	tempCard = new ColonyCard(txtMgr.getResource(STRFILE), { 0, 0 }, -1, "Colony: Alioth VIII", colony, Carbon, 1, 1);
	tempCard->setScale(CRDZNSCL);
	tempCard->updateTextRect();
	P1->getColonyZone()->insertNode(tempCard);

	tempCard = new ColonyCard(txtMgr.getResource(STRFILE), { 0, 0 }, -1, "Colony: Alioth VIII", colony, Carbon, 1, 1);
	tempCard->setScale(CRDZNSCL);
	tempCard->updateTextRect();
	P1->getColonyZone()->insertNode(tempCard);

	tempCard = new ColonyCard(txtMgr.getResource(STRFILE), { 0, 0 }, -1, "Colony: Alioth VIII", colony, Carbon, 1, 1);
	tempCard->setScale(CRDZNSCL);
	tempCard->updateTextRect();
	P1->getTradeZone()->insertNode(tempCard);

	tempCard = new ColonyCard(txtMgr.getResource(STRFILE), { 0, 0 }, -1, "Colony: Alioth VIII", colony, Carbon, 1, 1);
	tempCard->setScale(CRDZNSCL);
	tempCard->updateTextRect();
	P1->getTradeZone()->insertNode(tempCard);

	///////////////////////   END TEST STUFF


	//S		colony	Fuel		1	N/A	0	1	Colony: Megrez VII
	tempCard = new ColonyCard(txtMgr.getResource(STRFILE), { 1, 0 }, -1, "Colony: Megrez VII", colony, Fuel, 1, 1);
	tempCard->setScale(CRDZNSCL);
	tempCard->updateTextRect();
	P2->getColonyZone()->insertNode(tempCard);
	
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//
//  Checks for win condition and toggles the current player
//
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::gameLoop()
{
//	string choice = "";  // temp until win condition is set
//	while (toupper(choice[0]) != 'Q')  // mimics the checkwin loop.
//	{
	cPlyr == P1 ? cPlyr = P2 : cPlyr = P1;	// toggles between players
	cPlyr->update();
//		cout << "CheckWin will be here.\n";
//		gameTurn();
//		cout << "Q to Toggle Win Condition\n";
//		cin >> choice;
//	}
	int tempNum;
	sf::Event event;
	while (gWindow.isOpen())
	{
		if (!phaseSetupComplete)
			phaseSetup();
		while (gWindow.pollEvent(event))		// the event loop
		{
			switch (event.type) {
			case sf::Event::Closed:
				gWindow.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					gWindow.close();
				if (event.key.code == sf::Keyboard::Return && phaseComplete)
					endPhase();
				break;
			case sf::Event::MouseButtonPressed:
				switch (cPhase)
				{
				case production: 
					productionPhaseListener(gWindow);
					break;
				case flight:
					if (!sectorSelected)
						flightPhaseSectorSelectionListener(gWindow, tempNum);
					if (sectorSelected)
						flightPhaseListener(gWindow, tempNum);
					break;
				case trades:	
					tradePhaseListener(gWindow);
					break;
				case build:	
					buildPhaseListener(gWindow);
					break;
				}			
			case sf::Event::MouseMoved:
				switch (cPhase)
				{
				case production:
					break;
				case flight:
					//if (!sectorSelected)
					//{					
					//	std::cout << std::endl;
					//	if (universe->sectorsTargeted(gWindow, tempNum) && cPlyr->getStarship()->isSmall())
					//		std::cout << "Sector " << tempNum + 1 << " Glows" << std::endl;
					//}
					break;
				case trades:
					break;
				case build:
					//std::cout << std::endl;
					//if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall())
					//	std::cout << "P1 Ship Glows" << std::endl;
					break;
				}
			}				
		}
		gWindow.clear();
		updateGameWindow(gWindow);
		gWindow.display();
	}
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//
//  Initialize Combat Die
//
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::initCDie()
{
	combatDie[0] = 1;
	combatDie[1] = 2;
	combatDie[2] = 2;
	combatDie[3] = 3;
	combatDie[4] = 3;
	combatDie[5] = 4;
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//
//  inital phase setup
//
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::phaseSetup()
{	
	int dieRoll;
	std::string tempString;
	phaseComplete = false;	
	switch (cPhase)
	{
	case production:
		phaseNameString.setString("Production Phase");
		cPlyr->makeBig();
		cPlyr->expandColonyZone();		
		dieRoll = rollSpeedDie();
		cPlyr->getStarship()->calcMaxDistance(dieRoll);
		tempString.clear();
		
		if (cPlyr->getColonyZone()->findColonyResource(dieRoll))
		{
			tempString += " Resource(s) in Colony Zone Found!  Press Select One";
			gainProductionResource = true;
		}
		else
		{
			tempString += " No Resources in Colony Zone";	
			phaseComplete = true;
		}	

		infoString.setString(tempString);			
		break;
	case flight:
		phaseNameString.setString("Flight Phase");
		cPlyr->makeSmall();
		actionNum = 0;
		displaySectors = true;
		sectorSelected = false;		
		infoString.setString("Flight: 0 / " + std::to_string(cPlyr->getStarship()->getMaxDistance()) + "\nMax Actions: 0 / " + 
			std::to_string(cPlyr->getStarship()->getMaxActions()) + "\n\t\t\t\t\t\t\t\t\t\tChoose a sector");
		break;
	case trades:
		phaseNameString.setString("Trade Phase");
		infoString.setString("Max Trades: 2");
		cPlyr->makeBig();
		cPlyr->expandTradeZone();
		phaseComplete = true;		//  Only until there is an actual trade phase coded
		break;
	case build:
		phaseNameString.setString("Build Phase");
		infoString.setString("Build Phase");
		cPlyr->makeBig();
		phaseComplete = true;		//  Only until there is an actual build phase coded
		break;
	}
	phaseSetupComplete = true;
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//
//  sets cPhase to next phase, checks for end of build phase
//  and sets back to production
//
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::endPhase()
{
	cPhase++;
	if (cPhase == 4)
	{
		std::cout << "Checkwin Here?" << std::endl;
		cPhase = 0;
	}
	phaseSetupComplete = false;		
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//  
//  draws the icons and stats for game Window
//
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::updateGameWindow(sf::RenderWindow &gWindow)
{
	universe->getBoard()->draw(gWindow);
		switch (cPhase)
	{
	case production:
		flightDie.icon->draw(gWindow);
		gWindow.draw(flightDie.text);
		break;
	case flight:
		if (!sectorSelected && displaySectors)
			universe->drawSectors(gWindow);
		else
		{
			if (displayFlightPath)
				drawFlightPath(gWindow);
			drawCurrentPlanet(gWindow);
			if (!phaseComplete && actionNum < cPlyr->getStarship()->getMaxActions())
			{
				updateFlightMenu(gWindow);
				drawFlightMenu(gWindow);
				infoString.setString("Flight: " + std::to_string(universe->getCurrentMove()) + " / " + std::to_string(cPlyr->getStarship()->getMaxDistance())
					+ "\nMax Actions: " + std::to_string(actionNum) + " / " + std::to_string(cPlyr->getStarship()->getMaxActions()));
			}
			else
			{
				infoString.setString("Flight Complete");
				phaseComplete = true;
			}
		}
		break;
	default:
		break;
	}
	gWindow.draw(phaseNameString);
	gWindow.draw(infoString);	
	
	cPlyr->draw(gWindow);		
	if (statusUpdate.length())
		setError(statusUpdate);
	statusUpdate.clear();
	if (errorTimer)
	{
		errorString.setColor(sf::Color(255, 0, 0, errorTimer / 10));
		gWindow.draw(errorString);		
		errorTimer--;
	}
	if (phaseComplete){
		gWindow.draw(specialString);
	}

}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//  updates the Error String and timer with the error message
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::setError(std::string error)
{
	errorTimer = 2550;
	errorString.setString(error);
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//  rand(1-3) and updates the sprite to correct textureRect
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
int Game::rollSpeedDie()
{
	int num = rand() % 3;
	flightDie.icon->setSrcPos(sf::Vector2u(num, 0));
	flightDie.icon->updateTextRect();
	flightDie.text.setString("Dice roll: " + std::to_string(num + 1));
	return num + 1;
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//  Deals with Mouse Click actions in the Production Phase
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::productionPhaseListener(sf::RenderWindow &gWindow)
{
	int tempType;
	// Starship (Small) is clicked
	if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->makeBig();
	}
	// Colony Zone (Large Icon) is clicked
	else if (!cPlyr->getColonyZone()->isSmall() && cPlyr->getColonyZone()->showIconOnly() && cPlyr->getColonyZone()->isIconTargeted(gWindow))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandColonyZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	else if (!cPlyr->getTradeZone()->isSmall() && cPlyr->getTradeZone()->showIconOnly() && cPlyr->getTradeZone()->isIconTargeted(gWindow))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandTradeZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	// Colony Zone (Large List) is clicked and player is entitled to a production resource
	else if (!cPlyr->getColonyZone()->isSmall() && !cPlyr->getColonyZone()->showIconOnly() && cPlyr->getColonyZone()->isZoneTargeted(gWindow, tempType))
	{

		if (gainProductionResource && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			if (cPlyr->getStarship()->gainItem(tempType, statusUpdate))
			{
				cPlyr->updateIcon(tempType);
				infoString.setString("Resource Gained");
				gainProductionResource = false;
				phaseComplete = true;
			}
	}
	// Trade Zone (Large List) is clicked
	else if (!cPlyr->getTradeZone()->isSmall() && !cPlyr->getTradeZone()->showIconOnly() && cPlyr->getTradeZone()->isZoneTargeted(gWindow, tempType)){}		// Do Nothing this Phase
	//  Starship (Large) && Empty Space is clicked
	else if (!cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall())
		cPlyr->makeSmall();
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//  Flight Phase Sector Selection Listener
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::flightPhaseSectorSelectionListener(sf::RenderWindow &gWindow, int &tempType)
{
	// Starship (Small) is clicked
	if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			cPlyr->makeBig();
			displaySectors = false;
		}
	}
	// Starship (Large) is clicked
	else if (cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall()){}	// Do Nothing this Phase
	// Colony Zone (Large Icon) is clicked
	else if (!cPlyr->getColonyZone()->isSmall() && cPlyr->getColonyZone()->showIconOnly() && cPlyr->getColonyZone()->isIconTargeted(gWindow))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandColonyZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	// Trade Zone (Large Icon) is clicked
	else if (!cPlyr->getTradeZone()->isSmall() && cPlyr->getTradeZone()->showIconOnly() && cPlyr->getTradeZone()->isIconTargeted(gWindow))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandTradeZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	// Colony Zone (Large List) is clicked
	else if (!cPlyr->getColonyZone()->isSmall() && !cPlyr->getColonyZone()->showIconOnly() && cPlyr->getColonyZone()->isZoneTargeted(gWindow, tempType)){}	// Do Nothing this Phase
	// Trade Zone (Large List) is clicked
	else if (!cPlyr->getTradeZone()->isSmall() && !cPlyr->getTradeZone()->showIconOnly() && cPlyr->getTradeZone()->isZoneTargeted(gWindow, tempType)){}		// Do Nothing this Phase
	//  Sector is Clicked
	else if (universe->sectorsTargeted(gWindow, tempType) && cPlyr->getStarship()->isSmall())
	{
		std::cout << "Sector " << tempType  << " Clicked" << std::endl;
		infoString.setString("Flight: 1 / " + std::to_string(cPlyr->getStarship()->getMaxDistance()) + "\nMax Actions: 0 / " + std::to_string(cPlyr->getStarship()->getMaxActions()));
		displaySectors = false;
		sectorSelected = true;
		universe->initializeFlightPath(tempType);
		return;
	}
	//  Starship (Large) && Empty Space is clicked
	else if (!cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall())
	{
		cPlyr->makeSmall();
		displaySectors = true;
	}
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//  Deals with Mouse Click actions in the Flight Phase
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::flightPhaseListener(sf::RenderWindow &gWindow, int tempType)
{
	// Starship (Small) is clicked
	if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			cPlyr->makeBig();
			displayFlightPath = false;
		}
	}
	// Starship (Large) is clicked
	else if (cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall()){}	// Do Nothing this Phase
	// Colony Zone (Large Icon) is clicked
	else if (!cPlyr->getColonyZone()->isSmall() && cPlyr->getColonyZone()->showIconOnly() && cPlyr->getColonyZone()->isIconTargeted(gWindow))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandColonyZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	// Trade Zone (Large Icon) is clicked
	else if (!cPlyr->getTradeZone()->isSmall() && cPlyr->getTradeZone()->showIconOnly() && cPlyr->getTradeZone()->isIconTargeted(gWindow))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandTradeZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	// Colony Zone (Large List) is clicked
	else if (!cPlyr->getColonyZone()->isSmall() && !cPlyr->getColonyZone()->showIconOnly() && cPlyr->getColonyZone()->isZoneTargeted(gWindow, tempType)){}	// Do Nothing this Phase
	// Trade Zone (Large List) is clicked
	else if (!cPlyr->getTradeZone()->isSmall() && !cPlyr->getTradeZone()->showIconOnly() && cPlyr->getTradeZone()->isZoneTargeted(gWindow, tempType)){}		// Do Nothing this Phase
	// Objects in the FlightPath are clicked but not the current planet
	else if (!phaseComplete && universe->flightPathTargeted(gWindow, tempType) && tempType != universe->getCurrentMove() - 1)
	{
		std::cout << "Flight Path Object " << tempType << " Clicked" << std::endl;
	}
	// Current Planet in the FlightPath is clicked
	else if (!phaseComplete && universe->flightPathTargeted(gWindow, tempType) && tempType == universe->getCurrentMove() - 1)
	{
		std::cout << "Current Planet: " << universe->getCurrentPlanet()->getName() << std::endl;
		std::cout << "Deck Num: " << universe->getCurrentPlanet()->getDeckNum() << std::endl;
		std::cout << "Type: " << universe->getCurrentPlanet()->getType() << std::endl;
	}
	// Current Planet's Menu in the FlightPath is clicked
	else if (!phaseComplete && universe->menuOptionTargeted(gWindow, tempType))
	{
		std::cout << "Current Planet Option " << tempType << " Clicked" << std::endl;
		switch (tempType + 1)
		{
		case 1:
			tradeMenu(gWindow, tempType);
			break;
		case 2:
			actionNum++;
			break;
		case 3:
			universe->continueFlight();
			break;
		case 4:
			phaseComplete = true;
			break;
		}
	}
	//  Starship (Large) && Empty Space is clicked
	else if (!cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall())
	{
		cPlyr->makeSmall();
		displayFlightPath = true;
	}

}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//  Deals with Mouse Click actions in the Trade Phase
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::tradePhaseListener(sf::RenderWindow &gWindow)
{
	int tempType;
	// Starship (Small) is clicked
	if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->makeBig();
	}
	// Starship (Large) is clicked
	else if (cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall()){}	// Do Nothing this Phase
	// Colony Zone (Large Icon) is clicked
	else if (!cPlyr->getColonyZone()->isSmall() && cPlyr->getColonyZone()->showIconOnly() && cPlyr->getColonyZone()->isIconTargeted(gWindow))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandColonyZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	// Trade Zone (Large Icon) is clicked
	else if (!cPlyr->getTradeZone()->isSmall() && cPlyr->getTradeZone()->showIconOnly() && cPlyr->getTradeZone()->isIconTargeted(gWindow))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandTradeZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	// Colony Zone (Large List) is clicked
	else if (!cPlyr->getColonyZone()->isSmall() && !cPlyr->getColonyZone()->showIconOnly() && cPlyr->getColonyZone()->isZoneTargeted(gWindow, tempType)){}	// Do Nothing this Phase
	// Trade Zone (Large List) is clicked
	else if (!cPlyr->getTradeZone()->isSmall() && !cPlyr->getTradeZone()->showIconOnly() && cPlyr->getTradeZone()->isZoneTargeted(gWindow, tempType)){}		// Do Nothing this Phase
	//  Starship (Large) && Empty Space is clicked
	else if (!cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall())
		cPlyr->makeSmall();
	//  Starship (Large) && Empty Space is clicked
	else if (!cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall())
		cPlyr->makeSmall();

}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//  Deals with Mouse Click actions in the Build Phase
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::buildPhaseListener(sf::RenderWindow &gWindow)
{
	int tempType;
	// Starship (Small) is clicked
	if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->makeBig();
	}
	// Starship (Large) is clicked
	else if (cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (cPlyr->getStarship()->bigLeftClicked(gWindow, statusUpdate, tempType))
				cPlyr->updateIcon(tempType);
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if (cPlyr->getStarship()->bigRightClicked(gWindow, statusUpdate, tempType))
				cPlyr->updateIcon(tempType);
		}
	}
	// Colony Zone (Large Icon) is clicked
	else if (!cPlyr->getColonyZone()->isSmall() && cPlyr->getColonyZone()->showIconOnly() && cPlyr->getColonyZone()->isIconTargeted(gWindow))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandColonyZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	// Trade Zone (Large Icon) is clicked
	else if (!cPlyr->getTradeZone()->isSmall() && cPlyr->getTradeZone()->showIconOnly() && cPlyr->getTradeZone()->isIconTargeted(gWindow))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandTradeZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	// Colony Zone (Large List) is clicked
	else if (!cPlyr->getColonyZone()->isSmall() && !cPlyr->getColonyZone()->showIconOnly() && cPlyr->getColonyZone()->isZoneTargeted(gWindow, tempType))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (cPlyr->getStarship()->gainItem(tempType, statusUpdate))
				cPlyr->updateIcon(tempType);
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if (cPlyr->getStarship()->loseItem(tempType, statusUpdate))
				cPlyr->updateIcon(tempType);
		}

	}
	// Trade Zone (Large List) is clicked
	else if (!cPlyr->getTradeZone()->isSmall() && !cPlyr->getTradeZone()->showIconOnly() && cPlyr->getTradeZone()->isZoneTargeted(gWindow, tempType))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (cPlyr->getStarship()->gainItem(tempType, statusUpdate))
				cPlyr->updateIcon(tempType);
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if (cPlyr->getStarship()->loseItem(tempType, statusUpdate))
				cPlyr->updateIcon(tempType);
		}
	}
	//  Starship (Large) && Empty Space is clicked
	else if (!cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall())
	{
		cPlyr->makeSmall();
	}

}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//  Deals with Mouse Click actions in the Flight Phase
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::tradeMenu(sf::RenderWindow &gWindow, int tempType)
{
	std::cout << "Trade Menu Here" << std::endl;
	std::cout << "Trade Complete" << std::endl;
	actionNum++;
	universe->continueFlight();

}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//
//  Configures the Flight Menu Options
//
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::updateFlightMenu(sf::RenderWindow &gWindow)
{
	for (int i = 0; i < MENUSIZE; i++)
		universe->getMenuItem(i)->icon->setQty(0);
	universe->getMenuItem(endFl)->icon->setQty(1);	////////////////////////////////////////////  
	if (universe->getCurrentMove() < cPlyr->getStarship()->getMaxDistance()) /////////////////////  THESE THREE LINES SHOULDNT BE HERE
		universe->getMenuItem(conFly)->icon->setQty(1); /////////////////////////////////////////
	if (universe->getCurrentPlanet()->getType() == 2)		//  PIRATE
	{
		//std::cout << "Pirate" << std::endl;
	}
	else                                                  //  NOT PIRATE
	{
		////////////////////////////////////////////////////////////////////////////////////////  THEY SHOULD BE HERE ONCE PIRATE IS IMPLETEMENTED			
		if (universe->getCurrentPlanet()->getType() == 0)		//  Trade Planet
		{
			universe->getMenuItem(trdW)->icon->setQty(1);
			if (universe->getCurrentPlanet()->getPts() == 1)	//  Can be colonized
			{
				universe->getMenuItem(colIt)->text.setString("Establish Trade Post");
				universe->getMenuItem(colIt)->text.setPosition({ 480, 660 });
				universe->getMenuItem(colIt)->icon->setQty(1);
			}
		}
		else if (universe->getCurrentPlanet()->getType() == 1)	//  Colony Planet
		{
			universe->getMenuItem(colIt)->text.setString("Colonize the Planet");
			universe->getMenuItem(colIt)->text.setPosition({ 500, 660 });
			universe->getMenuItem(colIt)->icon->setQty(1);
		}
		else                                                             //  Everything else
		{
			//std::cout << "Everything Else" << std::endl;
		}
	}
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//
//  Draws the Flight Menu
//
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::drawFlightMenu(sf::RenderWindow &gWindow)
{
	for (int i = 0; i < MENUSIZE; i++)
	{
		if (universe->getMenuItem(i)->icon->getQty() == 1)
		{
			universe->getMenuItem(i)->icon->draw(gWindow);
			gWindow.draw(universe->getMenuItem(i)->text);
		}
	}
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//
//  Draws the Flight Path
//
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::drawFlightPath(sf::RenderWindow &gWindow)
{
	float xPos = 100;
	float yPos = 150;
	//  Draws the flightPath taken so far
	for (int i = 0; i < universe->getCurrentMove(); i++)
	{
		universe->getCurrentSector()[i]->setScale(CRDSSCL);
		universe->getCurrentSector()[i]->setPosition({ xPos + i * 100, yPos });
		universe->getCurrentSector()[i]->draw(gWindow);
	}
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//
//  Draws the Current Planet
//
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::drawCurrentPlanet(sf::RenderWindow &gWindow)
{
	gWindow.draw(cPlanet);
	universe->getCurrentPlanet()->setScale(CRDLSCL);
	universe->getCurrentPlanet()->setPosition({ 825, 520 });
	universe->getCurrentPlanet()->draw(gWindow);
}