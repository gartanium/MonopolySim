#include "Property.h"

Property::Property(int morgagePrice, int housePriceArray[6], std::string title)
{
	this->morgagePrice = morgagePrice;
	this->rentNoHouses = housePriceArray[0];
	this->inMonopoly = false;
	this->houseCount = 0;

	for (int i = 1; i < 6; i++) 
	{
		this->houseRents[i - 1] = housePriceArray[i];
	}
	this->title = title;
}

int Property::GetCurrentRent()
{
	if (!inMonopoly)
		return rentNoHouses;
	else if (inMonopoly && houseCount == 0)
	{
		return rentNoHouses * 2;
	}
	else
		return houseRents[houseCount - 1];
}

void Property::BuildHouse()
{
	if (houseCount < 5)
	{
		houseCount++;
	}
	else
		throw "ERROR: There are to many houses!";
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
