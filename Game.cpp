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
	P1 = new Player("Player1", 1);		// Default names for bugtesting
	P2 = new Player("Player2", 2);		// Default names for bugtesting
	universe = new Universe;
	gWindow.create(sf::VideoMode(1200, 900), "Starship Game");
	phaseSetupComplete = false;
	cPhase = production;
	phaseNameString.setFont(font);
	phaseNameString.setString("Production Phase");
	phaseNameString.setPosition({ 200, 820 });
	errorString.setFont(font);
	errorString.setStyle(sf::Text::Bold);
	errorString.setPosition({ 550, 820 });
	errorTimer = 255;
	cPlyr = P2;
	playerSetup();
	initSDie();
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
	tempCard = new ColonyCard(-1, "Colony: Alioth VIII", colony, Carbon, 1, 1, STRFILE, COLSPOS, CRDSSCL);
//	tempCard->setSrcPos({ 1, 0 });
	tempCard->getSprite()->setTextureRect(sf::IntRect(tempCard->getSrcPos().x * tempCard->getSrcSze().y, tempCard->getSrcPos().y * tempCard->getSrcSze().y, tempCard->getSrcSze().x, tempCard->getSrcSze().y));
	P1->getColonyZone()->insertNode(tempCard);



	
	///////////////////////   BEGIN TEST STUFF
	tempCard = new ColonyCard(-1, "Colony: Alioth VIII", colony, Carbon, 1, 1, STRFILE, { 400, 690 }, { .35f, .35f });
	tempCard->getSprite()->setTextureRect(sf::IntRect(tempCard->getSrcPos().x * tempCard->getSrcSze().y, tempCard->getSrcPos().y * tempCard->getSrcSze().y, tempCard->getSrcSze().x, tempCard->getSrcSze().y));
	P1->getColonyZone()->insertNode(tempCard);

	tempCard = new ColonyCard(-1, "Colony: Alioth VIII", colony, Carbon, 1, 1, STRFILE, { 500, 690 }, { .35f, .35f });
	tempCard->getSprite()->setTextureRect(sf::IntRect(tempCard->getSrcPos().x * tempCard->getSrcSze().y, tempCard->getSrcPos().y * tempCard->getSrcSze().y, tempCard->getSrcSze().x, tempCard->getSrcSze().y));
	P1->getColonyZone()->insertNode(tempCard);

	tempCard = new ColonyCard(-1, "Colony: Alioth VIII", colony, Carbon, 1, 1, STRFILE, { 600, 690 }, { .35f, .35f });
	tempCard->getSprite()->setTextureRect(sf::IntRect(tempCard->getSrcPos().x * tempCard->getSrcSze().y, tempCard->getSrcPos().y * tempCard->getSrcSze().y, tempCard->getSrcSze().x, tempCard->getSrcSze().y));
	P1->getColonyZone()->insertNode(tempCard);

	tempCard = new ColonyCard(-1, "Colony: Alioth VIII", colony, Carbon, 1, 1, STRFILE, TRDSPOS, { .35f, .35f });
	tempCard->getSprite()->setTextureRect(sf::IntRect(tempCard->getSrcPos().x * tempCard->getSrcSze().y, tempCard->getSrcPos().y * tempCard->getSrcSze().y, tempCard->getSrcSze().x, tempCard->getSrcSze().y));
	P1->getTradeZone()->insertNode(tempCard);

	tempCard = new ColonyCard(-1, "Colony: Alioth VIII", colony, Carbon, 1, 1, STRFILE, TRDSPOS, { .35f, .35f });
	tempCard->getSprite()->setTextureRect(sf::IntRect(tempCard->getSrcPos().x * tempCard->getSrcSze().y, tempCard->getSrcPos().y * tempCard->getSrcSze().y, tempCard->getSrcSze().x, tempCard->getSrcSze().y));
	P1->getTradeZone()->insertNode(tempCard);

	///////////////////////   END TEST STUFF


	//S		colony	Fuel		1	N/A	0	1	Colony: Megrez VII
	tempCard = new ColonyCard(-1, "Colony: Megrez VII", colony, Fuel, 1, 1, STRFILE, COLSPOS, CRDSSCL);
	tempCard->setSrcPos({ 1, 0 });
	tempCard->getSprite()->setTextureRect(sf::IntRect(tempCard->getSrcPos().x * tempCard->getSrcSze().y, tempCard->getSrcPos().y * tempCard->getSrcSze().y, tempCard->getSrcSze().x, tempCard->getSrcSze().y));
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
		switch (cPhase)
		{
		case production:
			while (gWindow.pollEvent(event))		// the event loop
			{
				switch (event.type) {
				case sf::Event::Closed:
					gWindow.close();
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
						gWindow.close();
					if (event.key.code == sf::Keyboard::Return)
						endPhase();
					break;
				}
			}
			break;
		case flight:
			while (gWindow.pollEvent(event))		// the event loop
			{
				switch (event.type) {
				case sf::Event::Closed:
					gWindow.close();
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
						gWindow.close();
					if (event.key.code == sf::Keyboard::Return)
						endPhase();
					break;
				}
			}
			break;
		case trades:
			while (gWindow.pollEvent(event))		// the event loop
			{
				switch (event.type) {
				case sf::Event::Closed:
					gWindow.close();
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
						gWindow.close();
					if (event.key.code == sf::Keyboard::Return)
						endPhase();
					break;
				}
			}
			break;
		case build:
			while (gWindow.pollEvent(event))		// the event loop
			{
				switch (event.type) {
				case sf::Event::Closed:
					gWindow.close();
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
						gWindow.close();
					if (event.key.code == sf::Keyboard::Return)
						endPhase();
					break;

				case sf::Event::MouseMoved:
					std::cout << std::endl;
					if (cPlyr->getStarship()->isTargeted(gWindow) && cPlyr->getStarship()->isSmall())
					{
						std::cout << "P1 Ship Glows" << std::endl;
					}
					break;
				case sf::Event::MouseButtonPressed:
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
			}
			break;
		}

		gWindow.clear();
		updateGameWindow(gWindow);
		gWindow.display();
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Initialize Speed Die
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::initSDie()
{
	speedDie[0] = 1;
	speedDie[1] = 1;
	speedDie[2] = 2;
	speedDie[3] = 2;
	speedDie[4] = 3;
	speedDie[5] = 3;
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
	switch (cPhase)
	{
	case production:
		phaseNameString.setString("Production Phase");
		dieRoll = rollSpeedDie();
		std::cout << dieRoll << std::endl;
		cPlyr->getStarship()->calcMaxDistance(dieRoll);
		cPlyr->makeBig();
		cPlyr->expandColonyZone();
		break;
	case flight:
		phaseNameString.setString("Flight Phase");
		break;
	case trades:
		phaseNameString.setString("Trade Phase");
		break;
	case build:
		phaseNameString.setString("Build Phase");
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
//  
//  updates the Error String and timer with the error message
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Game::setError(std::string error)
{
	errorTimer = 255;
	errorString.setString(error);
}
