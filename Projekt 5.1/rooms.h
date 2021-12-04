#ifndef ROOMS_H_INCLUDED
#define ROOMS_H_INCLUDED

#include <vector>


class Room
{
private:
    std::string type="none";
    bool visited=0;
public:

    void visit() {this->visited=true;}
    bool is_visited() {return this->visited;}

    void set_type(std::string typ) {this->type=typ;}
    std::string get_type() {return this->type;}

    std::vector<pickups*> pickups;
    sf::RectangleShape mini_map_icon;
};

#endif // ROOMS_H_INCLUDED
