#include "pch.h"
#include "../MonopolySimulation/DiceHandler.h"
#include "../MonopolySimulation/PlayerData.h"
#include "../MonopolySimulation/Property.h"
#include "test.h"
#include "../MonopolySimulation/GameData.h"

TEST(GAMETESTS, TestRollDie) {
	DiceHandler testObj(3);
	int result = testObj.RollDice();

	//EXPECT_EQ(, result);
	bool valid = result <= 12 && result >= 1;
	EXPECT_TRUE(valid);
}

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

// Player Tests

TEST(PLAYERDATATESTS, TestMovePlayer) {
	PlayerData testObject;
	int actual[4];
	int expected[4] = { 12, 24, 36, 0 };

	testObject.Move(12);
	actual[0] = testObject.GetPosition();

	testObject.Move(12);
	actual[1] = testObject.GetPosition();

	testObject.Move(12);
	actual[2] = testObject.GetPosition();

	testObject.Move(4);
	actual[3] = testObject.GetPosition();
	
	for (int i = 0; i < 4; i++) {
		ASSERT_EQ(expected[i], actual[i]);
	}
}

TEST(PLAYERDATATESTS, Test3TurnsInJail) {
	PlayerData testObject;
	testObject.Move(10);
	int actual = testObject.GetPosition();
	int expected = 10;
	
	ASSERT_EQ(expected, actual);

	testObject.sendToJail();
	
	testObject.Move(3);
	ASSERT_EQ(expected, actual);
	ASSERT_EQ(1, testObject.GetTimeInJail());

	testObject.Move(3);
	ASSERT_EQ(expected, actual);
	ASSERT_EQ(2, testObject.GetTimeInJail());
	
	testObject.Move(3);
	expected = 13;
	actual = testObject.GetPosition();
	ASSERT_EQ(expected, actual);
	ASSERT_EQ(0, testObject.GetTimeInJail());


}

// Property Tests
TEST(PROPERTYTESTS, TestGetCurrentRent) {
	int actual[7];
	
	int priceArray[6] = {
		6, 30, 90, 270, 400, 550
	};
	Property testObject(50, priceArray, "Oriental Ave");
	ASSERT_EQ(priceArray[0], testObject.GetCurrentRent());
	testObject.SetMonopolyStatus(true);
	ASSERT_EQ(priceArray[0] * 2, testObject.GetCurrentRent());
}

TEST(PROPERTYTESTS, TestHasHotel) {
	int priceArray[6] = {
		6, 30, 90, 270, 400, 550
	};
	Property testObject(50, priceArray, "Oriental Ave");
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
	Property testObject(50, priceArray, "Oriental Ave");
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
		EXPECT_EQ(result, "ERROR: There are to many houses!");
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
	Property testObject(50, priceArray, "Oriental Ave");

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

TEST(PROPERTYTESTS, TestBuildIfInMonopoly)
{
	int priceArray[6] = {
		6, 30, 90, 270, 400, 550
	};
	Property testObject(50, priceArray, "Oriental Ave");

	try {
		testObject.BuildHouse();
		FAIL() << "Expected Must Be In Monopoly Error.";
	}
	catch (const char* msg) {
		std::string result(msg);
		EXPECT_EQ(result, "ERROR: Property not in a monopoly!");
	}
	catch (...) {
		FAIL() << "Expected Must Be In Monopoly Error.";
	}
}

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

