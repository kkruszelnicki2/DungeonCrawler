#ifndef PICKUPS_H_INCLUDED
#define PICKUPS_H_INCLUDED

class pickups
{
private:
    // Wymiary tekstur: coin(15x15 px), key(12x28 px)
    std::string  coin_dir = "Textures/Coin.png";
    std::string  key_dir = "Textures/Key.png";
    int worth;
    std::string name;

    float pos_x;
    float pos_y;
public:
    virtual int get_worth() = 0;
    virtual void set_worth(int x) = 0;

    virtual std::string get_name() = 0;

    friend class coin;
    friend class key;

    //void texture(std::string tekstura,int a,int b,int c,int d) {this->entity_texture.loadFromFile(tekstura);this->entity.setTexture(&this->entity_texture);this->entity.setTextureRect(sf::IntRect(a, b, c, d));};

    sf::RectangleShape pickup;
    sf::Texture pickup_texture;
};

class coin : public pickups
{
public:
    coin(int w,float x,float y);

    int get_worth() {return worth;}
    void set_worth(int x) {worth = x;}

    std::string get_name() {return name;}
};

coin::coin(int w,float x,float y)
{
    name = "coin";
    set_worth(w);
    pos_x = x;
    pos_y = y;
    pickup_texture.loadFromFile(coin_dir);  // "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Textures/Coin.png"
    pickup.setTexture(&pickup_texture);
    pickup.setTextureRect(sf::IntRect(0, 0, 15, 15));
    pickup.setPosition(pos_x, pos_y);
    pickup.setSize(sf::Vector2f(10,10));
}

class key : public pickups
{
public:
    key(int w,float x,float y);

    int get_worth() {return worth;}
    void set_worth(int x) {worth = x;}

    std::string get_name() {return name;}
};

key::key(int w,float x,float y)
{
    name = "key";
    set_worth(w);
    pos_x = x;
    pos_y = y;
    pickup_texture.loadFromFile(key_dir);
    pickup.setTexture(&pickup_texture);
    pickup.setTextureRect(sf::IntRect(0, 0, 28, 12));
    pickup.setPosition(pos_x, pos_y);
    pickup.setSize(sf::Vector2f(14,6));  // klucze pomniejszone 2x
}

#endif // PICKUPS_H_INCLUDED
