#ifndef MONSTERS_H_INCLUDED
#define MONSTERS_H_INCLUDED
#include <string>
#include <cmath>
#include <vector>

// klasa bazowa dla wszystkich postaci
class Entity {

    bool protection=0;
    int health;
    float speed;
    float pos_x;
    float pos_y;
    int attack_damage;
    float zasieg;
public:
    Entity() {};
    int sizex;
    int sizey;

    int wartosc;

    virtual void texture(std::string tekstura,int a,int b,int c,int d) {};

    virtual void position(float x, float y) = 0;
    virtual float get_pos_x() = 0;
    virtual float get_pos_y() = 0;

    virtual float get_speed() = 0;
    virtual void set_speed(float speed) = 0;

    virtual void move_entity(float x,float y) = 0;

    virtual int get_attack_damage() = 0;

    virtual void set_health(int x) = 0;
    virtual int get_health() = 0;

    virtual void set_protection(bool x) = 0;
    virtual bool get_protection() = 0;

    friend class Player;
    friend class Zombie;

    sf::Texture entity_texture;
    sf::RectangleShape entity;
    sf::RectangleShape simulation;
};

//klasa zombie
class Zombie: public Entity
{
public:
    Zombie();

    void texture(std::string tekstura,int a,int b,int c,int d) {this->entity_texture.loadFromFile(tekstura);this->entity.setTexture(&this->entity_texture);this->entity.setTextureRect(sf::IntRect(a, b, c, d));};
    void position(float x, float y) {this->pos_x = x; this->pos_y = y; this->entity.setPosition(pos_x, pos_y);}

    float get_pos_x(){return this->pos_x;}
    float get_pos_y(){return this->pos_y;}

    float get_speed() {return this->speed;}
    void set_speed(float speed) {this->speed = speed;}

    int get_attack_damage() {return this->attack_damage;}

    void set_protection(bool x) {this->protection=x;}
    bool get_protection() {return this->protection;}

    void set_health(int x) {this->health=this->health-x;}
    int get_health() {return this->health;};

    void move_entity(float player_position_x,float player_position_y)
    {
        if(sqrt(pow(player_position_x-pos_x,2)+pow(player_position_y-pos_y,2)<pow(zasieg,2)))
        {
            if(player_position_x < this->pos_x)
            {
                this->pos_x = this->pos_x - this->speed;
            }
            else
            {
                this->pos_x = this->pos_x + this->speed;
            }

            if(player_position_y < this->pos_y)
            {
                this->pos_y = this->pos_y - this->speed;
            }
            else
            {
                this->pos_y = this->pos_y + this->speed;
            }
            this->position(this->pos_x,this->pos_y);
            this->simulation.setPosition(this->pos_x,this->pos_y);
        }
    }
};

Zombie::Zombie()
{
    wartosc=1;
    zasieg = 100;
    sizex = 183/9;
    sizey = 224/9;
    texture("Textures/Zombie.png",39,9,183,224);

    attack_damage=20;
    health=100;
    speed = 0.02f;

    simulation.setSize(sf::Vector2f(sizex,sizey));
}

#endif // MONSTERS_H_INCLUDED
