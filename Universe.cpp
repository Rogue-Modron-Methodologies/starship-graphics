//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#include "Universe.h"
#include "Game.h"


// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Constructor
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
Universe::Universe(ResourceManager<sf::Texture> &txtMgr, ResourceManager<sf::Font> &fntMgr)
{
	board = new Object(txtMgr.getResource("resources/board/starrynight.png"), sf::Vector2f(0, 0));
	board->setScale({ 3.1f, 3.6f });

	flightSector[0].ico = new Object(txtMgr.getResource("resources/cards/CardBackground.png"), sf::Vector2f(100, 150), 10, sf::Vector2u(200, 300));
	flightSector[0].text.setFont(fntMgr.getResource(FNTFLE));
	flightSector[0].text.Bold;
	flightSector[0].text.setScale(sf::Vector2f(5, 5));
	flightSector[0].text.setString("1");
	flightSector[0].text.setPosition({ 175, 200 });

	flightSector[1].ico = new Object(txtMgr.getResource("resources/cards/CardBackground.png"), sf::Vector2f(300, 150), 10, sf::Vector2u(200, 300));
	flightSector[1].text.setFont(fntMgr.getResource(FNTFLE));
	flightSector[1].text.Bold;
	flightSector[1].text.setScale(sf::Vector2f(5, 5));
	flightSector[1].text.setString("2");
	flightSector[1].text.setPosition({ 360, 200 });

	flightSector[2].ico = new Object(txtMgr.getResource("resources/cards/CardBackground.png"), sf::Vector2f(500, 150), 10, sf::Vector2u(200, 300));
	flightSector[2].text.setFont(fntMgr.getResource(FNTFLE));
	flightSector[2].text.Bold;
	flightSector[2].text.setScale(sf::Vector2f(5, 5));
	flightSector[2].text.setString("3");
	flightSector[2].text.setPosition({ 560, 200 });

	flightSector[3].ico = new Object(txtMgr.getResource("resources/cards/CardBackground.png"), sf::Vector2f(700, 150), 10, sf::Vector2u(200, 300));
	flightSector[3].text.setFont(fntMgr.getResource(FNTFLE));
	flightSector[3].text.Bold;
	flightSector[3].text.setScale(sf::Vector2f(5, 5));
	flightSector[3].text.setString("4");
	flightSector[3].text.setPosition({ 760, 200 });

	menu = new Ico*[4];
	for (int i = 0; i < MENUSIZE; i++)
		menu[i] = new Ico;

	menu[trdW]->ico = new Object(txtMgr.getResource("resources/board/iconTemp.png"), sf::Vector2f(760, 610), 0);
	menu[trdW]->text.setFont(fntMgr.getResource(FNTFLE));
	menu[trdW]->text.setString("Trade With Planet");
	menu[trdW]->text.setPosition({ 520, 610 });

	menu[colIt]->ico = new Object(txtMgr.getResource("resources/board/iconTemp.png"), sf::Vector2f(760, 660), 0);
	menu[colIt]->text.setFont(fntMgr.getResource(FNTFLE));


	menu[conFly]->ico = new Object(txtMgr.getResource("resources/board/iconTemp.png"), sf::Vector2f(760, 710), 0);
	menu[conFly]->text.setFont(fntMgr.getResource(FNTFLE));
	menu[conFly]->text.setString("Continue Flying");
	menu[conFly]->text.setPosition({ 550, 710 });

	menu[endFl]->ico = new Object(txtMgr.getResource("resources/board/iconTemp.png"), sf::Vector2f(760, 760), 0);
	menu[endFl]->text.setFont(fntMgr.getResource(FNTFLE));
	menu[endFl]->text.setString("End Flight");
	menu[endFl]->text.setPosition({ 610, 760 });


	S1 = new Card*[10];
	S2 = new Card*[10];
	S3 = new Card*[10];
	S4 = new Card*[10];
	SE = new Card*[28];
	AD = new Card*[9];
	cAdv = new Card*[3];
	universeSetup(txtMgr);
	adventureDeckSetup();
	ExtraDeckPtr = 0;
	advPtr = 0;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Adds a Card to the Sector and increments the Pointer
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
Universe::~Universe()
{
	for (int i = 0; i < MENUSIZE; i++)
		delete menu[i]->ico;
	for (int i = 0; i < MENUSIZE; i++)
		delete menu[i];
	for (int i = 0; i < 4; i++)
		delete flightSector[i].ico;
	for (int i = 0; i < 10; i++)
		delete S1[i];
	for (int i = 0; i < 10; i++)
		delete S2[i];
	for (int i = 0; i < 10; i++)
		delete S3[i];
	for (int i = 0; i < 10; i++)
		delete S4[i];
	for (int i = 0; i < 28; i++)
		delete SE[i];
	for (int i = 0; i < 9; i++)
		delete AD[i];
	for (int i = 0; i < 3; i++)
		delete cAdv[i];
	delete [] S1;
	delete [] S2;
	delete [] S3;
	delete [] S4;
	delete [] SE;
	delete [] AD;
	delete [] cAdv;
	delete [] menu;
	delete board;	
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Draws the Sector Icons to the Screen
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Universe::drawSectors(sf::RenderWindow &gWindow)
{
	for (int i = 0; i < 4; i++)
	{
		flightSector[i].ico->draw(gWindow);
		gWindow.draw(flightSector[i].text);
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Checks to see if any of the sectors are clicked
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Universe::sectorsTargeted(sf::RenderWindow &gWindow, int &num)
{
	for (int i = 0; i < 4; i++)
	{
		if (flightSector[i].ico->isTargeted(gWindow))
		{
			num = i;
			return true;
		}
	}
	return false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Checks to see if any objects in the flightpath are clicked
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Universe::flightPathTargeted(sf::RenderWindow &gWindow, int &num)
{
	for (int i = 0; i < currentMove; i++)
	{
		if (getSector(sectorNum)[i]->isTargeted(gWindow))
		{
			num = i;
			return true;
		}
	}
	return false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Intializes the current flight path
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Universe::initializeFlightPath(int tempType)
{
	sectorNum = tempType;
	currentMove = 1;												///  debugging only
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Checks if any current Menu Options are chosen
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Universe::menuOptionTargeted(sf::RenderWindow &gWindow, int &num)
{
	for (int i = 0; i < MENUSIZE; i++)
	{
		if (menu[i]->ico->getQty() == 1 && menu[i]->ico->isTargeted(gWindow))
		{
			num = i;
			return true;
		}
	}
	return false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Adds a Card to the Sector and increments the Pointer
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Universe::addCardtoSector(int secNum, int i)
{
	setSector(SE[ExtraDeckPtr], secNum, i);
	ExtraDeckPtr++;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Adds a Card to the Adventure Deck and increments the Pointer
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Universe::addCardtoAdvDeck(int i)
{
	cAdv[i] = AD[advPtr];
	advPtr++;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Prints the current adventures available
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Universe::printCurrentAdventure(sf::RenderWindow &gWindow)
{
	for (int i = 0; i < 3; i++)
	{
		std::cout << "Adventure Card " << i + 1 << std::endl;
		cAdv[i]->draw(gWindow);
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Prints the current adventures available
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
Card* Universe::getAdvCard(int i)
{
	return cAdv[i];
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Setter for the Sector Decks
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Universe::setSector(Card* nCard, int sNum, int cNum)
{
	switch (sNum)
	{
	case 0:
		S1[cNum] = nCard;
		break;
	case 1:
		S2[cNum] = nCard;
		break;
	case 2:
		S3[cNum] = nCard;
		break;
	case 3:
		S4[cNum] = nCard;
		break;
	default:
		SE[cNum] = nCard;
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Getter for the Sector Decks
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
Card** Universe::getSector(int num)
{
	switch (num)
	{
	case 0:
		return S1;
	case 1:
		return S2;
	case 2:
		return S3;
	case 3:
		return S4;
	default:
		return SE;
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Sets up the adventure deck
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Universe::adventureDeckSetup()
{
	std::stringstream ss;
	std::string name, buffer, mission, requirement, temp;
	int deckNum, astro, fame, resourceNum, vicPts;
	AdventureCard* tempCard = 0;
	int ctr2 = 0, ctr3 = 0, ctr4 = 0;
	AdventureCard* tAry2[3]; AdventureCard* tAry3[3]; AdventureCard* tAry4[3];

	std::ifstream inputFile(ADVENTURELIST.c_str());
	if (!inputFile)
	{
		std::cout << ADVENTURELIST.c_str() << " failed to open.  Terminating Program\n";
		exit(EXIT_FAILURE);
	}
	getline(inputFile, buffer); // Title Line

	for (int i = 0; i < 12; i++)
	{
		getline(inputFile, buffer);
		ss << buffer;
		/*A*/	getline(ss, temp, ',');
		deckNum = stoi(temp);
		/*B*/	getline(ss, name, ',');
		/*C*/	getline(ss, mission, ',');
		/*D*/	getline(ss, requirement, ',');
		/*E*/	getline(ss, temp, ',');
		resourceNum = stoi(temp);
		/*F*/	getline(ss, temp, ',');
		astro = stoi(temp);
		/*G*/	getline(ss, temp, ',');
		fame = stoi(temp);
		/*H*/	getline(ss, temp, ',');
		vicPts = stoi(temp);
		ss.clear();

		tempCard = new AdventureCard(deckNum, name, -1, mission, requirement, resourceNum, astro, fame, vicPts);
		switch (deckNum)
		{
		case 1:							// 3 cards will be in the initial Array
			cAdv[i] = tempCard;
			break;
		case 2:							// 3 cards will be in the initial Array
			tAry2[ctr2] = tempCard;
			ctr2++;
			break;
		case 3:							// 3 cards will be in the initial Array
			tAry3[ctr3] = tempCard;
			ctr3++;
			break;
		case 4:							// 3 cards will be in the initial Array
			tAry4[ctr4] = tempCard;
			ctr4++;
			break;
		default:
			std::cout << "Default Adventure Deck Setup...  should never print\n" << std::endl;
			break;
		}
	}

	//	shuffleDeck(tAry2, ctr2);
	//	shuffleDeck(tAry3, ctr3);
	//	shuffleDeck(tAry4, ctr4);

	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		AD[count] = tAry2[i];
		count++;
	}
	for (int i = 0; i < 3; i++)
	{
		AD[count] = tAry3[i];
		count++;
	}
	for (int i = 0; i < 3; i++)
	{
		AD[count] = tAry4[i];
		count++;
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Setting up the Flight Zone
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Universe::universeSetup(ResourceManager<sf::Texture> &txtMgr)
{
	std::stringstream ss;
	std::string name, buffer, transaction, temp;
	int deckNum, value, pts, resource, limit, type, srcX, srcY;
	int ctr0 = 0, ctr1 = 0, ctr2 = 0, ctr3 = 0, ctr4 = 0;
	Card* list0[40]; Card* list1[7]; Card* list2[7]; Card* list3[7]; Card* list4[7];
	Card* tempCard = 0;
	sf::Vector2u srcPos;

	std::ifstream inputFile(CARDLIST.c_str());
	if (!inputFile)
	{
		std::cout << CARDLIST.c_str() << " failed to open.  Terminating Program\n";
		exit(EXIT_FAILURE);
	}
	getline(inputFile, buffer); // Title Line

	while (getline(inputFile, buffer))
	{
	
		ss << buffer;
/*A*/	getline(ss, temp, ','); 
		deckNum = stoi(temp);
/*B*/	getline(ss, temp, ',');
		type = stoi(temp);
/*C*/	getline(ss, temp, ',');
		resource = stoi(temp);
/*D*/	getline(ss, temp, ',');
		value = stoi(temp);
/*E*/	getline(ss, transaction, ',');
/*F*/	getline(ss, temp, ',');
		limit = stoi(temp);
/*G*/	getline(ss, temp, ',');
		pts = stoi(temp);
/*H*/	getline(ss, name, ',');
/*I*/	getline(ss, temp, ',');
		srcY = stoi(temp);
/*I*/	getline(ss, temp, ',');
		srcX = stoi(temp);
		srcPos = sf::Vector2u(srcX, srcY);
		ss.clear();

		if (type == 0)
			tempCard = new TradeCard(txtMgr.getResource(CARDIMAGES), srcPos, deckNum, name, type, resource, value, transaction, limit, pts);
		else if (type == 1)
			tempCard = new ColonyCard(txtMgr.getResource(CARDIMAGES), srcPos, deckNum, name, type, resource, value, pts);
		else if (type == 2)
			tempCard = new Pirate(txtMgr.getResource(CARDIMAGES), srcPos, deckNum, name, type, resource, value, transaction, pts);
		else
			tempCard = new Card(txtMgr.getResource(CARDIMAGES), srcPos, type, deckNum, name);

		switch (deckNum)
		{
			case 0:							// 40 cards will eventually be in deck 0 (Starter cards)
				list0[ctr0] = tempCard;
				ctr0++;
				break;
			case 1:							// 7 cards will eventually be in deck 1 (Reserve Deck 1 cards)				
				list1[ctr1] = tempCard;
				ctr1++;
				break;
			case 2:							// 7 cards will eventually be in deck 2 (Reserve Deck 2 cards)
				list2[ctr2] = tempCard;
				ctr2++;
				break;
			case 3:							// 7 cards will eventually be in deck 3 (Reserve Deck 3 cards)
				list3[ctr3] = tempCard;
				ctr3++;
				break;
			case 4:							// 7 cards will eventually be in deck 4 (Reserve Deck 4 cards)
				list4[ctr4] = tempCard;
				ctr4++;
				break;
			default:
				std::cout << "Default Universe Setup...  should never print\n" << std::endl;
				break;
		}
	}

	//shuffleDeck(list0, ctr0);				// each of the decks are shuffed individually
	//shuffleDeck(list1, ctr1);
	//shuffleDeck(list2, ctr2);
	//shuffleDeck(list3, ctr3);
	//shuffleDeck(list4, ctr4);
	int count = 0;

	for (int i = 0; i < 10; i++) 	{ 
		S1[i] = list0[count]; 		
		count++; 
	} 	
	for (int i = 0; i < 10; i++) 	{ 
		S2[i] = list0[count];  		
		count++; 
	} 	
	for (int i = 0; i < 10; i++) 	{ 
		S3[i] = list0[count]; 		
		count++; 
	} 	
	for (int i = 0; i < 10; i++) 	{ 
		S4[i] = list0[count]; 		
		count++; 
	}

	count = 0;

	for (int i = 0; i < ctr1; i++, count++)		// the extra stack of cards is created from cards in decks 1 - 4.
		setSector(list1[i], 5, count);

	for (int i = 0; i < ctr2; i++, count++)
		setSector(list2[i], 5, count);

	for (int i = 0; i < ctr3; i++, count++)
		setSector(list3[i], 5, count);

	for (int i = 0; i < ctr4; i++, count++)
		setSector(list4[i], 5, count);

	inputFile.close();
}
