//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#ifndef MODULE_H
#define MODULE_H

class Module : Object
{
private:
	std::string type;
	int qty;
	int maxQty;

public:
	Module(std::string type = " ", int qty = 0, int maxQty = 2){
		this->type = type;
		this->qty = qty;
		this->maxQty = maxQty;
	}
	Module operator = (Module &right){
		type = right.type;
		qty = right.qty;
		maxQty = right.maxQty;
	}	
	~Module() {}
	// Getters and Setters
	std::string getType() const
	{  return type;  }
	int getQty() const
	{  return qty;  }
	int getMaxQty() const
	{  return maxQty;  }
	void setQty(int qty)
	{  this->qty = qty;  }
	void setMaxQty(int maxQty)
	{  this->maxQty = maxQty;  }
};

#endif // MODULE_H