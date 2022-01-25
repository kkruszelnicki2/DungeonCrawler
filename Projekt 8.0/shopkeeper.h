#ifndef SHOPKEEPER_H_INCLUDED
#define SHOPKEEPER_H_INCLUDED

// "extern" ~ means that the actual storage is located in another file
extern const int window_width;
extern const int window_height;
class shopkeeper: public boss
{
private:
    std::string Iselda_dir = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Iselda.png"; // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Iselda.png"
    // wymiary sklepu
    float size_x = 46;
    float size_y = 46;
    // pozycja sklepu
    float pos_x = window_width/2 - size_x/2; //pozycja x
    float pos_y = window_height/2 - size_y/2 - window_height/6; //pozycja y

    sf::Clock Iselda_timer;
    float Iselda_animation_time = 1000.0f;
public:
    shopkeeper();

    // zwracaj wymiary sklepu
    float get_sizex() {return this->size_x;}
    float get_sizey() {return this->size_y;}

    // zwracaj koordynaty sklepu
    float get_pos_x(){return this->pos_x;}
    float get_pos_y(){return this->pos_y;}

    void position(float x, float y) {this->pos_x = x; this->pos_y = y; this->Iselda_shape.setPosition(pos_x, pos_y); }
    sf::Clock bapanada;
    sf::RectangleShape Iselda_shape;
    sf::Texture Iselda_texture;
    // zczytuje konkretny fragment tekstury npc
    void texture(std::string tekstura,int a,int b,int c,int d) {this->Iselda_texture.loadFromFile(tekstura);this->Iselda_shape.setTexture(&this->Iselda_texture);this->Iselda_shape.setTextureRect(sf::IntRect(a, b, c, d));};
    friend class funkcje;
    Room *room;
    int frame = 0;

    void bapanada_animation0();
    void bapanada_animation1();
    void bapanada_animation2();
    void bapanada_animation3();
    void animation();
};

shopkeeper::shopkeeper()
{
    texture(Iselda_dir, 0, 0, 46, 46);
    Iselda_shape.setSize(sf::Vector2f(size_x, size_y));
}
// animacje sklepikarza
void shopkeeper::bapanada_animation0()
{
    texture(Iselda_dir, 0, 0, 46, 46);
}
void shopkeeper::bapanada_animation1()
{
    texture(Iselda_dir, 46, 0, 46, 46);
}
void shopkeeper::bapanada_animation2()
{
    texture(Iselda_dir, 0, 46, 46, 46);
}
void shopkeeper::bapanada_animation3()
{
    texture(Iselda_dir, 46, 46, 46, 46);
}

void shopkeeper::animation()
{
    if(Iselda_timer.getElapsedTime().asMilliseconds() > 12*Iselda_animation_time && frame == 0)
    {
        bapanada_animation0();  // podniesienie glowy
        frame = 1;
        Iselda_timer.restart();
    }
    else if(Iselda_timer.getElapsedTime().asMilliseconds() > 2*Iselda_animation_time && frame == 1)
    {
        bapanada_animation1();  // opuszczanie glowy
        frame = 2;
        Iselda_timer.restart();

    }
    else if(Iselda_timer.getElapsedTime().asMilliseconds() > 2.5*Iselda_animation_time && frame == 2)
    {
        bapanada_animation2(); // podniesienie reki
        frame = 3;
        Iselda_timer.restart();
    }
    else if(Iselda_timer.getElapsedTime().asMilliseconds() > 0.75*Iselda_animation_time && frame == 3)
    {
        bapanada_animation3();  //opuszczenie reki
        frame = 4;
        Iselda_timer.restart();
    }
    else if(Iselda_timer.getElapsedTime().asMilliseconds() > 0.75*Iselda_animation_time && frame == 4)
    {
        bapanada_animation2(); // podniesienie reki
        frame = 5;
        Iselda_timer.restart();
    }
    else if(Iselda_timer.getElapsedTime().asMilliseconds() > 0.75*Iselda_animation_time && frame == 5)
    {
        bapanada_animation3();  //opuszczenie reki
        frame = 0;
        Iselda_timer.restart();
    }
}


#endif //SHOPKEEPER_H_INCLUDED
