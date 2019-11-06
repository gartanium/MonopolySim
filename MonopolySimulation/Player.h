

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
		
		void ReceiveProperty(Property);
		void sendToJail();
		void AddTimeInJail(bool doubles);
		void Move(int value, bool doubles);
		void PayBail(int bail);
		int GetPosition() { return playerData.GetPosition(); };
		int GetTimeInJail() { return playerData.getJailTime(); };


	private:
		PlayerData playerData;
		

};


