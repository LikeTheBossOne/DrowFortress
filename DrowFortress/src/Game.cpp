#include "Game.h"

#include <iomanip>
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "Components/DrawComponent.h"
#include "Components/InputComponent.h"
#include "Components/MovementSpeedComponent.h"
#include "Components/RectangleColliderComponent.h"
#include "Components/TransformComponent.h"
#include "Systems/WorldInputSystem.h"

Registry Game::s_registry = {};
sf::RenderWindow* Game::s_window = nullptr;

TileMap* Game::s_tileMap = nullptr;
WorldLevel Game::s_worldLevel;


void Game::Run()
{
    s_window = new sf::RenderWindow(sf::VideoMode(600, 600), "SFML works!");

    sf::Font myFont;
    myFont.loadFromFile("resources/Flexi_IBM_VGA_True_437.ttf");

    sf::Texture playerTexture;
    playerTexture.loadFromFile("resources/magicAssetPack/novicePyromancer/NovicePyromancerIdle.png");


    auto playerEnt = s_registry.create();

    auto& inputComp = s_registry.emplace<InputComponent>(playerEnt);
    inputComp.InputState = WORLD;

    auto& transform = s_registry.emplace<TransformComponent>(playerEnt);
    transform.Position = { 24 * 16, 15 * 16 };
    SetCameraCenter(transform.Position);

    auto& drawComp = s_registry.emplace<DrawComponent>(playerEnt);
    drawComp.Sprite.setTexture(playerTexture);
    drawComp.Sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));

    auto& moveSpeedComp = s_registry.emplace<MovementSpeedComponent>(playerEnt);
    moveSpeedComp.BaseMovementSpeed = 0.25f;

    auto& rectCollComp = s_registry.emplace<RectangleColliderComponent>(playerEnt);
    rectCollComp.Box.left = 0;
    rectCollComp.Box.top = 0;
    rectCollComp.Box.width = 16;
    rectCollComp.Box.height = 16;


	int level[LEVEL_SIZE * LEVEL_SIZE];
    for (int i = 0; i < LEVEL_SIZE; i++)
    {
	    for (int j = 0; j < LEVEL_SIZE; j++)
	    {
            int block = 220;
            if (i == 10)
                block = 32;
            else if (i == 11)
                block = 64;
            level[i * LEVEL_SIZE + j] = block;
            s_worldLevel.Tiles[i][j] = (TileType)block;
	    }
    }

    s_tileMap = new TileMap;
    if (!s_tileMap->Load("resources/dungeonTileset/dungeonTileset.png", sf::Vector2u(16, 16), level, LEVEL_SIZE, LEVEL_SIZE))
        std::cout << "couldn't load tilemap";


    sf::Clock gameClock;
    while (s_window->isOpen())
    {
        float deltaTime = gameClock.restart().asMicroseconds() / 1000.f;
        std::cout << std::setprecision(3) << deltaTime << std::endl;

        sf::Event event;
        while (s_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                s_window->close();
        }

        Tick(deltaTime);
        Draw();
    }
}

void Game::Tick(float deltaTime)
{
    WorldInputSystem::Update(deltaTime);
}

void Game::Draw()
{
    s_window->clear();

    s_window->draw(*s_tileMap);

    auto group = s_registry.group<const TransformComponent, DrawComponent>();
    for (auto [entity, transform, drawComp] : group.each())
    {
        drawComp.Sprite.setPosition(transform.Position);
        s_window->draw(drawComp.Sprite);
    }
    //s_window.draw(myText);
    s_window->display();
}

void Game::SetCameraCenter(sf::Vector2f& newPos)
{
    sf::View view = s_window->getView();
    view.setCenter(newPos);
    s_window->setView(view);
}
