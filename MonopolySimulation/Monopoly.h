#pragma once
class Monopoly
{
	public:
		void AddHouse();
		// Returns the money gained for selling a house.
		int SellHouse();

	private:
		int HousePrice;
};

