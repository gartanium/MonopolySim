#pragma once
#include "Property.h"
#include <string>
/*
 * The player class contains all the information pertaining to a
 * Monopoly Player it is just a container for the data
 */
class PlayerData
{
	public:
		PlayerData() { position = 0; }
		int GetPosition();
		void SetPosition(int value) { position = value; };

		int * GetUnmorgaged();
		int * GetMorgaged();
		
		int * GetSpecialCards();
	


		
		//VVVV evert function regarding funds
		int GetCash() { return cash; };
		int GetAssets() { return assets; };

		void SpendCash(int value) { cash -= value; };
		void ReceiveCash(int value) { cash += value; };

		// these two are related to buying property and houses
		// the assets gained would be the price of mortgaging or selling houses
		// the assets spent are what they player spent to buy a property or house
		void updateAssets(int value) { assets = (cash + value); };
		


		bool IsBankrupt();
		//^^^^^^ every function regarding funds


		//vvv every function regarding jail

		//Returns how long the player has been in jail so the server knows when they need to pay to get out
		int getJailTime() { return jailTime; };
		bool IsInJail() { return isInJail; };

		void setJailTime(int value) { jailTime = value; };
		void setInJailStatus(bool isInJail);

		//^^^ every function regarding jail


		// Turns the player data and turns it into a json object.
		std::string Serialize();

		

	private:
		int position = 0;
		int cash = 200;
		int assets = 0;
		bool isInJail = false;
		int jailTime = 0;
};

