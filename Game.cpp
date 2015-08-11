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
	if (!font.loadFromFile(FNTFLE)){
		std::cout << "Font not Loaded" << std::endl;
	}

	flightDie.icon = new Object(txtMgr.getResource(SDIEFLE), sf::Vector2f{ 350, 525 }, 1, sf::Vector2u(200, 200));
	flightDie.icon->setScale({ .4f, .4f });
	flightDie.text.setFont(font);
	flightDie.text.setStyle(sf::Text::Bold);
	flightDie.text.setPosition({ 440, 545 });		///////////////////////////////   needs to be a relative position rather than fixed
	P1 = new Player(txtMgr, "Player1", 1);		// Default names for bugtesting
	P2 = new Player(txtMgr, "Player2", 2);		// Default names for bugtesting
	universe = new Universe(txtMgr);
	screenSize = sf::Vector2u(1200, 900);
	gWindow.create(sf::VideoMode(screenSize.x, screenSize.y), "Starship Game");
	visibleArea = sf::FloatRect(0.0f, 0.0f, (float)screenSize.x, (float)screenSize.y);
	view.reset(visibleArea);
	gWindow.setView(view);
	phaseSetupComplete = false;
	phaseComplete = false;
	gainProductionResource = false;
	cPhase = production;
	phaseNameString.setFont(font);
	phaseNameString.setString("Production Phase");
	phaseNameString.setPosition({ 200, 820 });		 ///////////////////////////////   needs to be a relative position rather than fixed
	errorString.setFont(font);
	errorString.setStyle(sf::Text::Bold);
	errorString.setPosition({ 550, 820 });   ///////////////////////////////   needs to be a relative position rather than fixed
	errorTimer = 255;
	infoString.setFont(font);
	infoString.setStyle(sf::Text::Bold);
	infoString.setPosition({ 40, 30 });		 ///////////////////////////////   needs to be a relative position rather than fixed
	cPlyr = P2;
	playerSetup();
	initCDie();
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
	//ColonyCard(int num, string name, int type, int resource, int actNum, int vicPts) 
	Card* tempCard;

	//M		colony	Carbon	1	N/A	0	1	Colony: Alioth VIII
	tempCard = new ColonyCard(-1, "Colony: Alioth VIII", colony, Carbon, 1, 1, txtMgr.getResource(STRFILE), CLPOS);
	tempCard->setScale(CRDSSCL);
//	tempCard->setSrcPos({ 1, 0 });
	tempCard->updateTextRect();
	P1->getColonyZone()->insertNode(tempCard);

	///////////////////////   BEGIN TEST STUFF
	tempCard = new ColonyCard(-1, "Colony: Alioth VIII", colony, Carbon, 1, 1, txtMgr.getResource(STRFILE), { 400, 690 });
	tempCard->setScale({ .35f, .35f });
	tempCard->updateTextRect();
	P1->getColonyZone()->insertNode(tempCard);

	tempCard = new ColonyCard(-1, "Colony: Alioth VIII", colony, Carbon, 1, 1, txtMgr.getResource(STRFILE), { 400, 690 });
	tempCard->setScale({ .35f, .35f });
	tempCard->updateTextRect();
	P1->getColonyZone()->insertNode(tempCard);

	tempCard = new ColonyCard(-1, "Colony: Alioth VIII", colony, Carbon, 1, 1, txtMgr.getResource(STRFILE), { 400, 690 });
	tempCard->setScale({ .35f, .35f });
	tempCard->updateTextRect();
	P1->getColonyZone()->insertNode(tempCard);

	tempCard = new ColonyCard(-1, "Colony: Alioth VIII", colony, Carbon, 1, 1, txtMgr.getResource(STRFILE), { 400, 690 });
	tempCard->setScale({ .35f, .35f });
	tempCard->updateTextRect();
	P1->getTradeZone()->insertNode(tempCard);

	tempCard = new ColonyCard(-1, "Colony: Alioth VIII", colony, Carbon, 1, 1, txtMgr.getResource(STRFILE), { 400, 690 });
	tempCard->setScale({ .35f, .35f });
	tempCard->updateTextRect();
	P1->getTradeZone()->insertNode(tempCard);

	///////////////////////   END TEST STUFF


	//S		colony	Fuel		1	N/A	0	1	Colony: Megrez VII
	tempCard = new ColonyCard(-1, "Colony: Megrez VII", colony, Fuel, 1, 1, txtMgr.getResource(STRFILE), CLPOS);
	tempCard->setScale(CRDSSCL);
	tempCard->setSrcPos({ 1, 0 });
	tempCard->updateTextRect();
	P2->getColonyZone()->insertNode(tempCard);
	
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
	cPlyr->update();
//		cout << "CheckWin will be here.\n";
//		gameTurn();
//		cout << "Q to Toggle Win Condition\n";
//		cin >> choice;
//	}
	sf::Event event;
	int tempType;
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
			case sf::Event::Resized:
				if (event.type == sf::Event::Resized){
					screenSize = gWindow.getSize();
					std::cout << event.size.width << " " << event.size.height << std::endl;
					visibleArea = sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height);
					gWindow.setView(sf::View(visibleArea));
				}

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
					// Colony Zone (Large Icon) is clicked
					if (!cPlyr->getColonyZone()->isSmall() && cPlyr->getColonyZone()->showIconOnly() && cPlyr->getColonyZone()->isIconTargeted(gWindow))
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
							if (cPlyr->getStarship()->gainResource(tempType, statusUpdate))
							{
								phaseComplete = true;
								gainProductionResource = false;
								infoString.setString("Press Enter to End Phase");
							}
					}
					break;
				case flight:
					break;
				case trades:
					break;
				case build:
					// Starship (Small) is clicked
					if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall())
					{
						//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						//	cPlyr->makeBig();
						view.setCenter(SMLPOS.x, SMLPOS.y);
						view.move(100, 100);
						view.zoom(0.75f);
						gWindow.setView(view);
					}
					// Starship (Large) is clicked
					else if (cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall())
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
							cPlyr->getStarship()->bigLeftClicked(gWindow, statusUpdate);
						else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
							cPlyr->getStarship()->bigRightClicked(gWindow, statusUpdate);
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
					// Colony Zone (Large List) is clicked
					else if (!cPlyr->getColonyZone()->isSmall() && !cPlyr->getColonyZone()->showIconOnly() && cPlyr->getColonyZone()->isZoneTargeted(gWindow, tempType))
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
							cPlyr->getStarship()->gainResource(tempType, statusUpdate);
						else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
							cPlyr->getStarship()->loseResource(tempType, statusUpdate);
					}
					// Trade Zone (Large List) is clicked
					else if (!cPlyr->getTradeZone()->isSmall() && !cPlyr->getTradeZone()->showIconOnly() && cPlyr->getTradeZone()->isZoneTargeted(gWindow, tempType))
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
							cPlyr->getStarship()->gainResource(tempType, statusUpdate);
						else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
							cPlyr->getStarship()->loseResource(tempType, statusUpdate);
					}
					//  Starship (Large) && Empty Space is clicked
					else if (!cPlyr->getStarship()->isTargeted(gWindow) && !cPlyr->getStarship()->isSmall())
					{
						cPlyr->makeSmall();
					}
				}			
			break;
			case sf::Event::MouseMoved:
				switch (cPhase)
				{
				case production:
					break;
				case flight:
					break;
				case trades:
					break;
				case build:
					std::cout << std::endl;
					if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall())
					{
						std::cout << "P1 Ship Glows" << std::endl;
					}
					break;
				}
			}				
		}
		gWindow.clear();
		updateGameWindow(gWindow);
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

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  inital phase setup
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::phaseSetup()
{	
	int dieRoll;
	std::string tempString;
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
			tempString += " Resource(s) in Colony Zone Found!.  Press Select One.";
			gainProductionResource = true;
			phaseComplete = false;
		}
		else
		{
			tempString += " No Resources in Colony Zone.  Press Enter to end Phase.";
			phaseComplete = true;
		}
		infoString.setString(tempString);			
		break;
	case flight:
		phaseNameString.setString("Flight Phase");
		cPlyr->makeSmall();
		infoString.setString("Max Flight: " + std::to_string(cPlyr->getStarship()->getMaxDistance()));
		break;
	case trades:
		phaseNameString.setString("Trade Phase");
		infoString.setString("Max Trades: 2");
		cPlyr->makeBig();
		cPlyr->expandTradeZone();
		break;
	case build:
		phaseNameString.setString("Build Phase");
		infoString.setString("Max Builds: N/A");
		cPlyr->makeBig();
		break;
	}
	phaseSetupComplete = true;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  sets cPhase to next phase, checks for end of build phase
//  and sets back to production
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
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

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
//  draws the icons and stats for game Window
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::updateGameWindow(sf::RenderWindow &gWindow)
{
	universe->getBoard()->draw(gWindow);
	cPlyr->draw(gWindow);
	gWindow.draw(phaseNameString);
	gWindow.draw(infoString);
	if (cPhase == production)
	{
		flightDie.icon->draw(gWindow);
		gWindow.draw(flightDie.text);
	}
		
	if (statusUpdate.length())
		setError(statusUpdate);
	statusUpdate.clear();
	if (errorTimer)
	{
		gWindow.draw(errorString);
		errorString.setColor(sf::Color(255, 0, 0, errorTimer));
		errorTimer--;
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  updates the Error String and timer with the error message
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::setError(std::string error)
{
	errorTimer = 255;
	errorString.setString(error);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  rand(1-3) and updates the sprite to correct textureRect
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
int Game::rollSpeedDie()
{
	int num = rand() % 3;
	flightDie.icon->setSrcPos(sf::Vector2u(num, 0));
	flightDie.icon->updateTextRect();
	flightDie.text.setString("Dice roll: " + std::to_string(num + 1));
	return num + 1;
}