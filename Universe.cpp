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
	board = new Object(txtMgr.getResource(BOARDFILE), sf::Vector2f(0, 0));
	board->setScale({ 3.1f, 3.6f });

	flightSector = new Icon*[4];

	flightSector[0] = new Icon(txtMgr.getResource(UNIVERSECARDIMAGES), sf::Vector2f(100, 150), 10, sf::Vector2u(200, 300), { 4, 13 });
	flightSector[0]->initString(fntMgr.getResource(FNTFLE), { 175, 200 }, "1", sf::Text::Bold);
	flightSector[0]->setTextScale({ 5, 5 });

	flightSector[1] = new Icon(txtMgr.getResource(UNIVERSECARDIMAGES), sf::Vector2f(300, 150), 10, sf::Vector2u(200, 300), { 4, 13 });
	flightSector[1]->initString(fntMgr.getResource(FNTFLE), { 360, 200 }, "2", sf::Text::Bold);
	flightSector[1]->setTextScale({ 5, 5 });

	flightSector[2] = new Icon(txtMgr.getResource(UNIVERSECARDIMAGES), sf::Vector2f(500, 150), 10, sf::Vector2u(200, 300), { 4, 13 });
	flightSector[2]->initString(fntMgr.getResource(FNTFLE), { 560, 200 }, "3", sf::Text::Bold);
	flightSector[2]->setTextScale({ 5, 5 });

	flightSector[3] = new Icon(txtMgr.getResource(UNIVERSECARDIMAGES), sf::Vector2f(700, 150), 10, sf::Vector2u(200, 300), { 4, 13 });
	flightSector[3]->initString(fntMgr.getResource(FNTFLE), { 760, 200 }, "4", sf::Text::Bold);
	flightSector[3]->setTextScale({ 5, 5 });

	S1 = new Card*[10];
	S2 = new Card*[10];
	S3 = new Card*[10];
	S4 = new Card*[10];
	SE = new Card*[28];
	AD = new AdventureCard*[9];
	cAdv = new AdventureCard*[3];
	universeSetup(txtMgr);
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

	for (int i = 0; i < 4; i++)
		delete flightSector[i];
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
	delete [] flightSector;
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
		flightSector[i]->draw(gWindow);
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
		if (flightSector[i]->isTargeted(gWindow))
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
	currentMove = 1;											
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
	AD[advPtr]->setPosition(cAdv[i]->getPosition());
	cAdv[i] = AD[advPtr];
	AD[advPtr++] = NULL;
	//////////////////////////////////   NEED TO CHECK FOR END OF THE DECK
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Prints the current adventures available
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Universe::drawCurrentAdventures(sf::RenderWindow &gWindow)
{
	for (int i = 0; i < 3; i++)
		cAdv[i]->draw(gWindow);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Prints the current adventures available
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
AdventureCard* Universe::getAdvCard(int i)
{
	return cAdv[i];
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Makes the three current adventures available to be chosen
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Universe::makeAdventuresAvailable()
{
	for (int i = 0; i < 3; i++)
		cAdv[i]->setAvailable(true);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
// Returns true if current planet is in the current adventure stack
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Universe::atAdventurePlanet()
{
	for (int i = 0; i < 3; i++)
		if (getCurrentPlanet()->getName() == cAdv[i]->getName())
			return true;
	return false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
// Returns true if current planet is in the current adventure planet
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Universe::atCurrentAdventurePlanet(int num)
{
	return getCurrentPlanet()->getName() == cAdv[num]->getName();
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//
//  Listener to see if one of the current adventures are targeted
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool Universe::isCurrentAdventureTargeted(sf::RenderWindow &gWindow, int &temp)
{
	for (int i = 0; i < 3; i++)
	{			
		if (cAdv[i]->isTargeted(gWindow))
		{
			temp = i;
			return true;
		}
	}
	return false;
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
//  Replaces the current planet with the top of the Extra Deck 
//
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void Universe::replaceCurrentPlanet()
{
	if (SE[ExtraDeckPtr])
	{
		getSector(sectorNum)[currentMove - 1] = SE[ExtraDeckPtr]; 
		SE[ExtraDeckPtr++] = NULL;
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
	std::string name, buffer, transaction, temp, mission;
	int deckNum, value, pts, resource, limit, type, srcX, srcY, astro, fame, resourceNum, vicPts, req1Qty, req1Type, req2Qty, req2Type;
	int ctr0 = 0, ctr1 = 0, ctr2 = 0, ctr3 = 0, ctr4 = 0;
	Card* list0[40]; Card* list1[7]; Card* list2[7]; Card* list3[7]; Card* list4[7];
	Card* tempCard = 0;
	AdventureCard* advTempCard = 0;
	sf::Vector2u srcPos;
	AdventureCard* tAry2[3]; AdventureCard* tAry3[3]; AdventureCard* tAry4[3];

	std::ifstream inputFile(CARDLIST.c_str());
	if (!inputFile)
	{
		std::cout << CARDLIST.c_str() << " failed to open.  Terminating Program\n";
		exit(EXIT_FAILURE);
	}
	getline(inputFile, buffer); // Title Line

	//  UNIVERSE CARD SETUP

	for (int i = 0; i < 68; i++)
	{
		getline(inputFile, buffer);
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
/*J*/	getline(ss, temp, ',');
		srcX = stoi(temp);
/*K*/	getline(ss, temp, ',');
/*L*/	getline(ss, temp, ',');
/*M*/	getline(ss, temp, ',');
		srcPos = sf::Vector2u(srcX, srcY);

		ss.clear();

		if (type == 0)
			tempCard = new TradeCard(txtMgr.getResource(UNIVERSECARDIMAGES), srcPos, deckNum, name, type, resource, value, transaction, limit, pts);
		else if (type == 1)
			tempCard = new ColonyCard(txtMgr.getResource(UNIVERSECARDIMAGES), srcPos, deckNum, name, type, resource, value, pts);
		else if (type == 2)
			tempCard = new Pirate(txtMgr.getResource(UNIVERSECARDIMAGES), srcPos, deckNum, name, type, resource, value, transaction, pts);
		else
			tempCard = new Card(txtMgr.getResource(UNIVERSECARDIMAGES), srcPos, type, deckNum, name);

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

	ss.clear();
	
	//  ADVENTURE CARD SETUP

	getline(inputFile, buffer); // Title Line

	ctr0 = 0, ctr1 = 0, ctr2 = 0, ctr3 = 0, ctr4 = 0;

	for (int i = 0; i < 12; i++)
	{
		getline(inputFile, buffer);
		ss << buffer;
		/*A*/	getline(ss, temp, ',');
		deckNum = stoi(temp);
		/*B*/	getline(ss, name, ',');
		/*C*/	getline(ss, mission, ',');
		/*D*/	getline(ss, temp, ',');
		req1Qty = stoi(temp);
		/*E*/	getline(ss, temp, ',');
		req1Type = stoi(temp);
		/*F*/	getline(ss, temp, ',');
		req2Qty = stoi(temp);
		/*G*/	getline(ss, temp, ',');
		req2Type = stoi(temp);
		/*H*/	getline(ss, temp, ',');
		resourceNum = stoi(temp);
		/*I*/	getline(ss, temp, ',');
		astro = stoi(temp);
		/*J*/	getline(ss, temp, ',');
		fame = stoi(temp);
		/*K*/	getline(ss, temp, ',');
		vicPts = stoi(temp);
		/*L*/	getline(ss, temp, ',');
		srcY = stoi(temp);
		/*M*/	getline(ss, temp, ',');
		srcX = stoi(temp);
		srcPos = sf::Vector2u(srcX, srcY);
		ss.clear();

		advTempCard = new AdventureCard(txtMgr.getResource(UNIVERSECARDIMAGES), srcPos, deckNum, name, -1, mission, req1Qty, req1Type, req2Qty, req2Type, resourceNum, astro, fame, vicPts);
		advTempCard->setScale(CRDZNSCL);
		switch (deckNum)
		{
		case 1:							// 3 cards will be in the initial Array
			cAdv[ctr1] = advTempCard;
			ctr1++;
			break;
		case 2:							// 3 cards will be in the initial Array
			tAry2[ctr2] = advTempCard;
			ctr2++;
			break;
		case 3:							// 3 cards will be in the initial Array
			tAry3[ctr3] = advTempCard;
			ctr3++;
			break;
		case 4:							// 3 cards will be in the initial Array
			tAry4[ctr4] = advTempCard;
			ctr4++;
			break;
		default:
			std::cout << "Default Adventure Deck Setup...  should never print\n" << std::endl;
			break;
		}
	}

		//shuffleDeck(tAry2, ctr2);
		//shuffleDeck(tAry3, ctr3);
		//shuffleDeck(tAry4, ctr4);

	 count = 0;
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

	cAdv[0]->setPosition({ 1050, 200 });
	cAdv[1]->setPosition({ 1050, 420 });
	cAdv[2]->setPosition({ 1050, 640 });

	inputFile.close();
}
