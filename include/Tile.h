#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>

class Tile
{
public:
    const int tsize = 32;
    int xt, yt, type;
    sf::RectangleShape entity;

    void settype( int );
    void create( int , int , int );
};

#endif // TILE_H
