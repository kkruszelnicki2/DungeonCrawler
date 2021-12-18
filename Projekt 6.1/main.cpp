#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>

#include "funkcje.h"
#include "monsters.h"
#include "rooms.h"
#include "hero.h"
#include "bullet.h"

#include "boss.h"
#include "hollow_knight.h"


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

    const float wall_size_x = window_width/24.0f;
    const float wall_size_y = window_height/13.5f;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "The Binding of Hollow");

    // ////////////////////////////////////////// BOHATER //////////////////////////////////////////////
    hero Hero;
    Hero.position(window_width / 2 - Hero.get_sizex()/2, window_height / 2 - Hero.get_sizey()/2);

    ///////////////////////////////////////////// NPC ///////////////////////////////////////////////////
    sf::RectangleShape Shopkeeper;
    sf::Texture ShopkeeperTexture;
    ShopkeeperTexture.loadFromFile("Textures/Iselda.png"); //"/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Iselda.png"
    Shopkeeper.setTexture(&ShopkeeperTexture);
    Shopkeeper.setSize(sf::Vector2f(46,46));
    Shopkeeper.setPosition(window_width/2 - 23,window_height/2 - window_height/4);
    ///////////////////////////////////////////// BOSS //////////////////////////////////////////////////
    vector <boss*> Boss;
    //boss * Boss = new hollow_knight();

    // ////////////////////////////////////////// TLO //////////////////////////////////////////////
    sf::Texture background_texture;
    std::string background_dir = "Textures/Background.png"; //"/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Background.png"
    background_texture.loadFromFile(background_dir); // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Background.png");
    sf::RectangleShape background(sf::Vector2f(window_width, window_height));
    background.setTexture(&background_texture);
    background.setPosition(0,0);

    ////////////////////////////////////////////// POTWORY ////////////////////////////////////////////
    int monsters_max_value = 1; //////ilosc przeciwnikow
    vector<Entity*> monsters; ////przeciwnicy
    vector<Bullet*> bullets; /////pocisku


    // /////////////////////////////////////////// DRZWI // ///////////////////////////////////////////
    const int door_size = 32;
    std::string door_dir = "Textures/Door.png"; //"/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Door.png"
    sf::Texture door_texture;
    door_texture.loadFromFile(door_dir); // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Door.png");
    sf::RectangleShape door(sf::Vector2f(door_size, door_size)); // takie wymiary ma jeden ze sprite-ow drzwi
    door.setTexture(&door_texture);

    vector<sf::Sprite> drzwi;
    for(int i = 0; i < 4; ++i)
    {
        drzwi.push_back(sf::Sprite());
        drzwi[i].setTexture(door_texture);
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

    ///////////////////////////////////////////// POKOJE ////////////////////////////////////////
    int actual_room_x;
    int actual_room_y;
    int room_amount = 7;
    int floor_size = 5;
    Room is_room[5][5];

    bool fight_mode = 0; // Czy sa konflikty z potworami?(na poczatku nie ma)
    /////////////////////////////////////////// ITEMY ////////////////////////////////////////////
    vector<pickups> items_pull;


    /////////////////////////////////////////// MAPA ////////////////////////////////////////////
    sf::RectangleShape mini_map;
    sf::Texture mini_map_texture;

    float mini_map_size = window_height/10.0;
    std::string map_dir = "Textures/Map.png"; // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Map.png"
    mini_map_texture.loadFromFile(map_dir);

    mini_map.setSize(sf::Vector2f(mini_map_size,mini_map_size));
    mini_map.setPosition(window_width-mini_map_size,0);
    mini_map.setTexture(&mini_map_texture);

    ////////////////////////////////////////// PASEK ZYCIA ////////////////////////////////////////
    sf::RectangleShape health_board;
    sf::RectangleShape health_bar(sf::Vector2f(52, 5));

    health_board.setSize(sf::Vector2f(60, 15));
    health_bar.setSize(sf::Vector2f(52, 15));
    float health_bar_width = 52;

    health_board.setPosition(0,window_height - 20);
    health_bar.setPosition(4,window_height - 20);

    sf::Texture health_bar_texture;
    std::string health_bar_dir = "Textures/Health_bar.png";  // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Health_bar.png"
    health_bar_texture.loadFromFile(health_bar_dir);

    health_board.setTexture(&health_bar_texture);
    health_bar.setTexture(&health_bar_texture);
    health_board.setTextureRect(sf::IntRect(0, 0, 60, 15));
    health_bar.setTextureRect(sf::IntRect(4, 19, 52, 7));

    //////////////////////////////////////////GENERATOR PIETRA////////////////////////////////////
    for(int j=0;j<5;j++)
    {
        for(int i=0;i<5;i++)
        {
            is_room[i][j].mini_map_icon.setPosition(window_width-mini_map_size + mini_map_size/10 + i * (mini_map_size- 2*mini_map_size/10)/5, mini_map_size/10.0 + j * (mini_map_size- 2*mini_map_size/10.0)/5);
            is_room[i][j].mini_map_icon.setSize(sf::Vector2f(8 * (mini_map_size/10)/5 , 8 * (mini_map_size/10)/5) );
        }
    }

    bool drawdoor[4];
    generate_floor(room_amount,is_room,window_width,window_height,mini_map_size,&actual_room_x,&actual_room_y);
    draw_door(is_room,drawdoor,actual_room_x,actual_room_y);
    door_closed(drzwi,is_room,2,2,fight_mode);


    /////////////////////////////////////////// GRA //////////////////////////////////////////////

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
            for(size_t i = 0;i < drzwi.size(); i++)
            {
                if(Hero.entity.getGlobalBounds().intersects(drzwi[i].getGlobalBounds()) && drawdoor[i] && !fight_mode)
                {
                    is_room[actual_room_x][actual_room_y].mini_map_icon.setFillColor(sf::Color::Yellow);
                    switch(i)
                    {
                        case 0: // drzwi gorne(przechodzi w dolne)
                            if(is_room[actual_room_x][actual_room_y - 1].get_type()!="none" && is_room[actual_room_x][actual_room_y - 1].can_enter())
                            {
                                Hero.position(window_width / 2 - Hero.get_sizex()/2, window_height - Hero.get_sizey() - door_size);
                                actual_room_y--;
                            }
                            else if(is_room[actual_room_x][actual_room_y - 1].get_type()=="treasure_room" && Hero.get_keyAmount()>0)
                            {
                                is_room[actual_room_x][actual_room_y - 1].open();
                                Hero.set_keyAmount(-1);
                            }
                            break;
                        case 1: // drzwi lewe(przechodzi w prawo)
                            if(is_room[actual_room_x-1][actual_room_y].get_type()!="none" && is_room[actual_room_x-1][actual_room_y].can_enter())
                            {
                                Hero.position(window_width - door_size -  Hero.get_sizex(), window_height / 2);
                                actual_room_x--;
                            }
                            else if(is_room[actual_room_x-1][actual_room_y].get_type()=="treasure_room" && Hero.get_keyAmount()>0)
                            {
                                is_room[actual_room_x-1][actual_room_y].open();
                                Hero.set_keyAmount(-1);
                            }
                            break;
                        case 2: // drzwi prawe(przechodzi na lewo)
                            if(is_room[actual_room_x+1][actual_room_y].get_type()!="none" && is_room[actual_room_x+1][actual_room_y].can_enter())
                            {
                                Hero.position( door_size, window_height / 2);
                                actual_room_x++;
                            }
                            else if(is_room[actual_room_x+1][actual_room_y].get_type()=="treasure_room" && Hero.get_keyAmount()>0)
                            {
                                is_room[actual_room_x+1][actual_room_y].open();
                                Hero.set_keyAmount(-1);
                            }
                            break;
                        case 3: // drzwi dolne(przechodzi w gorne)
                            if(is_room[actual_room_x][actual_room_y + 1].get_type()!="none" && is_room[actual_room_x][actual_room_y + 1].can_enter())
                            {
                                Hero.position(window_width / 2 - Hero.get_sizex()/2,door_size);
                                actual_room_y++;
                            }
                            else if(is_room[actual_room_x][actual_room_y + 1].get_type()=="treasure_room" && Hero.get_keyAmount()>0)
                            {
                                is_room[actual_room_x][actual_room_y + 1].open();
                                Hero.set_keyAmount(-1);
                            }
                            break;
                    }
                    is_room[actual_room_x][actual_room_y].mini_map_icon.setFillColor(sf::Color::Cyan);
                    draw_door(is_room,drawdoor,actual_room_x,actual_room_y);
                    Hero.idle();
                    Hero.set_direction(2);
                    monsters.clear();
                    if(!is_room[actual_room_x][actual_room_y].is_visited())
                    {
                        if(is_room[actual_room_x][actual_room_y].get_type() == "basic")
                        {
                            monsters_generator(monsters, monsters_max_value, Hero.get_pos_x(), Hero.get_pos_y(), window_width, window_height);
                        }
                        else if(is_room[actual_room_x][actual_room_y].get_type() == "boss_room")
                        {
                            Boss.push_back(new hollow_knight(window_width));
                        }
                        else if(is_room[actual_room_x][actual_room_y].get_type() == "treasure_room")
                        {
                            is_room[actual_room_x][actual_room_y].pickups.push_back(new mask_health);
                            is_room[actual_room_x][actual_room_y].pickups[0]->pickup.setPosition(window_width/2,window_height/2);
                        }
                        else if(is_room[actual_room_x][actual_room_y].get_type() == "shop")
                        {
                            //maska
                            is_room[actual_room_x][actual_room_y].pickups.push_back(new mask_speed);
                            is_room[actual_room_x][actual_room_y].pickups[0]->pickup.setPosition(window_width/2,window_height/2);
                            is_room[actual_room_x][actual_room_y].pickups[0]->set_worth(5);
                            //klucz
                            is_room[actual_room_x][actual_room_y].pickups.push_back(new key(window_width/2-window_width/10,window_height/2));
                            is_room[actual_room_x][actual_room_y].pickups[1]->set_worth(2);
                        }
                        fight_mode = 1;
                    }
                    door_closed(drzwi,is_room,actual_room_x,actual_room_y,fight_mode);
                }
            }
        }
        //Zdarzenia dziejace sie, gdy nie ma pauzy
        if(time)
        {
            if(!Boss.empty())
            {
                Boss[0]->boss_action(&Hero,&bullets,window_width,window_height,wall_size_x,wall_size_y,&Boss,is_room[actual_room_x][actual_room_y].pickups);
            }
            /////////////////////////RUCH POTWOROW//////////////////////////////////
            for(size_t i = 0; i < monsters.size(); i++)
            {
                if(!monsters[i]->hitbox.getGlobalBounds().intersects(Hero.hitbox.getGlobalBounds()))
                {
                    monsters[i]->move_entity(Hero.get_pos_x(),Hero.get_pos_y());
                }
                if(monsters[i]->get_protection() && monsters[i]->get_speed_x()>=0)
                {
                    monsters[i]->set_protection(false);
                }
                sort(monsters.begin(),monsters.end(),sort_monsters);
            }
            /////////////////////////RUCH POCISKOW//////////////////////////////////
            for(size_t i = 0; i < bullets.size(); i++)
            {
                bullets[i]->move_bullet();
                //kolizja pociskow ze sciana
                if(bullets[i]->get_pos_x() > window_width - wall_size_x || bullets[i]->get_pos_x() < wall_size_x || bullets[i]->get_pos_y() > window_height - wall_size_y || bullets[i]->get_pos_y() < wall_size_y)
                {
                    bullets.erase(bullets.begin()+i);
                }

                if(bullets[i]->bullet.getGlobalBounds().intersects(Hero.hitbox.getGlobalBounds())) //kolizja z pociskami
                {
                    Hero.damaged(bullets[i]->get_damage());
                    bullets.erase(bullets.begin()+i);
                    health_bar.setSize(sf::Vector2f(health_bar_width * float(Hero.get_health()/Hero.get_max_health()),15)); //update paska zdrowia
                }
            }
            for(size_t i = 0; i < monsters.size(); i++)
            {
                //atak boomera
                if(monsters[i]->detonate && monsters[i]->name == "boomer")
                {
                    if(monsters[i]->detonate==2)
                    {
                        if(monsters[i]->acceleration.getElapsedTime().asMilliseconds()>100) //Gdy czas sie skonczy boomer wybucha
                        {
                            monsters[i]->death(is_room[actual_room_x][actual_room_y].pickups,Hero.get_coinChance(),Hero.get_keyChance()); //wybuch

                            monsters.erase(monsters.begin() + i); //usuniecie boomera z mapy
                        }
                        else
                        {
                            for(size_t j=0;j<monsters.size();j++)
                            {
                                if(monsters[i]->hitbox.getGlobalBounds().intersects(monsters[j]->hitbox.getGlobalBounds()) && i!=j) //ranienie innych potworow
                                {
                                    monsters[j]->set_health(monsters[i]->get_spell_damage()); //zadane obrazenia
                                    monsters[j]->damaged(); //stan potworow po otrzymaniu obrazen
                                }
                            }
                        }
                    }
                    monsters[i]->attack_entity();
                }
            }

            //  ///////////////////// LEWO(left 0, top 86) ////////////////////////////////////
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && Hero.get_pos_x() - Hero.get_speed() > 5 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                Hero.move_left();
            }
            //  ///////////////////// PRAWO(left 43, top 0) ////////////////////////////////////
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && Hero.get_pos_x() + Hero.get_speed() < window_width - 50 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                Hero.move_right();
            }
            //  ///////////////////// GORA(bez zmian) ////////////////////////////////////
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && Hero.get_pos_y() - Hero.get_speed() > 0)
            {
                Hero.move_up();
            }
            //  ///////////////////// DOL(bez zmian) ////////////////////////////////////
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && Hero.get_pos_y() + Hero.get_speed() < window_height - 55)
            {
                Hero.move_down();
            }
            ///////////////////////// STANIE W MIEJSCU ///////////////////////////////////
            if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !Hero.get_attack())
            {
                Hero.idle();
            }
/////////////////////////////////////// PICKUPY ////////////////////////////////////////
            for(size_t i = 0;i < is_room[actual_room_x][actual_room_y].pickups.size(); i++)
            {
                if(Hero.hitbox.getGlobalBounds().intersects(is_room[actual_room_x][actual_room_y].pickups[i]->pickup.getGlobalBounds())) //podnoszenie pickupow
                {
                    if(Hero.get_coinAmount() >= is_room[actual_room_x][actual_room_y].pickups[i]->get_worth()) //warunek kupna
                    {
                        is_room[actual_room_x][actual_room_y].pickups[i]->pick(&Hero);
                        is_room[actual_room_x][actual_room_y].pickups.erase(is_room[actual_room_x][actual_room_y].pickups.begin()+i); //czyszczenie z mapy podniesionego pickupa
                    }

                }
            }
/////////////////////////////////////// ATAKI ///////////////////////////////////////////
            //zmiana animacji z atakujacej na chodzaca
            if(attack_cooldown.getElapsedTime().asMilliseconds() > attack_animation_time && Hero.get_attack())
            {
                Hero.attack_end();
            }
            //Atak w lewo
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && attack_cooldown.getElapsedTime().asSeconds() > attack_time)
            {
                Hero.attack_left();
                attack_cooldown.restart();
            }
            //Atak w prawo
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && attack_cooldown.getElapsedTime().asSeconds() > attack_time)
            {
                Hero.attack_right();
                attack_cooldown.restart();
            }
            //Atak w gore
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && attack_cooldown.getElapsedTime().asSeconds() > attack_time)
            {
                Hero.attack_up();
                attack_cooldown.restart();
            }
            //Atak w dol
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && attack_cooldown.getElapsedTime().asSeconds() > attack_time)
            {
                Hero.attack_down();
                attack_cooldown.restart();
            }
            // //////////////////////////////////////// KOLIZJA Z POTWORAMI ////////////////////////////////////////////
            for(size_t i = 0; i < monsters.size(); i++)
            {
                if(Hero.attack_hitbox.getGlobalBounds().intersects(monsters[i]->hitbox.getGlobalBounds()) && Hero.get_attack() && !monsters[i]->get_protection()) //kolizja potwora z mieczem
                {
                    monsters[i]->set_health(Hero.get_attack_damage());
                    monsters[i]->damaged();
                }

                if(monsters[i]->get_health() <= 0) //sprawzdanie stanu zdrowia potwora
                {
                    monsters[i]->death(is_room[actual_room_x][actual_room_y].pickups,Hero.get_coinChance(),Hero.get_keyChance());
                    monsters.erase(monsters.begin() + i);
                }
                // !!!!!Atak Boomera!!!!!!!
                if(Hero.hitbox.getGlobalBounds().intersects(monsters[i]->hitbox.getGlobalBounds()))
                {
                    if((monsters[i]->name == "boomer" && !monsters[i]->detonate) || monsters[i]->detonate)
                    {
                        monsters[i]->attack_entity();
                    }
                    Hero.damaged(monsters[i]->get_attack_damage());
                    health_bar.setSize(sf::Vector2f(health_bar_width * float(Hero.get_health()/Hero.get_max_health()),15));
                }
                // Atak shootera
                if(monsters[i]->name == "shooter" && monsters[i]->detonate)
                {
                    bullets.push_back(new Bullet(monsters[i]->hitbox_pos_x + 5,monsters[i]->hitbox_pos_y + 15,monsters[i]->get_spell_damage(),"Textures/Shooter_bullet.png",Hero.get_pos_x()+Hero.get_sizex()/2,Hero.get_pos_y()+Hero.get_sizey()/2));
                    monsters[i]->detonate = false;
                }
            }

            if(monsters.empty() && Boss.empty() && fight_mode) // dzialania po smierci ostatniego potwora
            {
                fight_mode = 0;
                door_closed(drzwi,is_room,actual_room_x,actual_room_y,fight_mode);
                is_room[actual_room_x][actual_room_y].visit();
            }
        }

        ///////////////////////////////////// RYSOWANIE ///////////////////////////////////////
        window.clear();
        window.draw(background);
        for(size_t i = 0; i < drzwi.size(); i++) //rysowanie drzwi
        {
            if(drawdoor[i])
            {
                window.draw(drzwi[i]);
            }
        }

        if(!is_room[actual_room_x][actual_room_y].pickups.empty()) //rysowanie pickupow
        {
            for(size_t i = 0; i < is_room[actual_room_x][actual_room_y].pickups.size(); i++)
            {
                window.draw(is_room[actual_room_x][actual_room_y].pickups[i]->pickup);
            }
        }

        for(size_t i=0;i<monsters.size(); i++) //rysowanie potworow
        {
            window.draw(monsters[i]->entity);
        }
        if(is_room[actual_room_x][actual_room_y].get_type()=="shop")
        {
            window.draw(Shopkeeper);
        }
        if(!Boss.empty()) ////////////////rysowanie bossa
        {
            if(Hero.hitbox.getGlobalBounds().intersects(Boss[0]->hitbox.getGlobalBounds()))
            {
                Hero.damaged(Boss[0]->get_attack_damage());
                health_bar.setSize(sf::Vector2f(health_bar_width * float(Hero.get_health()/Hero.get_max_health()),15));
            }
            window.draw(Boss[0]->Sprite);
        }
        for(size_t i=0;i<bullets.size();i++) //rysowanie pociskow
        {
            window.draw(bullets[i]->bullet);
        }
        if(!Hero.attacked || (Hero.attacked && Hero.damaged_cd.getElapsedTime().asMilliseconds()%100 > 50)) //rysowanie bohatera
        {
            if(Hero.damaged_cd.getElapsedTime().asSeconds() > Hero.damaged_cooldown && Hero.attacked)
            {
                Hero.attacked = 0;
            }
            window.draw(Hero.entity); //rysowanie bohatera
        }

        window.draw(mini_map); //rysowanie minimapy
        for(size_t i = 0; i < 5; i++)
        {
            for(size_t j = 0; j < 5; j++)
            {
                window.draw(is_room[i][j].mini_map_icon);
            }
        }

        window.draw(health_bar); //rysowanie health bara
        window.draw(health_board);
        window.display();
    }
    return 0;
}
