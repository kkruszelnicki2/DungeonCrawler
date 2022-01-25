#ifndef HOLLOW_KNIGHT_H_INCLUDED
#define HOLLOW_KNIGHT_H_INCLUDED

#include "boss.h"
#include "pickups.h"
#include "audio.h"

extern const int window_width;
extern const int window_height;


class hollow_knight : public boss
{
private:
    //spell 1(Dash)
    float zasieg1;
    float shoot_time = 0.5f;
    sf::Clock shoot_timer;

    //spell 2(Bullet)
    float zasieg2;
    float spell_speed = 0.3f;
    float spell_x;
    float spell_y;

    float run_animation_time = 200.0f;

    void boss_move(float player_position_x,float player_position_y);
public:
    hollow_knight();
    static int base_attack;
    static int base_spell_attack;
    static int base_health;

    void boss_action(hero *Hero,std::vector<Bullet*> *bullets,int wall_size_x,int wall_size_y,std::vector<boss*> *Boss,std::vector<pickups *> &pickups,bool &boss_dead, std::vector<Entity*> &monsters, Audio *audio);
};

hollow_knight::hollow_knight()
{
    boss_name = "Hollow Knight";

    health = base_health;
    attack_damage = base_attack;
    spell_damage = base_spell_attack;
    base_speed = 0.05f;
    zasieg1 = window_width/4;
    zasieg2 = window_width/4;

    size_x = 43;
    size_y = 43;

    hitbox.setSize(sf::Vector2f((size_x / 3.5), (size_y / 1.5) ));
    position(100, 100);

    spell_1cd = 5.0f;
    spell_2cd = 5.0f;

    spell_time1 = 5.0f;

    boss_dir = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Hollow_knight.png"; //  "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Hollow_knight.png"
    Texture.loadFromFile(boss_dir);
    Sprite.setTexture(&Texture);
    Sprite.setTextureRect(sf::IntRect(0, 0, 43, 43));
    Sprite.setSize(sf::Vector2f(43,43));
}

void hollow_knight::boss_action(hero *Hero,std::vector<Bullet*> *bullets,int wall_size_x,int wall_size_y,std::vector<boss*> *Boss,std::vector<pickups*> &pickups,bool &boss_dead, std::vector<Entity*> &monsters, Audio *audio)
{
    if(speed_x < base_speed && acceleration.getElapsedTime().asMilliseconds() > 50)
    {
        speed_x = speed_x + 0.001;
        speed_y = speed_y + 0.001;
        acceleration.restart();
    }
    if(sqrt(pow(Hero->get_pos_x() - hitbox_pos_x,2)+pow(Hero->get_pos_y() - hitbox_pos_y,2) < pow(zasieg1,2)) && !cast && spell_cd1.getElapsedTime().asSeconds()>spell_1cd)
    {
        cast = 1;
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
    else if(sqrt(pow(Hero->get_pos_x() - hitbox_pos_x,2)+pow(Hero->get_pos_y() - hitbox_pos_y,2) > pow(zasieg2,2)) && !cast && spell_cd2.getElapsedTime().asSeconds()>spell_2cd)
    {
        spell_x = (Hero->get_pos_x() - pos_x)/(sqrt(pow(Hero->get_pos_x() - pos_x,2) + pow(Hero->get_pos_y() - pos_y,2))) *spell_speed;
        spell_y = (Hero->get_pos_y() - pos_y)/(sqrt(pow(Hero->get_pos_x() - pos_x,2) + pow(Hero->get_pos_y() - pos_y,2))) *spell_speed;
        cast = 2;
        audio->DashSound.play();
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
        boss_move(Hero->get_pos_x(), Hero->get_pos_y());
    }

    // Bullet
    if(cast == 1 && spell_time.getElapsedTime().asSeconds() < spell_time1)
    {
        if(shoot_timer.getElapsedTime().asSeconds() > shoot_time)
        {
            // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Hollow_bullet.png"
            bullets->push_back(new Bullet(hitbox_pos_x + 5, hitbox_pos_y + 15, 5, 5, spell_damage,"/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Hollow_bullet.png",Hero->get_pos_x()+Hero->get_sizex()/2,Hero->get_pos_y()+Hero->get_sizey()/2));
            audio->LaserAttack.play();
            shoot_timer.restart();
        }
    }
    else if(cast == 1)
    {
        cast = 0;
        spell_cd1.restart();
        spell_time.restart();
    }

    if(cast == 2)
    {
        audio->DashSound.play();
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
        // Bohater zadaje obrazenia
        damaged(Hero->get_attack_damage());
        damage_ticks = 0;
        attacked.restart();
        protection = 1;
        speed_x = -0.02;
        speed_y = -0.02;
        audio->SwordAttack.play();
        if(direction == 0) // Skrecil w lewo
        {
            texture(boss_dir, 43, 258, 43, 43);
            run.restart();
        }
        else  // Skrecil w prawo
        {
            texture(boss_dir, 0, 258, 43, 43);
            run.restart();
        }
        if(health <= 0)
        {
            Boss->clear();
            boss_dead = true;
            death(pickups);
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
                position(get_pos_x() - speed_x, get_pos_y());
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
            else if(player_position_x + 43/2 > hitbox_pos_x && (get_pos_x() + speed_x < player_position_x) && pos_x + speed_x > 0 && pos_x + speed_x <= 430)
            {
                position(get_pos_x() + speed_x, get_pos_y());
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
            if(player_position_y < pos_y && pos_y - speed_y > 0 && pos_y - speed_y <= 210)
            {
                position(get_pos_x(), get_pos_y() - speed_y);
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
            else if(player_position_y > pos_y && pos_y + speed_y > 0 && pos_y + speed_y <= 210)
            {
                position(get_pos_x(), get_pos_y() + speed_y);
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
        }

}
int hollow_knight::base_attack = 20;
int hollow_knight::base_spell_attack = 20;
int hollow_knight::base_health = 300;
#endif // HOLLOW_KNIGHT_H_INCLUDED
