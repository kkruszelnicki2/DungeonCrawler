#ifndef MONSTERS_H_INCLUDED
#define MONSTERS_H_INCLUDED
#include <string>
#include <cmath>
#include <vector>
#include <time.h>

#include "pickups.h"

// klasa bazowa dla wszystkich postaci


class Entity{
private:
    std::string zombie_dir = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Zombie.png";

    int direction = 2; //skierowany do przodu (2), w prawo (1) czy w lewo (0)

    bool protection = 0;

    int health;
    float speed;
    float base_speed;
    int attack_damage;

    float pos_x;
    float pos_y;
    float zasieg;
public:

    Entity() {};

    float hitbox_pos_x; //pozycja x
    float hitbox_pos_y; //pozycja y

    int size_x;
    int size_y;

    sf::Clock run;


    //zmienne zwiazane z poruszaniem
    float run_animation_time = 200.0f; //czas pomiedzy klatkami animacji
    bool frame; //klatka animacji

    int wartosc;
    bool damage = 0;
    int damage_ticks;

    int id;

    virtual void texture(std::string tekstura,int a,int b,int c,int d) {};

    virtual void position(float x, float y) = 0;
    virtual float get_pos_x() = 0;
    virtual float get_pos_y() = 0;

    virtual float get_speed() = 0;
    virtual void set_speed(float speed) = 0;
    virtual float get_base_speed() = 0;

    virtual void move_entity(float x,float y) = 0;

    virtual int get_attack_damage() = 0;

    virtual void set_health(int x) = 0;
    virtual int get_health() = 0;

    virtual void set_protection(bool x) = 0;
    virtual bool get_protection() = 0;
    virtual void damaged() = 0;
    virtual void death(std::vector<pickups*> &pickups, int coin_chance, int key_chance) = 0;

    friend class Player;
    friend class Zombie;

    sf::Texture entity_texture;
    sf::RectangleShape entity;
    sf::RectangleShape hitbox;
    sf::RectangleShape simulation;
    sf::Clock attacked;
};

//klasa zombie
class Zombie: public Entity
{
private:

public:
    Zombie();

    int direction = 2; //skierowany do przodu (2), w prawo (1) czy w lewo (0)
    // Sprawdzenie w ktora strone porusza sie potwor
    void get_direction(){return; this->direction;}

    void texture(std::string tekstura,int a,int b,int c,int d) {this->entity_texture.loadFromFile(tekstura);this->entity.setTexture(&this->entity_texture);this->entity.setTextureRect(sf::IntRect(a, b, c, d));};

    // Pozycja hitboxa/potwora(kolor czerwony)
    void position(float x, float y) {this->pos_x = x; this->pos_y = y; this->entity.setPosition(pos_x, pos_y); hitbox.setPosition(hitbox_pos_x = (pos_x - 2) + (size_x/2.5), hitbox_pos_y = pos_y + (size_y/6) );}  // kolor czerwony

    float get_pos_x(){return this->pos_x;}
    float get_pos_y(){return this->pos_y;}

    float get_speed() {return this->speed;}
    void set_speed(float speed) {this->speed = speed;}
    float get_base_speed() {return this->base_speed;}

    int get_attack_damage() {return this->attack_damage;}

    void set_protection(bool x) {this->protection=x;}
    bool get_protection() {return this->protection;}
    void damaged();
    void death(std::vector<pickups*> &pickups, int coin_chance, int key_chance);

    void set_health(int x) {this->health = this->health-x;}
    int get_health() {return this->health;};

    //zmienne zwiazane z poruszaniem
    float run_animation_time = 200.0f; //czas pomiedzy klatkami animacji
    bool frame; //klatka animacji

    //////////////////////////////////// PORUSZANIE POTWORÓW///////////////////////////////////////////////
    void move_entity(float player_position_x,float player_position_y)
    {
        if(sqrt(pow(player_position_x - hitbox_pos_x,2)+pow(player_position_y - hitbox_pos_y,2) < pow(zasieg,2)))
        {
            // lewo
            if(player_position_x + 43/2 < this->hitbox_pos_x && (get_pos_x() - get_speed() > player_position_x))
            {
                position(get_pos_x() - get_speed(), get_pos_y());
                if(direction != 0 && !protection)
                {
                    run.restart();
                    direction = 0;
                    texture(zombie_dir, 43, 43, 43, 43);
                }
                if(run.getElapsedTime().asMilliseconds() > run_animation_time)
                {
                    if(frame && !protection)
                    {
                        texture(zombie_dir, 86, 43, 43, 43);
                        frame = 0;
                    }
                    else if(!frame && !protection)
                    {
                        texture(zombie_dir, 0, 86, 43, 43);
                        frame = 1;
                    }
                    run.restart();
                }
            }

            // Prawo
            else if(player_position_x + 43/2 > this->hitbox_pos_x && (get_pos_x() + get_speed() < player_position_x))
            {
                position(get_pos_x() + get_speed(), get_pos_y());
                if(direction != 1 && !protection)
                {
                    run.restart();
                    direction = 1;  // skierowany w prawo
                    texture(zombie_dir, 43, 0, 43, 43);
                }
                if(run.getElapsedTime().asMilliseconds() > run_animation_time)
                {
                    if(frame && !protection)
                    {
                        texture(zombie_dir, 86, 0, 43, 43);
                        frame = 0;
                    }
                    else if(!frame && !protection)
                    {
                        texture(zombie_dir, 0, 43, 43, 43);
                        frame = 1;
                    }
                    run.restart();
                }
            }
            // Gora
            if(player_position_y + 43/2 < this->pos_y)
            {
                position(get_pos_x(), get_pos_y() - get_speed());
                if(run.getElapsedTime().asMilliseconds() > run_animation_time)
                {
                    if(direction == 1 && !protection)  // skierowany w prawo
                    {
                        if(frame)
                        {
                            texture(zombie_dir, 86, 0, 43, 43);
                            frame = 0;
                        }
                        else
                        {
                            texture(zombie_dir, 0, 43, 43, 43);
                            frame = 1;
                        }
                        run.restart();
                    }
                    else if(direction == 0 && !protection)  // skierowany w lewo
                    {
                        if(frame)
                        {
                            texture(zombie_dir, 86, 43, 43, 43);
                            frame = 0;
                        }
                        else
                        {
                            texture(zombie_dir, 0, 86, 43, 43);
                            frame = 1;
                        }
                        run.restart();
                    }
                }
            }
            // Dol
            else if(player_position_y + 43/2 > this->pos_y)
            {
                position(get_pos_x(), get_pos_y() + get_speed());
                if(run.getElapsedTime().asMilliseconds() > run_animation_time)
                {
                    if(direction == 1 && !protection)  // skierowany w prawo
                    {
                        if(frame )
                        {
                            texture(zombie_dir, 86, 0, 43, 43);
                            frame = 0;
                        }
                        else
                        {
                            texture(zombie_dir, 0, 43, 43, 43);
                            frame = 1;
                        }
                        run.restart();
                    }
                    else if(direction == 0 && !protection)  // skierowany w lewo
                    {
                        if(frame)
                        {
                            texture(zombie_dir, 86, 43, 43, 43);
                            frame = 0;
                        }
                        else
                        {
                            texture(zombie_dir, 0, 86, 43, 43);
                            frame = 1;
                        }
                        run.restart();
                    }
                }
            }
            this->position(this->pos_x, this->pos_y);
        }
        else // Jesli potwor sie nie porusza
        {
            if(direction != 2 && !protection) // Potwor nie stal w miejscu
            {
                texture(zombie_dir, 0, 0, 43, 43);
                direction = 2;
            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};

Zombie::Zombie()  // konstruktor powtorow
{
    texture(zombie_dir, 0, 0, 43, 43);  // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Zombie.png"
    wartosc = 1;
    zasieg = 150;
    size_x = 43;
    size_y = 43;

    // wielkosc hitboxa potwora
    hitbox.setSize(sf::Vector2f((size_x / 3.5), (size_y / 1.5) ));
    hitbox.setFillColor(sf::Color::Red);

    attack_damage = 20;
    health = 100;
    speed = 0.02f;
    base_speed = 0.02f;
}

// Potwor otrzymuje obrazenia
void Zombie::damaged()
{
    this->damage_ticks = 0;
    this->attacked.restart();
    this->damage = 1;
    this->speed = -0.02f;
    if(direction == 0)
    {
        texture(zombie_dir, 86, 86, 43, 43);
    }
    else
    {
        texture(zombie_dir, 43, 86, 43, 43);
    }
}
// Potwor dropie monety
void Zombie::death(std::vector<pickups*> &pickups, int coin_chance, int key_chance)
{
    srand(time(NULL));
    int chance = rand()%100 + 1;
    if(chance <= coin_chance)
    {
        pickups.push_back(new coin(1, pos_x,pos_y));
    }
    else if(chance > 50 && chance < 50+key_chance)
    {
        pickups.push_back(new key(1, pos_x,pos_y));
    }
}


#endif // MONSTERS_H_INCLUDED
