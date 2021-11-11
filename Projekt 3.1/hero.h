#ifndef HERO_H
#define HERO_H


class hero
{
private:
    float size = 43; //rozmiar
    std::string knight_dir = "Textures/Knight.png"; //"/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Knight.png"
    //statystyki
    int atack_damage = 20; //punkty ataku bohatera
    int health = 100; //zdrowie
    float speed = 0.05f; //predkosc
    //zmienne zwiazane z atakiem
    bool attack = 0; //czy w trakcie animacji ataku

    //zmienne zwiazane z poruszaniem
    float run_animation_time = 200.0f; //czas pomiêdzy klatkami animacji
    bool frame; //klatka animacji
    float pos_x; //pozycja x
    float pos_y; //pozycja y
    int direction = 2; //skierowany do przodu (2), w prawo (1) czy w lewo (0)
public:
    hero();

    sf::Texture entity_texture;
    sf::RectangleShape entity;
    sf::Clock run;
    sf::RectangleShape attack_hitbox;

    // zczytuje konkretny fragment tekstury gracza
    void texture(std::string tekstura,int a,int b,int c,int d) {this->entity_texture.loadFromFile(tekstura);this->entity.setTexture(&this->entity_texture);this->entity.setTextureRect(sf::IntRect(a, b, c, d));};
    /////////////////////////////// GET/SET ///////////////////////////
    // pozycja
    float get_pos_x(){return this->pos_x;}
    float get_pos_y(){return this->pos_y;}
    void position(float x, float y) {this->pos_x = x; this->pos_y = y; this->entity.setPosition(pos_x, pos_y);}
    float get_size() {return this->size;}
    void set_direction(int x) {this->direction=x;}
    // szybkosc
    float get_speed(){return this->speed;};
    float set_speed(float x) {this->speed=x;};
    // atak
    bool get_attack() {return this->attack;};
    /////////////////////////////// PORUSZANIE /////////////////////////////
    void move_left();
    void move_right();
    void move_up();
    void move_down();
    void idle();
    ////////////////////////////// ATAKI /////////////////////////
    void attack_end();
    void attack_left();
    void attack_right();
    void attack_up();
    void attack_down();
};

hero::hero()
{
    texture(knight_dir, 0, 0, 43, 43);
    entity.setSize(sf::Vector2f(size, size));
    attack_hitbox.setFillColor(sf::Color::Green);
}
//////////////////////////////////////////////////PORUSZANIE///////////////////////////////////////////////
//lewo
void hero::move_left()
{
    position(get_pos_x() - get_speed(), get_pos_y());
    if(direction != 0 && !attack)
    {
        run.restart();
        direction=0;
        texture(knight_dir, 86, 86, 43, 43);
    }
    if(!attack && run.getElapsedTime().asMilliseconds() > run_animation_time)
    {
        if(frame)
        {
            texture(knight_dir, 86, 86, 43, 43);
            frame=0;
        }
        else
        {
            texture(knight_dir, 43, 86, 43, 43);
            frame=1;
        }
        run.restart();
    }
}
//prawo
void hero::move_right()
{
    position(get_pos_x() + get_speed(), get_pos_y());
    if(direction != 1 && !attack)
    {
        run.restart();
        direction=1;
        texture(knight_dir, 86, 0, 43, 43);
    }
    if(!attack && run.getElapsedTime().asMilliseconds() > run_animation_time)
    {
        if(frame)
        {
            texture(knight_dir, 86, 0, 43, 43);
            frame=0;
        }
        else
        {
            texture(knight_dir, 129, 0, 43, 43);
            frame=1;
        }
        run.restart();
    }
}
//góra
void hero::move_up()
{
    position(get_pos_x(), get_pos_y() - get_speed());
    if(!attack && run.getElapsedTime().asMilliseconds() > run_animation_time)
    {
        if(direction == 1)
        {
            if(frame)
            {
                texture(knight_dir, 86, 0, 43, 43);
                frame=0;
            }
            else
            {
                texture(knight_dir, 129, 0, 43, 43);
                frame=1;
            }
        run.restart();
        }
        else
        {
            if(frame)
            {
                texture(knight_dir, 86, 86, 43, 43);
                frame=0;
            }
            else
            {
                texture(knight_dir, 43, 86, 43, 43);
                frame=1;
            }
            run.restart();
        }
    }
}
//dó³
void hero::move_down()
{
    position(get_pos_x(), get_pos_y() + get_speed());
    if(!attack && run.getElapsedTime().asMilliseconds() > run_animation_time)
    {
        if(direction == 1)
        {
            if(frame)
            {
                texture(knight_dir, 86, 0, 43, 43);
                frame=0;
            }
            else
            {
                texture(knight_dir, 129, 0, 43, 43);
                frame=1;
            }
        run.restart();
        }
        else
        {
            if(frame)
            {
                texture(knight_dir, 86, 86, 43, 43);
                frame=0;
            }
            else
            {
                texture(knight_dir, 43, 86, 43, 43);
                frame=1;
            }
            run.restart();
        }
    }
}
//w bezruchu
void hero::idle()
{
    texture(knight_dir, 0, 0, 43, 43);
}
////////////////////////////////////////////////////////////ATAKI///////////////////////////////////////////
//koniec animacji ataku
void hero::attack_end()
{
    if(direction==1)
    {
        texture(knight_dir, 43, 0, 43, 43);
    }
    else
    {
        texture(knight_dir, 0, 86, 43, 43);
    }
    attack = 0;
}
//atak w lewo
void hero::attack_left()
{
    texture(knight_dir, 0, 129, 43, 43);
    attack = 1;
}
void hero::attack_right()
{
    texture(knight_dir, 43, 43, 43, 43);
    attack = 1;
}

void hero::attack_up()
{
    // gora, prawo
    if(direction == 1)
    {
        texture(knight_dir, 129, 43, 43, 43);
    }
    // gora, lewo
    else
    {
        texture(knight_dir, 86, 129, 43, 43);
    }
    attack = 1;
    attack_hitbox.setSize(sf::Vector2f(size/2+size/45,size/3));
    attack_hitbox.setPosition(get_pos_x()+size/4,get_pos_y());
}

void hero::attack_down()
{
    // dol, prawo
    if(direction == 1)
    {
        texture(knight_dir, 86, 43, 43, 43);
    }
    // dol, lewo
    else
    {
        texture(knight_dir, 43, 129, 43, 43);
    }
    attack = 1;
    attack_hitbox.setSize(sf::Vector2f(size/2+size/45,size/3));
    attack_hitbox.setPosition(get_pos_x()+size/4-size/40,get_pos_y()+size-size/3);
}

#endif // HERO_H
