#ifndef PICKUPS_H_INCLUDED
#define PICKUPS_H_INCLUDED

#include "hero.h"

class pickups
{
private:
    // Wymiary tekstur: coin(15x15 px), key(12x28 px)
    std::string  coin_dir = "Textures/Coin.png"; //"/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Coin.png"
    std::string  key_dir = "Textures/Key.png"; //"/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Key.png"
    std::string  healthPotion_dir = "Textures/Potion.png"; //"/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Potion.png"
    std::string  mask_dir = "Textures/Mask.png"; //"/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Mask.png"
    int worth = 0;
    std::string name;

    float pos_x;
    float pos_y;
public:
    int get_worth() {return worth;};
    void set_worth(int x) {worth=x;};

    virtual std::string get_name() {return name;};

    virtual void pick(hero *Hero) {};

    friend class coin;
    friend class key;
    friend class health_potion;

    friend class mask_health;
    friend class mask_attack_damage;
    friend class mask_speed;

    sf::RectangleShape pickup;
    sf::Texture pickup_texture;
};

class coin : public pickups
{
public:
    coin(float x,float y);

    int get_worth() {return worth;}
    void set_worth(int x) {worth = x;}

    void pick(hero *Hero);

    std::string get_name() {return name;}
};

coin::coin(float x,float y)
{
    name = "coin";
    pos_x = x;
    pos_y = y;
    pickup_texture.loadFromFile(coin_dir);  // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Coin.png"
    pickup.setTexture(&pickup_texture);
    pickup.setTextureRect(sf::IntRect(0, 0, 15, 15));
    pickup.setPosition(pos_x, pos_y);
    pickup.setSize(sf::Vector2f(10,10));
}

void coin::pick(hero *Hero)
{
    Hero->set_coinAmount(1);
}

class key : public pickups
{
public:
    key(float x,float y);

    int get_worth() {return worth;}
    void set_worth(int x) {worth = x;}

    void pick(hero *Hero);

    std::string get_name() {return name;}
};

key::key(float x,float y)
{
    name = "key";
    pos_x = x;
    pos_y = y;
    pickup_texture.loadFromFile(key_dir);
    pickup.setTexture(&pickup_texture);
    pickup.setTextureRect(sf::IntRect(0, 0, 28, 12));
    pickup.setPosition(pos_x, pos_y);
    pickup.setSize(sf::Vector2f(14,6));  // klucze pomniejszone 2x
}

void key::pick(hero *Hero)
{
    Hero->set_keyAmount(1);
}

class health_potion : public pickups
{
public:
    health_potion(float x,float y);

    int get_worth() {return worth;}
    void set_worth(int x) {worth = x;}

    void pick(hero *Hero);

    std::string get_name() {return name;}
};

health_potion::health_potion(float x,float y)
{
    name = "health_potion";
    pos_x = x;
    pos_y = y;
    pickup_texture.loadFromFile(healthPotion_dir);
    pickup.setTexture(&pickup_texture);
    pickup.setTextureRect(sf::IntRect(0, 0, 15, 20));
    pickup.setPosition(pos_x, pos_y);
    pickup.setSize(sf::Vector2f(9,12));  // klucze pomniejszone 2x
}

void health_potion::pick(hero *Hero)
{
    Hero->set_health(50);
}

#endif // PICKUPS_H_INCLUDED
