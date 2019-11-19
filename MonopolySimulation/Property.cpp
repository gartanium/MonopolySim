#include "Property.h"

Property::Property(int morgagePrice, int housePriceArray[6], std::string title, int purchasePrice)
{
	this->morgagePrice = morgagePrice;
	this->inMonopoly = false;
	this->houseCount = 0;

	for (int i = 1; i < 6; i++) 
	{
		this->houseRents[i - 1] = housePriceArray[i - 1];
	}
	this->title = title;
	this->cost = purchasePrice;
	this->position = 6;

}

Property::Property(std::string data[12])
{
	this->title = data[0];
	this->color = data[1];
	this->position = std::stoi(data[2]);
	this->cost = std::stoi(data[3]);
	this->morgagePrice = std::stoi(data[4]);
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

void Property::BuildHouse()
{
	if (inMonopoly)
	{
		if (houseCount < 5)
		{
			houseCount++;
		}
		else
			throw "ERROR: There are to many houses!";
	}
	else
		throw "ERROR: Property not in a monopoly!";
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
