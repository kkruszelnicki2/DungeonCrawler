#ifndef BOOMER_H_INCLUDED
#define BOOMER_H_INCLUDED

#ifndef PROJEKT_CPP_BOOMER_H
#define PROJEKT_CPP_BOOMER_H

#include "monsters.h"
#include "hero.h"

//klasa boomer
class Boomer: public Entity
{
private:

public:
    Boomer();

    //eksplozja
    sf::Clock blow;
    float blow_time = 70.0f;


    int direction = 2; //skierowany do przodu (2), w prawo (1) czy w lewo (0)
    // Sprawdzenie w ktora strone porusza sie potwor

    void texture(std::string tekstura,int a,int b,int c,int d) {entity_texture.loadFromFile(tekstura);entity.setTexture(&entity_texture);entity.setTextureRect(sf::IntRect(a, b, c, d));};

    // Pozycja hitboxa/potwora(kolor czerwony)
    void position(float x, float y) {pos_x = x; pos_y = y; entity.setPosition(pos_x, pos_y); hitbox.setPosition(hitbox_pos_x = (pos_x - 2) + (size_x/2.5), hitbox_pos_y = pos_y + (size_y/6) );}  // kolor czerwony

    float get_pos_x(){return pos_x;}
    float get_pos_y(){return pos_y;}

    float get_speed_x() {return speed_x;}
    float get_speed_y() {return speed_y;}
    void set_speed_x(float speed) {speed_x = speed_x;}
    void set_speed_y(float speed) {speed_y = speed_y;}
    float get_base_speed() {return base_speed;}

    int get_attack_damage() {return attack_damage;}
    int get_spell_damage() {return spell_damage;}

    void set_protection(bool x) {protection=x;}
    bool get_protection() {return protection;}
    void damaged();
    void death(std::vector<pickups*> &pickups, int coin_chance, int key_chance);

    void set_health(int x) {health = health-x;}
    int get_health() {return health;};

    void attack_entity();

    //zmienne zwiazane z poruszaniem
    float run_animation_time = 200.0f; //czas pomiedzy klatkami animacji
    bool frame; //klatka animacji

    //////////////////////////////////// PORUSZANIE POTWOROW///////////////////////////////////////////////
    void move_entity(float player_position_x,float player_position_y)
    {
        if(sqrt(pow(player_position_x - hitbox_pos_x,2)+pow(player_position_y - hitbox_pos_y,2) < pow(zasieg,2)) && !detonate)
        {
            if(speed_x < base_speed && acceleration.getElapsedTime().asMilliseconds() > 50)
            {
                speed_x = speed_x + 0.001f;
                speed_y = speed_y + 0.001f;
                acceleration.restart();
            }
            // lewo
            if(player_position_x + 43/2 < hitbox_pos_x && (get_pos_x() - speed_x > player_position_x) && pos_x - speed_x > 0 && pos_x - speed_x <= 430)
            {
                position(get_pos_x() - speed_x, get_pos_y());
                if(direction != 0 && !protection)
                {
                    run.restart();
                    direction = 0;
                    texture(boomer_dir, 43, 43, 43, 43);
                }
                if(run.getElapsedTime().asMilliseconds() > run_animation_time)
                {
                    if(frame && !protection)
                    {
                        texture(boomer_dir, 86, 43, 43, 43);
                        frame = 0;
                    }
                    else if(!frame && !protection)
                    {
                        texture(boomer_dir, 0, 86, 43, 43);
                        frame = 1;
                    }
                    run.restart();
                }
            }

                // Prawo
            else if(player_position_x + 43/2 > hitbox_pos_x && (get_pos_x() + speed_x < player_position_x) && pos_x + speed_x > 0 && pos_x + speed_x <= 430)
            {
                position(get_pos_x() + speed_x, get_pos_y());
                if(direction != 1 && !protection)
                {
                    run.restart();
                    direction = 1;  // skierowany w prawo
                    texture(boomer_dir, 43, 0, 43, 43);
                }
                if(run.getElapsedTime().asMilliseconds() > run_animation_time)
                {
                    if(frame && !protection)
                    {
                        texture(boomer_dir, 86, 0, 43, 43);
                        frame = 0;
                    }
                    else if(!frame && !protection)
                    {
                        texture(boomer_dir, 0, 43, 43, 43);
                        frame = 1;
                    }
                    run.restart();
                }
            }
            // Gora
            if(player_position_y < pos_y && pos_y - speed_y > 0 && pos_y - speed_y <= 210)
            {
                position(get_pos_x(), get_pos_y() - speed_y);
                if(run.getElapsedTime().asMilliseconds() > run_animation_time)
                {
                    if(direction == 1 && !protection)  // skierowany w prawo
                    {
                        if(frame)
                        {
                            texture(boomer_dir, 86, 0, 43, 43);
                            frame = 0;
                        }
                        else
                        {
                            texture(boomer_dir, 0, 43, 43, 43);
                            frame = 1;
                        }
                        run.restart();
                    }
                    else if(direction == 0 && !protection)  // skierowany w lewo
                    {
                        if(frame)
                        {
                            texture(boomer_dir, 86, 43, 43, 43);
                            frame = 0;
                        }
                        else
                        {
                            texture(boomer_dir, 0, 86, 43, 43);
                            frame = 1;
                        }
                        run.restart();
                    }
                }
            }
                // Dol
            else if(player_position_y > pos_y && pos_y + speed_y > 0 && pos_y + speed_y <= 210)
            {
                position(get_pos_x(), get_pos_y() + speed_y);
                if(run.getElapsedTime().asMilliseconds() > run_animation_time)
                {
                    if(direction == 1 && !protection)  // skierowany w prawo
                    {
                        if(frame )
                        {
                            texture(boomer_dir, 86, 0, 43, 43);
                            frame = 0;
                        }
                        else
                        {
                            texture(boomer_dir, 0, 43, 43, 43);
                            frame = 1;
                        }
                        run.restart();
                    }
                    else if(direction == 0 && !protection)  // skierowany w lewo
                    {
                        if(frame)
                        {
                            texture(boomer_dir, 86, 43, 43, 43);
                            frame = 0;
                        }
                        else
                        {
                            texture(boomer_dir, 0, 86, 43, 43);
                            frame = 1;
                        }
                        run.restart();
                    }
                }
            }
        }
        else // Jesli potwor sie nie porusza
        {
            if(direction != 2 && !protection && !detonate) // Potwor nie stal w miejscu
            {
                texture(boomer_dir, 0, 0, 43, 43);
                direction = 2;
                if(speed_x > 0)
                {
                    speed_x = 0;
                    speed_y = 0;
                }
            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

};

Boomer::Boomer()  // konstruktor powtorow
{
    texture(boomer_dir, 0, 0, 43, 43);  // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Zombie.png"
    wartosc = 1;
    zasieg = 150;
    size_x = 43;
    size_y = 43;
    name="boomer";

    // wielkosc hitboxa potwora
    hitbox.setSize(sf::Vector2f((size_x / 3.5), (size_y / 1.5) ));

    attack_damage = 10;
    spell_damage = 50;
    health = 100;
    base_speed = 0.02f;
    speed_x = 0;
    speed_y = 0;
}

// Potwor otrzymuje obrazenia
void Boomer::damaged()
{
    damage_ticks = 0;
    attacked.restart();
    protection = 1;
    speed_x = -0.02;
    speed_y = -0.02;
    if(direction == 0)
    {
        texture(boomer_dir, 86, 86, 43, 43);
    }
    else
    {
        texture(boomer_dir, 43, 86, 43, 43);
    }
}
// Potwor dropie monety
void Boomer::death(std::vector<pickups*> &pickups, int coin_chance, int key_chance)
{
    srand(time(NULL));
    int chance = rand()%100 + 1;
    if(chance <= coin_chance)
    {
        pickups.push_back(new coin(1, hitbox_pos_x+size_x/2,hitbox_pos_y+size_y/1.5 - 10));
    }
    else if(chance > 50 && chance < 50+key_chance)
    {
        pickups.push_back(new key(1, hitbox_pos_x+size_x/2,pos_y+size_y/1.5 - 6));
    }
}

void Boomer::attack_entity()
{
    if(!detonate)
    {
        detonate = 1;
        blow.restart();
        texture(boomer_dir, 0, 129, 43, 43);
    }

    if(blow.getElapsedTime().asMilliseconds() >= blow_time)
    {
        if(detonate!=2)
        {
            if(!detonation_phase)
            {
                texture(boomer_dir, 43, 129, 43, 43);
                detonation_phase=!detonation_phase;
                blow.restart();
                blow_time=blow_time-1.0;
            }
            else
            {
                texture(boomer_dir, 0, 129, 43, 43);
                detonation_phase=!detonation_phase;
                blow.restart();
                blow_time=blow_time-1.0;
            }
        }
        if(blow_time <= 0 && detonate!=2)
        {
            detonate = 2;

            position(hitbox_pos_x - size_x, hitbox_pos_y - size_y);
            entity.setSize(sf::Vector2f(size_x=size_x*2,size_y=size_y*2));

            hitbox.setPosition(sf::Vector2f(pos_x, pos_y));
            hitbox.setSize(sf::Vector2f(size_x,size_y));

            texture(boomer_dir, 86, 129, 43, 43);
            acceleration.restart();
        }
    }
}
#endif //PROJEKT_CPP_BOOMER_H

#endif // BOOMER_H_INCLUDED
