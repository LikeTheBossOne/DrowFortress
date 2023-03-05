#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "Core.h"
#include "Drawables/TileMap.h"
#include "World/WorldLevel.h"

class Game
{
public:
	static Registry& GetRegistry() { return s_registry; }
	static WorldLevel& GetWorldLevel() { return s_worldLevel; }
	static void SetCameraCenter(sf::Vector2f& newPos);

	static void Run();

private:
	static void Tick(float deltaTime);
	static void Draw();

	static Registry s_registry;
	static sf::RenderWindow* s_window;

	static WorldLevel s_worldLevel;
	static TileMap* s_tileMap;
};
