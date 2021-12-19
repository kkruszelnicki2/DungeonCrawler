#ifndef HERO_H
#define HERO_H
#include <iostream>
#include <SFML/Graphics.hpp>

class hero
{
private:
    //rozmiar
    float size_x = 43;
    float size_y = 43;
    std::string knight_dir = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Knight.png"; //  "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Knight.png"

    //statystyki
    int attack_damage = 100; //punkty ataku bohatera
    float max_health = 100;
    float health = 100; //zdrowie
    float speed = 0.05f; //predkosc

    //zmienne zwiazane z walka
    bool attack = 0; //czy w trakcie animacji ataku

    float attack_hitbox_pos_x;
    float attack_hitbox_pos_y;

    //zmienne zwiazane z poruszaniem
    float run_animation_time = 200.0f; //czas pomiedzy klatkami animacji chodzenia
    bool frame; //klatka animacji

    float pos_x; //pozycja x
    float pos_y; //pozycja y

    //zmienne zwiazane z przedmiotami
    int coin_amount = 0;
    int key_amount = 1;

    int coin_chance = 25;
    int key_chance = 25;

    int direction = 2; //skierowany do przodu (2), w prawo (1) czy w lewo (0)
public:
    hero();

    bool attacked = 0;

    sf::Texture entity_texture;
    sf::RectangleShape entity;
    sf::RectangleShape hitbox;  // Miejsce gdzie bohater otrzymuje obrazenia
    sf::RectangleShape attack_hitbox;  // Miejsce gdzie bohater zadaje obrazenia

    sf::Clock run;
    sf::Clock damaged_cd;

    float damaged_cooldown = 2.0f;

    float hitbox_pos_x; //pozycja x
    float hitbox_pos_y; //pozycja y

    // zczytuje konkretny fragment tekstury gracza
    void texture(std::string tekstura,int a,int b,int c,int d) {this->entity_texture.loadFromFile(tekstura);this->entity.setTexture(&this->entity_texture);this->entity.setTextureRect(sf::IntRect(a, b, c, d));};
    /////////////////////////////// GET/SET ///////////////////////////
    // pozycja
    float get_pos_x(){return this->pos_x;}
    float get_pos_y(){return this->pos_y;}

    // Pozycja hitboxa bohatera(otrzymywanie obrazen)
    void position(float x, float y) {this->pos_x = x; this->pos_y = y; this->entity.setPosition(pos_x, pos_y);hitbox.setPosition(hitbox_pos_x = pos_x + size_x / 3 + size_x / 40, hitbox_pos_y = pos_y + size_y / 7); }
    float get_sizex() {return this->size_x;}
    float get_sizey() {return this->size_y;}
    void set_direction(int x) {this->direction = x;}
    // zdrowie
    float get_health() {return this->health;};
    void set_health(int x) {health = health + x;};
    float get_max_health() {return this->max_health;};
    void set_max_health(int x) {max_health = max_health+x;};
    // szybkosc
    float get_speed(){return this->speed;};
    void set_speed(float x) {this->speed =speed + x;};
    // atak
    bool get_attack() {return this->attack;};
    int get_attack_damage() {return this->attack_damage;};
    void set_attack_damage(int x) {attack_damage = attack_damage + x;}
    // przedmioty
    void set_coinChance(int x) {coin_chance = coin_chance+x;}
    int get_coinChance() {return coin_chance;}

    void set_keyChance(int x) {key_chance = key_chance+x;}
    int get_keyChance() {return key_chance;}

    void set_coinAmount(int x) {coin_amount = coin_amount+x;}
    int get_coinAmount() {return coin_amount;}

    void set_keyAmount(int x) {key_amount = key_amount+x;}
    int get_keyAmount() {return key_amount;}
    /////////////////////////////// PORUSZANIE(funkcje) /////////////////////////////
    void move_left();
    void move_right();
    void move_up();
    void move_down();
    void idle();
    ////////////////////////////// ATAKI /////////////////////////
    void attack_end();
    void attack_left();
    void attack_right();
    void attack_up();
    void attack_down();
    void damaged(int damage);
};


hero::hero()
{
    texture(knight_dir, 0, 0, 43, 43);
    entity.setSize(sf::Vector2f(size_x, size_y));

    // Wielkosc hitboxa bohatera(obrazenia)
    hitbox.setSize(sf::Vector2f(size_x / 3 - size_x / 25, size_y - size_y / 3));
}
//////////////////////////////////////// PORUSZANIE BOHATERA///////////////////////////////////////////////
//lewo
void hero::move_left()
{
    position(get_pos_x() - get_speed(), get_pos_y());
    attack_hitbox.setPosition(attack_hitbox_pos_x = attack_hitbox_pos_x - get_speed(),attack_hitbox_pos_y);
    if(direction != 0 && !attack)
    {
        run.restart();
        direction = 0;
        texture(knight_dir, 86, 86, 43, 43);
    }
    if(!attack && run.getElapsedTime().asMilliseconds() > run_animation_time)
    {
        if(frame)
        {
            texture(knight_dir, 86, 86, 43, 43);
            frame = 0;
        }
        else
        {
            texture(knight_dir, 43, 86, 43, 43);
            frame = 1;
        }
        run.restart();
    }
}
//prawo
void hero::move_right()
{
    attack_hitbox.setPosition(attack_hitbox_pos_x = attack_hitbox_pos_x + get_speed(),attack_hitbox_pos_y);
    position(get_pos_x() + get_speed(), get_pos_y());
    if(direction != 1 && !attack)
    {
        run.restart();
        direction = 1;
        texture(knight_dir, 86, 0, 43, 43);
    }
    if(!attack && run.getElapsedTime().asMilliseconds() > run_animation_time)
    {
        if(frame)
        {
            texture(knight_dir, 86, 0, 43, 43);
            frame = 0;
        }
        else
        {
            texture(knight_dir, 129, 0, 43, 43);
            frame = 1;
        }
        run.restart();
    }
}
//gora
void hero::move_up()
{
    attack_hitbox.setPosition(attack_hitbox_pos_x,attack_hitbox_pos_y = attack_hitbox_pos_y - get_speed());
    position(get_pos_x(), get_pos_y() - get_speed());
    if(!attack && run.getElapsedTime().asMilliseconds() > run_animation_time)
    {
        if(direction == 1)
        {
            if(frame)
            {
                texture(knight_dir, 86, 0, 43, 43);
                frame = 0;
            }
            else
            {
                texture(knight_dir, 129, 0, 43, 43);
                frame = 1;
            }
            run.restart();
        }
        else
        {
            if(frame)
            {
                texture(knight_dir, 86, 86, 43, 43);
                frame = 0;
            }
            else
            {
                texture(knight_dir, 43, 86, 43, 43);
                frame = 1;
            }
            run.restart();
            direction = 0;
        }
    }
}
//dol
void hero::move_down()
{
    position(get_pos_x(), get_pos_y() + get_speed());
    attack_hitbox.setPosition(attack_hitbox_pos_x,attack_hitbox_pos_y = attack_hitbox_pos_y + get_speed());
    if(!attack && run.getElapsedTime().asMilliseconds() > run_animation_time)
    {
        if(direction == 1)
        {
            if(frame)
            {
                texture(knight_dir, 86, 0, 43, 43);
                frame = 0;
            }
            else
            {
                texture(knight_dir, 129, 0, 43, 43);
                frame = 1;
            }
            run.restart();
        }
        else
        {
            if(frame)
            {
                texture(knight_dir, 86, 86, 43, 43);
                frame = 0;
            }
            else
            {
                texture(knight_dir, 43, 86, 43, 43);
                frame = 1;
            }
            run.restart();
            direction = 0;
        }
    }
}
//w bezruchu
void hero::idle()
{
    if(direction != 2)
    {
        texture(knight_dir, 0, 0, 43, 43);
        direction = 2;
    }
}
////////////////////////////////////////// ATAKI BOHATERA///////////////////////////////////////////
//koniec animacji ataku
void hero::attack_end()
{
    if(direction == 1)
    {
        texture(knight_dir, 43, 0, 43, 43);
    }
    else
    {
        texture(knight_dir, 0, 86, 43, 43);
    }
    attack = 0;
}
//atak w lewo
void hero::attack_left()
{
    texture(knight_dir, 0, 129, 43, 43);
    attack = 1;
    // hitbox ataku bohatera(bohater atakuje)
    attack_hitbox_pos_x = get_pos_x();
    attack_hitbox_pos_y = get_pos_y() + size_y / 4;
    attack_hitbox.setSize(sf::Vector2f(size_x / 3 + size_x / 45, size_y / 3));
    attack_hitbox.setPosition(attack_hitbox_pos_x,attack_hitbox_pos_y);
}

void hero::attack_right()
{
    texture(knight_dir, 43, 43, 43, 43);
    attack = 1;
    // hitbox ataku bohatera(bohater atakuje)
    attack_hitbox_pos_x = get_pos_x() + size_x - size_x / 3;
    attack_hitbox_pos_y = get_pos_y() + size_y / 4 - size_y / 40;
    attack_hitbox.setSize(sf::Vector2f(size_x / 3 + size_x / 45, size_y / 3));
    attack_hitbox.setPosition(get_pos_x() + size_x - size_x / 3, get_pos_y() + size_y / 4 - size_y / 40);
}

void hero::attack_up()
{
    // gora, prawo
    if(direction == 1)
    {
        texture(knight_dir, 129, 43, 43, 43);
    }
        // gora, lewo
    else
    {
        texture(knight_dir, 86, 129, 43, 43);
    }
    attack = 1;
    // hitbox ataku bohatera(bohater atakuje)
    attack_hitbox_pos_x = get_pos_x() + size_x / 4;
    attack_hitbox_pos_y = get_pos_y();
    attack_hitbox.setSize(sf::Vector2f(size_x / 2 + size_x / 45, size_y / 3));
    attack_hitbox.setPosition(attack_hitbox_pos_x,attack_hitbox_pos_y);
}

void hero::attack_down()
{
    // dol, prawo
    if(direction == 1)
    {
        texture(knight_dir, 86, 43, 43, 43);
    }
        // dol, lewo
    else
    {
        texture(knight_dir, 43, 129, 43, 43);
    }
    attack = 1;
    // hitbox ataku bohatera(bohater atakuje)
    attack_hitbox_pos_x = get_pos_x() + size_x / 4 - size_x / 40;
    attack_hitbox_pos_y = get_pos_y() + size_y - size_y / 3;
    attack_hitbox.setSize(sf::Vector2f(size_x / 2 + size_x / 45, size_y / 3));
    attack_hitbox.setPosition(get_pos_x() + size_x / 4 - size_x / 40, get_pos_y() + size_y - size_y / 3);
}

void hero::damaged(int damage)
{
    if(damaged_cd.getElapsedTime().asSeconds() > damaged_cooldown)
    {
        health = health - damage;
        damaged_cd.restart();
        attacked = 1;
    }
}


#endif // HERO_H
