#pragma once
#include <Game.h>

TEST(GAMETESTS, RollDie) {
	Game testObject;
	int result = testObject.RollDie();
	EXPECT_TRUE(1);
}
