#pragma once
#include <string>
#include "Tile.h"
class Property : public Tile
{
	public:
		Property(int morgagePrice,  int housePriceArray[6], std::string title, int purchasePrice, int position);
		Property(std::string data[12]);
		int GetHouseCount() { return houseCount; }
		int GetHousePrice() { return housePrice; }
		int GetMorgagePrice() { return morgagePrice; }
		int GetCurrentRent();
		int GetCost() { return cost; };
		int GetPosition() { return position; };
		int getOwnerNumber() { return playerOwnerNumber; };

		std::string GetColor() { return color; }
		std::string GetTitle() { return title; }


		void setOwner(int owner) { this->playerOwnerNumber = owner; };
		void SetMonopolyStatus(bool value) { inMonopoly = value; }
		void BuildHouse();
		void SellHouse();
		void setMortgaged(bool value) { mortgaged = value; };
		

		bool HasHotel() { return houseCount == 5; }
		bool CanBuild();
		bool Mortgaged() { return mortgaged; };


		


	private:
		int houseCount;
		int housePrice;
		int morgagePrice;
		int houseRents[6];
		std::string color;
		std::string title;
		bool inMonopoly;
		int cost;
		bool mortgaged = false;
		bool isOwned = false;
		int position;
		

		int playerOwnerNumber = -1;
};

