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
		cAdv[i]->displayCard(gWindow);
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
	case 1:
		S1[cNum] = nCard;
		break;
	case 2:
		S2[cNum] = nCard;
		break;
	case 3:
		S3[cNum] = nCard;
		break;
	case 4:
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
	case 1:
		return S1;
	case 2:
		return S2;
	case 3:
		return S3;
	case 4:
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
void Universe::universeSetup()
{
	std::stringstream ss;
	std::string name, buffer, transaction, temp;
	int deckNum, value, pts, resource, limit, type;
	int ctr0 = 0, ctr1 = 0, ctr2 = 0, ctr3 = 0, ctr4 = 0;
	Card* list0[40]; Card* list1[7]; Card* list2[7]; Card* list3[7]; Card* list4[7];
	Card* tempCard = 0;

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
		ss.clear();

		if (type == 0)
			tempCard = new TradeCard(deckNum, name, type, resource, value, transaction, limit, pts);
		else if (type == 1)
			tempCard = new ColonyCard(deckNum, name, type, resource, value, pts);
		else if (type == 2)
			tempCard = new Pirate(deckNum, name, type, resource, value, transaction, pts);
		else
			tempCard = new Card(deckNum, name, type);

		switch (deckNum)
		{
			case 0:							// 40 cards will eventually be in deck 0 (Starter cards)
				list0[ctr0] = tempCard;
				ctr0++;
				break;
			case 1:							// 7 cards will eventually be in deck 0 (Starter cards)
				list1[ctr1] = tempCard;
				ctr1++;
				break;
			case 2:							// 7 cards will eventually be in deck 0 (Starter cards)
				list2[ctr2] = tempCard;
				ctr2++;
				break;
			case 3:							// 7 cards will eventually be in deck 0 (Starter cards)
				list3[ctr3] = tempCard;
				ctr3++;
				break;
			case 4:							// 7 cards will eventually be in deck 0 (Starter cards)
				list4[ctr4] = tempCard;
				ctr4++;
				break;
		}
	}

//	shuffleDeck(list0, ctr0);				// each of the decks are shuffed individually
//	shuffleDeck(list1, ctr1);
//	shuffleDeck(list2, ctr2);
//	shuffleDeck(list3, ctr3);
//	shuffleDeck(list4, ctr4);
	int count = 0;

	for (int j = 0; j < 10; j++)			// Sectors 1-4 are populated into 4 stacks of 10 cards from deck 0 
	{ 
		setSector(list0[count], 1, j);
		count++;
		setSector(list0[count], 2, j);
		count++;
		setSector(list0[count], 3, j);
		count++;
		setSector(list0[count], 4, j);
		count++;
	}

	count = 0;

	for (int i = 0; i < ctr1; i++, count++)	// the extra stack of cards is created from cards in decks 1 - 4.
		setSector(list1[i], 5, count);

	for (int i = 0; i < ctr2; i++, count++)
		setSector(list2[i], 5, count);

	for (int i = 0; i < ctr3; i++, count++)
		setSector(list3[i], 5, count);

	for (int i = 0; i < ctr4; i++, count++)
		setSector(list4[i], 5, count);

	inputFile.close();
}
