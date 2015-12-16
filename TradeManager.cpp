#include "TradeManager.h"

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Constructor
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
TradeManager::TradeManager(ResourceManager<sf::Texture> &txtMgr, ResourceManager<sf::Font> &fntMgr)
	: resourceMenu(fntMgr), tradeMenu(fntMgr)
{
	active = false;
	choosingRes = false;
	resChosen = false;
	cTradeNum = 0;
	limit = 0;
	createResourceMenu(txtMgr);
	createTradeMenu(txtMgr);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Toggles the Active and Both Menus
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void TradeManager::setActive(bool toggle)
{
	cTradeNum = 0;
	active = toggle;
	productionGain = false;
	resourceMenu.setActive(toggle);
	tradeMenu.setActive(toggle);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Toggles the Active and Both Menus
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void TradeManager::setAvailableResources(int resAvail[])
{
	productionGain = true;
	for (int i = 0; i < NUMRESOURCES; i++)
		this->resAvail[i] = resAvail[i];
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  saves the current resource and astro values	
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void TradeManager::saveResources(Player *cPlyr)
{
	for (int i = 0; i < 6; i++)
	{
		resourceMenu.setItemQty(i, cPlyr->getStatQty(i));
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  restores the current resource and astro values  
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void TradeManager::restoreResources(Player *cPlyr)
{
	for (int i = 0; i < 6; i++)
	{
		cPlyr->getStarship()->setShipObjectQty(i, (resourceMenu.getItemQty(i)));
		cPlyr->updateIcon(i);
	}
	cPlyr->getStarship()->updateShipIcons();
	cPlyr->setAstro(resourceMenu.getItemQty(astro));
	cPlyr->updateIcon(astro);
	cTradeNum = 0;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Greys out all resources and unGreys the current Resource
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void TradeManager::greyAllButChosesnResources()
{
	for (int i = 0; i < resourceMenu.size(); i++)
	{
		resourceMenu.greyItem(i);
	}
	resourceMenu.unGreyItem(cResource);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Greys out any only resources that are maxed 
//  If productionGain has been toggled... will also filter by 
//  resAvail array.
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void TradeManager::greyUnavailResources(Player *cPlyr)
{
	for (int i = 0; i < resourceMenu.size(); i++)				
	{
		resourceMenu.unGreyItem(i);
		if (cPlyr->getStarship()->holdFull(i) || (productionGain && resAvail[i] == 0))
			resourceMenu.greyItem(i);
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Adjust the four trade icons based on inventory levels
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void TradeManager::updateTradeIcons(Player *cPlyr)
{
	//  If player has option to chose resource but hasn't yet done so
	if (choosingResource() && !resourceChosen())
	{
		tradeMenu.hideAll();
	}
	else
	{
		tradeMenu.unhideAll();
		if (cost)
		{
			if (resourceMenu.getItemQty(astro) == cPlyr->getStatQty(astro))
				tradeMenu.greyItem(check);
			else
				tradeMenu.unGreyItem(check);
		}
		else
		{
			if (cTradeNum)
				tradeMenu.unGreyItem(check);
			else
				tradeMenu.greyItem(check);
		}

		if (limit && cTradeNum == limit)
		{
			tradeMenu.greyItem(plus);
			tradeMenu.greyItem(minus);
		}
		else
		{
			cPlyr->getStarship()->holdFull(cResource) ? tradeMenu.greyItem(plus) : tradeMenu.unGreyItem(plus);
			cPlyr->getStarship()->holdEmpty(cResource) ? tradeMenu.greyItem(minus) : tradeMenu.unGreyItem(minus);
		}

		if (transaction == "Buy")				//  Can only buy at this trade post
			tradeMenu.greyItem(minus);
		else if (transaction == "Sell")			//  Can only sell at this trade post
			tradeMenu.greyItem(plus);
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Returns true if Resource Icon is Click
//  Returns position through reference parameter  
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool TradeManager::resourceTargeted(sf::RenderWindow &gWindow, int &pos)
{
	if (resourceMenu.isMenuTargeted(gWindow, pos))
		return true;
	return false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Returns true if any Trade or Resource Icons are clicked
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
bool TradeManager::iconsTargeted(sf::RenderWindow &gWindow)			////////////////////////////////////   REFACTOR
{
	int thisISTEMP = 0;
	if (active && !paused)
	{
		if (tradeMenu.isMenuTargeted(gWindow, thisISTEMP))
			return true;
		if (resourceMenu.isMenuTargeted(gWindow, thisISTEMP))
			return true;
	}
	return false;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void TradeManager::pauseTrade()			
{
	if (active)
	{
		paused = true;
		tradeMenu.hideAll();
		resourceMenu.hideAll();
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void TradeManager::unpauseTrade()
{
	if (active)
	{
		paused = false;
		tradeMenu.unhideAll();
		resourceMenu.unhideAll();
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
// draws the resourceMenu if a trade is in progress  
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void TradeManager::draw(sf::RenderWindow &gWindow)
{
	if (active && !paused)
	{
		resourceMenu.draw(gWindow);
		tradeMenu.draw(gWindow);
	}
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Creates the Resource Managment/Save State Menu
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void TradeManager::createResourceMenu(ResourceManager<sf::Texture> &txtMgr)
{
	Object* tempObject;

	tempObject = new Object(txtMgr.getResource(RICNFLE), { 780, 565 }, 1, { 35, 35 });				//  Science
	resourceMenu.push_back(tempObject);
	tempObject = new Object(txtMgr.getResource(RICNFLE), { 780, 600 }, 1, { 35, 35 }, { 1, 0 });		//  Ore
	resourceMenu.push_back(tempObject);
	tempObject = new Object(txtMgr.getResource(RICNFLE), { 780, 635 }, 1, { 35, 35 }, { 2, 0 });		//  Fuel
	resourceMenu.push_back(tempObject);
	tempObject = new Object(txtMgr.getResource(RICNFLE), { 780, 670 }, 1, { 35, 35 }, { 3, 0 });		//  TradeGood
	resourceMenu.push_back(tempObject);
	tempObject = new Object(txtMgr.getResource(RICNFLE), { 780, 705 }, 1, { 35, 35 }, { 4, 0 });		//  Wheat
	resourceMenu.push_back(tempObject);
	tempObject = new Object(txtMgr.getResource(RICNFLE), { 780, 740 }, 1, { 35, 35 }, { 5, 0 });		//  Carbon	
	resourceMenu.push_back(tempObject);
	tempObject = new Object(txtMgr.getResource(SYM1FLE), { 780, 562 }, 25, { 35, 35 }, { 3, 0 });		//  Astro
	tempObject->hide();
	resourceMenu.push_back(tempObject);
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
//  Creates the Trade Menu
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯) 
void TradeManager::createTradeMenu(ResourceManager<sf::Texture> &txtMgr)
{
	tradeMenu.push_back(new Object(txtMgr.getResource(TRDICN), { 675, 575 }, 1, { 50, 50 }, { 0, 0 }));
	tradeMenu.push_back(new Object(txtMgr.getResource(TRDICN), { 675, 675 }, 1, { 50, 50 }, { 1, 0 }));
	tradeMenu.push_back(new Object(txtMgr.getResource(TRDICN), { 635, 760 }, 1, { 50, 50 }, { 2, 0 }));
	tradeMenu.push_back(new Object(txtMgr.getResource(TRDICN), { 710, 760 }, 1, { 50, 50 }, { 3, 0 }));
}