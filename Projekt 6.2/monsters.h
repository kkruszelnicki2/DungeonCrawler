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
    std::string zombie_dir = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Zombie.png";   // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Zombie.png"
    std::string boomer_dir = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Boomer.png";   // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Boomer.png"
    std::string shooter_dir = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Shooter.png"; // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Shooter.png"

    int direction = 2; //skierowany do przodu (2), w prawo (1) czy w lewo (0)

    bool protection = 0;

    int health;
    float base_speed;
    float speed_x;
    float speed_y;
    int attack_damage;
    int spell_damage;

    float pos_x;
    float pos_y;
    float zasieg;
public:

    Entity() {};

    std::string name;

    float hitbox_pos_x; //pozycja x
    float hitbox_pos_y; //pozycja y

    int size_x;
    int size_y;

    sf::Clock run;
    sf::Clock acceleration;

    //zmienne dla boomera
    int detonate = 0;
    bool detonation_phase=0;

    //zmienne zwiazane z poruszaniem
    float run_animation_time = 200.0f; //czas pomiedzy klatkami animacji
    bool frame; //klatka animacji

    int wartosc;
    int damage_ticks;

    int id;

    virtual void texture(std::string tekstura,int a,int b,int c,int d) = 0;

    virtual void position(float x, float y) = 0;
    virtual float get_pos_x() = 0;
    virtual float get_pos_y() = 0;

    virtual void set_speed_x(float speed) = 0;
    virtual void set_speed_y(float speed) = 0;

    virtual float get_speed_x() = 0;
    virtual float get_speed_y() = 0;
    virtual float get_base_speed() = 0;

    virtual void move_entity(float x,float y) = 0;

    virtual int get_attack_damage() = 0;
    virtual int get_spell_damage() = 0;

    virtual void set_health(int x) = 0;
    virtual int get_health() = 0;

    virtual void set_protection(bool x) = 0;
    virtual bool get_protection() = 0;
    virtual void damaged() = 0;
    virtual void death(std::vector<pickups*> &pickups, int coin_chance, int key_chance) = 0;

    virtual void attack_entity() = 0;


    friend class Zombie;
    friend class Boomer;
    friend class Shooter;

    sf::Texture entity_texture;
    sf::RectangleShape entity;
    sf::RectangleShape hitbox;
    sf::RectangleShape simulation;
    sf::Clock attacked;
};




#endif // MONSTERS_H_INCLUDED
