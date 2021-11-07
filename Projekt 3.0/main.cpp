#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "funkcje.h"
#include "klasy.h"

using namespace std;

int main()
{
    // Resolutions that divide perfectly in 1080p:
    //160 x 90 (12x12 pixels)
    //192 x 108 (10x10 pixels)
    //320 x 180 (6x6 pixels)
    //384 x 216 (5x5 pixels)
    //480 x 270 (4x4 pixels)
    // Niestety SFML nie obsluguje natywnego fullscreena(czyli zawsze trzeba wlaczac go recznie w okienku)
    const int window_width = 480;
    const int window_height = 270;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "The Binding of Hollow");

    // ////////////////////////////////////////// BOHATER //////////////////////////////////////////////
    Player player;

    player.position(window_width / 2 - player.size/2, window_height / 2 - player.size/2);
    player.entity.setSize(sf::Vector2f(player.size, player.size));
    player.texture("Textures/Knight.png", 0, 0, 43, 43);

    int tekstura=2;

    bool is_right; // Czy gracz skrecil w prawo?
    bool attack = 0; //Czy atakuje?
    bool klatka; //klatka animacji chodzenia

    //tlo
    sf::Texture background_texture;
    background_texture.loadFromFile("Textures/Background.png"); // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Background.png");
    sf::RectangleShape background(sf::Vector2f(window_width, window_height));
    background.setTexture(&background_texture);
    background.setPosition(0,0);

    ////////////////////////////////////////////// POTWORY ////////////////////////////////////////////
    int monsters_max_value = 7;
    vector<Entity*> monsters;

    // /////////////////////////////////////////// DRZWI // ///////////////////////////////////////////
    const int door_size = 32;
    sf::Texture door_texture;
    door_texture.loadFromFile("Textures/Door.png"); // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Door.png");
    sf::RectangleShape door(sf::Vector2f(door_size, door_size)); // takie wymiary ma jeden ze sprite-ow drzwi
    door.setTexture(&door_texture);
    sf::IntRect texture_rect(0, 0, 32, 32); // pierwsze drzwi

    vector<sf::Sprite> drzwi; //  !!!Chcialbym tutaj miec tylko 1 sprite'a zamiast calej tekstury!!!
    for(int i = 0; i < 4; ++i)
    {
        drzwi.push_back(sf::Sprite());
        drzwi[i].setTexture(door_texture);
        drzwi[i].setTextureRect(sf::IntRect(0, 0, 32, 32));
    }

    drzwi[0].setPosition(window_width / 2 - door_size/2, 0);  // srodek, gora
    drzwi[1].setPosition(0, window_height / 2);  // lewo, srodek
    drzwi[2].setPosition(window_width - door_size, window_height / 2);  // prawo srodek
    drzwi[3].setPosition(window_width / 2 - door_size/2, window_height - door_size);  // srodek dol

    ///////////////////////////////////////////// CZAS /////////////////////////////////////////////
    bool time = 1;
    sf::Clock attack_cooldown; //czas do kolejnego ataku
    float attack_time = 1.0f;
    float attack_animation_time = 200.0f;
    sf::Clock run;
    float run_animation_time = 200.0f;

    ///////////////////////////////////////////// POKOJE ////////////////////////////////////////
    int actual_room_x = 2;
    int actual_room_y = 2;
    int room_amount = 7;
    bool is_room[5][5];
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            is_room[i][j] = false;
        }
    }
    is_room[2][2] = true;
    //generator pietra
    bool drawdoor[4];
    generate_floor(room_amount, is_room);
    draw_door(is_room,drawdoor,actual_room_x,actual_room_y);

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
                    time =! time;
                }
            }
            //    const int window_width = 480;
            //    const int window_height = 270;
            for(int i = 0;i < drzwi.size(); i++)
            {
                if(player.entity.getGlobalBounds().intersects(drzwi[i].getGlobalBounds()) && drawdoor[i])
                {
                    switch(i)
                    {
                        case 0: // drzwi gorne(przechodzi w dolne)
                            if(is_room[actual_room_x][actual_room_y - 1])
                            {
                                player.position(window_width / 2, window_height - player.size - door_size);
                                actual_room_y--;
                            }
                            break;
                        case 1: // drzwi lewe(przechodzi w prawo)
                            if(is_room[actual_room_x-1][actual_room_y])
                            {
                                player.position(window_width - door_size -  player.size, window_height / 2);
                                actual_room_x--;
                            }
                            break;
                        case 2: // drzwi prawe(przechodzi na lewo)
                            if(is_room[actual_room_x+1][actual_room_y])
                            {
                                player.position( door_size, window_height / 2);
                                actual_room_x++;
                            }
                            break;
                        case 3: // drzwi dolne(przechodzi w gorne)
                            if(is_room[actual_room_x][actual_room_y + 1])
                            {
                                player.position(window_width / 2,door_size);
                                actual_room_y++;
                            }
                            break;
                    }
                    draw_door(is_room,drawdoor,actual_room_x,actual_room_y);
                    player.texture("Textures/Knight.png", 0, 0, 43, 43);
                    tekstura = 3;
                    monsters.clear();
                    monsters_generator(monsters, monsters_max_value, player.get_pos_x(), player.get_pos_y(), window_width, window_height);
                }
            }
        }
        //Zdarzenia dziejace sie, gdy nie ma pauzy
        if(time)
        {
            /////////////////////////RUCH POTWORÓW//////////////////////////////////
            for(int i=0;i<monsters.size();i++)
            {
                monsters[i]->move_entity(player.get_pos_x(),player.get_pos_y());
            }
            //  ///////////////////// LEWO(left 0, top 86) ////////////////////////////////////
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.get_pos_x() - player.get_speed() > 5)
            {
                player.position(player.get_pos_x() - player.get_speed(), player.get_pos_y());
                if(tekstura != 0 && !attack)
                {
                    run.restart();
                    tekstura=0;
                    player.texture("Textures/Knight.png", 86, 86, 43, 43);
                    is_right = false;
                }
                if(!attack && run.getElapsedTime().asMilliseconds() > run_animation_time)
                {
                    if(klatka)
                    {
                        player.texture("Textures/Knight.png", 86, 86, 43, 43);
                        klatka=0;
                    }
                    else
                    {
                        player.texture("Textures/Knight.png", 43, 86, 43, 43);
                        klatka=1;
                    }
                    run.restart();
                }
            }
            //  ///////////////////// PRAWO(left 43, top 0) ////////////////////////////////////
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.get_pos_x() + player.get_speed() < window_width - 50)
            {
                player.position(player.get_pos_x() + player.get_speed(), player.get_pos_y());
                if(tekstura != 1 && !attack)
                {
                    run.restart();
                    tekstura=1;
                    player.texture("Textures/Knight.png", 86, 0, 43, 43);
                    is_right = true;
                }
                if(!attack && run.getElapsedTime().asMilliseconds() > run_animation_time)
                {
                    if(klatka)
                    {
                        player.texture("Textures/Knight.png", 86, 0, 43, 43);
                        klatka=0;
                    }
                    else
                    {
                        player.texture("Textures/Knight.png", 129, 0, 43, 43);
                        klatka=1;
                    }
                    run.restart();
                }
            }
            //  ///////////////////// GORA(bez zmian) ////////////////////////////////////
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.get_pos_y() - player.get_speed() > 0)
            {
                player.position(player.get_pos_x(), player.get_pos_y() - player.get_speed());
                if(!attack && run.getElapsedTime().asMilliseconds() > run_animation_time)
                {
                    if(is_right)
                    {
                        if(klatka)
                        {
                            player.texture("Textures/Knight.png", 86, 0, 43, 43);
                            klatka=0;
                        }
                        else
                        {
                            player.texture("Textures/Knight.png", 129, 0, 43, 43);
                            klatka=1;
                        }
                    run.restart();
                    }
                    else
                    {
                        if(klatka)
                        {
                            player.texture("Textures/Knight.png", 86, 86, 43, 43);
                            klatka=0;
                        }
                        else
                        {
                            player.texture("Textures/Knight.png", 43, 86, 43, 43);
                            klatka=1;
                        }
                        run.restart();
                    }
                }
            }
            //  ///////////////////// DOL(bez zmian) ////////////////////////////////////
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player.get_pos_y() + player.get_speed() < window_height - 50)
            {
                player.position(player.get_pos_x(), player.get_pos_y() + player.get_speed());
                if(!attack && run.getElapsedTime().asMilliseconds() > run_animation_time)
                {
                    if(is_right)
                    {
                        if(klatka)
                        {
                            player.texture("Textures/Knight.png", 86, 0, 43, 43);
                            klatka=0;
                        }
                        else
                        {
                            player.texture("Textures/Knight.png", 129, 0, 43, 43);
                            klatka=1;
                        }
                    run.restart();
                    }
                    else
                    {
                        if(klatka)
                        {
                            player.texture("Textures/Knight.png", 86, 86, 43, 43);
                            klatka=0;
                        }
                        else
                        {
                            player.texture("Textures/Knight.png", 43, 86, 43, 43);
                            klatka=1;
                        }
                        run.restart();
                    }
                }
            }
            if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !attack)
            {
                player.texture("Textures/Knight.png", 0, 0, 43, 43);
            }
/////////////////////////////////////// ATAKI ///////////////////////////////////////////
            //zmiana animacji z atakujacej na chodzaca
            if(attack_cooldown.getElapsedTime().asMilliseconds() > attack_animation_time && attack)
            {
                if(is_right)
                {
                    player.texture("Textures/Knight.png", 43, 0, 43, 43);
                }
                else
                {
                    player.texture("Textures/Knight.png", 0, 86, 43, 43);
                }
                attack = 0;
            }
            ///////////////////// ATAK W LEWO ////////////////////////////////////
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && attack_cooldown.getElapsedTime().asSeconds() > attack_time)
            {
                player.texture("Textures/Knight.png", 0, 129, 43, 43);
                attack_cooldown.restart();
                //attack_animation_cooldown.restart();
                attack = 1;
            }
            //  ///////////////////// ATAK W PRAWO ////////////////////////////////////
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && attack_cooldown.getElapsedTime().asSeconds() > attack_time)
            {
                player.texture("Textures/Knight.png", 43, 43, 43, 43);
                attack_cooldown.restart();
                //attack_animation_cooldown.restart();
                attack = 1;
            }
            ///////////////////// ATAK W GORE ////////////////////////////////////
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && attack_cooldown.getElapsedTime().asSeconds() > attack_time)
            {
                // gora, prawo
                if(is_right)
                {
                    player.texture("Textures/Knight.png", 129, 43, 43, 43);
                }
                // gora, lewo
                else{
                    player.texture("Textures/Knight.png", 86, 129, 43, 43);
                }
                attack_cooldown.restart();
                //attack_animation_cooldown.restart();
                attack = 1;
            }
            ///////////////////// ATAK W DOL ////////////////////////////////////
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && attack_cooldown.getElapsedTime().asSeconds() > attack_time)
            {
                // dol, prawo
                if(is_right){
                    player.texture("Textures/Knight.png", 86, 43, 43, 43);
                }
                // dol, lewo
                else{
                    player.texture("Textures/Knight.png", 43, 129, 43, 43);
                }
                attack_cooldown.restart();
                //attack_animation_cooldown.restart();
                attack = 1;
            }

        }
        window.clear();
        window.draw(background);
        for(int i = 0; i < drzwi.size(); i++) //rysowanie drzwi
        {
            if(drawdoor[i])
            {
                window.draw(drzwi[i]);
            }
        }
        for(int i=0;i<monsters.size();i++) //rysowanie potworów
        {
            window.draw(monsters[i]->entity);
        }
        window.draw(player.entity); //rysowanie bohatera
        window.display();
    }
    return 0;
}
