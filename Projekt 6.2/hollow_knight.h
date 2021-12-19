#ifndef HOLLOW_KNIGHT_H_INCLUDED
#define HOLLOW_KNIGHT_H_INCLUDED
#include "boss.h"
#include "pickups.h"

class hollow_knight : public boss
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
    hollow_knight(int window_x);

    void boss_action(hero *Hero,std::vector<Bullet*> *bullets,int window_width,int window_height,int wall_size_x,int wall_size_y,std::vector<boss*> *Boss,std::vector<pickups *> &pickups);
};

hollow_knight::hollow_knight(int window_x)
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

    boss_dir = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Hollow_knight.png"; // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Hollow_knight.png"
    Texture.loadFromFile(boss_dir);
    Sprite.setTexture(&Texture);
    Sprite.setTextureRect(sf::IntRect(0, 0, 43, 43));
    Sprite.setSize(sf::Vector2f(43,43));
}

void hollow_knight::boss_action(hero *Hero,std::vector<Bullet*> *bullets,int window_width,int window_height,int wall_size_x,int wall_size_y,std::vector<boss*> *Boss,std::vector<pickups*> &pickups)
{
    if(sqrt(pow(Hero->get_pos_x() - hitbox_pos_x,2)+pow(Hero->get_pos_y() - hitbox_pos_y,2) < pow(zasieg1,2)) && !cast && spell_cd1.getElapsedTime().asSeconds()>spell_1cd && cast==0)
    {
        cast=1;
        spell_time.restart();
        if(direction == 1)
        {
            texture(boss_dir, 43, 215, 43, 43);
        }
        else
        {
            texture(boss_dir, 86, 215, 43, 43);
        }
    }
    else if(sqrt(pow(Hero->get_pos_x() - hitbox_pos_x,2)+pow(Hero->get_pos_y() - hitbox_pos_y,2) > pow(zasieg2,2)) && !cast && spell_cd2.getElapsedTime().asSeconds()>spell_2cd && cast==0)
    {
        spell_x = (Hero->get_pos_x() - pos_x)/(sqrt(pow(Hero->get_pos_x() - pos_x,2) + pow(Hero->get_pos_y() - pos_y,2))) *spell_speed;
        spell_y = (Hero->get_pos_y() - pos_y)/(sqrt(pow(Hero->get_pos_x() - pos_x,2) + pow(Hero->get_pos_y() - pos_y,2))) *spell_speed;
        cast = 2;
        if(abs(Hero->get_pos_x() - pos_x) > abs(Hero->get_pos_y() - pos_y))
        {
            if(direction == 1)
            {
                texture(boss_dir, 86, 43, 43, 43);
            }
            else
            {
                texture(boss_dir, 0, 172, 43, 43);
            }
        }
        else
        {
            if(Hero->get_pos_y()>pos_y)
            {
                if(direction == 1)
                {
                    texture(boss_dir, 0, 86, 43, 43);
                }
                else
                {
                    texture(boss_dir, 43, 172, 43, 43);
                }
            }
            else
            {
                if(direction == 1)
                {
                    texture(boss_dir, 43, 86, 43, 43);
                }
                else
                {
                    texture(boss_dir, 86, 172, 43, 43);
                }
            }
        }
    }


    if(!cast)
    {
        boss_move(Hero->get_pos_x(),Hero->get_pos_y());
    }


    if(cast==1 && spell_time.getElapsedTime().asSeconds()<spell_time1)
    {
        if(shoot_timer.getElapsedTime().asSeconds() > shoot_time)
        {
            bullets->push_back(new Bullet(hitbox_pos_x + 5,hitbox_pos_y + 15,spell_damage,"/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Hollow_bullet.png",Hero->get_pos_x()+Hero->get_sizex()/2,Hero->get_pos_y()+Hero->get_sizey()/2));
            shoot_timer.restart();
        }
    }
    else if(cast==1)
    {
        cast = 0;
        spell_cd1.restart();
        spell_time.restart();
    }

    if(cast==2)
    {
        if( (pos_x + spell_x > wall_size_x) && (pos_x + spell_x < window_width - wall_size_x - size_x) && (pos_y + spell_y > wall_size_y) && (pos_y + spell_y < window_height - wall_size_y-size_y))
        {
            position(pos_x + spell_x, pos_y + spell_y);
        }
        else
        {
            cast = 0;
            spell_cd2.restart();
        }
    }

    if(protection && attacked.getElapsedTime().asSeconds()>protection_time)
    {
        protection = false;
    }

    if(Hero->attack_hitbox.getGlobalBounds().intersects(hitbox.getGlobalBounds()) && Hero->get_attack() && !protection)
    {
        get_damaged(Hero->get_attack_damage());
        if(health<=0)
        {
            Boss->clear();
            death(pickups,window_width,window_height);
        }
    }
}

void hollow_knight::boss_move(float player_position_x,float player_position_y)
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
                    texture(boss_dir, 86, 86, 43, 43);
                }
                if(run.getElapsedTime().asMilliseconds() > run_animation_time)
                {
                    if(frame)
                    {
                        texture(boss_dir, 0, 129, 43, 43);
                        frame = 0;
                    }
                    else if(!frame)
                    {
                        texture(boss_dir, 43, 129, 43, 43);
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
                    texture(boss_dir, 43, 0, 43, 43);
                }
                if(run.getElapsedTime().asMilliseconds() > run_animation_time)
                {
                    if(frame)
                    {
                        texture(boss_dir, 86, 0, 43, 43);
                        frame = 0;
                    }
                    else if(!frame)
                    {
                        texture(boss_dir, 0, 43, 43, 43);
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
                    if(direction == 1)  // skierowany w prawo
                    {
                        if(frame)
                        {
                            texture(boss_dir, 86, 0, 43, 43);
                            frame = 0;
                        }
                        else
                        {
                            texture(boss_dir, 0, 43, 43, 43);
                            frame = 1;
                        }
                        run.restart();
                    }
                    else if(direction == 0)  // skierowany w lewo
                    {
                        if(frame)
                        {
                            texture(boss_dir, 0, 129, 43, 43);
                            frame = 0;
                        }
                        else
                        {
                            texture(boss_dir, 43, 129, 43, 43);
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
                        if(frame )
                        {
                            texture(boss_dir, 86, 0, 43, 43);
                            frame = 0;
                        }
                        else
                        {
                            texture(boss_dir, 0, 43, 43, 43);
                            frame = 1;
                        }
                        run.restart();
                    }
                    else if(direction == 0)  // skierowany w lewo
                    {
                        if(frame)
                        {
                            texture(boss_dir, 0, 129, 43, 43);
                            frame = 0;
                        }
                        else
                        {
                            texture(boss_dir, 43, 129, 43, 43);
                            frame = 1;
                        }
                        run.restart();
                    }
                }
            }
        }

}

#endif // HOLLOW_KNIGHT_H_INCLUDED
