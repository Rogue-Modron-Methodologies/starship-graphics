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
Game::Game()
{
	txtMgr.addDirectory("resources/");
	fntMgr.addDirectory("resources/");
	initCDie();
	flightDie = new Icon(txtMgr.getResource(SDIEFLE), sf::Vector2f{ 350, 525 }, 1, sf::Vector2u(80, 80));
	flightDie->initString(fntMgr.getResource(FNTFLE), { 440, 545 }, "", sf::Text::Bold);		
	
	P1 = new Player(txtMgr, fntMgr, "Player1", 1);		// Default names for bugtesting
	P2 = new Player(txtMgr, fntMgr, "Player2", 2);		// Default names for bugtesting
	cPlyr = P2;

	cPlanet = new Icon(fntMgr.getResource(FNTFLE), { 835, 480 }, "Current Planet");

	phaseNameString = new Icon(fntMgr.getResource(FNTFLE), { 200, 820 }, "Production Planet");	 
	
	errorString = new Icon(fntMgr.getResource(FNTFLE), { 550, 820 }, "", sf::Text::Bold);
	errorTimer = 255;
	
	infoString = new Icon(fntMgr.getResource(FNTFLE), { 40, 30 }, "", sf::Text::Bold);
	
	endPhaseString = new Icon(fntMgr.getResource(FNTFLE), { 825, 25 }, "End of Phase\n(Press Enter)", sf::Text::Bold);
	endPhaseString->setTextScale({ 2, 2 });
	endPhaseString->setTextColor(sf::Color::Red);

	specialString = new Icon(fntMgr.getResource(FNTFLE), { 650, 30 }, "", sf::Text::Bold);
	specialString->setTextColor(sf::Color::Green);

	tradeProgressString = new Icon(fntMgr.getResource(FNTFLE), { 580, 525 }, "");
	tradeProgressString->setTextColor(sf::Color::Green);

	tradeSaveState = new Icon*[7];
	tradeSaveState[astro] = new Icon(txtMgr.getResource(SYM1FLE), { 780, 562 }, 25, { 35, 35 }, { 3, 0 });
	tradeSaveState[science] = new Icon(txtMgr.getResource(RICNFLE), { 780, 565 }, 1, { 35, 35 });
	tradeSaveState[ore] = new Icon(txtMgr.getResource(RICNFLE), { 780, 600 }, 1, { 35, 35 }, { 1, 0 });
	tradeSaveState[fuel] = new Icon(txtMgr.getResource(RICNFLE), { 780, 635 }, 1, { 35, 35 }, { 2, 0 });
	tradeSaveState[tradeGood] = new Icon(txtMgr.getResource(RICNFLE), { 780, 670 }, 1, { 35, 35 }, { 3, 0 });
	tradeSaveState[wheat] = new Icon(txtMgr.getResource(RICNFLE), { 780, 705 }, 1, { 35, 35 }, { 4, 0 });
	tradeSaveState[carbon] = new Icon(txtMgr.getResource(RICNFLE), { 780, 740 }, 1, { 35, 35 }, { 5, 0 });

	tradeMenuIcons = new Icon*[4];
	tradeMenuIcons[plus] = new Icon(txtMgr.getResource(TRDICN), { 675, 575 }, 1, { 50, 50 }, { 0, 0 });
	tradeMenuIcons[minus] = new Icon(txtMgr.getResource(TRDICN), { 675, 675 }, 1, { 50, 50 }, { 1, 0 });
	tradeMenuIcons[check] = new Icon(txtMgr.getResource(TRDICN), { 635, 760 }, 1, { 50, 50 }, { 2, 0 });
	tradeMenuIcons[cancel] = new Icon(txtMgr.getResource(TRDICN), { 710, 760 }, 1, { 50, 50 }, { 3, 0 });

	menu = new Icon*[4];

	menu[trdW] = new Icon(txtMgr.getResource(SYMBFLE), { 760, 610 }, 0, { 50, 50 }, { 3, 0 });
	menu[trdW]->initString(fntMgr.getResource(FNTFLE), { 520, 610 }, "Trade With Planet");

	menu[colIt] = new Icon(txtMgr.getResource(SYMBFLE), sf::Vector2f(760, 660), 0, { 50, 50 }, { 1, 0 });
	menu[colIt]->initString(fntMgr.getResource(FNTFLE), { 760, 660 }, "Colonize");

	menu[conFly] = new Icon(txtMgr.getResource(SYMBFLE), sf::Vector2f(760, 710), 0, { 50, 50 }, { 4, 0 });
	menu[conFly]->initString(fntMgr.getResource(FNTFLE), { 550, 710 }, "Continue Flying");

	menu[endFl] = new Icon(txtMgr.getResource(SYMBFLE), sf::Vector2f(760, 760), 0, { 50, 50 }, { 5, 0 });
	menu[endFl]->initString(fntMgr.getResource(FNTFLE), { 610, 760 }, "End Flight");

	for (int i = 0; i < FLAGNUM; i++)
		flag[i] = false;
	flag[visFlightPath] = true;
	flag[visSectors] = true;
	flag[visFlightMenu] = true;

	universe = new Universe(txtMgr, fntMgr);
	screenSize = sf::Vector2u(1200, 900);
	gWindow.create(sf::VideoMode(screenSize.x, screenSize.y), "Starship Game");
	playerSetup();
	cPhase = production;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Player Name Setup
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
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
	ColonyCard* tempCard;
	//M		colony	Carbon	1	N/A	0	1	Colony: Alioth VIII
	//ColonyCard(const sf::Texture &texture, sf::Vector2u srcPos, int num, std::string name, int type, int resource, int actNum, int vicPts)
	tempCard = new ColonyCard(txtMgr.getResource(STRFILE), { 0, 0 }, -1, "Colony: Alioth VIII", colony, Fuel, 1, 1);
	tempCard->setScale(CRDZNSCL);
	tempCard->updateTextRect();
	P1->getColonyZone()->push_back(tempCard);

	//S		colony	Fuel		1	N/A	0	1	Colony: Megrez VII
	tempCard = new ColonyCard(txtMgr.getResource(STRFILE), { 1, 0 }, -1, "Colony: Megrez VII", colony, Fuel, 1, 1);
	tempCard->setScale(CRDZNSCL);
	tempCard->updateTextRect();
	P2->getColonyZone()->push_back(tempCard);
	
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
	cPlyr == P1 ? cPlyr = P2 : cPlyr = P1;	// toggles between players
	cPlyr->updatePlayerIcon();
//		cout << "CheckWin will be here.\n";
//		gameTurn();
//		cout << "Q to Toggle Win Condition\n";
//		cin >> choice;
//	}
	int tempNum;
	sf::Event event;
	while (gWindow.isOpen())
	{
		if (!flag[phaseSetupComplete])
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
				if (event.key.code == sf::Keyboard::Return && flag[phaseComplete])
					endPhase();
				break;
			case sf::Event::MouseButtonPressed:
				switch (cPhase)
				{
				case production: 
					productionPhaseListener(gWindow);
					break;
				case flight:
					if (!flag[sectorSelected])
						preFlightListener(gWindow, tempNum);
					if (flag[sectorSelected])
						flightPhaseListener(gWindow, tempNum);
					if (flag[tradeInProgress])
						tradeMenuListener(gWindow, tempNum);
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
					//if (!flag[sectorSelected])
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
		updateGameWindow(gWindow);			//  Updates the screen objects	
		gWindow.display();
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Initialize Combat Die
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::initCDie()
{
	combatDie[0] = 1;
	combatDie[1] = 2;
	combatDie[2] = 2;
	combatDie[3] = 3;
	combatDie[4] = 3;
	combatDie[5] = 4;
}

bool Game::resourcesAvailable(int resAvail[])
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
//  inital phase setup
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::phaseSetup()
{	
	std::string tempString;
	flag[phaseComplete] = false;	
	int resAvail[6] = { 0 };
	switch (cPhase)
	{
	case production:
		phaseNameString->setString("Production Phase");
		cPlyr->makeBig();
		cPlyr->expandColonyZone();		
		rollSpeedDie();
		cPlyr->getStarship()->calcMaxDistance(flightDie->getQty());
		tempString.clear();
		specialString->setTextPosition({ 525, 30 });

		if (cPlyr->getColonyZone()->findResource(flightDie->getQty(), resAvail)){
			tempString += " Resource(s) in Colony Zone Found!";
			if (resourcesAvailable(resAvail)){
				specialString->setString(+"Chose a colony resource");			
				flag[gainResource] = true;
			}
			else{
				specialString->setString(+"No Choices Available");
				flag[phaseComplete] = true;
			}
		}
		else{
			tempString += " No Resources in Colony Zone";	
			flag[phaseComplete] = true;
		}	

		infoString->setString(tempString);			
		break;
	case flight:
		phaseNameString->setString("Flight Phase");
		cPlyr->makeSmall();
		actionNum = 0;
		flag[visSectors] = true;
		flag[sectorSelected] = false;		
		flag[visFlightMenu] = true;
		flag[justTraded] = false;
		flag[justColonized] = false;
		infoString->setString("Flight: 0 / " + std::to_string(cPlyr->getStarship()->getMaxDistance()) + "\nMax Actions: 0 / " + 
			std::to_string(cPlyr->getStarship()->getMaxActions()));
		specialString->setString("Select a Sector");
		specialString->setTextPosition({ 425, 40 });
		break;
	case trades:
		phaseNameString->setString("Trade Phase");
		infoString->setString("Max Trades: 2");
		cPlyr->makeBig();
		cPlyr->expandTradeZone();
		flag[phaseComplete] = true;		//  Only until there is an actual trade phase coded
		break;
	case build:
		phaseNameString->setString("Build Phase");
		infoString->setString("Build Phase");
		cPlyr->makeBig();
		flag[phaseComplete] = true;		//  Only until there is an actual build phase coded
		break;
	}
	flag[phaseSetupComplete] = true;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  sets cPhase to next phase, checks for end of build phase
//  and sets back to production
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::endPhase()
{
	specialString->clear();
	cPhase++;
	if (cPhase == 4)
	{
		std::cout << "Checkwin Here?" << std::endl;
		cPhase = 0;
	}
	flag[phaseSetupComplete] = false;		
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  draws the icons and stats for game Window
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::updateGameWindow(sf::RenderWindow &gWindow)
{
	universe->getBoard()->draw(gWindow);
	switch (cPhase)
	{
	case production:
		flightDie->draw(gWindow);
		break;
	case flight:
		if (!flag[sectorSelected] && flag[visSectors])
			universe->drawSectors(gWindow);
		else if (!flag[sectorSelected] && !flag[visSectors])
			break;
		else{
			specialString->setString("Flight Sector: " + std::to_string(universe->getCurrentSectorNum() + 1));
			if (flag[visFlightPath])
				drawFlightPath(gWindow);	
			drawCurrentPlanet(gWindow);
			//  If phase is not complete and player hasn't reached max actions
			if (!flag[phaseComplete] && actionNum < cPlyr->getStarship()->getMaxActions()){
				infoString->setString("Flight: " + std::to_string(universe->getCurrentMove()) + " / " + std::to_string(cPlyr->getStarship()->getMaxDistance())
					+ "\nMax Actions: " + std::to_string(actionNum) + " / " + std::to_string(cPlyr->getStarship()->getMaxActions()));

				//  When flight menu is active	
				if (flag[visFlightMenu]){
					updateFlightMenu(gWindow);
					drawFlightMenu(gWindow);
				}
				else{									//  When trade menu is active
					for (int i = 0; i < 4; i++)
						tradeMenuIcons[i]->draw(gWindow);	//  Prints the Trade Menu Clickable Items
					for (int i = 0; i < 6; i++)					
						tradeSaveState[i]->draw(gWindow);	//  Prints the resource icons available			
 				}
			}
			else{     //  When the flight phase is complete
				specialString->setString("Flight Complete");
				tradeProgressString->clear();
				flag[phaseComplete] = true;
			}
		}
		break;
	default:
		break;
	}
	// Non Phase Specific Drawables
	phaseNameString->draw(gWindow);
	infoString->draw(gWindow);	
	specialString->draw(gWindow);	
	tradeProgressString->draw(gWindow);
	cPlyr->draw(gWindow);	

	if (statusUpdate.length())
		setError(statusUpdate);
	statusUpdate.clear();

	if (errorTimer){
		errorString->setTextColor(sf::Color(255, 0, 0, errorTimer / 10));
		errorString->draw(gWindow);		
		errorTimer--;
	}
	if (flag[phaseComplete]){
		endPhaseString->draw(gWindow);
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  updates the Error String and timer with the error message
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::setError(std::string error)
{
	errorTimer = 2550;
	errorString->setString(error);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  rand(1-3) and updates the sprite to correct textureRect
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::rollSpeedDie(){
	int num = rand() % 3;
	flightDie->setSrcPos(sf::Vector2u(num, 0));
	flightDie->updateTextRect();
	flightDie->setQty(num + 1);	
	flightDie->setString("Dice roll: " + std::to_string(num + 1));
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Deals with Mouse Click actions in the Production Phase
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::productionPhaseListener(sf::RenderWindow &gWindow){
	int tempType;
	// Starship (Small) is clicked
	if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall()){
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			cPlyr->makeBig();
			flightDie->setIconPosition({ 350, 525 });
			flightDie->setTextPosition({ 440, 545 });
		}
	}
	// Colony Zone (Large Icon) is clicked
	else if (!cPlyr->zonesSmall() && cPlyr->getColonyZone()->getIconOnly() && cPlyr->getColonyZone()->isIconTargeted(gWindow)){
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandColonyZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	else if (!cPlyr->zonesSmall() && cPlyr->getTradeZone()->getIconOnly() && cPlyr->getTradeZone()->isIconTargeted(gWindow)){
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandTradeZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	// Colony Zone (Large List) is clicked and player is entitled to a production resource
	else if (!cPlyr->zonesSmall() && !cPlyr->getColonyZone()->getIconOnly() && cPlyr->getColonyZone()->isZoneTargeted(gWindow, tempType)){
		
		if (flag[gainResource] && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			if (cPlyr->getColonyZone()->resourceMatchesActNum(tempType, flightDie->getQty()) && cPlyr->getStarship()->gainItem(tempType, statusUpdate)){
				cPlyr->updateIcon(tempType);
				specialString->setString("Resource Gained");
				flag[gainResource] = false;
				flag[phaseComplete] = true;
			}
	}
	// Trade Zone (Large List) is clicked
	else if (!cPlyr->zonesSmall() && !cPlyr->getTradeZone()->getIconOnly() && cPlyr->getTradeZone()->isZoneTargeted(gWindow, tempType)){}		// Do Nothing this Phase
	//  Starship (Large) && Empty Space is clicked
	else if (!cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall()){
		cPlyr->makeSmall();
		flightDie->setIconPosition({ 250, 725 });
		flightDie->setTextPosition({ 340, 745 });
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Flight Phase Sector Selection Listener
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::preFlightListener(sf::RenderWindow &gWindow, int &tempType){
	// Starship (Small) is clicked
	if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall()){
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			cPlyr->makeBig();
			flag[visSectors] = false;	
		}
	}
	// Starship (Large) is clicked
	else if (cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall()){}	// Do Nothing this Phase
	// Colony Zone (Large Icon) is clicked
	else if (!cPlyr->zonesSmall() && cPlyr->getColonyZone()->getIconOnly() && cPlyr->getColonyZone()->isIconTargeted(gWindow)){
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandColonyZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	// Trade Zone (Large Icon) is clicked
	else if (!cPlyr->zonesSmall() && cPlyr->getTradeZone()->getIconOnly() && cPlyr->getTradeZone()->isIconTargeted(gWindow)){
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandTradeZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	// Colony Zone (Large List) is clicked
	else if (!cPlyr->zonesSmall() && !cPlyr->getColonyZone()->getIconOnly() && cPlyr->getColonyZone()->isZoneTargeted(gWindow, tempType)){}	// Do Nothing this Phase
	// Trade Zone (Large List) is clicked
	else if (!cPlyr->zonesSmall() && !cPlyr->getTradeZone()->getIconOnly() && cPlyr->getTradeZone()->isZoneTargeted(gWindow, tempType)){}		// Do Nothing this Phase
	//  Sector is Clicked
	else if (universe->sectorsTargeted(gWindow, tempType) && cPlyr->getStarship()->isSmall()){
		infoString->setString("Flight: 1 / " + std::to_string(cPlyr->getStarship()->getMaxDistance()) + "\nMax Actions: 0 / " + std::to_string(cPlyr->getStarship()->getMaxActions()));
		flag[visSectors] = false;
		flag[sectorSelected] = true;
		universe->initializeFlightPath(tempType);
		return;
	}
	//  Starship (Large) && Empty Space is clicked
	else if (!cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall()){
		cPlyr->makeSmall();
		flag[visSectors] = true;
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Deals with Mouse Click actions in the Flight Phase
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::flightPhaseListener(sf::RenderWindow &gWindow, int tempType){	
	// Starship (Small) is clicked
	if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall()){
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			cPlyr->makeBig();
			flag[visFlightPath] = false;
		}
	}
	// Starship (Large) is clicked
	else if (cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall()){}	// Do Nothing this Phase
	// Colony Zone (Large Icon) is clicked
	else if (!cPlyr->zonesSmall() && cPlyr->getColonyZone()->getIconOnly() && cPlyr->getColonyZone()->isIconTargeted(gWindow)){
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandColonyZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	// Trade Zone (Large Icon) is clicked
	else if (!cPlyr->zonesSmall() && cPlyr->getTradeZone()->getIconOnly() && cPlyr->getTradeZone()->isIconTargeted(gWindow)){
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandTradeZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	// Colony Zone (Large List) is clicked
	else if (!cPlyr->zonesSmall() && !cPlyr->getColonyZone()->getIconOnly() && cPlyr->getColonyZone()->isZoneTargeted(gWindow, tempType)){}	// Do Nothing this Phase
	// Trade Zone (Large List) is clicked
	else if (!cPlyr->zonesSmall() && !cPlyr->getTradeZone()->getIconOnly() && cPlyr->getTradeZone()->isZoneTargeted(gWindow, tempType)){}		// Do Nothing this Phase
	// Objects in the FlightPath are clicked but not the current planet
	else if (!flag[phaseComplete] && flag[visFlightPath] && universe->flightPathTargeted(gWindow, tempType) && tempType != universe->getCurrentMove() - 1){
		std::cout << "Flight Path Object " << tempType << " Clicked" << std::endl;
	}
	// Current Planet in the FlightPath is clicked
	else if (!flag[phaseComplete] && flag[visFlightMenu] && universe->getCurrentPlanet()->isTargeted(gWindow)){
		std::cout << "Current Planet Clicked" << std::endl;
		std::cout << "Resource " << universe->getCurrentPlanet()->getResource() << std::endl;
	}
	//  Current Planet's Menu in the FlightPath is clicked
	else if (!flag[phaseComplete] && flag[visFlightMenu] && menuOptionTargeted(gWindow, tempType)){
		switch (tempType)
		{
		case colIt:	//  Colonize/Establish Post
			if (universe->getCurrentPlanet()->getType() == tradeShip && cPlyr->getStarship()->shipAvailable(tradeShip, tempType, statusUpdate)){
				//cPlyr->getStarship()->loseItem(tempType, statusUpdate);
				cPlyr->getTradeZone()->push_back((TradeCard*)universe->getCurrentPlanet());
				cPlyr->getTradeZone()->updateZone(cPlyr->getTradeZone()->getPosition(), cPlyr->getTradeZone()->getScale(), cPlyr->getTradeZone()->getIconOnly());
				universe->replaceCurrentPlanet();
				flag[justColonized] = true;
				actionNum++;
			}
			else if (universe->getCurrentPlanet()->getType() == colonyShip &&cPlyr->getStarship()->shipAvailable(colonyShip, tempType, statusUpdate)){
				//cPlyr->getStarship()->loseItem(tempType, statusUpdate);
				cPlyr->getColonyZone()->push_back((ColonyCard*)universe->getCurrentPlanet());
				cPlyr->getColonyZone()->updateZone(cPlyr->getColonyZone()->getPosition(), cPlyr->getColonyZone()->getScale(), cPlyr->getColonyZone()->getIconOnly());
				universe->replaceCurrentPlanet();
				flag[justColonized] = true;
				actionNum++;
			}
			infoString->setString(statusUpdate);
			break;			
		case trdW:	//  Trade with Planet
			initTradeMenu(gWindow, tempType);
			break;
		case conFly:	// Continue Flight
			universe->continueFlight();
			flag[justTraded] = false;
			flag[justColonized] = false;
			tradeProgressString->clear();
			break;
		case endFl:	//  End Flight
			flag[phaseComplete] = true;
			tradeProgressString->clear();
			break;
		}
	}
	//  Starship (Large) && Empty Space is clicked
	else if (!cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall() && !tradeIconsTargeted(gWindow)){
		cPlyr->makeSmall();
		flag[visFlightPath] = true;
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Deals with Mouse Click actions in the Trade Phase
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::tradePhaseListener(sf::RenderWindow &gWindow)
{
	int tempType;
	// Starship (Small) is clicked
	if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall()){
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->makeBig();
	}
	// Starship (Large) is clicked
	else if (cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall()){}	// Do Nothing this Phase
	// Colony Zone (Large Icon) is clicked
	else if (!cPlyr->zonesSmall() && cPlyr->getColonyZone()->getIconOnly() && cPlyr->getColonyZone()->isIconTargeted(gWindow)){
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandColonyZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	// Trade Zone (Large Icon) is clicked
	else if (!cPlyr->zonesSmall() && cPlyr->getTradeZone()->getIconOnly() && cPlyr->getTradeZone()->isIconTargeted(gWindow)){
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandTradeZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	// Colony Zone (Large List) is clicked
	else if (!cPlyr->zonesSmall() && !cPlyr->getColonyZone()->getIconOnly() && cPlyr->getColonyZone()->isZoneTargeted(gWindow, tempType)){}	// Do Nothing this Phase
	// Trade Zone (Large List) is clicked
	else if (!cPlyr->zonesSmall() && !cPlyr->getTradeZone()->getIconOnly() && cPlyr->getTradeZone()->isZoneTargeted(gWindow, tempType)){}		// Do Nothing this Phase
	//  Starship (Large) && Empty Space is clicked
	else if (!cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall())
		cPlyr->makeSmall();
	//  Starship (Large) && Empty Space is clicked
	else if (!cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall())
		cPlyr->makeSmall();

}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Deals with Mouse Click actions in the Build Phase
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::buildPhaseListener(sf::RenderWindow &gWindow)
{
	int tempType;
	// Starship (Small) is clicked
	if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall()){
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->makeBig();
	}
	// Starship (Large) is clicked
	else if (cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall()){
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			if (cPlyr->getStarship()->bigLeftClicked(gWindow, statusUpdate, tempType))
				cPlyr->updateIcon(tempType);
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			if (cPlyr->getStarship()->bigRightClicked(gWindow, statusUpdate, tempType))
				cPlyr->updateIcon(tempType);
		}
	}
	// Colony Zone (Large Icon) is clicked
	else if (!cPlyr->zonesSmall() && cPlyr->getColonyZone()->getIconOnly() && cPlyr->getColonyZone()->isIconTargeted(gWindow)){
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandColonyZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	// Trade Zone (Large Icon) is clicked
	else if (!cPlyr->zonesSmall() && cPlyr->getColonyZone()->getIconOnly() && cPlyr->getTradeZone()->isIconTargeted(gWindow)){
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandTradeZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	// Colony Zone (Large List) is clicked
	else if (!cPlyr->zonesSmall() && !cPlyr->getColonyZone()->getIconOnly() && cPlyr->getColonyZone()->isZoneTargeted(gWindow, tempType)){
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			if (cPlyr->getStarship()->gainItem(tempType, statusUpdate))
				cPlyr->updateIcon(tempType);
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			if (cPlyr->getStarship()->loseItem(tempType, statusUpdate))
				cPlyr->updateIcon(tempType);
		}

	}
	// Trade Zone (Large List) is clicked
	else if (!cPlyr->zonesSmall() && !cPlyr->getTradeZone()->getIconOnly() && cPlyr->getTradeZone()->isZoneTargeted(gWindow, tempType)){
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			if (cPlyr->getStarship()->gainItem(tempType, statusUpdate))
				cPlyr->updateIcon(tempType);
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			if (cPlyr->getStarship()->loseItem(tempType, statusUpdate))
				cPlyr->updateIcon(tempType);
		}
	}
	//  Starship (Large) && Empty Space is clicked
	else if (!cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall()){
		cPlyr->makeSmall();
	}

}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Sets up and maintains tradeMenu Details
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::initTradeMenu(sf::RenderWindow &gWindow, int tempType)
{
	flag[visFlightMenu] = false;
	flag[tradeInProgress] = true;
	tradeProgressString->setString("Trade In Progress");
	int cResource = universe->getCurrentPlanet()->getResource();
	for (int i = 0; i < 7; i++)							
	{
		tradeSaveState[i]->setQty(cPlyr->getStatQty(i));			//  saves the current resource and astro values
		tradeSaveState[i]->greyOut();							
	}
	tradeSaveState[cResource]->setColor();
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Deals with Mouse Click actions when the tradeMenu is displayed
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::tradeMenuListener(sf::RenderWindow &gWindow, int tempType)
{
	tempType = universe->getCurrentPlanet()->getResource();
	int cost = universe->getCurrentPlanet()->getCost();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && tradeMenuIcons[plus]->isTargeted(gWindow))
	{
		if (cPlyr->canAfford(cost, statusUpdate) && cPlyr->getStarship()->gainItem(tempType, statusUpdate))
		{
			cPlyr->updateIcon(tempType);
			cPlyr->subAstro(cost);				
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && tradeMenuIcons[minus]->isTargeted(gWindow))
	{
		if (cPlyr->getStarship()->loseItem(tempType, statusUpdate))
		{
			cPlyr->updateIcon(tempType);
			cPlyr->addAstro(cost);
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && tradeMenuIcons[check]->isTargeted(gWindow))
	{
		flag[tradeInProgress] = false;
		flag[visFlightMenu] = true;

		if (tradeSaveState[astro]->getQty() != cPlyr->getStatQty(astro))
		{
			actionNum++;		
			flag[justTraded] = true;
			tradeProgressString->setString("Trade Complete");
		}
		else
			tradeProgressString->setString("No Trade");

	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && tradeMenuIcons[cancel]->isTargeted(gWindow))
	{
		flag[tradeInProgress] = false;
		flag[visFlightMenu] = true;		
		for (int i = 0; i < 6; i++)							// restores the saveState for all resource and astro values
		{
			cPlyr->setStatQty(i, tradeSaveState[i]->getQty());
			cPlyr->getStarship()->setShipObjectQty(i, tradeSaveState[i]->getQty());
		}
		cPlyr->setStatQty(astro, tradeSaveState[astro]->getQty());
		cPlyr->getStarship()->updateShipIcons();
		tradeProgressString->setString("Trade Cancelled");
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Configures the Flight Menu Options
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::updateFlightMenu(sf::RenderWindow &gWindow)
{
	for (int i = 0; i < MENUSIZE; i++)
		menu[i]->setQty(0, false);
	menu[endFl]->setQty(1, false);	////////////////////////////////////////////  
	if (universe->getCurrentMove() < cPlyr->getStarship()->getMaxDistance()) /////////////////////  THESE THREE LINES SHOULDNT BE HERE
		menu[conFly]->setQty(1, false); /////////////////////////////////////////
	if (universe->getCurrentPlanet()->getType() == 2)		//  PIRATE
	{
		//std::cout << "Pirate" << std::endl;
	}
	else                                                  //  NOT PIRATE
	{
		////////////////////////////////////////////////////////////////////////////////////////  THEY SHOULD BE HERE ONCE PIRATE IS IMPLETEMENTED			
		if (universe->getCurrentPlanet()->getType() == 0)		//  Trade Planet
		{
			if (!flag[justTraded] && !flag[justColonized])
				menu[trdW]->setQty(1, false);
			if (universe->getCurrentPlanet()->getPts() == 1 && !flag[justColonized])	//  Can be colonized
			{
				menu[colIt]->setString("Establish Trade Post");
				menu[colIt]->setSrcPos({ 1, 0 });
				menu[colIt]->updateTextRect();
				menu[colIt]->setTextPosition({ 480, 660 });
				menu[colIt]->setQty(1, false);
			}
		}
		else if (universe->getCurrentPlanet()->getType() == 1 && !flag[justColonized])	//  Colony Planet
		{
			menu[colIt]->setString("Colonize the Planet");
			menu[colIt]->setTextPosition({ 500, 660 });
			menu[colIt]->setSrcPos({ 0, 0 });
			menu[colIt]->updateTextRect();
			menu[colIt]->setQty(1, false);
		}
		else                                                             //  Everything else
		{
			//std::cout << "Everything Else" << std::endl;
		}
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Draws the Flight Menu
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::drawFlightMenu(sf::RenderWindow &gWindow)
{
	for (int i = 0; i < MENUSIZE; i++)
	{
		if (menu[i]->getQty() == 1)
			menu[i]->draw(gWindow);
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Draws the Flight Path
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::drawFlightPath(sf::RenderWindow &gWindow)
{
	float xPos = 50;
	float yPos = 200;
	//  Draws the flightPath taken so far
	for (int i = 0; i < universe->getCurrentMove(); i++)
	{
		universe->getCurrentSector()[i]->setScale(CRDSSCL);
		universe->getCurrentSector()[i]->setPosition({ xPos + i * 100, yPos });
		universe->getCurrentSector()[i]->draw(gWindow);
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Draws the Current Planet
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::drawCurrentPlanet(sf::RenderWindow &gWindow)
{
	cPlanet->draw(gWindow);
	universe->getCurrentPlanet()->setScale(CRDLSCL);
	universe->getCurrentPlanet()->setPosition({ 825, 520 });
	universe->getCurrentPlanet()->draw(gWindow);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Returns true if any Trade Icons are clicked
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Game::tradeIconsTargeted(sf::RenderWindow &gWindow)
{
	if (flag[tradeInProgress])
	{
		for (int i = 0; i < 4; i++)
			if (tradeMenuIcons[i]->isTargeted(gWindow))
				return true;
		for (int i = 0; i < 6; i++)						
			if(tradeSaveState[i]->isTargeted(gWindow))
				return true;
		if (universe->getCurrentPlanet()->isTargeted(gWindow))
			return true;
	}
	return false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Checks if any current Menu Options are chosen
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Game::menuOptionTargeted(sf::RenderWindow &gWindow, int &num)
{
	for (int i = 0; i < MENUSIZE; i++)
	{
		if (menu[i]->getQty() == 1 && menu[i]->isTargeted(gWindow))
		{
			num = i;
			return true;
		}
	}
	return false;
}