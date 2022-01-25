#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED

#include "bullet.h"
#include "items.h"
#include "grimmchild.h"
#include "audio.h"

extern const int window_width;
extern const int window_height;

class boss
{
private:
    std::string boss_dir;
    ///////////////////// otrzymywanie obrazen
    bool protection = 0;
    sf::Clock attacked;
    float protection_time = 1.0f;
    /////////////////////statystyki
    int health;
    float base_speed;
    float speed_x;
    float speed_y;
    int attack_damage;
    int spell_damage;
    ///////////////////////pozycja
    float pos_x;
    float pos_y;

    float hitbox_pos_x; //pozycja x
    float hitbox_pos_y; //pozycja y

    int size_x;
    int size_y;
    /////////////////zmienne zwiazane z poruszaniem
    int direction = 2;
    bool frame;
    sf::Clock run;
    int cast=0;
    ////////////////spells
    float spell_1cd;
    float spell_2cd;

    float spell_time1;
    float spell_time2;

    sf::Clock spell_time;
    sf::Clock spell_cd1;
    sf::Clock spell_cd2;
    sf::Clock acceleration;
public:
    std::string boss_name;
    int damage_ticks;
    void set_health(int x) {health = x;}
    int get_health() {return health;}
    int get_attack_damage() {return attack_damage;}

    float get_pos_x() {return pos_x;}
    float get_pos_y() {return pos_y;}

    virtual void boss_action(hero *Hero, std::vector<Bullet*> *bullet,int wall_size_x,int wall_size_y,std::vector<boss*> *Boss,std::vector<pickups*> &pickup,bool &boss_dead, std::vector<Entity*> &monsters, Audio *audio) {};

    void position(float x, float y) {pos_x = x; pos_y = y; Sprite.setPosition(pos_x, pos_y); hitbox.setPosition(hitbox_pos_x = (pos_x - 2) + (size_x/2.5), hitbox_pos_y = pos_y + (size_y/6) );}
    void texture(std::string tekstura,int a,int b,int c,int d) {Texture.loadFromFile(tekstura);Sprite.setTexture(&Texture);Sprite.setTextureRect(sf::IntRect(a, b, c, d));};

    virtual void boss_move(float player_position_x,float player_position_y) {};

    void damaged(int x);
    void death(std::vector<pickups*> &pickup);

    friend class hollow_knight;
    friend class grimm;

    sf::RectangleShape Sprite;
    sf::RectangleShape hitbox;
    sf::Texture Texture;
};

void boss::damaged(int x)
{
    health = health - x;
    protection = 1;
    attacked.restart();
}

void boss::death(std::vector<pickups*> &pickups)
{
    pickups.push_back(new mask_attack_damage);
    pickups[0]->pickup.setPosition(window_width/2,window_height/4);
}
#endif // BOSS_H_INCLUDED
