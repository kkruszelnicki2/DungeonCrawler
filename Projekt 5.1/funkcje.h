#ifndef FUNKCJE_H_INCLUDED
#define FUNKCJE_H_INCLUDED
#include "monsters.h"
#include "rooms.h"
#include "zombie.h"
#include "boomer.h"
#include "shooter.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

//generowanie pietra
void generate_floor(int room_amount,Room is_room[][5],int window_width,int window_height,float mini_map_size)
{
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

#endif // FUNKCJE_H_INCLUDED
