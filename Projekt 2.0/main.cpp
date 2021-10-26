#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include "funkcje.h"

using namespace std;

int main()
{
    int Windowposx = 1920;
    int Windowposy = 1080;
    sf::RenderWindow window(sf::VideoMode(Windowposx, Windowposy), "Dungeon Crawler");

    //Sprite bohatera
    sf::Texture bohaterTexture;
    bohaterTexture.loadFromFile("Sprite/bohater2.png");
    sf::RectangleShape bohater(sf::Vector2f(50.0f,100.0f));
    bohater.setTexture(&bohaterTexture);
    bohater.setTextureRect(sf::IntRect(15,6,13,27));
    //Pozycja bohatera
    float bohaterPosx=Windowposx/2;
    float bohaterPosy=Windowposy/2;

    //tlo
    sf::RectangleShape podloga(sf::Vector2f(Windowposx-425,Windowposy));
    podloga.setFillColor(sf::Color::Green);
    podloga.setPosition(0,0);

    //drzwi
    sf::Texture drzwiTexture;
    drzwiTexture.loadFromFile("Sprite/drzwi.png");
    vector<sf::Sprite> drzwi(4,sf::Sprite(drzwiTexture));
    for(int i=0;i<4;i++)
    {
        drzwi[i].setScale(0.2,0.2);
    }
    drzwi[0].setPosition((Windowposx-400)/2,0);
    drzwi[1].setPosition(0,(Windowposy-50)/2);
    drzwi[2].setPosition(Windowposx-500,(Windowposy-50)/2);
    drzwi[3].setPosition((Windowposx-400)/2,Windowposy-150);

    //czas
    bool time=1;

    //pokoje
    int aktualnyPokojx=2;
    int aktualnyPokojy=2;
    int iloscPokoi=7;
    bool czyPokoj[5][5];
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            czyPokoj[i][j]=false;
        }
    }
    czyPokoj[2][2]=true;
    //generator pietra
    generuj(iloscPokoi,czyPokoj);
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(czyPokoj[i][j])
            {
                cout<<i<<" "<<j<<endl;
            }
        }
    }

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
            for(int i=0;i<drzwi.size();i++)
            {
                if(bohater.getGlobalBounds().intersects(drzwi[i].getGlobalBounds()))
                {
                    switch(i)
                    {
                        case 0:
                            if(czyPokoj[aktualnyPokojx][aktualnyPokojy-1])
                            {
                                bohaterPosx=(Windowposx-400)/2;
                                bohaterPosy=Windowposy-350;
                                aktualnyPokojy--;
                            }
                            break;
                        case 1:
                            if(czyPokoj[aktualnyPokojx-1][aktualnyPokojy])
                            {
                                bohaterPosx=Windowposx-550;
                                bohaterPosy=(Windowposy-50)/2;
                                aktualnyPokojx--;
                            }
                            break;
                        case 2:
                            if(czyPokoj[aktualnyPokojx+1][aktualnyPokojy])
                            {
                                bohaterPosx=80;
                                bohaterPosy=(Windowposy-50)/2;
                                aktualnyPokojx++;
                            }
                            break;
                        case 3:
                            if(czyPokoj[aktualnyPokojx][aktualnyPokojy+1])
                            {
                                bohaterPosx=(Windowposx-400)/2;
                                bohaterPosy=125;
                                aktualnyPokojy++;
                            }
                            break;
                    }
                    bohater.setTextureRect(sf::IntRect(14,6,14,27));
                }
            }
        }
        //Zdarzenia dziejace sie, gdy nie ma pauzy
        if(time)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && bohaterPosx-0.5>0)
            {
                bohaterPosx=bohaterPosx-0.5;
                bohater.setTextureRect(sf::IntRect(14,93,15,27));
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && bohaterPosy-0.5>0)
            {
                bohaterPosy=bohaterPosy-0.5;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && bohaterPosy+0.5<Windowposy-100)
            {
                bohaterPosy=bohaterPosy+0.5;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && bohaterPosx+0.5<Windowposx-475)
            {
                bohaterPosx=bohaterPosx+0.5;
                bohater.setTextureRect(sf::IntRect(56,7,15,27));
            }
        }

        bohater.setPosition(bohaterPosx,bohaterPosy);

        window.clear();
        window.draw(podloga);
        for(int i=0;i<drzwi.size();i++)
        {
            window.draw(drzwi[i]);
        }
        window.draw(bohater);
        window.display();
    }

    return 0;
}
