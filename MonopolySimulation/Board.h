#pragma once
#include <map>
#include <vector>
#include <string>
#include "Property.h"
#include "Tile.h"

class Board
{
	public:
		Board();

	private:
		std::map<std::string, std::vector<Property>> monopolies;
		Tile tiles[40];
};

