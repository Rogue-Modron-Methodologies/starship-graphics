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
Game::Game() : cPlanet(txtMgr.getResource(UNIVERSECARDIMAGES), { 825, 520 }, 0, { 200, 300 }, { 4, 13 })
{
	flightDie = new Icon(txtMgr.getResource(SDIEFLE), sf::Vector2f{ 350, 525 }, 1, sf::Vector2u(80, 80));
	flightDie->initString(fntMgr.getResource(FNTFLE), { 440, 545 }, "", sf::Text::Bold);		

	combatDie = new Icon*[2];

	combatDie[ply] = new Icon(txtMgr.getResource(CDIEFLE), sf::Vector2f{ 350, 525 }, 1, sf::Vector2u(200, 200));
	combatDie[ply]->initString(fntMgr.getResource(FNTFLE), { 440, 545 }, "", sf::Text::Bold);

	combatDie[prt] = new Icon(txtMgr.getResource(CDIEFLE), sf::Vector2f{ 350, 525 }, 1, sf::Vector2u(200, 200));
	combatDie[prt]->initString(fntMgr.getResource(FNTFLE), { 440, 545 }, "", sf::Text::Bold);
	
	P1 = new Player(txtMgr, fntMgr, "Player1", 1);		// Default names for bugtesting
	P2 = new Player(txtMgr, fntMgr, "Player2", 2);		// Default names for bugtesting
	cPlyr = P2;

	friendPeople = new Icon(txtMgr.getResource(FRIENDHERO), sf::Vector2f{ 900, 840 }, 1, sf::Vector2u(200, 200), { 1, 0 });
	friendPeople->setScale({ .3f, .3f });
	heroPeople = new Icon(txtMgr.getResource(FRIENDHERO), sf::Vector2f{ 975, 840 }, 1, sf::Vector2u(200, 200), { 0, 0 });
	heroPeople->setScale({ .3f, .3f });

	cPlanet.initString(fntMgr.getResource(FNTFLE), { 835, 480 }, "Current Planet");

	phaseNameString = new Icon(fntMgr.getResource(FNTFLE), { 200, 820 }, "Production Planet");	 
	
	errorString = new Icon(fntMgr.getResource(FNTFLE), { 550, 820 }, "", sf::Text::Bold);
	errorTimer = 255;
	
	infoString = new Icon(fntMgr.getResource(FNTFLE), { 40, 30 }, "", sf::Text::Bold);
	
	endPhaseString = new Icon(fntMgr.getResource(FNTFLE), { 825, 25 }, "End of Phase\n(Press Enter)", sf::Text::Bold);
	endPhaseString->setTextScale({ 2, 2 });
	endPhaseString->setTextColor(sf::Color::Red);

	specialString = new Icon(fntMgr.getResource(FNTFLE), { 650, 30 }, "", sf::Text::Bold);
	specialString->setTextColor(sf::Color::Green);

	flightEventString = new Icon(fntMgr.getResource(FNTFLE), { 580, 525 }, "");
	flightEventString->setTextColor(sf::Color::Green);

	tradeSaveState = new Icon*[NUMRESOURCES];
	tradeSaveState[astro] = new Icon(txtMgr.getResource(SYM1FLE), { 780, 562 }, 25, { 35, 35 }, { 3, 0 });
	tradeSaveState[science] = new Icon(txtMgr.getResource(RICNFLE), { 780, 565 }, 1, { 35, 35 });
	tradeSaveState[ore] = new Icon(txtMgr.getResource(RICNFLE), { 780, 600 }, 1, { 35, 35 }, { 1, 0 });
	tradeSaveState[fuel] = new Icon(txtMgr.getResource(RICNFLE), { 780, 635 }, 1, { 35, 35 }, { 2, 0 });
	tradeSaveState[tradeGood] = new Icon(txtMgr.getResource(RICNFLE), { 780, 670 }, 1, { 35, 35 }, { 3, 0 });
	tradeSaveState[wheat] = new Icon(txtMgr.getResource(RICNFLE), { 780, 705 }, 1, { 35, 35 }, { 4, 0 });
	tradeSaveState[carbon] = new Icon(txtMgr.getResource(RICNFLE), { 780, 740 }, 1, { 35, 35 }, { 5, 0 });

	tradeMenuIcons = new Icon*[TRADEMENUSIZE];
	tradeMenuIcons[plus] = new Icon(txtMgr.getResource(TRDICN), { 675, 575 }, 1, { 50, 50 }, { 0, 0 });
	tradeMenuIcons[minus] = new Icon(txtMgr.getResource(TRDICN), { 675, 675 }, 1, { 50, 50 }, { 1, 0 });
	tradeMenuIcons[check] = new Icon(txtMgr.getResource(TRDICN), { 635, 760 }, 1, { 50, 50 }, { 2, 0 });
	tradeMenuIcons[cancel] = new Icon(txtMgr.getResource(TRDICN), { 710, 760 }, 1, { 50, 50 }, { 3, 0 });

	pirateMenuIcons = new Icon*[PMENUSIZE];

	pirateMenuIcons[pay] = new Icon(txtMgr.getResource(SYMBFLE), { 710, 610 }, 0, { 50, 50 }, { 3, 0 });
	pirateMenuIcons[pay]->initString(fntMgr.getResource(FNTFLE), { 600, 610 }, "Bribe");

	pirateMenuIcons[fight] = new Icon(txtMgr.getResource(SYMBFLE), { 710, 660 }, 0, { 50, 50 }, { 2, 0 });
	pirateMenuIcons[fight]->initString(fntMgr.getResource(FNTFLE), { 600, 660 }, "Fight");

	flightMenuIcons = new Icon*[FMENUSIZE];

	flightMenuIcons[trdW] = new Icon(txtMgr.getResource(SYMBFLE), { 760, 610 }, 0, { 50, 50 }, { 3, 0 });
	flightMenuIcons[trdW]->initString(fntMgr.getResource(FNTFLE), { 520, 610 }, "Trade With Planet");

	flightMenuIcons[colIt] = new Icon(txtMgr.getResource(SYMBFLE), sf::Vector2f(760, 660), 0, { 50, 50 }, { 1, 0 });
	flightMenuIcons[colIt]->initString(fntMgr.getResource(FNTFLE), { 760, 660 }, "Colonize");

	flightMenuIcons[conFly] = new Icon(txtMgr.getResource(SYMBFLE), sf::Vector2f(760, 710), 0, { 50, 50 }, { 4, 0 });
	flightMenuIcons[conFly]->initString(fntMgr.getResource(FNTFLE), { 550, 710 }, "Continue Flying");

	flightMenuIcons[endFl] = new Icon(txtMgr.getResource(SYMBFLE), sf::Vector2f(760, 760), 0, { 50, 50 }, { 5, 0 });
	flightMenuIcons[endFl]->initString(fntMgr.getResource(FNTFLE), { 610, 760 }, "End Flight");

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
	ColonyCard* tempCard;
	//M		colony	Carbon	1	N/A	0	1	Colony: Alioth VIII
	//ColonyCard(const sf::Texture &texture, sf::Vector2u srcPos, int num, std::string name, int type, int resource, int actNum, int vicPts)
	tempCard = new ColonyCard(txtMgr.getResource(STRFILE), { 1, 0 }, -1, "Colony: Alioth VIII", colony, Carbon, 1, 1);
	tempCard->setScale(CRDZNSCL);
	tempCard->updateTextRect();
	P1->getColonyZone()->push_back(tempCard);

	//S		colony	Fuel		1	N/A	0	1	Colony: Megrez VII
	tempCard = new ColonyCard(txtMgr.getResource(STRFILE), { 0, 0 }, -1, "Colony: Megrez VII", colony, Fuel, 1, 1);
	tempCard->setScale(CRDZNSCL);
	tempCard->updateTextRect();
	P2->getColonyZone()->push_back(tempCard);
	
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
	//cPlyr == P1 ? cPlyr = P2 : cPlyr = P1;	// toggles between players
	//cPlyr->updatePlayerIcon();
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
					productionPhaseListener();
					break;
				case flight:
					if (!flag[sectorSelected])
						preFlightListener(tempNum);
					if (flag[sectorSelected])
						flightPhaseListener(tempNum);
					if (flag[tradeInProgress])
						tradeMenuListener(tempNum);
					break;
				case tradeBuild:
					tradeBuildPhaseListener();
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
				case tradeBuild:
					//std::cout << std::endl;
					//if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall())
					//	std::cout << "P1 Ship Glows" << std::endl;
					break;
				}
			}				
		}

		gWindow.clear();
		updateDrawGameWindow();			//  Updates the screen objects	
		gWindow.display();
	}
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//
//  inital phase setup
//
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
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
		flag[pirateAttack] = false;
		flag[pirateChoice] = false;
		infoString->setString("Flight: 0 / " + std::to_string(cPlyr->getStarship()->getMaxDistance()) + "\nMax Actions: 0 / " + 
			std::to_string(cPlyr->getStarship()->getMaxActions()));
		specialString->setString("Select a Sector");
		specialString->setTextPosition({ 425, 40 });
		break;
	case tradeBuild:
		phaseNameString->setString("Trade & Build Phase");
		infoString->setString("Trade & Build Phase");
		cPlyr->makeBig();
		flag[phaseComplete] = true;		//  Only until there is an actual phase coded
		break;
	}
	flag[phaseSetupComplete] = true;
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//  
//  draws the icons and stats for game Window
//
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::updateDrawGameWindow()
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
			// Draw Flight Path
			if (flag[visFlightPath]) 
			{
				float xPos = 50;
				float yPos = 200;
				int cMove = universe->getCurrentMove();
				int numToDisplay = flag[pirateAttack] ? cMove - 1 : cMove;
				//  Draws the flightPath taken so far
				for (int i = 0; i < numToDisplay; i++)
				{
					universe->getCurrentSector()[i]->setScale(CRDSSCL);
					universe->getCurrentSector()[i]->setPosition({ xPos + i * 100, yPos });
					universe->getCurrentSector()[i]->draw(gWindow);
				}
			}
			cPlanet.draw(gWindow);
			//  Flight Phase - phase is not complete and player hasn't reached max actions
			if (!flag[phaseComplete] && actionNum < cPlyr->getStarship()->getMaxActions())
			{
				infoString->setString("Flight: " + std::to_string(universe->getCurrentMove()) + " / " + std::to_string(cPlyr->getStarship()->getMaxDistance())
					+ "\nMax Actions: " + std::to_string(actionNum) + " / " + std::to_string(cPlyr->getStarship()->getMaxActions()));

				//  When flight menu is active	
				if (flag[visFlightMenu])
				{
					updateFlightMenu();
					// Draw the Flight Menu
					for (int i = 0; i < FMENUSIZE; i++)
					{
						if (flightMenuIcons[i]->getQty() == 1)
							flightMenuIcons[i]->draw(gWindow);
					}
				}
				//  When pirate menu is active ( Bribe/Flight Choice )
				else if (flag[pirateAttack] && !flag[pirateChoice])
				{
					pirateMenuIcons[pay]->draw(gWindow);
					pirateMenuIcons[fight]->draw(gWindow);				
				}
				//  When Winner of Pirate Attack (Gain a resource)
				else if (flag[pirateAttack] && flag[pirateChoice] && flag[gainResource])
				{
					for (int i = 0; i < 6; i++)
						tradeSaveState[i]->draw(gWindow);	//  Prints the resource icons available	
					if (gainOneResource())
					{
						std::cout << "Pirate being pushed into the zone " << universe->getCurrentPlanet()->getName() << std::endl;
						cPlyr->getPirateZone()->push_back((Pirate*)universe->getCurrentPlanet());
						universe->replaceCurrentPlanet();
						flag[gainResource] = false;
					}			
				}
				//  When Loser of Pirate Attack (Lose a part of your ship)  Implement with build phase
				else if (flag[pirateAttack] && flag[pirateResult])
				{
					; //  Implement
				}
				//  When trade menu is active
				else if (flag[tradeInProgress])
				{									
					for (int i = 0; i < 4; i++)
						tradeMenuIcons[i]->draw(gWindow);	//  Prints the Trade Menu Clickable Items
					for (int i = 0; i < 6; i++)					
						tradeSaveState[i]->draw(gWindow);	//  Prints the resource icons available			
 				}				
			}
			//  When the flight phase is complete
			else
			{     
				specialString->setString("Flight Complete");
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
	flightEventString->draw(gWindow);
	cPlyr->draw(gWindow);	

	if (cPlyr->isFriend())
		friendPeople->draw(gWindow);
	if (cPlyr->isHero())
		heroPeople->draw(gWindow);

	if (statusUpdate.length())
	{
		errorTimer = 2550;
		errorString->setString(statusUpdate);
	}
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

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//  Deals with Mouse Click actions in the Production Phase
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::productionPhaseListener(){
	int tempType;
	// Starship (Small) is clicked
	if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			cPlyr->makeBig();
			flightDie->setIconPosition({ 350, 525 });
			flightDie->setTextPosition({ 440, 545 });
		}
	}
	// Colony Zone (Large Icon) is clicked
	else if (!cPlyr->zonesSmall() && cPlyr->getColonyZone()->getIconOnly() && cPlyr->getColonyZone()->isIconTargeted(gWindow))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandColonyZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	else if (!cPlyr->zonesSmall() && cPlyr->getTradeZone()->getIconOnly() && cPlyr->getTradeZone()->isIconTargeted(gWindow))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cPlyr->expandTradeZone();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cPlyr->makeBig();
	}
	// Colony Zone (Large List) is clicked and player is entitled to a production resource
	else if (!cPlyr->zonesSmall() && !cPlyr->getColonyZone()->getIconOnly() && cPlyr->getColonyZone()->isZoneTargeted(gWindow, tempType))
	{
		
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

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//  Flight Phase Sector Selection Listener
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::preFlightListener(int &tempType){
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

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//  Deals with Mouse Click actions in the Flight Phase
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::flightPhaseListener(int tempType){	

	//  If Pirate Attack is 
	if (flag[pirateAttack]){
		pirateMenuListener();
	}
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
	else if (!flag[phaseComplete] && flag[visFlightMenu] && flightMenuOptionTargeted(tempType)){
		switch (tempType)
		{
		case colIt:	//  Colonize/Establish Post
			if (universe->getCurrentPlanet()->getType() == tradeShip && cPlyr->getStarship()->shipAvailable(tradeShip, tempType, statusUpdate)){
				//cPlyr->getStarship()->loseItem(tempType, statusUpdate);
				cPlyr->getTradeZone()->push_back((TradeCard*)universe->getCurrentPlanet());
				cPlyr->getTradeZone()->updateZone(cPlyr->getTradeZone()->getPosition(), cPlyr->getTradeZone()->getScale(), cPlyr->getTradeZone()->getIconOnly());
				cPlyr->addFrdPt();
				updateFriendOfThePeople();
				universe->replaceCurrentPlanet();
				flag[justColonized] = true;
				actionNum++;
			}
			else if (universe->getCurrentPlanet()->getType() == colonyShip &&cPlyr->getStarship()->shipAvailable(colonyShip, tempType, statusUpdate)){
				//cPlyr->getStarship()->loseItem(tempType, statusUpdate);
				cPlyr->getColonyZone()->push_back((ColonyCard*)universe->getCurrentPlanet());
				cPlyr->getColonyZone()->updateZone(cPlyr->getColonyZone()->getPosition(), cPlyr->getColonyZone()->getScale(), cPlyr->getColonyZone()->getIconOnly());
				cPlyr->addVicPt();
				universe->replaceCurrentPlanet();
				flag[justColonized] = true;
				actionNum++;
			}
			infoString->setString(statusUpdate);
			break;			
		case trdW:	//  Trade with Planet
			initTradeMenu(tempType);
			break;
		case conFly:	// Continue Flight
			universe->continueFlight();
			flag[justTraded] = false;
			flag[justColonized] = false;
			flag[pirateAttack] = false;
			flag[pirateChoice] = false;
			flightEventString->clear();
			specialString->setString("Flight Sector: " + std::to_string(universe->getCurrentSectorNum() + 1));
			break;
		case endFl:	//  End Flight
			flag[phaseComplete] = true;
			flightEventString->clear();
			break;
		}
	}
	//  Starship (Large) && Empty Space is clicked
	else if (!cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall() && !tradeIconsTargeted()){
		cPlyr->makeSmall();
		flag[visFlightPath] = true;
	}
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//  Deals with Mouse Click actions when the tradeMenu is displayed
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::tradeMenuListener(int tempType)
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
			flightEventString->setString("Trade Complete");
		}
		else
			flightEventString->setString("No Trade");

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
		flightEventString->setString("Trade Cancelled");
	}
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//  Deals with Mouse Click actions in the Pirate Menu
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::pirateMenuListener(){
	if (!flag[pirateChoice])								//  If the choice to pay/fight hasn't been made yet
	{
		if (pirateMenuIcons[pay]->isTargeted(gWindow))		//  If the player decides to pay
		{
			if (cPlyr->canAfford(universe->getCurrentPlanet()->getCost(), statusUpdate))
			{
				cPlyr->subAstro(universe->getCurrentPlanet()->getCost());
				specialString->clear();
				cPlanet.setSrcPos(universe->getCurrentPlanet()->getSrcPos());
				cPlanet.updateTextRect();
				flightEventString->setString("Bribe Payed");
				flag[pirateChoice] = true;
				flag[pirateAttack] = false;
				flag[visFlightMenu] = true;
			}
		}
		else	if (pirateMenuIcons[fight]->isTargeted(gWindow))	// If the player decides to fight
		{	
			flag[pirateChoice] = true;
			rollCombatDie(ply);
			rollCombatDie(prt);
			int plyRes = combatDie[ply]->getQty() + cPlyr->getStarship()->totalLasers();
			int pirRes = combatDie[ply]->getQty() + universe->getCurrentPlanet()->getCannons();
			std::cout << "Player: " << plyRes << "   " << combatDie[ply]->getQty() << " + " << cPlyr->getStarship()->totalLasers() << std::endl;
			std::cout << "Pirate: " << pirRes << "   " << combatDie[prt]->getQty() << " + " << universe->getCurrentPlanet()->getCannons() << std::endl;
			if (plyRes >= pirRes)			//  If the player wins
			{
				flag[gainResource] = true;
				flightEventString->setString("Choose a resource");
				specialString->setString("VICTORY!!! Gain a resource and a fame point");
				cPlyr->addFmPt();
				updateFriendOfThePeople();
			}
			else                              	//  If the pirate wins
			{
				specialString->setString("Flight Complete");
				if (universe->getCurrentPlanet()->getResult() == "N/A")
				{
					flag[pirateResult] = false;
					flag[gainResource] = false;
					flag[phaseComplete] = true;
					flag[visFlightMenu] = true;
					flightEventString->setString("DEFEAT!\n\nRESULT: Flight Ends");
				}
				else
				{
					std::cout << "RESULT: " << universe->getCurrentPlanet()->getResult() << std::endl;
					std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl; //  Implement this
					flightEventString->setString("DEFEAT!\n\nRESULT:");
				}
			}
			//  Reveal the Pirate
			cPlanet.setSrcPos(universe->getCurrentPlanet()->getSrcPos());
			cPlanet.updateTextRect();
		}
	}
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//  Deals with Mouse Click actions in the Build Phase
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::tradeBuildPhaseListener()
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

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//  Sets up and maintains tradeMenu Details
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::initTradeMenu(int tempType)
{
	flag[visFlightMenu] = false;
	flag[tradeInProgress] = true;
	flightEventString->setString("Trade In Progress");
	int cResource = universe->getCurrentPlanet()->getResource();
	for (int i = 0; i < NUMRESOURCES; i++)
	{
		tradeSaveState[i]->setQty(cPlyr->getStatQty(i));			//  saves the current resource and astro values
		tradeSaveState[i]->greyOut();							
	}
	tradeSaveState[cResource]->unGreyOut();

	std::string type = universe->getCurrentPlanet()->getTransaction();
	if (type == "Buy")			//  Can only buy at this trade post
	{
		tradeMenuIcons[plus]->unGreyOut();
		tradeMenuIcons[minus]->greyOut();
	}
	else if (type == "Sell")		//  Can only sell at this trade post
	{
		tradeMenuIcons[plus]->greyOut();
		tradeMenuIcons[minus]->unGreyOut();
	}
	else                          //  Can buy or sell at this trade post
	{
		tradeMenuIcons[plus]->unGreyOut();
		tradeMenuIcons[minus]->unGreyOut();
	}
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//  Sets up and maintains combat menu
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::initPirateMenu()
{
	flag[pirateAttack] = true;
	flag[visFlightMenu] = false;
	cPlanet.setSrcPos({ 4, 13 });				//  Card Back
	cPlanet.updateTextRect();
	specialString->setString("There is a Pirate Here!  They demand " + std::to_string(universe->getCurrentPlanet()->getCost()) + " astro!");
	flightEventString->setString("Bribe / Fight");
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//
//  Configures the Flight Menu Options
//
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::updateFlightMenu()
{
	for (int i = 0; i < FMENUSIZE; i++)
		flightMenuIcons[i]->setQty(0, false);

	if (universe->getCurrentPlanet()->getType() == 2 && !flag[justColonized] && !flag[pirateChoice])			//  PIRATE'S CHOICE
		initPirateMenu();
	else  //  NOT PIRATE
	{
		cPlanet.setSrcPos(universe->getCurrentPlanet()->getSrcPos());
		cPlanet.updateTextRect();
		flightMenuIcons[endFl]->setQty(1, false);
		if (universe->getCurrentMove() < cPlyr->getStarship()->getMaxDistance()) 
			flightMenuIcons[conFly]->setQty(1, false);
		if (universe->getCurrentPlanet()->getType() == 0)							//  Trade Planet
		{
			if (!flag[justTraded] && !flag[justColonized])
				flightMenuIcons[trdW]->setQty(1, false);
			if (universe->getCurrentPlanet()->getPts() == 1 && !flag[justColonized])	//  Can be colonized
			{
				flightMenuIcons[colIt]->setString("Establish Trade Post");
				flightMenuIcons[colIt]->setSrcPos({ 1, 0 });
				flightMenuIcons[colIt]->updateTextRect();
				flightMenuIcons[colIt]->setTextPosition({ 480, 660 });
				flightMenuIcons[colIt]->setQty(1, false);
			}
		}
		else if (universe->getCurrentPlanet()->getType() == 1 && !flag[justColonized])	//  Colony Planet
		{
			flightMenuIcons[colIt]->setString("Colonize the Planet");
			flightMenuIcons[colIt]->setTextPosition({ 500, 660 });
			flightMenuIcons[colIt]->setSrcPos({ 0, 0 });
			flightMenuIcons[colIt]->updateTextRect();
			flightMenuIcons[colIt]->setQty(1, false);
		}
		else                                                             //  Everything else
		{
			//std::cout << "Everything Else" << std::endl;
		}
	}
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//
//  Returns true if any Trade Icons are clicked
//
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
bool Game::tradeIconsTargeted()
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

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//
//  Checks if any current Menu Options are chosen
//
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
bool Game::flightMenuOptionTargeted(int &num)
{
	for (int i = 0; i < FMENUSIZE; i++)
	{
		if (flightMenuIcons[i]->getQty() == 1 && flightMenuIcons[i]->isTargeted(gWindow))
		{
			num = i;
			return true;
		}
	}
	return false;
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//
//  Checks for Friend of the people on both players
//
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
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

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//
//  Checks for Hero of the people on both players
//
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::updateHeroOfThePeople()
{
	//  If current player has less than three hero points...
	if (cPlyr->getStatQty(fmPt) < 3)
		return;
	int p1pts = getP1()->getStatQty(fmPt);
	int p2pts = getP2()->getStatQty(fmPt);

	if (p1pts == p2pts)
	{
		getP1()->toggleFriend(false);
		getP2()->toggleFriend(false);
		statusUpdate = "Hero of the People Lost";
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

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//
//  Checks to see if a any resources in the parameter array exist
//  in the holds of the startship
//
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
bool Game::resourcesAvailable(int resAvail[])
{
	for (int i = 0; i < 6; i++){
		if (resAvail[i] && !cPlyr->getStarship()->holdFull(i)){
			return true;
		}
	}
	return false;
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//
//  Checks to see if a resource is available and if so allows 
//  player to chose one that is available.
//
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
bool Game::gainOneResource()
{
	int resAvail[6] = { 1, 1, 1, 1, 1, 1 };		
	for (int i = 0; i < 6; i++)
	{
		tradeSaveState[i]->unGreyOut();
		if(cPlyr->getStarship()->holdFull(i))			
			tradeSaveState[i]->greyOut();
	}
	//  If there are available resources
	if (resourcesAvailable(resAvail))
	{
		for (int i = 0; i < 6; i++)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && tradeSaveState[i]->isTargeted(gWindow))
			{
				if (cPlyr->getStarship()->gainItem(i, statusUpdate))
				{
					cPlyr->updateIcon(i);
					flightEventString->setString("Resources Gained");
					flag[gainResource] = false;
					flag[pirateAttack] = false;
					flag[visFlightMenu] = true;
					return true;
				}
			}
		}
	}
	//  If there are no available resources
	else
	{
		statusUpdate = "No Resources Available";
		flightEventString->setString("No Resources\nAvailable");
		flag[gainResource] = false;
		flag[pirateAttack] = false;
		flag[visFlightMenu] = true;
		return true;
	}
	return false;
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//  rand(1-3) and updates the sprite to correct textureRect
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::rollSpeedDie()
{
	int num = rand() % 3;
	flightDie->setSrcPos(sf::Vector2u(num, 0));
	flightDie->updateTextRect();
	flightDie->setQty(num + 1);
	flightDie->setString("Dice roll: " + std::to_string(num + 1));
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//  Rolls Combat Die
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
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
	combatDie[party]->updateTextRect();
	combatDie[party]->setString("Dice roll: " + std::to_string(num));
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
//
//  sets cPhase to next phase, checks for end of build phase
//  and sets back to production
//
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��) 
void Game::endPhase()
{
	specialString->clear();
	flightEventString->clear();
	cPhase++;
	if (cPhase == 3)
		cPhase = 0;
	flag[phaseSetupComplete] = false;
}