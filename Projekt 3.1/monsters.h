#ifndef MONSTERS_H_INCLUDED
#define MONSTERS_H_INCLUDED
#include <string>

// klasa bazowa dla wszystkich postaci
class Entity {

    float speed;
    float pos_x;
    float pos_y;
public:
    Entity() {};
    int size;
    virtual void texture(std::string tekstura,int a,int b,int c,int d) {};

    virtual void position(float x, float y) {};
    float get_pos_x() {};
    float get_pos_y() {};

    virtual float get_speed() {};
    virtual void set_speed(float speed) {};

    virtual void move_entity(float x,float y) {};

    friend class Player;
    friend class Zombie;

    sf::Texture entity_texture;
    sf::RectangleShape entity;
};

//klasa zombie
class Zombie: public Entity
{
public:
    Zombie() {this->speed = 0.02f; this->size = 43; this->texture("Textures/Zombie.png",0,0,43,43);};

    void texture(std::string tekstura,int a,int b,int c,int d) {this->entity_texture.loadFromFile(tekstura);this->entity.setTexture(&this->entity_texture);this->entity.setTextureRect(sf::IntRect(a, b, c, d));};
    void position(float x, float y) {this->pos_x = x; this->pos_y = y; this->entity.setPosition(pos_x, pos_y);}
    float get_pos_x(){return this->pos_x;}
    float get_pos_y(){return this->pos_y;}
    float get_speed() {return this->speed;}
    void set_speed(float speed) {this->speed = speed;}
    void move_entity(float player_position_x,float player_position_y)
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
    }
};

#endif // MONSTERS_H_INCLUDED
