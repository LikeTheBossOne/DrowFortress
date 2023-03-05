#include "WorldInputSystem.h"

#include <SFML/Window/Keyboard.hpp>

#include "Game.h"
#include "Components/InputComponent.h"
#include "Components/MovementSpeedComponent.h"
#include "Components/RectangleColliderComponent.h"
#include "Components/TransformComponent.h"

void WorldInputSystem::Update(float deltaTime)
{
	Registry& registry = Game::GetRegistry();
	auto view = registry.view<const InputComponent>();
	// Should only be one

	assert(view.size() <= 1);
	if (view.size() < 1)
		return;

	Entity entity = view.front();

	const auto& inputComponent = registry.get<const InputComponent>(entity);
	if (inputComponent.InputState != WORLD)
		return;

	auto& transform = registry.get<TransformComponent>(entity);
	const auto& boxCollider = registry.get<const RectangleColliderComponent>(entity);
	const auto& moveSpeed = registry.get<const MovementSpeedComponent>(entity);

	// Check tiles for collision
	WorldLevel& worldLevel = Game::GetWorldLevel();

	bool moved = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		const uint32_t futurePosX = static_cast<uint32_t>(transform.Position.x - moveSpeed.BaseMovementSpeed * deltaTime + boxCollider.Box.left) / 16;
		const uint32_t posY = static_cast<uint32_t>(transform.Position.y) / 16;

		if (futurePosX < LEVEL_SIZE && posY < LEVEL_SIZE)
		{
			const TileType tileAtPos = worldLevel.Tiles[posY][futurePosX];

			if (tileAtPos != TileType::WALL)
			{
				transform.Position.x -= moveSpeed.BaseMovementSpeed * deltaTime;
				moved = true;
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		const uint32_t futurePosX = static_cast<uint32_t>(transform.Position.x + moveSpeed.BaseMovementSpeed * deltaTime + boxCollider.Box.left + boxCollider.Box.width) / 16;
		const uint32_t posY = static_cast<uint32_t>(transform.Position.y) / 16;

		if (futurePosX < LEVEL_SIZE && posY < LEVEL_SIZE)
		{
			const TileType tileAtPos = worldLevel.Tiles[posY][futurePosX];
			if (tileAtPos != TileType::WALL)
			{
				transform.Position.x += moveSpeed.BaseMovementSpeed * deltaTime;
				moved = true;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		const uint32_t posX = static_cast<uint32_t>(transform.Position.x) / 16;
		const uint32_t futurePosY = static_cast<uint32_t>(transform.Position.y - moveSpeed.BaseMovementSpeed * deltaTime + boxCollider.Box.top) / 16;

		if (posX < LEVEL_SIZE && futurePosY < LEVEL_SIZE)
		{
			const TileType tileAtPos = worldLevel.Tiles[futurePosY][posX];
			if (tileAtPos != TileType::WALL)
			{
				transform.Position.y -= moveSpeed.BaseMovementSpeed * deltaTime;
				moved = true;
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		const uint32_t posX = static_cast<uint32_t>(transform.Position.x) / 16;
		const uint32_t futurePosY = static_cast<uint32_t>(transform.Position.y + moveSpeed.BaseMovementSpeed * deltaTime + boxCollider.Box.top + boxCollider.Box.height) / 16;

		if (posX < LEVEL_SIZE && futurePosY < LEVEL_SIZE)
		{
			const TileType tileAtPos = worldLevel.Tiles[futurePosY][posX];
			if (tileAtPos != TileType::WALL)
			{
				transform.Position.y += moveSpeed.BaseMovementSpeed * deltaTime;
				moved = true;
			}
		}
	}

	if (moved)
	{
		Game::SetCameraCenter(transform.Position);
	}
}

