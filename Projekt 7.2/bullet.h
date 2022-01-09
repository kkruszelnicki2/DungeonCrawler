#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

class Bullet
{
    private:
        float speed = 0.05;
        int damage;

        // Pozycja pociskow
        float pos_x;
        float pos_y;

        // Wielkosc pociskow
        int size_x;
        int size_y;

        sf::Texture bullet_texture;

        float trajectory[2];
    public:
        Bullet(float posX,float posY, int sizeX, int sizeY,int damage,std::string texture,float hero_pos_x,float hero_pos_y);

        void set_trajectory(float hero_pos_x,float hero_pos_y);
        void move_bullet();

        float get_pos_x() {return pos_x;}
        float get_pos_y() {return pos_y;}

        int get_size_x() {return size_x;}
        int get_size_y() {return size_y;}

        int get_damage() {return damage;}

        sf::RectangleShape bullet;
};

Bullet::Bullet(float posX, float posY, int sizeX, int sizeY, int dmg,std::string texture,float hero_pos_x,float hero_pos_y)
{
    pos_x = posX;
    pos_y = posY;
    size_x = sizeX;
    size_y = sizeY;
    damage = dmg;

    bullet.setSize(sf::Vector2f(sizeX, sizeY));
    bullet.setPosition(posX, posY);

    bullet_texture.loadFromFile(texture);
    bullet.setTexture(&bullet_texture);

    trajectory[0] = (hero_pos_x - pos_x)/(sqrt(pow(hero_pos_x - pos_x,2) + pow(hero_pos_y - pos_y,2))) *speed;
    trajectory[1] = (hero_pos_y - pos_y)/(sqrt(pow(hero_pos_x - pos_x,2) + pow(hero_pos_y - pos_y,2))) *speed;
}

void Bullet::move_bullet()
{
    bullet.setPosition(pos_x = pos_x + trajectory[0],pos_y = pos_y + trajectory[1]);
}



#endif // BULLET_H_INCLUDED
