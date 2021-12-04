#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

class Bullet
{
    private:
        float speed = 0.05;
        int damage;

        float pos_x;
        float pos_y;

        int size = 5;

        sf::Texture bullet_texture;

        std::string bullet_dir = "Textures/Shooter_bullet.png";

        float trajectory[2];
    public:
        Bullet(float x,float y, int damage);

        void set_trajectory(float hero_pos_x,float hero_pos_y);
        void move_bullet();

        float get_pos_x() {return pos_x;}
        float get_pos_y() {return pos_y;}
        int get_damage() {return damage;}

        sf::RectangleShape bullet;
};

Bullet::Bullet(float x,float y, int dmg)
{
    bullet.setSize(sf::Vector2f(size,size));

    pos_x = x;
    pos_y = y;
    damage = dmg;

    bullet.setPosition(x,y);

    bullet_texture.loadFromFile(bullet_dir);
    bullet.setTexture(&bullet_texture);
}

void Bullet::set_trajectory(float hero_pos_x,float hero_pos_y)
{
    trajectory[0] = (hero_pos_x - pos_x)/(sqrt(pow(hero_pos_x - pos_x,2) + pow(hero_pos_y - pos_y,2))) *speed;
    trajectory[1] = (hero_pos_y - pos_y)/(sqrt(pow(hero_pos_x - pos_x,2) + pow(hero_pos_y - pos_y,2))) *speed;
}

void Bullet::move_bullet()
{
    bullet.setPosition(pos_x = pos_x + trajectory[0],pos_y = pos_y + trajectory[1]);
}



#endif // BULLET_H_INCLUDED
