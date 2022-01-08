#ifndef GRIMM_H_INCLUDED
#define GRIMM_H_INCLUDED

#include "boss.h"
#include "pickups.h"

class grimm : public boss
{
private:
    //spell 1
    float zasieg1;
    float shoot_time = 0.5f;
    sf::Clock shoot_timer;

    //spell 2
    float zasieg2;
    float spell_speed = 0.1f;
    float spell_x;
    float spell_y;

    void boss_move(float player_position_x,float player_position_y);
public:
    grimm(int window_x);

    void boss_action(hero *Hero,std::vector<Bullet*> *bullets,int window_width,int window_height,int wall_size_x,int wall_size_y,std::vector<boss*> *Boss,std::vector<pickups *> &pickups,bool &boss_dead);
};

grimm::grimm(int window_x)
{
    health = 200;
    attack_damage = 30;
    spell_damage = 15;
    base_speed = 0.02f;
    zasieg1 = window_x/4;
    zasieg2 = window_x/4;

    size_x = 43;
    size_y = 43;

    hitbox.setSize(sf::Vector2f((size_x / 3.5), (size_y / 1.5) ));
    position(100, 100);

    spell_1cd = 5.0f;
    spell_2cd = 5.0f;

    spell_time1 = 5.0f;

    boss_dir = "Textures/Grimm.png"; //"/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/grimm.png"
    Texture.loadFromFile(boss_dir);
    Sprite.setTexture(&Texture);
    Sprite.setTextureRect(sf::IntRect(0, 0, 43, 43));
    Sprite.setSize(sf::Vector2f(43,43));
}

void grimm::boss_move(float player_position_x,float player_position_y)
{
    if(true)
        {
            // lewo
            if(player_position_x + 43/2 < hitbox_pos_x && (get_pos_x() - base_speed > player_position_x) && pos_x - base_speed > 0 && pos_x - base_speed <= 430)
            {
                position(get_pos_x() - base_speed, get_pos_y());
                if(direction != 0)
                {
                    run.restart();
                    direction = 0;
                    texture(boss_dir, 86, 86, 86, 86);
                }
                if(run.getElapsedTime().asMilliseconds() > run_animation_time)
                {
                    if(frame)
                    {
                        texture(boss_dir, 172, 86, 86, 86);
                        frame = 0;
                    }
                    else if(!frame)
                    {
                        texture(boss_dir, 0, 172, 86, 86);
                        frame = 1;
                    }
                    run.restart();
                }
            }

                // Prawo
            else if(player_position_x + 43/2 > hitbox_pos_x && (get_pos_x() + base_speed < player_position_x) && pos_x + base_speed > 0 && pos_x + base_speed <= 430)
            {
                position(get_pos_x() + base_speed, get_pos_y());
                if(direction != 1)
                {
                    run.restart();
                    direction = 1;  // skierowany w prawo
                    texture(boss_dir, 86, 0, 86, 86);
                }
                if(run.getElapsedTime().asMilliseconds() > run_animation_time)
                {
                    if(frame)
                    {
                        texture(boss_dir, 172, 0, 86, 86);
                        frame = 0;
                    }
                    else if(!frame)
                    {
                        texture(boss_dir, 86, 0, 86, 86);
                        frame = 1;
                    }
                    run.restart();
                }
            }
            // Gora
            if(player_position_y < pos_y && pos_y - base_speed > 0 && pos_y - base_speed <= 210)
            {
                position(get_pos_x(), get_pos_y() - base_speed);
                if(run.getElapsedTime().asMilliseconds() > run_animation_time)
                {
                    if(direction == 1)
                    {
                        if(frame)
                        {
                            texture(boss_dir, 172, 0, 86, 86);
                            frame = 0;
                        }
                        else if(!frame)
                        {
                            texture(boss_dir, 86, 0, 86, 86);
                            frame = 1;
                        }
                        run.restart();
                    }
                    else if(direction == 0)  // skierowany w lewo
                    {
                        if(frame)
                        {
                            texture(boss_dir, 172, 86, 86, 86);
                            frame = 0;
                        }
                        else if(!frame)
                        {
                            texture(boss_dir, 0, 172, 86, 86);
                            frame = 1;
                        }
                        run.restart();
                    }
                }
            }
                // Dol
            else if(player_position_y > pos_y && pos_y + base_speed > 0 && pos_y + base_speed <= 210)
            {
                position(get_pos_x(), get_pos_y() + base_speed);
                if(run.getElapsedTime().asMilliseconds() > run_animation_time)
                {
                    if(direction == 1)  // skierowany w prawo
                    {
                        if(frame)
                        {
                            texture(boss_dir, 172, 0, 86, 86);
                            frame = 0;
                        }
                        else if(!frame)
                        {
                            texture(boss_dir, 86, 0, 86, 86);
                            frame = 1;
                        }
                        run.restart();
                    }
                    else if(direction == 0)  // skierowany w lewo
                    {
                        if(frame)
                        {
                            texture(boss_dir, 172, 86, 86, 86);
                            frame = 0;
                        }
                        else if(!frame)
                        {
                            texture(boss_dir, 0, 172, 86, 86);
                            frame = 1;
                        }
                        run.restart();
                    }
                }
            }
        }

}

#endif // GRIMM_H_INCLUDED
