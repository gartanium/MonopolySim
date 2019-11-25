#include "pch.h"
#include "../MonopolySimulation/DiceHandler.h"
#include "../MonopolySimulation/PlayerData.h"
#include "../MonopolySimulation/Player.h"
#include "../MonopolySimulation/Property.h"
#include "test.h"
#include "..//MonopolySimulation/Game.h"
#include "../MonopolySimulation/GameData.h"

TEST(GAMETESTS, TestRollDie) {
	DiceHandler testObj(3);
	int result = testObj.RollDice();

	//EXPECT_EQ(, result);
	bool valid = result <= 12 && result >= 1;
	EXPECT_TRUE(valid);
}


//Ryan: I'm not too sure how this works or what it really is doing?
//		-how does this check for doubles?
TEST(GAMETESTS, TestDoubles) {
	DiceHandler testObj(3);
	int result;
	result = testObj.RollDice();
	ASSERT_FALSE(testObj.GetIsDouble());
	result = testObj.RollDice();
	ASSERT_FALSE(testObj.GetIsDouble());
	result = testObj.RollDice();
	ASSERT_FALSE(testObj.GetIsDouble());
	result = testObj.RollDice();
	ASSERT_FALSE(testObj.GetIsDouble());
	result = testObj.RollDice();
	ASSERT_FALSE(testObj.GetIsDouble());
	result = testObj.RollDice();
	ASSERT_TRUE(testObj.GetIsDouble());

}

TEST(GAMETESTS, TestPayingRent) {
	Game testGame(2);
	Player testPlayer;
	testGame.players.push_back(testPlayer);
	testGame.players.push_back(testPlayer);

	int priceArray[6] = {
		6, 30, 90, 270, 400, 550
	};
	Property testObject(50, priceArray, "Oriental Ave", 200, 9);
	testGame.Deeds.push_back(testObject);
	testGame.Deeds[0].setOwner(1);
	ASSERT_EQ(200, testGame.players[0].getCash());
	ASSERT_EQ(200, testGame.players[1].getCash());
	testGame.players[0].Move(testObject.GetPosition(), false);
	testGame.HandleMovementResult(1);
	ASSERT_EQ(206, testGame.players[1].getCash());
	ASSERT_EQ(194, testGame.players[0].getCash());
	

}


//focuses on starting game cash
TEST(GAMETESTS, TestPayingTaxes) {
	Game testGame(1);
	testGame.players[0].Move(4, false);
	testGame.HandleMovementResult(1);
	ASSERT_EQ(180, testGame.players[0].getAssets());
}

TEST(GAMETESTS, TestExecutePlayer) {
	int propertyCount = 0;
	Game testGame(2);
	int priceArray[6] = {
		6, 30, 90, 270, 400, 550
	};
	Property testObjectOriental(50, priceArray, "Oriental Ave", 200, 8);
	testGame.Deeds.push_back(testObjectOriental);
	testGame.Deeds[0].setOwner(0);

	Property testObjectBaltic(50, priceArray, "Baltic Ave", 200, 20);
	testObjectBaltic.SetMonopolyStatus(true);

	//builds five houses to put a hotel on it
	testObjectBaltic.BuildHouse(); testObjectBaltic.BuildHouse();
	testObjectBaltic.BuildHouse(); testObjectBaltic.BuildHouse(); 
	testObjectBaltic.BuildHouse();
	
	testGame.Deeds.push_back(testObjectBaltic);
	testGame.Deeds[1].setOwner(1);
	ASSERT_EQ(550, testObjectBaltic.GetCurrentRent());
	
	testGame.players[0].Move(20, false);
	//testGame.HandleMovementResult(1);
	testGame.executePlayer(1);

 	for (std::vector<Property>::iterator it = testGame.Deeds.begin(); it != testGame.Deeds.end(); ++it)
	{
		if (it->getOwnerNumber() == 1)
		{
			propertyCount++;
		}
	}
	
	ASSERT_EQ(2, propertyCount);


}

// Player Tests

TEST(PLAYERDATATESTS, TestMovePlayer) {
	Player testObject;
	int actual[4];
	int expected[4] = { 12, 24, 36, 0 };

	testObject.Move(12, 0);
	actual[0] = testObject.GetPosition();

	testObject.Move(12, 0);
	actual[1] = testObject.GetPosition();

	testObject.Move(12, 0);
	actual[2] = testObject.GetPosition();

	testObject.Move(4 ,0);
	actual[3] = testObject.GetPosition();
	
	for (int i = 0; i < 4; i++) {
		ASSERT_EQ(expected[i], actual[i]);
	}
}

TEST(PLAYERDATATESTS, Test3TurnsInJail) {
	Player testObject;
	testObject.Move(10, 0);
	int actual = testObject.GetPosition();
	int expected = 10;
	
	ASSERT_EQ(expected, actual);

	testObject.sendToJail();
	
	testObject.Move(3, 0);
	ASSERT_EQ(expected, actual);
	ASSERT_EQ(1, testObject.GetTimeInJail());

	testObject.Move(3, 0);
	ASSERT_EQ(expected, actual);
	ASSERT_EQ(2, testObject.GetTimeInJail());
	
	testObject.Move(3, 0);
	expected = 13;
	actual = testObject.GetPosition();
	ASSERT_EQ(expected, actual);
	ASSERT_EQ(0, testObject.GetTimeInJail());


}

TEST(PLAYERDATATESTS, PayTaxes) {
	Player testObject;
	ASSERT_EQ(testObject.getCash(), testObject.getAssets());
	testObject.payTaxes(200);
	ASSERT_EQ(0, testObject.getCash());
	ASSERT_EQ(0, testObject.getAssets());
}

// Property Tests
TEST(PROPERTYTESTS, TestGetCurrentRent) {
	int actual[7];
	
	int priceArray[6] = {
		6, 30, 90, 270, 400, 550
	};
	Property testObject(50, priceArray, "Oriental Ave", 200, 9);
	ASSERT_EQ(priceArray[0], testObject.GetCurrentRent());
	testObject.SetMonopolyStatus(true);
	ASSERT_EQ(priceArray[0] * 2, testObject.GetCurrentRent());
}

TEST(PROPERTYTESTS, TestHasHotel) {
	int priceArray[6] = {
		6, 30, 90, 270, 400, 550
	};
	Property testObject(50, priceArray, "Oriental Ave", 200, 9);
	testObject.SetMonopolyStatus(true);
	
	for (int i = 0; i < 5; i++)
	{
		ASSERT_FALSE(testObject.HasHotel());
		testObject.BuildHouse();
	}
	ASSERT_TRUE(testObject.HasHotel());
}

TEST(PROPERTYTESTS, TestOnlyFiveHouses)
{
	int priceArray[6] = {
		6, 30, 90, 270, 400, 550
	};
	Property testObject(50, priceArray, "Oriental Ave", 200, 9);
	testObject.SetMonopolyStatus(true);

	try {
		for (int i = 0; i < 5; i++)
		{
			testObject.BuildHouse();
		}

		testObject.BuildHouse();
		FAIL() << "Expected To Many Houses Error.";
	}
	catch (const char* msg) {
		std::string result(msg);
		EXPECT_EQ(result, "unable to build a house");
	}
	catch (...) {
		FAIL() << "Expected To Many Houses Error.";
	}
}

TEST(PROPERTYTESTS, TestNoHousesToSell)
{
	int priceArray[6] = {
		6, 30, 90, 270, 400, 550
	};
	Property testObject(50, priceArray, "Oriental Ave", 200, 9);

	try {
		testObject.SellHouse();
		FAIL() << "Expected No Houses To Sell Error.";
	}
	catch (const char* msg) {
		std::string result(msg);
		EXPECT_EQ(result, "ERROR: There are no houses to sell!");
	}
	catch (...) {
		FAIL() << "Expected No Houses To Sell Error.";
	}
}

//TEST(PROPERTYTESTS, TestBuildIfInMonopoly)
//{
//	int priceArray[6] = {
//		6, 30, 90, 270, 400, 550
//	};
//	Property testObject(50, priceArray, "Oriental Ave", 200, 9);
//
//	try {
//		testObject.BuildHouse();
//		FAIL() << "Expected Must Be In Monopoly Error.";
//	}
//	catch (const char* msg) {
//		std::string result(msg);
//		EXPECT_EQ(result, "ERROR: Property not in a monopoly!");
//	}
//	catch (...) {
//		FAIL() << "Expected Must Be In Monopoly Error.";
//	}
//}

// Game tests

// GameData tests
TEST(GAMEDATATESTS, TestPlayerPositions)
{
	GameData testObject;
	testObject.AddPlayerPosition(10);
	testObject.AddPlayerPosition(20);
	testObject.AddPlayerPosition(30);
	testObject.AddPlayerPosition(3);

	std::string expected = "PlayerPositions: [10, 20, 30, 3, ]";
	std::string actual = testObject.ToJson();

	EXPECT_EQ(expected, actual);
}

