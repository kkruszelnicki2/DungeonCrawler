#ifndef GRIMM_H_INCLUDED
#define GRIMM_H_INCLUDED

#include "boss.h"
#include "pickups.h"
#include "audio.h"

extern const int window_width;
extern const int window_height;

class grimm : public boss
{
private:
    //spell 1
    float zasieg1;
    float shoot_time = 1.5f;
    sf::Clock shoot_timer;

    //spell 2
    float zasieg2;
    float spell_speed = 0.1f;
    float spell_x;
    float spell_y;

    float run_animation_time = 400.0f;

    void boss_move(float player_position_x,float player_position_y);
public:
    grimm();
    static int base_attack;
    static int base_health;
    static int base_spell_attack;

    void boss_action(hero *Hero,std::vector<Bullet*> *bullets,int wall_size_x,int wall_size_y,std::vector<boss*> *Boss,std::vector<pickups *> &pickups,bool &boss_dead, std::vector<Entity*> &monsters, Audio *audio);
};

grimm::grimm()
{
    boss_name = "Grimm";

    // Statystyki Grimm'a:
    health = base_health;
    attack_damage = base_attack;
    spell_damage = base_spell_attack;
    base_speed = 0.04f;
    zasieg1 = window_width/3;
    zasieg2 = window_width/3;

    size_x = 86;
    size_y = 86;

    hitbox.setSize(sf::Vector2f((size_x / 3.5), (size_y / 1.5) ));
    position(100, 100);

    spell_1cd = 5.0f;
    spell_2cd = 6.0f;

    spell_time1 = 6.0f;

    boss_dir = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Grimm.png"; // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Grimm.png"
    Texture.loadFromFile(boss_dir);
    Sprite.setTexture(&Texture);
    Sprite.setTextureRect(sf::IntRect(0, 0, 86, 86));
    Sprite.setSize(sf::Vector2f(86, 86));
}


void grimm::boss_action(hero *Hero,std::vector<Bullet*> *bullets,int wall_size_x,int wall_size_y,std::vector<boss*> *Boss,std::vector<pickups*> &pickups,bool &boss_dead, std::vector<Entity*> &monsters, Audio *audio)
{
    if(speed_x < base_speed && acceleration.getElapsedTime().asMilliseconds() > 50)
    {
        speed_x = speed_x + 0.001;
        speed_y = speed_y + 0.001;
        acceleration.restart();
    }
    // PRZYZWANIE GRIMMCHILDE'A
    if(!cast && spell_cd1.getElapsedTime().asSeconds()>spell_1cd && monsters.size()<2)
    {
        monsters.push_back(new Grimmchild);
        if(Hero->get_pos_x() > window_width/2)
        {
            monsters[monsters.size()-1]->position(monsters[monsters.size()-1]->size_x,window_height/2);
        }
        else
        {
            monsters[monsters.size()-1]->position(window_width-monsters[monsters.size()-1]->size_x,window_height/2);
        }
        monsters[monsters.size()-1]->entity.setSize(sf::Vector2f(55,57));
        spell_cd1.restart();
    }
    // Teleportacja Grimm'a
    else if(!cast && spell_cd2.getElapsedTime().asSeconds()>spell_2cd)
    {
        cast = true;
        if(Hero->get_pos_x() > window_width/2)
        {
            direction = 0;
        }
        else
        {
            direction = 1;
        }
        spell_time.restart();
    }

    if(cast)
    {
        if(shoot_timer.getElapsedTime().asSeconds()>=shoot_time)
        {
            if(direction == 1)
            {
                position(window_width - window_width * 33/270 - size_x/2,window_height/2 - size_y/2);
                texture(boss_dir,172,172,86,86);
                direction = 0;  // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Iselda.png"
                bullets->push_back(new Bullet(hitbox_pos_x - size_x/2, hitbox_pos_y, 22, 33, spell_damage,"/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Grimm_bullet.png",Hero->get_pos_x()+Hero->get_sizex()/2,Hero->get_pos_y()+Hero->get_sizey()/2));
                audio->FireAttack.play();
            }
            else
            {
                position(window_width * 33/270 - size_x/2,window_height/2 - size_y/2);
                texture(boss_dir,86,172,86,86);
                direction = 1;
                bullets->push_back(new Bullet(hitbox_pos_x + size_x/2, hitbox_pos_y, 22, 33, spell_damage,"/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Grimm_bullet.png",Hero->get_pos_x()+Hero->get_sizex()/2,Hero->get_pos_y()+Hero->get_sizey()/2));
                audio->FireAttack.play();
            }
            shoot_timer.restart();
        }
        if(spell_time.getElapsedTime().asSeconds()>= spell_time1)
        {
            cast = 0;
            spell_cd2.restart();
        }
    }

    if(!cast)
    {
        boss_move(Hero->get_pos_x(),Hero->get_pos_y());
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
            texture(boss_dir, 86, 258, 86, 86);
            run.restart();
        }
        else  // Skrecil w prawo
        {
            texture(boss_dir, 0, 258, 86, 86);
            run.restart();
        }
        if(health<=0)
        {
            Boss->clear();
            boss_dead = true;
            death(pickups);
            monsters.clear();
        }
    }
}

// PORUSZANIE GRIMM'A
void grimm::boss_move(float player_position_x,float player_position_y)
{
    if(true)
        {
            // Lewo
            if(player_position_x + 43/2 < hitbox_pos_x && (get_pos_x() - speed_x > player_position_x) && pos_x - speed_x > 0 && pos_x - speed_x <= 430)
            {
                position(get_pos_x() - speed_x, get_pos_y());
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
            else if(player_position_x + 43/2 > hitbox_pos_x && (get_pos_x() + speed_x < player_position_x) && pos_x + speed_x > 0 && pos_x + speed_x <= 430)
            {
                position(get_pos_x() + speed_x, get_pos_y());
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
                        texture(boss_dir, 0, 86, 86, 86);
                        frame = 1;
                    }
                    run.restart();
                }
            }
            // Gora
            if(player_position_y < pos_y && pos_y - speed_y > 0 && pos_y - speed_y <= window_height - window_height * 33/270 - size_y)
            {
                position(get_pos_x(), get_pos_y() - speed_y);
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
            else if(player_position_y > pos_y && pos_y + speed_y > 0 && pos_y + speed_y <= window_height - window_height * 33/270 - size_y)
            {
                position(get_pos_x(), get_pos_y() + speed_y);
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
int grimm::base_attack = 20;
int grimm::base_spell_attack = 20;
int grimm::base_health = 300;

#endif // GRIMM_H_INCLUDED
