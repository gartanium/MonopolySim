#pragma once
#include <string>
#include "Tile.h"
class Property : public Tile
{
	public:
		Property(int morgagePrice,  int housePriceArray[6], std::string title);
		int GetHouseCount() { return houseCount; }
		int GetHousePrice() { return housePrice; }
		int GetMorgagePrice() { return morgagePrice; }
		std::string GetColor() { return color; }
		int GetCurrentRent();

		void SetMonopolyStatus(bool value) { inMonopoly = value; }
		void BuildHouse();
		void SellHouse();
		bool HasHotel() { return houseCount == 5; }


	private:
		int houseCount;
		int housePrice;
		int morgagePrice;
		int houseRents[5];
		int rentNoHouses;
		std::string color;
		std::string title;
		bool inMonopoly;
};

