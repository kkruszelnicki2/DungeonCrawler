#ifndef ROOMS_H_INCLUDED
#define ROOMS_H_INCLUDED

#include <vector>


class Room
{
private:
    std::string type="none";
    bool visited=0;
    bool is_opened=0;
public:
    void close() {is_opened=0;}
    void open() {is_opened=1;}

    bool can_enter() {return is_opened;}

    void visit() {this->visited=true;}
    void unvisit() {this->visited=false;}
    bool is_visited() {return this->visited;}

    void set_type(std::string typ) {this->type=typ;}
    std::string get_type() {return this->type;}

    std::vector<pickups*> pickups;
    sf::RectangleShape mini_map_icon;
};

#endif // ROOMS_H_INCLUDED
