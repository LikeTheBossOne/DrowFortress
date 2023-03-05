#pragma once
#include <array>

#include "Core.h"

constexpr uint16_t LEVEL_SIZE = 64;

enum TileType : uint8_t
{
	GRASS = 0,
	STONE = 220,
	WATER = 2,
	WALL = 32,
	STONE_NEXT_TO_WALL = 64
};

class WorldLevel
{
public:
	// outer array is y, inner is x
	std::array<std::array<TileType, LEVEL_SIZE>, LEVEL_SIZE> Tiles;
};
