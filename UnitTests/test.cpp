#include "pch.h"
#include "../MonopolySimulation/DiceHandler.h"
#include "../MonopolySimulation/PlayerData.h"
#include "../MonopolySimulation/Property.h"
#include "test.h"

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
	
	for (int i = 0; i < 5; i++)
	{
		ASSERT_FALSE(testObject.HasHotel());
		testObject.BuildHouse();
	}
	ASSERT_TRUE(testObject.HasHotel());
}
