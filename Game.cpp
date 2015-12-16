//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#include "Game.h"

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Player Name Setup
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
Game::Game() : currentPlanet(txtMgr.getResource(UNIVERSECARDIMAGES), { 4, 13 }, 0, "", 0, 0, 0, "", 0, 0),
			friendPeople(txtMgr.getResource(FRIENDHERO), sf::Vector2f{ 900, 840 }, 1, sf::Vector2u(200, 200), { 1, 0 }),		
			heroPeople(txtMgr.getResource(FRIENDHERO), sf::Vector2f{ 975, 840 }, 1, sf::Vector2u(200, 200), { 0, 0 }),
			flightDie(txtMgr.getResource(SDIEFLE), sf::Vector2f{ 350, 525 }, 1, sf::Vector2u(80, 80)),
			flightMenu(fntMgr), buildMenu(fntMgr), pirateMenu(fntMgr), sectorMenu(fntMgr), trdMgr(txtMgr, fntMgr)
{  
	flightDie.initString(fntMgr.getResource(FNTFLE), { 440, 545 }, "", sf::Text::Bold);		

	combatDie = new Object*[2];
	combatDie[ply] = new Object(txtMgr.getResource(CDIEFLE), sf::Vector2f{ 350, 525 }, 1, sf::Vector2u(200, 200));
	combatDie[ply]->initString(fntMgr.getResource(FNTFLE), { 440, 545 }, "", sf::Text::Bold);

	combatDie[prt] = new Object(txtMgr.getResource(CDIEFLE), sf::Vector2f{ 350, 525 }, 1, sf::Vector2u(200, 200));
	combatDie[prt]->initString(fntMgr.getResource(FNTFLE), { 440, 545 }, "", sf::Text::Bold);
	
	P1 = new Player(txtMgr, fntMgr, "Player1", 1);		// Default names for bugtesting
	P2 = new Player(txtMgr, fntMgr, "Player2", 2);		// Default names for bugtesting
	cPlyr = P2;

	friendPeople.setScale({ .3f, .3f });				//  Will resize images if I don't need the icons for anything else
	heroPeople.setScale({ .3f, .3f });					//  Will resize images if I don't need the icons for anything else

	currentPlanet.setPosition({ 825, 520 });
	currentPlanet.initString(fntMgr.getResource(FNTFLE), { 835, 480 }, "Current Planet");

	createFlightMenu();
	createBuildMenu();
	createPirateMenu();
	createSectorMenu();

	phaseNameString.setFont(fntMgr.getResource(FNTFLE));
	phaseNameString.setPosition({ 200, 820 });
	phaseNameString.setString("Production Planet");
	
	errorString.setFont(fntMgr.getResource(FNTFLE));
	errorString.setPosition({ 550, 820 });
	errorString.setString("");
	errorString.setStyle(sf::Text::Bold);
	errorTimer = 255;
	
	infoString.setFont(fntMgr.getResource(FNTFLE));
	infoString.setPosition({ 40, 30 });
	infoString.setString("");
	infoString.setStyle(sf::Text::Bold);
	
	endPhaseString.setFont(fntMgr.getResource(FNTFLE));
	endPhaseString.setPosition({ 825, 25 });
	endPhaseString.setString("End of Phase\n(Press Enter)");
	endPhaseString.setStyle(sf::Text::Bold);
	endPhaseString.setScale({ 2, 2 });
	endPhaseString.setColor(sf::Color::Red);

	specialString.setFont(fntMgr.getResource(FNTFLE));
	specialString.setColor(sf::Color::Green);
	specialString.setPosition({ 650, 30 });
	specialString.setString("");
	specialString.setStyle(sf::Text::Bold);

	flightEventString.setFont(fntMgr.getResource(FNTFLE));
	flightEventString.setColor(sf::Color::Green);
	flightEventString.setPosition({ 500, 525 });
	flightEventString.setString("");
	flightEventString.setStyle(sf::Text::Bold);

	flightPathActions = new Object*[FLIGHTACTIONS];
	for (int i = 0; i < FLIGHTACTIONS; i++)
	{
		flightPathActions[i] = new Object(txtMgr.getResource(SYMBFLE), { 710, 610 }, 0, { 50, 50 }, { 6, 0 });
		flightPathActions[i]->setPosition(sf::Vector2f{ 70.0f + i * 100, 350 });
	}

	for (int i = 0; i < FLAGNUM; i++)
		flag[i] = false;

	universe = new Universe(txtMgr, fntMgr);
	screenSize = sf::Vector2u(1200, 900);
	gWindow.create(sf::VideoMode(screenSize.x, screenSize.y), "Starship Game");
	/*     -------------------These commented parts will be readded when I'm further along... 
	string tempName;
	cout << "Please enter Player 1 Name. \n";
	getline(cin, tempName);
	P1->setName(tempName);
	cout << "Please enter Player 2 Name. \n";
	getline(cin, tempName);
	P2->setName(tempName);
	*/
	ColonyCard* tempCard;
	tempCard = new ColonyCard(txtMgr.getResource(UNIVERSECARDIMAGES), { 4, 13 }, -1, "Colony: Alioth VIII", colony, Carbon, 1, 1);
	tempCard->setScale(CRDZNSCL);
	P1->getColonyZone()->push_back(tempCard);

	tempCard = new ColonyCard(txtMgr.getResource(UNIVERSECARDIMAGES), { 3, 13 }, -1, "Colony: Megrez VII", colony, Fuel, 1, 1);
	tempCard->setScale(CRDZNSCL);
	P2->getColonyZone()->push_back(tempCard);	
	cPhase = production;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Checks for win condition and toggles the current player
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::gameLoop()
{
//	string choice = "";  // temp until win condition is set
//	while (toupper(choice[0]) != 'Q')  // mimics the checkwin loop.
//	{
	//cPlyr == P1 ? cPlyr = P2 : cPlyr = P1;	// toggles between players
	//cPlyr->updatePlayerIcon();
//		cout << "CheckWin will be here.\n";
//		gameTurn();
//		cout << "Q to Toggle Win Condition\n";
//		cin >> choice;
//	}
	int tempNum;
	gWindow.setKeyRepeatEnabled(false);

	while (gWindow.isOpen())
	{
		if (!flag[phaseSetupComplete])
			phaseSetup();
		while (gWindow.pollEvent(event))		
		{
			switch (event.type) 
			{
			case sf::Event::Closed:
				gWindow.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					gWindow.close();
				if (event.key.code == sf::Keyboard::Return && flag[phaseComplete])
					endPhase();
				if (event.key.code == sf::Keyboard::F1)
					cPlyr->fillHolds();
				break;
			case sf::Event::MouseButtonPressed:
				switch (cPhase)
				{
				case production:
					if (trdMgr.isActive())
						tradeMenuListener();
					productionPhaseListener();
					break;
				case flight:
					if (sectorMenu.isActive())
						preFlightListener(tempNum);
					else if (pirateMenu.isActive())
						pirateMenuListener();
					else
					{
						flightPhaseListener(tempNum);
						if (trdMgr.isActive())
							tradeMenuListener();
					}
					break;
				case tradeBuild:
					buildPhaseListener(tempNum);
					if (trdMgr.isActive() && (!flag[buildTradeBegin] != !flag[buildTradeEnd]))
						tradeMenuListener();					
					break;
				}			
			case sf::Event::MouseMoved:
				switch (cPhase)
				{
				case production:
					break;
				case flight:
					//if (sectorMenu.isActive())
					//{					
					//	std::cout << std::endl;
					//	if (universe->sectorsTargeted(gWindow, tempNum) && cPlyr->getStarship()->isSmall())
					//		std::cout << "Sector " << tempNum + 1 << " Glows" << std::endl;
					//}
					break;
				case tradeBuild:
					//std::cout << std::endl;
					//if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall())
					//	std::cout << "P1 Ship Glows" << std::endl;
					break;
				}
			}				
		}

		gWindow.clear();
		drawGameWindow();				
		gWindow.display();
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  draws the icons and stats for game Window
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::drawGameWindow()
{
	universe->getBoard()->draw(gWindow);
	switch (cPhase)
	{
	case production:
		flightDie.draw(gWindow);
		break;
	case flight:		
		sectorMenu.draw(gWindow);
		updateFlightMenu();
		flightMenu.draw(gWindow);			
		showFlightPath();				
		pirateMenu.draw(gWindow);	
		break;
	case tradeBuild:
		break;
	}

	// Non Phase Specific Drawables
	drawCurrentPlanet();
	trdMgr.draw(gWindow);	
	gWindow.draw(phaseNameString);
	gWindow.draw(infoString);
	gWindow.draw(specialString);
	gWindow.draw(flightEventString);
	cPlyr->draw(gWindow);	

	if (cPlyr->isFriend())
		friendPeople.draw(gWindow);
	if (cPlyr->isHero())
		heroPeople.draw(gWindow);

	if (statusUpdate.length())
	{
		errorTimer = 2550;
		errorString.setString(statusUpdate);
	}
	statusUpdate.clear();

	if (errorTimer){
		errorString.setColor(sf::Color(255, 0, 0, errorTimer / 10));
		gWindow.draw(errorString);		
		errorTimer--;
	}
	if (flag[phaseComplete]){
		gWindow.draw(endPhaseString);
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  inital phase setup
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::phaseSetup()
{	
	std::string tempString;
	flag[phaseComplete] = false;	
	int resAvail[NUMRESOURCES] = { 0 };
	switch (cPhase)
	{
	case production:
		phaseNameString.setString("Production Phase");
		cPlyr->makeBig();
		cPlyr->expandColonyZone();		
		rollFlightDie();
		cPlyr->getStarship()->calcMaxDistance(flightDie.getQty());
		tempString.clear();
		specialString.setPosition({ 525, 30 });

		if (cPlyr->getColonyZone()->findResource(flightDie.getQty(), resAvail))
		{
			tempString += " Resource(s) in Colony Zone Found!";
			if (anyResourcesInListAvailable(resAvail))
			{
				specialString.setString("Chose a colony resource");
				currentPlanet.setSrcPos(CARDBACK);
				flag[cPlanetActive] = true;
				trdMgr.setActive(true);
				trdMgr.setAvailableResources(resAvail);
				gainOneResource();
			}
			else
			{
				specialString.setString("No Choices Available");
				flag[phaseComplete] = true;
			}
		}
		else
		{
			tempString += " No Resources in Colony Zone";	
			flag[phaseComplete] = true;
		}	

		infoString.setString(tempString);			
		break;
	case flight:
		cPlyr->makeSmall();
		actionNum = 0;
		sectorMenu.setActive(true);	
		pirateMenu.setActive(false);
		flightMenu.setActive(false);
		flag[adventureAvailable] = false;
		flag[cPlanetActive] = false;
		flag[flightPathActive] = false;
		infoString.setString("Flight: 0 / " + std::to_string(cPlyr->getStarship()->getMaxDistance()) + "\nMax Actions: 0 / " + 
			std::to_string(cPlyr->getStarship()->getMaxActions()));		
		phaseNameString.setString("Flight Phase");
		specialString.setString("Select a Sector");
		specialString.setPosition({ 425, 40 });
		break;
	case tradeBuild:
		phaseNameString.setString("Trade & Build Phase");
		cPlyr->makeBig();
		numPlntsTrd = 0;
		flightEventString.setString("");
		infoString.setString("Trades: " + std::to_string(numPlntsTrd) + " / 2");
		buildMenu.setActive(true);
		flag[buildTradeBegin] = false;
		flag[buildTradeEnd] = false;
		flag[phaseComplete] = true;		//  Only until there is an actual phase coded
		break;
	}
	flag[phaseSetupComplete] = true;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Deals with Mouse Click actions in the Production Phase
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::productionPhaseListener()
{
	int pos;
	int cType = trdMgr.resourceChosen();
	// Starship (Small) is clicked
	if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall())
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			cPlyr->makeBig();
			flightDie.setPosition({ 350, 525 });
			flightDie.setTextPosition({ 440, 545 });
		}
	}
	// Colony Zone (Large Icon) is clicked
	if (!cPlyr->zonesSmall() && cPlyr->getColonyZone()->getIconOnly() && cPlyr->getColonyZone()->isIconTargeted(gWindow))
	{
		if (event.mouseButton.button == sf::Mouse::Left)
			cPlyr->expandColonyZone();
		else if (event.mouseButton.button == sf::Mouse::Right)
			cPlyr->makeBig();
	}
	// Trade Zone (Large Icon) is clicked
	else if (!cPlyr->zonesSmall() && cPlyr->getTradeZone()->getIconOnly() && cPlyr->getTradeZone()->isIconTargeted(gWindow))
	{
		if (event.mouseButton.button == sf::Mouse::Left)
			cPlyr->expandTradeZone();
		else if (event.mouseButton.button == sf::Mouse::Right)
			cPlyr->makeBig();
	}
	// Colony Zone (Large List) is clicked and player is entitled to a production resource
	else if (!cPlyr->zonesSmall() && !cPlyr->getColonyZone()->getIconOnly() && cPlyr->getColonyZone()->isZoneTargeted(gWindow, cType, pos))
	{
		if (trdMgr.isActive() && event.mouseButton.button == sf::Mouse::Left)	
			if (cPlyr->getColonyZone()->resourceMatchesActNum(cType, flightDie.getQty()))
			{
				currentPlanet.setSrcPos(cPlyr->getColonyZone()->getZoneItem(pos)->getSrcPos());

			}
	}
	// Trade Zone (Large List) is clicked
	else if (!cPlyr->getTradeZone()->getIconOnly() && cPlyr->getTradeZone()->isZoneTargeted(gWindow, cType, cType)){}		// Do Nothing this Phase
	//  Trade Menu is targeted
	else if (trdMgr.iconsTargeted(gWindow)){}	// Do Nothing this Phase
	//  Starship (Large) && Empty Space is clicked
	else if (!cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall()){
		cPlyr->makeSmall();
		flightDie.setPosition({ 250, 725 });
		flightDie.setTextPosition({ 340, 745 });
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Flight Phase Sector Selection Listener
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::preFlightListener(int &tempType){
	// Starship (Small) is clicked
	if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall())
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			cPlyr->makeBig();
			sectorMenu.hideAll();
		}
	}
	// Starship (Large) is clicked
	else if (cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall()){}	// Do Nothing this Phase
	// Colony Zone (Large Icon) is clicked
	else if (!cPlyr->zonesSmall() && cPlyr->getColonyZone()->getIconOnly() && cPlyr->getColonyZone()->isIconTargeted(gWindow))
	{
		if (event.mouseButton.button == sf::Mouse::Left)
			cPlyr->expandColonyZone();
		else if (event.mouseButton.button == sf::Mouse::Right)
			cPlyr->makeBig();
	}
	// Trade Zone (Large Icon) is clicked
	else if (!cPlyr->zonesSmall() && cPlyr->getTradeZone()->getIconOnly() && cPlyr->getTradeZone()->isIconTargeted(gWindow))
	{
		if (event.mouseButton.button == sf::Mouse::Left)
			cPlyr->expandTradeZone();
		else if (event.mouseButton.button == sf::Mouse::Right)
			cPlyr->makeBig();
	}
	// Colony Zone (Large List) is clicked
	else if (!cPlyr->zonesSmall() && !cPlyr->getColonyZone()->getIconOnly() && cPlyr->getColonyZone()->isZoneTargeted(gWindow, tempType, tempType)){}	// Do Nothing this Phase
	// Trade Zone (Large List) is clicked
	else if (!cPlyr->zonesSmall() && !cPlyr->getTradeZone()->getIconOnly() && cPlyr->getTradeZone()->isZoneTargeted(gWindow, tempType, tempType)){}		// Do Nothing this Phase
	//  Sector is Clicked  (Initializes upcoming Flight Phase)
	else if (sectorMenu.isMenuTargeted(gWindow, tempType) && cPlyr->getStarship()->isSmall())
	{
		sectorMenu.setActive(false);
		flightMenu.setActive(true);
		flag[flightPathActive] = true;
		flag[cPlanetActive] = true;
		universe->initializeFlightPath(tempType);
		currentPlanet.setSrcPos(universe->getCurrentPlanet()->getSrcPos());
		for (int i = 0; i < FLIGHTACTIONS; i++)
			flightPathActions[i]->setSrcPosX(6);
		specialString.setString("");
		return;
	}
	//  Starship (Large) && Empty Space is clicked
	else if (!cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall())
	{
		cPlyr->makeSmall();
		sectorMenu.unhideAll();
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Deals with Mouse Click actions in the Flight Phase
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::flightPhaseListener(int tempType)
{	
	// Starship (Small) is clicked
	if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall())
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			cPlyr->makeBig();
			flag[flightPathActive] = false;
		}
	}
	// Starship (Large) is clicked
	else if (cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall()){}	// Do Nothing this Phase
	// Colony Zone (Large Icon) is clicked
	else if (!cPlyr->zonesSmall() && cPlyr->getColonyZone()->getIconOnly() && cPlyr->getColonyZone()->isIconTargeted(gWindow))
	{
		if (event.mouseButton.button == sf::Mouse::Left)
			cPlyr->expandColonyZone();
		else if (event.mouseButton.button == sf::Mouse::Right)
			cPlyr->makeBig();
	}
	// Trade Zone (Large Icon) is clicked
	else if (!cPlyr->zonesSmall() && cPlyr->getTradeZone()->getIconOnly() && cPlyr->getTradeZone()->isIconTargeted(gWindow))
	{
		if (event.mouseButton.button == sf::Mouse::Left)
			cPlyr->expandTradeZone();
		else if (event.mouseButton.button == sf::Mouse::Right)
			cPlyr->makeBig();
	}
	// Colony Zone (Large List) is clicked
	else if (!cPlyr->zonesSmall() && !cPlyr->getColonyZone()->getIconOnly() && cPlyr->getColonyZone()->isZoneTargeted(gWindow, tempType, tempType)){}	// Do Nothing this Phase
	// Trade Zone (Large List) is clicked
	else if (!cPlyr->zonesSmall() && !cPlyr->getTradeZone()->getIconOnly() && cPlyr->getTradeZone()->isZoneTargeted(gWindow, tempType, tempType)){}		// Do Nothing this Phase
	// Objects in the FlightPath are clicked but not the current planet
	else if (flag[flightPathActive] && universe->flightPathTargeted(gWindow, tempType) && tempType != universe->getCurrentMove() - 1)
	{
		if (!pirateMenu.isActive())
		{
			currentPlanet.setSrcPos(universe->getFlightPathPlanet(tempType)->getSrcPos());
			currentPlanet.setString("Previous Planet");
			flightMenu.setActive(false);
			if (trdMgr.isActive())
			{
				flightEventString.setString("Trade Paused");
				trdMgr.pauseTrade();
			}
		}
	}
	// Current Planet in the FlightPath is clicked
	else if (flag[flightPathActive] && universe->getCurrentPlanet()->isTargeted(gWindow))
	{		
		if (!pirateMenu.isActive())
		{
			currentPlanet.setSrcPos(universe->getCurrentPlanet()->getSrcPos());
			currentPlanet.setString("Current Planet");
			if (!flag[phaseComplete] && !trdMgr.isActive())
				flightMenu.setActive(true);	
			if (trdMgr.isActive())
			{
				flightEventString.setString("Trade In Progress");
				trdMgr.unpauseTrade();
			}
		}
	}
	// Current Planet (Large Icon) clicked
	else if (isCPlanetTargeted()) { ; }
	//  Current Planet's Menu in the FlightPath is clicked
	else if (!flag[phaseComplete] && !trdMgr.isActive() && flightMenu.isActive() && flightMenu.isMenuTargeted(gWindow, tempType))
	{
		switch (tempType)
		{
		case estTP:	//  Establish Post
			if (cPlyr->getStarship()->shipAvailabletoCompleteAction(tradeShip, tempType, statusUpdate))
			{
				cPlyr->getStarship()->loseItem(tempType, statusUpdate);
				cPlyr->getTradeZone()->push_back((TradeCard*)universe->getCurrentPlanet());
				cPlyr->getTradeZone()->updateZone(cPlyr->getTradeZone()->getPosition(), cPlyr->getTradeZone()->getScale(), cPlyr->getTradeZone()->getIconOnly());
				cPlyr->addFrdPt();
				updateFriendOfThePeople();
				universe->replaceCurrentPlanet();
				flightPathActions[universe->getCurrentMove() - 1]->setSrcPosX(1);
				flag[justActed] = true;
				actionNum++;
			}
			infoString.setString(statusUpdate);
			break;
		case colIt:	//  Colonize
			if (cPlyr->getStarship()->shipAvailabletoCompleteAction(colonyShip, tempType, statusUpdate))
			{
				cPlyr->getStarship()->loseItem(tempType, statusUpdate);
				cPlyr->getColonyZone()->push_back((ColonyCard*)universe->getCurrentPlanet());
				cPlyr->getColonyZone()->updateZone(cPlyr->getColonyZone()->getPosition(), cPlyr->getColonyZone()->getScale(), cPlyr->getColonyZone()->getIconOnly());
				cPlyr->addVicPt();
				flightPathActions[universe->getCurrentMove() - 1]->setSrcPosX(0);
				universe->replaceCurrentPlanet();
				flag[justActed] = true;
				actionNum++;
			}
			infoString.setString(statusUpdate);
			break;
		case trdW:	//  Trade with Planet
			initTradeMenu(tempType);
			break;
		case conFly:	// Continue Flight
			if (!flag[justActed])
				flightPathActions[universe->getCurrentMove() - 1]->setSrcPosX(4);
			currentPlanet.setString("Current Planet");
			universe->continueFlight();
			currentPlanet.setSrcPos(universe->getCurrentPlanet()->getSrcPos());
			flag[justActed] = false;
			pirateMenu.setActive(false);
			flightMenu.setActive(true);
			flightEventString.setString("");
			universe->makeAdventuresAvailable();
			break;
		case adv:
			if (flag[adventureAvailable] && universe->getAdvCard(curAdv)->isAvailable())
			{
				if (startAdventure())
					adventureRewards();	
			}
			else if (!flag[adventureAvailable] && universe->getAdvCard(curAdv)->isAvailable())
			{
				statusUpdate = "Select an adventure on " + universe->getCurrentPlanet()->getName();
				flightEventString.setString("");
			}
			else if (flag[adventureAvailable] && !universe->getAdvCard(curAdv)->isAvailable())
			{
				statusUpdate = "New Adventures are Not Available this Flight";
				flightEventString.setString("");
			}
			break;
		case endFl:	//  End Flight
			flag[phaseComplete] = true;
			flightMenu.setActive(false);
			flightEventString.setString("");
			break;
		}
	}
	//  Adventure Card is Clicked
	else if (universe->isCurrentAdventureTargeted(gWindow, tempType) && !pirateMenu.isActive())
	{
		curAdv = tempType;
		currentPlanet.setSrcPos(universe->getAdvCard(curAdv)->getSrcPos());
		currentPlanet.setString("Adventure");
		
		if (universe->atCurrentAdventurePlanet(curAdv))
		{
			flag[adventureAvailable] = true;
			if (!universe->getAdvCard(curAdv)->isAvailable())
				statusUpdate = "New Adventures are Not Available this Flight";
			else
				flightEventString.setString(getAdvReqString());
		}
		else
		{
			flag[adventureAvailable] = false;
			flightEventString.setString("");
			statusUpdate = "Adventure Only Available on " + universe->getAdvCard(curAdv)->getName();
		}
		if (trdMgr.isActive())
		{
			flightEventString.setString("Trade Paused");
			trdMgr.pauseTrade();
		}
	}
	//  Starship (Large) && Empty Space is clicked
	else if (!cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall() && !trdMgr.iconsTargeted(gWindow))
	{
		cPlyr->makeSmall();
		flag[flightPathActive] = true;
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Deals with Mouse Click actions when the tradeMenu is displayed
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::tradeMenuListener()
{	
	int temp = -1;
	//  If player has option to chose resource but hasn't yet done so
	if (trdMgr.choosingResource() && !trdMgr.resourceChosen())
	{
		
		if (trdMgr.resourceTargeted(gWindow, temp))
		{
			trdMgr.setTradedResource(temp);
			trdMgr.setResourceChosen(true);
			trdMgr.greyAllButChosesnResources();
		}
	}
	//  If player doesn't have the option to chose resource (auto chooses the resource)
	else if (!trdMgr.choosingResource())
	{
		trdMgr.setResourceChosen(true);
		//flightEventString.setString("Trade In Progress");
	}	
	//  If the plus icon has been selected
	if (event.mouseButton.button == sf::Mouse::Left && trdMgr.plusTargeted(gWindow))
	{
		if (cPlyr->canAfford(trdMgr.getCost(), statusUpdate) && cPlyr->getStarship()->gainItem(trdMgr.getTradedResource(), statusUpdate))
		{
			cPlyr->updateIcon(trdMgr.getTradedResource());
			cPlyr->subAstro(trdMgr.getCost());
			cPlyr->updateIcon(astro);				
			trdMgr.tradNumPlusOne();
		}		
	}
	//  If the minus icon has been selected
	else if (trdMgr.resourceChosen() && event.mouseButton.button == sf::Mouse::Left && trdMgr.minusTargeted(gWindow))
	{
		if (cPlyr->getStarship()->loseItem(trdMgr.getTradedResource(), statusUpdate))
		{
			cPlyr->updateIcon(trdMgr.getTradedResource());
			cPlyr->addAstro(trdMgr.getCost());
			cPlyr->updateIcon(astro);				
			trdMgr.tradNumPlusOne();
		}
	}
	//  If the Check Icon has been selected
	else if (event.mouseButton.button == sf::Mouse::Left && trdMgr.checkTargeted(gWindow))
	{
		if (cPhase == flight)
		{
			flag[justActed] = true;
			flightPathActions[universe->getCurrentMove() - 1]->setSrcPosX(3);					
			flightMenu.setActive(true);
			//  If the resource was granted by a pirate
			if (universe->getCurrentPlanet()->getType() == pirate)
				endPiratePhase();
			else if (flag[adventureReward])
				endAdventurePhase();
			else
				actionNum++;
		}
		else if (cPhase == tradeBuild)
		{
			numPlntsTrd++;
			if (numPlntsTrd == 2)
				flag[buildTradeEnd] = true;
			flag[cPlanetActive] = false;
		}
		else
		{
			flag[phaseComplete] = true;
			flag[cPlanetActive] = false;
		}
		flightEventString.setString("Trade Complete");	
		trdMgr.setActive(false);
	}
	//  If the Cancel Icon has been selected
	else if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && trdMgr.cancelTargeted(gWindow))
	{
		trdMgr.restoreResources(cPlyr);
		flightEventString.setString("Trade Cancelled");

		trdMgr.setChoosingResource(false);
		trdMgr.setResourceChosen(false);

		switch (cPhase)
		{
		case production:
			trdMgr.setLimit(1);
			trdMgr.setTransaction("Buy");
			gainOneResource();
			break;
		case flight:
			if (universe->getCurrentPlanet()->getType() == pirate)
			{
				trdMgr.setLimit(1);
				trdMgr.setTransaction("Buy");
				gainOneResource();
			}
			// Adventure Resource
			else if (flag[adventureReward])
			{
				trdMgr.setLimit(1);
				trdMgr.setTransaction("Buy");
				gainOneResource();
			}
			else
			{
				trdMgr.setActive(false);
				flightMenu.setActive(true); 
			}		
			break;
		case tradeBuild:
			flag[cPlanetActive] = false;
			break;
		}
	}
	trdMgr.updateTradeIcons(cPlyr);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Deals with Mouse Click actions in the Pirate Menu
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::pirateMenuListener()
{
	if (pirateMenu.isItemTargeted(gWindow, pay))			//  If the player decides to pay
	{
		if (cPlyr->canAfford(universe->getCurrentPlanet()->getCost(), statusUpdate))
		{
			cPlyr->subAstro(universe->getCurrentPlanet()->getCost());
			specialString.setString("");
			flightEventString.setString("Bribe Payed");
			flightPathActions[universe->getCurrentMove() - 1]->setSrcPosX(3);
			flag[justActed] = true;
			pirateMenu.setActive(false);
			flightMenu.setActive(true);
			//  Reveal the Pirate
			currentPlanet.setSrcPos(universe->getCurrentPlanet()->getSrcPos());
		}
	}
	else	if (pirateMenu.isItemTargeted(gWindow, fight))		// If the player decides to fight
	{	
		rollCombatDie(ply);
		rollCombatDie(prt);
		int plyRes = combatDie[ply]->getQty() + cPlyr->getStarship()->totalLasers();
		int pirRes = combatDie[ply]->getQty() + universe->getCurrentPlanet()->getCannons();
		std::cout << "Player: " << plyRes << "   " << combatDie[ply]->getQty() << " + " << cPlyr->getStarship()->totalLasers() << std::endl;
		std::cout << "Pirate: " << pirRes << "   " << combatDie[prt]->getQty() << " + " << universe->getCurrentPlanet()->getCannons() << std::endl;
		if (plyRes >= pirRes)			//  If the player wins
		{
			trdMgr.setActive(true); 
			flightEventString.setString("Choose a resource");
			specialString.setString("VICTORY!!! Gain a resource and a fame point");
			cPlyr->addFmPt();
			updateHeroOfThePeople();
			flightPathActions[universe->getCurrentMove() - 1]->setSrcPosX(2);
			trdMgr.setLimit(1);
			trdMgr.setTransaction("Buy");
			gainOneResource();		
		}
		else                              	//  If the pirate wins
		{
			specialString.setString("Flight Complete");
			if (universe->getCurrentPlanet()->getResult() == "N/A")
			{
				flag[phaseComplete] = true;
				flightEventString.setString("DEFEAT!\n\nRESULT: Flight Ends");
			}
			else
			{
				std::cout << "RESULT: " << universe->getCurrentPlanet()->getResult() << std::endl;
				std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl; //  Implement this!!!!!!!!!!!!!!!!!!!!!!!!!
				flightEventString.setString("DEFEAT!\n\nRESULT:");
			}				
			flightMenu.setActive(false);				
			pirateMenu.setActive(false);
		}
		//  Reveal the Pirate
		currentPlanet.setSrcPos(universe->getCurrentPlanet()->getSrcPos());
	}	
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Deals with Mouse Click actions in the Build Phase
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::buildPhaseListener(int &tempNum)
{
	int tempPos = -1;
	// Starship (Small) is clicked
	if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall())
	{
		if (event.mouseButton.button == sf::Mouse::Left)
			cPlyr->makeBig();
	}
	// Starship (Large) Build Icon is selected
	else if (cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall() && buildMenu.isMenuTargeted(gWindow, tempNum))
	{
		if (event.mouseButton.button == sf::Mouse::Left)
			if (buildShipObject(tempNum) && flag[buildTradeBegin] && !flag[buildTradeEnd])
			{
				flag[buildTradeEnd] = true;
				statusUpdate = "All further trades this turn are cancelled";
			}
	}
	////////////////////////////////////  BUGTESTING ----  Enable changing of resource quantities
	//else if (cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall())
	//{
	//	if (event.mouseButton.button == sf::Mouse::Left)
	//	{
	//		if (cPlyr->getStarship()->bigLeftClicked(gWindow, statusUpdate, tempNum))
	//			cPlyr->updateIcon(tempNum);
	//	}
	//	else if (event.mouseButton.button == sf::Mouse::Right)
	//	{
	//		if (cPlyr->getStarship()->bigRightClicked(gWindow, statusUpdate, tempNum))
	//			cPlyr->updateIcon(tempNum);
	//	}
	//}
	// Colony Zone (Large Icon) is clicked
	else if (!cPlyr->zonesSmall() && cPlyr->getColonyZone()->getIconOnly() && cPlyr->getColonyZone()->isIconTargeted(gWindow))
	{
		if (event.mouseButton.button == sf::Mouse::Left)
			cPlyr->expandColonyZone();
		else if (event.mouseButton.button == sf::Mouse::Right)
			cPlyr->makeBig();
	}
	// Trade Zone (Large Icon) is clicked
	else if (!cPlyr->zonesSmall() && cPlyr->getTradeZone()->getIconOnly() && cPlyr->getTradeZone()->isIconTargeted(gWindow))
	{
		if (event.mouseButton.button == sf::Mouse::Left)
			cPlyr->expandTradeZone();
		else if (event.mouseButton.button == sf::Mouse::Right)
			cPlyr->makeBig();
	}
	// Colony Zone (Large List) is clicked
	else if (!cPlyr->zonesSmall() && !cPlyr->getColonyZone()->getIconOnly() && cPlyr->getColonyZone()->isZoneTargeted(gWindow, tempNum, tempNum)){}
	// Trade Zone (Large List) is clicked
	else if (!cPlyr->zonesSmall() && !cPlyr->getTradeZone()->getIconOnly() && !flag[buildTradeEnd] && cPlyr->getTradeZone()->isZoneTargeted(gWindow, tempNum, tempPos))
		initTradeMenu(tempPos);
	else if (!cPlyr->zonesSmall() && !cPlyr->getTradeZone()->getIconOnly() && flag[buildTradeEnd] && cPlyr->getTradeZone()->isZoneTargeted(gWindow, tempNum, tempPos))
		statusUpdate = "Max Trades Reached";
	else if (trdMgr.iconsTargeted(gWindow) && (!flag[buildTradeBegin] != !flag[buildTradeEnd])){}
	//  Starship (Large) && Empty Space is clicked
	else if (!cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall())
		cPlyr->makeSmall();
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Sets up and maintains tradeMenu Details
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::initTradeMenu(int tempPos)
{
	std::cout << "initTradeMenu" << std::endl;
	switch (cPhase)
	{
	case flight:
		currentPlanet.copyData((TradeCard*)universe->getCurrentPlanet());
		break;
	case tradeBuild:
		flag[buildTradeBegin] = true;
		currentPlanet.copyData(cPlyr->getTradeZone()->getZoneItem(tempPos));
		flag[cPlanetActive] = true;
		break;
	}

	flightMenu.setActive(false);
	flightEventString.setString("Trade In Progress");
	trdMgr.setActive(true);
	trdMgr.saveResources(cPlyr);

	// If the card allows for any resource to be chosen
	if (currentPlanet.getResource() == 6) 
	{
		//  calls the gainOneResource function getLimit() times
		for (int i = currentPlanet.getLimit(); i > 0; i--)
			gainOneResource();
		return;
	}

	trdMgr.saveResources(cPlyr);
	trdMgr.setTransaction(currentPlanet.getTransaction());
	trdMgr.setLimit(currentPlanet.getLimit());
	trdMgr.setCost(currentPlanet.getCost());
	trdMgr.setTradedResource(currentPlanet.getResource());
	trdMgr.greyAllButChosesnResources();
	trdMgr.setChoosingResource(false);
	trdMgr.setResourceChosen(false);
	trdMgr.updateTradeIcons(cPlyr);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Checks to see if a resource is available and initiates tradeMenu with no cost.
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::gainOneResource()
{	
	std::cout << "GainOneResource" << std::endl;
	if (!anyResAvail())
	{
		flag[justActed] = true;
		statusUpdate = "All Cargo Holds Full";
		flightEventString.setString("No Resources Gained");
		trdMgr.setActive(false);
		flightMenu.setActive(true);
		//  If the resource was granted by a pirate
		if (universe->getCurrentPlanet()->getType() == pirate)
		{
			endPiratePhase();
		}
		else if (flag[adventureReward])
		{
			endAdventurePhase();
		}
		return;
	}
	pirateMenu.setActive(false);
	flightMenu.setActive(false);	
	flightEventString.setString("Choose a Resource");
	trdMgr.saveResources(cPlyr);
	trdMgr.setTransaction("Buy");
	trdMgr.setLimit(1);
	trdMgr.setCost(0);
	trdMgr.greyUnavailResources(cPlyr);
	trdMgr.setChoosingResource(true);
	trdMgr.setResourceChosen(false);
	trdMgr.updateTradeIcons(cPlyr);	
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Configures the Flight Menu Options
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::updateFlightMenu()
{
	if (flightMenu.isActive())
	{
		flightMenu.hideAll();
		infoString.setString("Flight: " + std::to_string(universe->getCurrentMove()) + " / " + std::to_string(cPlyr->getStarship()->getMaxDistance())
			+ "\nMax Actions: " + std::to_string(actionNum) + " / " + std::to_string(cPlyr->getStarship()->getMaxActions())
			+ "\nFlight Sector: " + std::to_string(universe->getCurrentSectorNum() + 1));

		if (universe->getCurrentPlanet()->getType() == 2 && !flag[justActed])			//  PIRATE'S CHOICE
		{
			currentPlanet.setSrcPos(CARDBACK);	
			pirateMenu.setActive(true);
			flightMenu.setActive(false);
			specialString.setString("There is a Pirate Here!  They demand " + std::to_string(universe->getCurrentPlanet()->getCost()) + " astro!");
			flightEventString.setString("Bribe / Fight");
		}
		else  //  NOT PIRATE
		{
			flightMenu.unhideItem(endFl);
			if (universe->getCurrentMove() < cPlyr->getStarship()->getMaxDistance() && actionNum < cPlyr->getStarship()->getMaxActions())
				flightMenu.unhideItem(conFly);
			if (universe->getCurrentPlanet()->getType() == 0 && actionNum < cPlyr->getStarship()->getMaxActions())						//  Trade Planet
			{
				if (!flag[justActed] && actionNum < cPlyr->getStarship()->getMaxActions())
				{
					flightMenu.unhideItem(trdW);
					if (universe->getCurrentPlanet()->getPts() == 1)															//  Can Establish Trade Post
						flightMenu.unhideItem(estTP);
				}
			}
			else if (universe->getCurrentPlanet()->getType() == 1 && !flag[justActed] && actionNum < cPlyr->getStarship()->getMaxActions())	//  Colony Planet
				flightMenu.unhideItem(colIt);
			else if (universe->getCurrentPlanet()->getType() == 3 && actionNum < cPlyr->getStarship()->getMaxActions())					//  Adventure Planet
			{
				if (universe->atAdventurePlanet())
					flightMenu.unhideItem(adv);
			}
		}
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  displays the flight path, the flight action path, and the 
//  adventure planets if it's currently active
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::showFlightPath()
{
	if (flag[flightPathActive])
	{
		float xPos = 50;
		float yPos = 200;
		int cMove = universe->getCurrentMove();
		int numToDisplay = pirateMenu.isActive() ? cMove - 1 : cMove;
		//  Draws the flightPath and actionPath taken so far (doesn't display current planet if Pirate Attack is occuring)
		for (int i = 0; i < numToDisplay; i++)
		{
			universe->getCurrentSector()[i]->setScale(CRDSSCL);
			universe->getCurrentSector()[i]->setPosition({ xPos + i * 100, yPos });
			universe->getCurrentSector()[i]->draw(gWindow);
			flightPathActions[i]->draw(gWindow);
		}
		universe->drawCurrentAdventures(gWindow);
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Checks for Friend of the people on both players
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::updateFriendOfThePeople()
{
	//  If current player has less than three friend points...
	if (cPlyr->getStatQty(frdPt) < 3)
		return;
	int p1pts = getP1()->getStatQty(frdPt);
	int p2pts = getP2()->getStatQty(frdPt);

	if (p1pts == p2pts)
	{
		getP1()->toggleFriend(false);
		getP2()->toggleFriend(false);
		statusUpdate = "Friend of the People Lost";
	}
	else if (p1pts > p2pts)
	{
		getP1()->toggleFriend(true);
		getP2()->toggleFriend(false);
	}
	else
	{
		getP1()->toggleFriend(false);
		getP2()->toggleFriend(true);
	}

}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Checks for Hero of the people on both players
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::updateHeroOfThePeople()
{
	//  If current player has less than three hero points...
	if (cPlyr->getStatQty(fmPt) < 3)
		return;
	int p1pts = getP1()->getStatQty(fmPt);
	int p2pts = getP2()->getStatQty(fmPt);

	if (p1pts == p2pts)
	{
		getP1()->toggleHero(false);
		getP2()->toggleHero(false);
		statusUpdate = "Hero of the People Lost";
	}
	else if (p1pts > p2pts)
	{
		getP1()->toggleHero(true);
		getP2()->toggleHero(false);
	}
	else
	{
		getP1()->toggleHero(false);
		getP2()->toggleHero(true);
	}

}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Checks to see if a any resources in the parameter array exist
//  in the holds of the startship
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Game::anyResourcesInListAvailable(int resAvail[])
{
	for (int i = 0; i < 6; i++){
		if (resAvail[i] && !cPlyr->getStarship()->holdFull(i)){
			return true;
		}
	}
	return false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Checks to see if a all resources in the parameter array exist
//  in the holds of the startship
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Game::allRequirementsMet(int resAvail[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (resAvail[i] > cPlyr->getStarship()->getShipObjectQty(i))
		{
			statusUpdate = "Requirements Not Met";
			return false;
		}		
	}
	return true;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Checks to see if a any resources available 
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Game::anyResAvail()
{
	for (int i = 0; i < 6; i++){
		if (!cPlyr->getStarship()->holdFull(i)){
			return true;
		}
	}
	return false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Attempts to buy an item chosen buy player
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Game::buildShipObject(int item)
{
	int requirements[6] = { 0, 0, 0, 0, 0, 0 };
	int pos = -99, type = -1;
	switch (item)
	{
	case 0:	//  Booter Lvl 1
		requirements[2] = 2;
		pos = B1;
		break;
	case 1:	//  Booter Lvl 2
		requirements[0] = 1;
		requirements[2] = 2;
		pos = B2;
		break;
	case 2:	//  Laser Lvl 1
		requirements[5] = 2;
		pos = L1;
		break;
	case 3:	//  Laser Lvl 2
		requirements[0] = 1;
		requirements[5] = 2;
		pos = L2;
		break;
	case 4:	//  Colony Ship
		requirements[1] = 1;
		requirements[2] = 1;
		requirements[4] = 1;
		pos = H1;
		type = 0;
		break;
	case 5:	//  Trade Ship
		requirements[1] = 1;
		requirements[2] = 1;
		requirements[3] = 1;
		pos = H1;
		type = 1;
		break;
	default:
		std::cout << "BUY ITEM Default:  This should never print\n";
		for (int i = 0; i < 6; i++)
			requirements[i] = 99;
		pos = -1;
		type = 1;
		break;
	}
	if (allRequirementsMet(requirements) && cPlyr->getStarship()->checkBuildItemAvailability(pos, statusUpdate))
	{
		cPlyr->getStarship()->gainItem(pos, statusUpdate, type);
		for (int i = 0; i < 6; i++)
		{
			if (requirements[i])
			{
				for (int j = requirements[i]; j > 0; j--)
					cPlyr->getStarship()->loseItem(i, statusUpdate);
			}
		}
		return true;
	}
	else
		return false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  rand(1-3) and updates the sprite to correct textureRect
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::rollFlightDie()
{
	int num = rand() % 3;
	flightDie.setSrcPos(sf::Vector2u(num, 0));
	flightDie.setQty(num + 1);
	flightDie.setString("Dice roll: " + std::to_string(num + 1));
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Rolls Combat Die
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::rollCombatDie(int party)
{
	int num = rand() % 6;
	switch (num)
	{
	case 0:
		combatDie[party]->setQty(1);
		combatDie[party]->setSrcPos(sf::Vector2u(0, 0));
		break;
	case 1:
	case 2:
		combatDie[party]->setQty(2);
		combatDie[party]->setSrcPos(sf::Vector2u(1, 0));
		break;
	case 3:
	case 4:
		combatDie[party]->setQty(3);
		combatDie[party]->setSrcPos(sf::Vector2u(2, 0));
		break;
	case 5:
		combatDie[party]->setQty(4);
		combatDie[party]->setSrcPos(sf::Vector2u(3, 0));
		break;
	}
	combatDie[party]->setString("Dice roll: " + std::to_string(num));
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Ends Pirate Combat
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::endPiratePhase()
{
	std::cout << "Pirate being replaced";
	flag[justActed] = true;
	trdMgr.setActive(false);
	flightMenu.setActive(true);
	pirateMenu.setActive(false);
	cPlyr->getPirateZone()->push_back((Pirate*)universe->getCurrentPlanet());
	universe->replaceCurrentPlanet();
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Ends Adventure Combat
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::endAdventurePhase()
{
	flag[adventureReward] = false;
	cPlyr->getAdventureZone()->push_back((AdventureCard*)universe->getAdvCard(curAdv));
	universe->addCardtoAdvDeck(curAdv);
	currentPlanet.setSrcPos(universe->getCurrentPlanet()->getSrcPos());
	actionNum++;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  sets cPhase to next phase, checks for end of build phase
//  and sets back to production
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::endPhase()
{
	specialString.setString("");
	flightEventString.setString("");
	flag[cPlanetActive] = false;
	switch (cPhase)
	{
	case production:
		
		break;
	case flight:
		flag[flightPathActive] = false;
		flag[justActed] = false;
		break;
	case tradeBuild:
		buildMenu.setActive(false);
		break;
	}
	cPhase++;
	if (cPhase == 3)
		cPhase = 0;
	flag[phaseSetupComplete] = false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Parses adventure requirements into std::string format
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
std::string Game::getAdvReqString()
{
	int reqQty = universe->getAdvCard(curAdv)->getReq1Qty();
	std::string tempString = "Requirements:\n";
	if (reqQty == -1)
		return tempString += "None";
	else
	{
		int reqType = universe->getAdvCard(curAdv)->getReq1Type();
		tempString += std::to_string(reqQty) + " ";
		if (reqType >= 0 && reqType < 6)				//  Resource
			tempString += universe->getAdvCard(curAdv)->getResName(reqType) + "\n";
		else if (reqType == 6)						//  Boosters
			tempString += "Boosters\n";
		else if (reqType == 9)						//  Lasers
			tempString += "Lasers\n";
		else if (reqType == 14)						//  Astro
			tempString += "Astro\n";
	}

	reqQty = universe->getAdvCard(curAdv)->getReq2Qty();
	if (reqQty != -1)
	{
		int req2Type = universe->getAdvCard(curAdv)->getReq2Type();
		tempString += std::to_string(reqQty) + " ";
		if (req2Type >= 0 && req2Type < 6)				//  Resource
			tempString += universe->getAdvCard(curAdv)->getResName(req2Type) + "\n";
		else if (req2Type == 6)						//  Boosters
			tempString += "Boosters\n";
		else if (req2Type == 9)						//  Lasers
			tempString += "Lasers\n";
		else if (req2Type == 14)						//  Astro
			tempString += "Astro\n";
	}

	return tempString;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Checks if adventure requirements are met and if so removes them
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Game::startAdventure()
{
	bool flag = false;
	bool secRes = false;
	int req1Qty = universe->getAdvCard(curAdv)->getReq1Qty();

	if (req1Qty == -1)
		return true;
	int req1Type = universe->getAdvCard(curAdv)->getReq1Type();

	if (req1Type >= 0 && req1Type < 6 && cPlyr->getStarship()->resourceAvailable(req1Type, req1Qty, statusUpdate))	//  Resource
		flag = true;
	else if (req1Type == 6)								//  Boosters
	{
		if (req1Qty <= cPlyr->getStarship()->totalBoosters())
			flag = true;
		else
			statusUpdate = "Not enough boosters";
	}
	else if (req1Type == 9)								//  Lasers
	{
		if (req1Qty <= cPlyr->getStarship()->totalLasers())		
			flag = true;
		else
			statusUpdate = "Not enough lasers";
	}
	else if (req1Type == 14 && cPlyr->canAfford(req1Qty, statusUpdate))			//  Astro
		flag = true;

	if (!flag)
		return false;
			
	int req2Qty = universe->getAdvCard(curAdv)->getReq2Qty();
	int req2Type = universe->getAdvCard(curAdv)->getReq2Type();
	if (req2Qty != -1)
	{
		secRes = true;
		if (req2Type >= 0 && req2Type < 6 && cPlyr->getStarship()->resourceAvailable(req2Type, req2Qty, statusUpdate))	//  Resource
			flag = true;
		else if (req2Type == 6)								//  Boosters
		{
			if (req2Qty <= cPlyr->getStarship()->totalBoosters())
				flag = true;
			else
				statusUpdate = "Not enough boosters";
		}
		else if (req2Type == 9)								//  Lasers
		{
			if (req2Qty <= cPlyr->getStarship()->totalLasers())
				flag = true;
			else
				statusUpdate = "Not enough lasers";
		}
		else if (req2Type == 14 && cPlyr->canAfford(req2Qty, statusUpdate))			//  Astro
			flag = true;
		else
			flag = false;
	}
	
	if (flag)			//  Remove resources and/or astro
	{
		if (req1Type >= 0 && req1Type < 6)								//  Resource
		{
			for (int i = 0; i < req1Qty; i++)
				cPlyr->getStarship()->loseItem(req1Type, statusUpdate);		
		}		
		else if (req1Type == 14)
			cPlyr->subAstro(req1Qty);								//  Astro

		if (secRes)		//  If second requirement... Remove resources and/or astro
		{
			if (req2Type >= 0 && req2Type < 6)							//  Resource
			{
				for (int i = 0; i < req2Qty; i++)
					cPlyr->getStarship()->loseItem(req2Type, statusUpdate);
			}
			else if (req2Type == 14)
				cPlyr->subAstro(req2Qty);							//  Astro
		}
	}	
	return flag;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Dispenses Rewards of completed Adventure
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::adventureRewards()
{
	int numRes = universe->getAdvCard(curAdv)->getRecRcvd();
	int astroNum = universe->getAdvCard(curAdv)->getAstros();
	int fame = universe->getAdvCard(curAdv)->getFame();
	int vic = universe->getAdvCard(curAdv)->getVicPts();
	flightEventString.setString(getAdvRewardsString(numRes, astroNum, fame, vic));
	if (astroNum > 0)
	{
		cPlyr->addAstro(astroNum);
		cPlyr->updateIcon(astro);
	}

	for (int i = 0; i < fame; i++)
		cPlyr->addFmPt(fame);  
	updateHeroOfThePeople();
	for (int i = 0; i < vic; i++)
		cPlyr->addVicPt(vic);
	trdMgr.setActive(true);
	if (numRes > 0)
	{
		flag[adventureReward] = true;
		trdMgr.setLimit(1);
		trdMgr.setTransaction("Buy");
		gainOneResource();
	}
	else
	{
		flag[adventureReward] = false;
		cPlyr->getAdventureZone()->push_back((AdventureCard*)universe->getAdvCard(curAdv));
		universe->addCardtoAdvDeck(curAdv);
		currentPlanet.setSrcPos(universe->getCurrentPlanet()->getSrcPos());
		actionNum++;
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Parses adventure rewards into std::string format
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
std::string Game::getAdvRewardsString(int res, int astro, int fame, int vic)
{
	std::string tempString = "Rewards:\n";
	if (res > 0)
		tempString += std::to_string(res) + " Resource\n";
	if (astro > 0)
		tempString += std::to_string(astro) + " Astro\n";
	if (fame > 0)
		tempString += std::to_string(fame) + " Fame Point(s)\n";
	if (vic > 0)
		tempString += std::to_string(vic) + " Victory Point\n";
	return tempString;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Creates the Flight Menu
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::createFlightMenu()
{
	Object* tempObject;
	tempObject = new Object(txtMgr.getResource(SYMBFLE), { 710, 610 }, 0, { 50, 50 }, { 3, 0 });			// Trade With Icon
	tempObject->initString(fntMgr.getResource(FNTFLE), { 480, 610 }, "Trade With Planet");
	flightMenu.push_back(tempObject);

	tempObject = new Object(txtMgr.getResource(SYMBFLE), sf::Vector2f(710, 660), 0, { 50, 50 }, { 1, 0 });	//  Establish Trade Post
	tempObject->initString(fntMgr.getResource(FNTFLE), { 430, 660 }, "Establish Trade Post");
	flightMenu.push_back(tempObject);

	tempObject = new Object(txtMgr.getResource(SYMBFLE), sf::Vector2f(710, 660), 0, { 50, 50 }, { 0, 0 });	//  Colonize Icon
	tempObject->initString(fntMgr.getResource(FNTFLE), { 450, 660 }, "Colonize the Planet");
	flightMenu.push_back(tempObject);

	tempObject = new Object(txtMgr.getResource(SYMBFLE), sf::Vector2f(710, 710), 0, { 50, 50 }, { 4, 0 });	//  Continue Flying Icon
	tempObject->initString(fntMgr.getResource(FNTFLE), { 500, 710 }, "Continue Flying");
	flightMenu.push_back(tempObject);

	tempObject = new Object(txtMgr.getResource(SYMBFLE), sf::Vector2f(710, 760), 0, { 50, 50 }, { 5, 0 });	//  End Flight Icon
	tempObject->initString(fntMgr.getResource(FNTFLE), { 570, 760 }, "End Flight");
	flightMenu.push_back(tempObject);

	tempObject = new Object(txtMgr.getResource(SYMBFLE), sf::Vector2f(710, 660), 0, { 50, 50 }, { 9, 0 });	//  Adventure Icon
	tempObject->initString(fntMgr.getResource(FNTFLE), { 450, 660 }, "Complete Adventure");
	flightMenu.push_back(tempObject);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Creates the Build Menu
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::createBuildMenu()
{
	Object* tempObject;

	for (int i = 0; i < 6; i++)
	{
		tempObject = new Object(txtMgr.getResource(SYMBFLE), { 0, 0 }, 0, { 50, 50 });
		tempObject->setVisible(false);
		buildMenu.push_back(tempObject);
	}
	buildMenu.setPositionOfItem(BLVL1, sf::Vector2f{ 110, 125 });
	buildMenu.setPositionOfItem(BLVL2, sf::Vector2f{ 110, 450 });
	buildMenu.setPositionOfItem(LLVL1, sf::Vector2f{ 750, 175 });
	buildMenu.setPositionOfItem(LLVL2, sf::Vector2f{ 750, 400 });
	buildMenu.setPositionOfItem(TRDSHIP, sf::Vector2f{ 150, 175 });
	buildMenu.setPositionOfItem(COLSHIP, sf::Vector2f{ 150, 400 });
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Creates the Pirate Menu
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::createPirateMenu()
{
	Object* tempObject;

	tempObject = new Object(txtMgr.getResource(SYMBFLE), { 710, 610 }, 0, { 50, 50 }, { 3, 0 });
	tempObject->initString(fntMgr.getResource(FNTFLE), { 600, 610 }, "Bribe");
	pirateMenu.push_back(tempObject);

	tempObject = new Object(txtMgr.getResource(SYMBFLE), { 710, 660 }, 0, { 50, 50 }, { 2, 0 });
	tempObject->initString(fntMgr.getResource(FNTFLE), { 600, 660 }, "Fight");
	pirateMenu.push_back(tempObject);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Creates the Trade Menu
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::createSectorMenu()
{
	Object* tempObject;

	tempObject = new Object(txtMgr.getResource(UNIVERSECARDIMAGES), sf::Vector2f(100, 150), 10, sf::Vector2u(200, 300), CARDBACK);
	tempObject->initString(fntMgr.getResource(FNTFLE), { 175, 200 }, "1", sf::Text::Bold);
	tempObject->setTextScale({ 5, 5 });
	sectorMenu.push_back(tempObject);

	tempObject = new Object(txtMgr.getResource(UNIVERSECARDIMAGES), sf::Vector2f(300, 150), 10, sf::Vector2u(200, 300), CARDBACK);
	tempObject->initString(fntMgr.getResource(FNTFLE), { 360, 200 }, "2", sf::Text::Bold);
	tempObject->setTextScale({ 5, 5 });
	sectorMenu.push_back(tempObject);

	tempObject = new Object(txtMgr.getResource(UNIVERSECARDIMAGES), sf::Vector2f(500, 150), 10, sf::Vector2u(200, 300), CARDBACK);
	tempObject->initString(fntMgr.getResource(FNTFLE), { 560, 200 }, "3", sf::Text::Bold);
	tempObject->setTextScale({ 5, 5 });
	sectorMenu.push_back(tempObject);

	tempObject = new Object(txtMgr.getResource(UNIVERSECARDIMAGES), sf::Vector2f(700, 150), 10, sf::Vector2u(200, 300), CARDBACK);
	tempObject->initString(fntMgr.getResource(FNTFLE), { 760, 200 }, "4", sf::Text::Bold);
	tempObject->setTextScale({ 5, 5 });
	sectorMenu.push_back(tempObject);

}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Calls the draw function only if planet is active
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::drawCurrentPlanet()
{
	if (flag[cPlanetActive])
		currentPlanet.draw(gWindow);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Calls the targeted function only if planet is active
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Game::isCPlanetTargeted()
{
	if (flag[cPlanetActive])
		return currentPlanet.isTargeted(gWindow);
	return false;
}
