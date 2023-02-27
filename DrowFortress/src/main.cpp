
#include "entt/entt.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Graphics/Text.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
    sf::String text = "asdadakdakdkadkaskdadwLWwWMmNn$%ASDAFNI)AGlf|";
    text += sf::Uint32(0x263A);

    sf::Font myFont;
    myFont.loadFromFile("resources/Flexi_IBM_VGA_True_437.ttf");
    sf::Text myText(text, myFont, 20);
    myText.setColor(sf::Color(220, 220, 220));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(myText);
        window.display();
    }

    return 0;
}
