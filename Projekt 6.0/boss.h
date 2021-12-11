#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED

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
    float run_animation_time = 200.0f;
    int cast=0;
    ////////////////spells
    float spell_1cd;
    float spell_2cd;

    float spell_time1;
    float spell_time2;

    sf::Clock spell_time;
    sf::Clock spell_cd1;
    sf::Clock spell_cd2;
public:

    void set_health(int x) {health = x;}
    int get_health() {return health;}
    int get_attack_damage() {return attack_damage;}

    float get_pos_x() {return pos_x;}
    float get_pos_y() {return pos_y;}

    virtual void boss_action(hero *Hero, std::vector<Bullet*> *bullet,int window_width,int window_height,int wall_size_x,int wall_size_y,std::vector<boss*> *Boss) {};

    void position(float x, float y) {pos_x = x; pos_y = y; Sprite.setPosition(pos_x, pos_y); hitbox.setPosition(hitbox_pos_x = (pos_x - 2) + (size_x/2.5), hitbox_pos_y = pos_y + (size_y/6) );}
    void texture(std::string tekstura,int a,int b,int c,int d) {Texture.loadFromFile(tekstura);Sprite.setTexture(&Texture);Sprite.setTextureRect(sf::IntRect(a, b, c, d));};

    virtual void boss_move(float player_position_x,float player_position_y) {};

    void get_damaged(int x);

    friend class hollow_knight;

    sf::RectangleShape Sprite;
    sf::RectangleShape hitbox;
    sf::Texture Texture;
};

void boss::get_damaged(int x)
{
    health = health - x;
    protection = 1;
    attacked.restart();
}

#endif // BOSS_H_INCLUDED
