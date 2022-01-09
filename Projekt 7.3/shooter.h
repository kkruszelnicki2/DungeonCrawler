#ifndef SHOOTER_H_INCLUDED
#define SHOOTER_H_INCLUDED

#include <iostream>


class Shooter: public Entity
{
private:
    sf::Clock reload;
    float reload_time = 2;


public:
    Shooter();

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

    //zmienne zwiazane z poruszaniem
    float run_animation_time = 200.0f; //czas pomiedzy klatkami animacji
    bool frame; //klatka animacji

    void attack_entity() {};

    //////////////////////////////////// PORUSZANIE POTWOROW///////////////////////////////////////////////
    void move_entity(float player_position_x,float player_position_y)
    {
        if(sqrt(pow(player_position_x - hitbox_pos_x,2)+pow(player_position_y - hitbox_pos_y,2) > pow(zasieg,2)) || (protection && speed_x<=0) )
        {
            if(speed_x < base_speed && acceleration.getElapsedTime().asMilliseconds() > 50)
            {
                speed_x = speed_x + 0.001;
                speed_y = speed_y + 0.001;
                acceleration.restart();
            }
            // Lewo
            if(player_position_x + 43/2 < hitbox_pos_x && (get_pos_x() - speed_x > player_position_x) && pos_x - speed_x > 0 && pos_x - speed_x <= 430)
            {
                position(get_pos_x() - speed_x, get_pos_y());
                if(direction != 0 && !protection)
                {
                    run.restart();
                    direction = 0;
                    texture(shooter_dir, 43, 43, 43, 43);
                }
                if(run.getElapsedTime().asMilliseconds() > run_animation_time)
                {
                    if(frame && !protection)
                    {
                        if(reload.getElapsedTime().asSeconds()>reload_time)
                        {
                            texture(shooter_dir, 0, 172,43,43);
                        }
                        else
                        {
                            texture(shooter_dir, 86, 43, 43, 43);
                        }
                        frame = 0;
                    }
                    else if(!frame && !protection)
                    {
                        if(reload.getElapsedTime().asSeconds()>reload_time)
                        {
                            texture(shooter_dir,86,129,43,43);
                        }
                        else
                        {
                            texture(shooter_dir, 0, 86, 43, 43);
                        }
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
                    texture(shooter_dir, 43, 0, 43, 43);
                }
                if(run.getElapsedTime().asMilliseconds() > run_animation_time)
                {
                    if(frame && !protection)
                    {
                        if(reload.getElapsedTime().asSeconds()>reload_time)
                        {
                            texture(shooter_dir, 0, 129,43,43);
                        }
                        else
                        {
                            texture(shooter_dir, 86, 0, 43, 43);
                        }
                        frame = 0;
                    }
                    else if(!frame && !protection)
                    {
                        if(reload.getElapsedTime().asSeconds()>reload_time)
                        {
                            texture(shooter_dir, 43, 129,43,43);
                        }
                        else
                        {
                            texture(shooter_dir, 0, 43, 43, 43);
                        }
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
                            if(reload.getElapsedTime().asSeconds()>reload_time)
                            {
                                texture(shooter_dir, 0, 129,43,43);
                            }
                            else
                            {
                                texture(shooter_dir, 86, 0, 43, 43);
                            }
                            frame = 0;
                        }
                        else
                        {
                            if(reload.getElapsedTime().asSeconds()>reload_time)
                            {
                                texture(shooter_dir, 43, 129,43,43);
                            }
                            else
                            {
                                texture(shooter_dir, 0, 43, 43, 43);
                            }
                            frame = 1;
                        }
                        run.restart();
                    }
                    else if(direction == 0 && !protection)  // skierowany w lewo
                    {
                        if(frame)
                        {
                            if(reload.getElapsedTime().asSeconds()>reload_time)
                            {
                                texture(shooter_dir, 0, 172,43,43);
                            }
                            else
                            {
                                texture(shooter_dir, 86, 43, 43, 43);
                            }
                            frame = 0;
                        }
                        else
                        {
                            if(reload.getElapsedTime().asSeconds()>reload_time)
                            {
                                texture(shooter_dir,86,129,43,43);
                            }
                            else
                            {
                                texture(shooter_dir, 0, 86, 43, 43);
                            }
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
                            if(reload.getElapsedTime().asSeconds()>reload_time)
                            {
                                texture(shooter_dir, 0, 129,43,43);
                            }
                            else
                            {
                                texture(shooter_dir, 86, 0, 43, 43);
                            }
                            frame = 0;
                        }
                        else
                        {
                            if(reload.getElapsedTime().asSeconds()>reload_time)
                            {
                                texture(shooter_dir, 43, 129,43,43);
                            }
                            else
                            {
                                texture(shooter_dir, 0, 43, 43, 43);
                            }
                            frame = 1;
                        }
                        run.restart();
                    }
                    else if(direction == 0 && !protection)  // skierowany w lewo
                    {
                        if(frame)
                        {
                            if(reload.getElapsedTime().asSeconds()>reload_time)
                            {
                                texture(shooter_dir, 0, 172,43,43);
                            }
                            else
                            {
                                texture(shooter_dir, 86, 43, 43, 43);
                            }
                            frame = 0;
                        }
                        else
                        {
                            if(reload.getElapsedTime().asSeconds()>reload_time)
                            {
                                texture(shooter_dir,86,129,43,43);
                            }
                            else
                            {
                                texture(shooter_dir, 0, 86, 43, 43);
                            }
                            frame = 1;
                        }
                        run.restart();
                    }
                }
            }
        }
        else // Jesli potwor sie nie porusza
        {
            if(direction != 2 && !protection) // Potwor nie stal w miejscu
            {
                if(direction == 0)
                {
                    texture(shooter_dir,86,173,43,43);
                }
                else
                {
                    texture(shooter_dir,43,173,43,43);
                }
                direction = 2;
                if(speed_x > 0)
                {
                    speed_x = 0;
                    speed_y = 0;
                }
            }

            if(reload.getElapsedTime().asSeconds()>reload_time)
            {
                detonate = true;
                reload.restart();
            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};

Shooter::Shooter()  // konstruktor powtorow
{
    texture(shooter_dir, 0, 0, 43, 43);  // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Zombie.png"
    wartosc = 1;
    zasieg = 100;
    size_x = 43;
    size_y = 43;
    name="shooter";

    // wielkosc hitboxa potwora
    hitbox.setSize(sf::Vector2f((size_x / 3.5), (size_y / 1.5) ));
    hitbox.setFillColor(sf::Color::Red);

    attack_damage = 10;
    spell_damage = 20;
    health = 100;
    base_speed = 0.02f;
    speed_x = 0;
    speed_y = 0;
}

// Potwor otrzymuje obrazenia
void Shooter::damaged()
{
    damage_ticks = 0;
    attacked.restart();
    protection = 1;
    speed_x = -0.02;
    speed_y = -0.02;
    if(direction == 0)
    {
        texture(shooter_dir, 86, 86, 43, 43);
    }
    else
    {
        texture(shooter_dir, 43, 86, 43, 43);
    }
}
// Potwor dropie monety
void Shooter::death(std::vector<pickups*> &pickups, int coin_chance, int key_chance)
{
    srand(time(NULL));
    int chance = rand()%100 + 1;
    if(chance <= coin_chance)
    {
        pickups.push_back(new coin(hitbox_pos_x,hitbox_pos_y+size_y/1.5 - 10));
    }
    else if(chance > 50 && chance < 50+key_chance)
    {
        pickups.push_back(new key(hitbox_pos_x,pos_y+size_y/1.5 - 6));
    }
}


#endif // SHOOTER_H_INCLUDED
