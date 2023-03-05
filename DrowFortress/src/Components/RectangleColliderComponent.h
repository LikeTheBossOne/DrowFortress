#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

struct RectangleColliderComponent
{
	sf::Rect<float> Box;

	RectangleColliderComponent() = default;
};
