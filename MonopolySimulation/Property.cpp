#include "Property.h"

Property::Property(int mortgagePrice, int housePriceArray[6], std::string title, int purchasePrice, int position)
{
	this->mortgagePrice = mortgagePrice;
	this->inMonopoly = false;
	this->houseCount = 0;

	for (int i = 0; i < 6; i++) 
	{
		this->houseRents[i] = housePriceArray[i];
	}
	this->title = title;
	this->cost = purchasePrice;
	this->position = position;

}

Property::Property(std::string data[12])
{
	this->title = data[0];
	this->color = data[1];
	this->position = std::stoi(data[2]);
	this->cost = std::stoi(data[3]);
	this->mortgagePrice = std::stoi(data[4]);
	this->housePrice = std::stoi(data[5]);
	for (int i = 0; i < 6; i++)
	{
		this->houseRents[i] = std::stoi(data[6 + i]);
	}
	this->houseCount = 0;
	this->inMonopoly = false;
}

int Property::GetCurrentRent()
{
	if (!inMonopoly)
		return houseRents[0];
	else if (inMonopoly && houseCount == 0)
	{
		return houseRents[0] * 2;
	}
	else
		return houseRents[houseCount];
}

int Property::GetAssetValue()
{
	if (mortgaged)
	{
		return 0;
	}
	else
	{
		return (mortgagePrice + (houseCount * housePrice));
	}
	
}

void Property::BuildHouse()
{
	if (CanBuild())
	{	
			houseCount++;
	}
	else
	{
		throw "unable to build a house";
	}
}

void Property::SellHouse()
{
	if (houseCount > 0)
	{
		houseCount--;
	}
	else
		throw "ERROR: There are no houses to sell!";
}

bool Property::CanBuild()
{
	if (inMonopoly && houseCount != 5)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}
