#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Dungeon Crawler");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    float x=0;
    float y=0;
    bool time=1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if  (event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    time=!time;
                }
            }
        }
        if(time)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                x=x-1;
                sprite.setPosition(x,y);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                y=y-1;
                sprite.setPosition(x,y);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                y=y+1;
                sprite.setPosition(x,y);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                x=x+0.5f;
                sprite.setPosition(x,y);
            }
        }

        window.clear();
        //window.draw(shape);
        window.draw(sprite);
        window.display();
    }

    return 0;
}
