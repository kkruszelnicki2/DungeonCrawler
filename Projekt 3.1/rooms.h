#ifndef ROOMS_H_INCLUDED
#define ROOMS_H_INCLUDED


class Room
{
private:
    std::string type="none";
    bool visited=0;
public:
    void visit() {this->visited=true;};
    void set_type(std::string typ) {this->type=typ;};
    std::string get_type() {return this->type;};
};

#endif // ROOMS_H_INCLUDED
