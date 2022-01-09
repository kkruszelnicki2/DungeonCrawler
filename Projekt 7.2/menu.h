#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <vector>

extern const int window_width;
extern const int window_height;

class button
{
private:
    float pos_x;
    float pos_y;
public:
    button(float x, float y, float menu_size, std::string txt);

    sf::RectangleShape button_window;
    sf::Text text;
    sf::Font font;
    std::string font_dir = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/font.ttf";  // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/font.ttf"
    std::string name;

    friend class menu;
};

button::button(float x,float y,float menu_size,std::string txt)
{
    pos_x = x;
    pos_y = y;

    name = txt;

    button_window.setPosition(pos_x,pos_y);
    button_window.setFillColor(sf::Color::White);
    button_window.setSize(sf::Vector2f(menu_size * 56 / 64,menu_size/10));

    text.setString(txt);
    font.loadFromFile(font_dir);
    text.setFont(font);
    text.setPosition(pos_x,pos_y);
    text.setCharacterSize(menu_size/10 - menu_size/50);
    text.setColor(sf::Color::Black);
}

class menu
{
public:
    menu(float menu_size);
    void index_update(int i);
    void execute(bool &is_main_menu,sf::RenderWindow &window,bool &time,bool &restart);
    void change_buttonAmount(int x);
    // Tlo menu
    sf::RectangleShape window;
    sf::Texture window_texture;
    std::string menu_dir = "Textures/Portal.png";  // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Portal.png"
    // Tytul gry
    sf::RectangleShape title;
    sf::Texture title_texture;
    std::string title_dir = "Textures/Title.png";  // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Title.png"

    std::vector<button> buttons;

private:
    float space_between;
    int index = 0;
    float m_size;
};

menu::menu(float menu_size)
{
    m_size = menu_size;
    window.setPosition(window_width/2 - m_size/2,window_height/2 - m_size/2);
    space_between = m_size/100.0;
    window_texture.loadFromFile(menu_dir);
    window.setTexture(&window_texture);
    window.setTextureRect(sf::IntRect(0,64,64,64));
    window.setSize(sf::Vector2f(m_size,m_size));

    // wymiary loga: 145x102 px
    title.setPosition(window_width/2 - m_size/2,window_height/2 - m_size/2);
    title_texture.loadFromFile(title_dir);
    title.setTexture(&title_texture);
    title.setTextureRect(sf::IntRect(0,64,64,64));
    title.setSize(sf::Vector2f(m_size, m_size));

    change_buttonAmount(3);
}

void menu::index_update(int i)
{
    buttons[index].button_window.setFillColor(sf::Color::White);

    if(index + i < 0)
    {
        index = buttons.size()-1;
    }
    else if(index + i > buttons.size()-1)
    {
        index = 0;
    }
    else
    {
        index= index + i;
    }
    buttons[index].button_window.setFillColor(sf::Color(96,96,96));
}

void menu::execute(bool &is_main_menu,sf::RenderWindow &window,bool &time,bool &restart)
{
    if(buttons[index].name == "Play")
    {
        is_main_menu = false;
        time = true;
    }
    else if(buttons[index].name == "Exit")
    {
        window.close();
    }
    else if(buttons[index].name == "Restart")
    {
        restart = true;
        is_main_menu = false;
        time = true;
    }
}

void menu::change_buttonAmount(int x)
{
    float pos_x = window_width/2 - m_size/2;
    float pos_y = window_height/2 - m_size/2;

    float start = x * m_size/10.0 + (x-1) * space_between;
    std::string txt;

    if(x == 3)
    {
        for(int i=0;i<x;i++)
        {
            switch(i)
            {
            case(0):
                txt = "Play";
                break;
            case(1):
                txt = "Restart";
                break;
            case(2):
                txt = "Exit";
                break;
            }
            buttons.push_back(*new button(pos_x + m_size *4.0 / 64.0,pos_y + m_size/2 - start/2 + i * (space_between + m_size/10.0), m_size,txt));
        }
    }
}

#endif // MENU_H_INCLUDED
