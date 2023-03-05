#pragma once
#include <string>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	bool Load(const std::string& tileMapPath, sf::Vector2u tileSize, const int* tiles, uint32_t width, uint32_t height);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::VertexArray _vertices;
	sf::Texture _tileset;
};
