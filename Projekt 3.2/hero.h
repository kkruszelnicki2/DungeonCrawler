#ifndef HERO_H
#define HERO_H


class hero
{
private:
    float sizex = 43; //rozmiar
    float sizey = 43;
    std::string knight_dir = "Textures/Knight.png"; //"/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Knight.png"
    //statystyki
    int attack_damage = 20; //punkty ataku bohatera
    int health = 100; //zdrowie
    float speed = 0.05f; //predkosc
    //zmienne zwiazane z walka
    bool attack = 0; //czy w trakcie animacji ataku

    //zmienne zwiazane z poruszaniem
    float run_animation_time = 200.0f; //czas pomiêdzy klatkami animacji
    bool frame; //klatka animacji
    float pos_x; //pozycja x
    float pos_y; //pozycja y
    float hitbox_pos_x; //pozycja x
    float hitbox_pos_y; //pozycja y
    int direction = 2; //skierowany do przodu (2), w prawo (1) czy w lewo (0)
public:
    hero();

    bool attacked=0;

    sf::Texture entity_texture;
    sf::RectangleShape entity;
    sf::RectangleShape hitbox;
    sf::RectangleShape attack_hitbox;

    sf::Clock run;
    sf::Clock damaged_cd;
    float damaged_cooldown = 2.0f;

    // zczytuje konkretny fragment tekstury gracza
    void texture(std::string tekstura,int a,int b,int c,int d) {this->entity_texture.loadFromFile(tekstura);this->entity.setTexture(&this->entity_texture);this->entity.setTextureRect(sf::IntRect(a, b, c, d));};
    /////////////////////////////// GET/SET ///////////////////////////
    // pozycja
    float get_pos_x(){return this->pos_x;}
    float get_pos_y(){return this->pos_y;}
    void position(float x, float y) {this->pos_x = x; this->pos_y = y; this->entity.setPosition(pos_x, pos_y);hitbox.setPosition(pos_x+sizex/3+sizex/40,pos_y+sizey/7);}
    float get_sizex() {return this->sizex;}
    float get_sizey() {return this->sizey;}
    void set_direction(int x) {this->direction=x;}
    // zdrowie
    int get_health() {return this->health;};
    // szybkosc
    float get_speed(){return this->speed;};
    void set_speed(float x) {this->speed=x;};
    // atak
    bool get_attack() {return this->attack;};
    int get_attack_damage() {return this->attack_damage;};
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
    void damaged(int damage);
};

hero::hero()
{
    texture(knight_dir, 0, 0, 43, 43);
    entity.setSize(sf::Vector2f(sizex, sizey));
    attack_hitbox.setFillColor(sf::Color::Green);
    hitbox.setFillColor(sf::Color::Green);
    hitbox.setSize(sf::Vector2f(sizex/3 - sizex/25,sizey-sizey/3));
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
    attack_hitbox.setSize(sf::Vector2f(sizex/2+sizex/45,sizey/3));
    attack_hitbox.setPosition(get_pos_x()+sizex/4,get_pos_y());
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
    attack_hitbox.setSize(sf::Vector2f(sizex/2+sizex/45,sizey/3));
    attack_hitbox.setPosition(get_pos_x()+sizex/4-sizex/40,get_pos_y()+sizey-sizey/3);
}

void hero::damaged(int damage)
{
    if(damaged_cd.getElapsedTime().asSeconds() > damaged_cooldown)
    {
        health = health - damage;
        damaged_cd.restart();
        attacked = 1;
    }
}

#endif // HERO_H
