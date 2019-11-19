

#pragma once
#include "PlayerData.h"
/*
 * The Player class contains all the information pertaining to a
 * Monopoly Player. It also contains functionality for manipulating
 * the Player.
 */
class Player
{
	public:
		
		void ReceiveProperty(Property &property, int playerTurnIndex);

		void sendToJail();
		void AddTimeInJail(bool doubles);
		void Move(int value, bool doubles);
		void PayBail(int bail);
		void payRent(Property property);
		void receiveRent(Property property);
		int GetPosition() { return playerData.GetPosition(); };
		int GetTimeInJail() { return playerData.getJailTime(); };
		int getCash() { return playerData.GetCash(); };

	private:
		PlayerData playerData;
		

};


