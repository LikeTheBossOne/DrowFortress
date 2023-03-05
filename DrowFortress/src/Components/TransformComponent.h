#pragma once
#include <SFML/System/Vector2.hpp>

struct TransformComponent
{
	sf::Vector2f Position;
	sf::Vector2f Rotation;

	TransformComponent() = default;
};
