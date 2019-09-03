

#pragma once
/*
 * The Player class contains all the information pertaining to a
 * Monopoly Player. It also contains functionality for manipulating
 * the Player.
 */
class PlayerData
{
	public:
		int * GetPosition();
		int * GetUnmorgaged();
		int * GetMorgaged();
		int * GetCash();
		int * GetSpecialCards();
		int * GetTimeInJail();
	
		int SpendCash(int value);
		int ReceiveCash(int value);

		bool IsBankrupt();

		void ReceiveProperty();


	private:
		int position[2];
		Property
		

};

