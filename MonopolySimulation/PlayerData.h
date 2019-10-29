#pragma once
#include "Property.h"
#include <string>
/*
 * The player class contains all the information pertaining to a
 * Monopoly Player
 */
class PlayerData
{
	public:
		PlayerData() { position = 0; }
		int GetPosition();

		int * GetUnmorgaged();
		int * GetMorgaged();
		int * GetCash();
		int * GetSpecialCards();
		int GetTimeInJail();
		bool IsInJail();

	
		int SpendCash(int value);
		int ReceiveCash(int value);

		bool IsBankrupt();

		void ReceiveProperty(Property);
		void sendToJail();
		void AddTimeInJail();

		// Turns the player data and turns it into a json object.
		std::string Serialize();

		void Move(int value);

	private:
		int position;
		bool isInJail = false;
		int jailTime = 0;
};

