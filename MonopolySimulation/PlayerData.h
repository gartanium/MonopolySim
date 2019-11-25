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
		void formatPosition() { position = position % 40; };

		int * GetUnmorgaged();
		int * GetMorgaged();
		
		int * GetSpecialCards();
	


		
		//VVVV evert function regarding funds
		int GetCash() { return cash; };
		int GetAssets() { return assets; };

		void SpendCash(int value) { cash -= value; updateAssets(); };
		void ReceiveCash(int value) { cash += value; updateAssets(); };

		
		void updateLiquidAssets(int value) { liquidAssets += value; updateAssets(); };
		int getLiquidAssets() { return liquidAssets; };


		//needs to be called everytime money is spent, gained or property
		//is bought or mortgaged as well as houses bought or sold
		void updateAssets() { assets = (cash + liquidAssets); };
		


		bool IsBankrupt();
		//^^^^^^ every function regarding funds


		//vvv every function regarding jail

		//Returns how long the player has been in jail so the server knows when they need to pay to get out
		int getJailTime() { return jailTime; };
		bool IsInJail() { return isInJail; };

		void setJailTime(int value) { jailTime = value; };
		void setInJailStatus(bool isInJail);

		void setGOOJF(bool value) { GOOJF = value; };
		bool getGOOJF() { return GOOJF; };

		//^^^ every function regarding jail


		// Turns the player data and turns it into a json object.
		std::string Serialize();

		

	private:
		int position = 0;
		int cash = 200;
		int liquidAssets = 0;
		int assets = 200;
		bool isInJail = false;
		int jailTime = 0;
		bool GOOJF = false;
		
};

