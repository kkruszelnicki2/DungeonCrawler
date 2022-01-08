#ifndef ITEMS_H_INCLUDED
#define ITEMS_H_INCLUDED

#include <iostream>

//////////////////////////////////MASKA NA ZDROWIE//////////////////////////////////
class mask_health: public pickups
{
    private:
        int health = 20;
    public:
        mask_health();
        void pick(hero *Hero);

};

mask_health::mask_health()
{
    name = "mask_health";
    pickup_texture.loadFromFile(mask_dir);  // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Coin.png"
    pickup.setTexture(&pickup_texture);
    pickup.setTextureRect(sf::IntRect(0, 0, 15, 17));
    pickup.setSize(sf::Vector2f(15,17));
}

void mask_health::pick(hero *Hero)
{
    Hero->set_health(health);
    Hero->set_max_health(health);
}

////////////////////////////////MASKA NA ATAK//////////////////////////////////////

class mask_attack_damage: public pickups
{
    private:
        int attack = 20;
    public:
        mask_attack_damage();
        void pick(hero *Hero);

};

mask_attack_damage::mask_attack_damage()
{
    name = "mask_attack_damage";
    pickup_texture.loadFromFile(mask_dir);  // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Coin.png"
    pickup.setTexture(&pickup_texture);
    pickup.setTextureRect(sf::IntRect(45, 0, 15, 17));
    pickup.setSize(sf::Vector2f(15,17));
}

void mask_attack_damage::pick(hero *Hero)
{
    Hero->set_attack_damage(attack);
}

////////////////////////////////MASKA NA SZYBKOSC//////////////////////////////////////

class mask_speed: public pickups
{
    private:
        float speed = 0.01f;
    public:
        mask_speed();
        void pick(hero *Hero);

};

mask_speed::mask_speed()
{
    name = "mask_speed";
    pickup_texture.loadFromFile(mask_dir);  // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Coin.png"
    pickup.setTexture(&pickup_texture);
    pickup.setTextureRect(sf::IntRect(15, 0, 15, 17));
    pickup.setSize(sf::Vector2f(15,17));
}

void mask_speed::pick(hero *Hero)
{
    if(Hero->get_coinAmount()>=worth)
    {
        Hero->set_coinAmount(-worth);
        Hero->set_speed(speed);
    }
}


#endif // ITEMS_H_INCLUDED
