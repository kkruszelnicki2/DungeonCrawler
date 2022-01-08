#ifndef FUNKCJE_H_INCLUDED
#define FUNKCJE_H_INCLUDED
#include "monsters.h"
#include "rooms.h"
#include "zombie.h"
#include "boomer.h"
#include "shooter.h"
#include "pickups.h"
#include "items.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

//generowanie pietra
void generate_floor(int room_amount,Room is_room[][5],int window_width,int window_height,float mini_map_size, int *actual_room_x, int *actual_room_y)
{
    *actual_room_x=2;
    *actual_room_y=2;

    for(int j=0;j<5;j++)
    {
        for(int i=0;i<5;i++)
        {
            is_room[i][j].close();
            is_room[i][j].set_type("none");
            is_room[i][j].pickups.clear();
            is_room[i][j].unvisit();
        }
    }

    is_room[2][2].visit();
    is_room[2][2].open();
    is_room[2][2].set_type("basic");

    for(int j=0;j<5;j++)
    {
        for(int i=0;i<5;i++)
        {
            is_room[i][j].mini_map_icon.setFillColor(sf::Color::Black);
        }
    }

    is_room[2][2].mini_map_icon.setFillColor(sf::Color::Cyan);

    srand(time(NULL));
    int how_many=0; //ile juz pokoi stworzonych
    int x=2; //x srodkowego pokoju
    int y=2; //y srodkowego pokoju
    while(true)
    {
        switch(rand()%4+1) //losowanie kierunku
        {
        case 1:
            if(y-1>=0)
            {
                if(is_room[x][y-1].get_type()=="none") //sprawdzanie, czy pokoj jest pusty
                {
                    is_room[x][y-1].set_type("basic");
                    how_many++;
                    is_room[x][y-1].open();
                }
                y=y-1;
            }
            break;
        case 2:
            if(x+1<=4)
            {
                if(is_room[x+1][y].get_type()=="none")
                {
                    is_room[x+1][y].set_type("basic");
                    how_many++;
                    is_room[x+1][y].open();
                }
                x=x+1;
            }
            break;
        case 3:
            if(x-1>=0)
            {
                if(is_room[x-1][y].get_type()=="none")
                {
                    is_room[x-1][y].set_type("basic");
                    how_many++;
                    is_room[x-1][y].open();
                }
                x=x-1;
            }
            break;
        case 4:
            if(y+1<=4)
            {
                if(is_room[x][y+1].get_type()=="none")
                {
                    is_room[x][y+1].set_type("basic");;
                    how_many++;
                    is_room[x][y+1].open();
                }
                y=y+1;
            }
            break;
        }
        if(how_many==room_amount) //sprawdzanie, czy wystarczajaca ilosc pokoi jest juz zajeta
        {
            break;
        }
    }

    bool is_boss = 1;
    bool is_treasure = 1;
    bool is_shop = 1;

    while(is_shop)
    {
        switch(rand()%4+1) //losowanie kierunku
        {
        case 1:
            if(y-1>=0)
            {
                if(is_room[x][y-1].get_type()=="none") //sprawdzanie, czy pokoj jest pusty
                {
                    is_room[x][y-1].set_type("shop");
                    is_shop = 0;
                    is_room[x][y-1].open();
                }
                y=y-1;
            }
            break;
        case 2:
            if(x+1<=4)
            {
                if(is_room[x+1][y].get_type()=="none")
                {
                    is_room[x+1][y].set_type("shop");
                    is_shop = 0;
                    is_room[x+1][y].open();
                }
                x=x+1;
            }
            break;
        case 3:
            if(x-1>=0)
            {
                if(is_room[x-1][y].get_type()=="none")
                {
                    is_room[x-1][y].set_type("shop");
                    is_shop = 0;
                    is_room[x-1][y].open();
                }
                x=x-1;
            }
            break;
        case 4:
            if(y+1<=4)
            {
                if(is_room[x][y+1].get_type()=="none")
                {
                    is_room[x][y+1].set_type("shop");;
                    is_shop = 0;
                    is_room[x][y+1].open();
                }
                y=y+1;
            }
            break;
        }
    }

    while(is_boss)
    {
        switch(rand()%4+1) //losowanie kierunku
        {
        case 1:
            if(y-1>=0)
            {
                if(is_room[x][y-1].get_type()=="none") //sprawdzanie, czy pokoj jest pusty
                {
                    is_room[x][y-1].set_type("boss_room");
                    is_boss = 0;
                    is_room[x][y-1].open();
                }
                y=y-1;
            }
            break;
        case 2:
            if(x+1<=4)
            {
                if(is_room[x+1][y].get_type()=="none")
                {
                    is_room[x+1][y].set_type("boss_room");
                    is_boss = 0;
                    is_room[x+1][y].open();
                }
                x=x+1;
            }
            break;
        case 3:
            if(x-1>=0)
            {
                if(is_room[x-1][y].get_type()=="none")
                {
                    is_room[x-1][y].set_type("boss_room");
                    is_boss = 0;
                    is_room[x-1][y].open();
                }
                x=x-1;
            }
            break;
        case 4:
            if(y+1<=4)
            {
                if(is_room[x][y+1].get_type()=="none")
                {
                    is_room[x][y+1].set_type("boss_room");;
                    is_boss = 0;
                    is_room[x][y+1].open();
                }
                y=y+1;
            }
            break;
        }
        is_room[x][y].open();
    }

    while(is_treasure)
    {
        switch(rand()%4+1) //losowanie kierunku
        {
        case 1:
            if(y-1>=0)
            {
                if(is_room[x][y-1].get_type()=="none") //sprawdzanie, czy pokoj jest pusty
                {
                    is_room[x][y-1].set_type("treasure_room");
                    is_treasure = 0;
                }
                y=y-1;
            }
            break;
        case 2:
            if(x+1<=4)
            {
                if(is_room[x+1][y].get_type()=="none")
                {
                    is_room[x+1][y].set_type("treasure_room");
                    is_treasure = 0;
                }
                x=x+1;
            }
            break;
        case 3:
            if(x-1>=0)
            {
                if(is_room[x-1][y].get_type()=="none")
                {
                    is_room[x-1][y].set_type("treasure_room");
                    is_treasure = 0;
                }
                x=x-1;
            }
            break;
        case 4:
            if(y+1<=4)
            {
                if(is_room[x][y+1].get_type()=="none")
                {
                    is_room[x][y+1].set_type("treasure_room");;
                    is_treasure = 0;
                }
                y=y+1;
            }
            break;
        }
    }
}

void draw_door(Room is_room[][5],bool drawdoor[4],int x,int y)
{
    sf::Color color(74,84,90);
    if(y-1>=0 && is_room[x][y-1].get_type()!="none") //drzwi gorne
    {
        drawdoor[0]=true;
        if(!is_room[x][y-1].is_visited())
        {
            is_room[x][y-1].mini_map_icon.setFillColor(color);
        }
    }
    else
    {
        drawdoor[0]=false;
    }

    if(x-1>=0 && is_room[x-1][y].get_type()!="none") //drzwi lewe
    {
        drawdoor[1]=true;
        if(!is_room[x-1][y].is_visited())
        {
            is_room[x-1][y].mini_map_icon.setFillColor(color);
        }
    }
    else
    {
        drawdoor[1]=false;
    }

    if(x+1<5 && is_room[x+1][y].get_type()!="none") //drzwi prawe
    {
        drawdoor[2]=true;
        if(!is_room[x+1][y].is_visited())
        {
            is_room[x+1][y].mini_map_icon.setFillColor(color);
        }
    }
    else
    {
        drawdoor[2]=false;
    }

    if(y+1<5 && is_room[x][y+1].get_type()!="none") //drzwi dolne
    {
        drawdoor[3]=true;
        if(!is_room[x][y+1].is_visited())
        {
            is_room[x][y+1].mini_map_icon.setFillColor(color);
        }
    }
    else
    {
        drawdoor[3]=false;
    }
}

void monsters_generator(std::vector<Entity*> &monsters, int monster_max_value, float player_pos_x, float player_pos_y, int window_width, int window_height)
{
    srand(time(NULL));
    int monster_pos_x, monster_pos_y;
    for(int i=0;i<monster_max_value;)
    {
        switch(rand() % 3 + 1)  // uwazaj na rand()
        {
            case 1:
                if(i+1 <= monster_max_value)
                {
                    monsters.push_back(new Zombie);
                    monster_pos_x = rand()%430;
                    monster_pos_y = rand()%210;
                    monsters[i]->position(monster_pos_x,monster_pos_y);
                    monsters[i]->entity.setSize(sf::Vector2f(monsters[i]->size_x, monsters[i]->size_y));
                    monsters[i]->id = i;
                    i=i+monsters[i]->wartosc;
                    break;
                }
            case 2:
                if(i+1 <= monster_max_value)
                {
                    monsters.push_back(new Boomer);
                    monster_pos_x = rand()%430;
                    monster_pos_y = rand()%210;
                    monsters[i]->position(monster_pos_x,monster_pos_y);
                    monsters[i]->entity.setSize(sf::Vector2f(monsters[i]->size_x, monsters[i]->size_y));
                    monsters[i]->id = i;
                    i=i+monsters[i]->wartosc;
                    break;
                }
            case 3:
                if(i+1 <= monster_max_value)
                {
                    monsters.push_back(new Shooter);
                    monster_pos_x = rand()%430;
                    monster_pos_y = rand()%210;
                    monsters[i]->position(monster_pos_x,monster_pos_y);
                    monsters[i]->entity.setSize(sf::Vector2f(monsters[i]->size_x, monsters[i]->size_y));
                    monsters[i]->id = i;
                    i=i+monsters[i]->wartosc;
                    break;
                }
        }
    }
}

bool sort_monsters(Entity* a,Entity* b)
{
    return (a->get_pos_y() < b->get_pos_y());
}

void item_pull(std::vector<pickups*> items)
{
    items.push_back(new mask_health);
    items.push_back(new mask_attack_damage);
    items.push_back(new mask_speed);
}

void door_closed(std::vector<sf::Sprite> &drzwi,Room is_room[][5],int x,int y,bool fight_mode)
{
    for(int i=0;i<4;i++)
    {
        if(i==0)
        {
            if(is_room[x][y-1].can_enter())
            {
                if(!fight_mode)
                {
                    drzwi[i].setTextureRect(sf::IntRect(1, 34, 30, 26));
                }
                else
                {
                    drzwi[i].setTextureRect(sf::IntRect(1, 2, 30, 25));
                }
            }
            else
            {
                drzwi[i].setTextureRect(sf::IntRect(38, 0, 30, 25));
            }
        }
        else if(i==1)
        {
            if(is_room[x-1][y].can_enter())
            {
                if(!fight_mode)
                {
                    drzwi[i].setTextureRect(sf::IntRect(1, 34, 30, 26));
                }
                else
                {
                    drzwi[i].setTextureRect(sf::IntRect(1, 2, 30, 25));
                }
            }
            else
            {
                drzwi[i].setTextureRect(sf::IntRect(38, 0, 30, 25));
            }
        }
        else if(i==2)
        {
            if(is_room[x+1][y].can_enter())
            {
                if(!fight_mode)
                {
                    drzwi[i].setTextureRect(sf::IntRect(1, 34, 30, 26));
                }
                else
                {
                    drzwi[i].setTextureRect(sf::IntRect(1, 2, 30, 25));
                }
            }
            else
            {
                drzwi[i].setTextureRect(sf::IntRect(38, 0, 30, 25));
            }
        }
        else if(i == 3)
        {
            if(is_room[x][y+1].can_enter())
            {
                if(!fight_mode)
                {
                    drzwi[i].setTextureRect(sf::IntRect(1, 34, 30, 26));
                }
                else
                {
                    drzwi[i].setTextureRect(sf::IntRect(1, 2, 30, 25));
                }
            }
            else
            {
                drzwi[i].setTextureRect(sf::IntRect(38, 0, 30, 25));
            }
        }
    }
}

void next_floor(hero *Hero,bool &boss_dead,int &actual_room_x,int &actual_room_y)
{
    boss_dead = 0;
    Hero->position(window_width / 2 - Hero->get_sizex()/2, window_height / 2 - Hero->get_sizey()/2);
    actual_room_x = 2;
    actual_room_y = 2;
}

#endif // FUNKCJE_H_INCLUDED
