#include "../include/Tile.h"

void Tile::settype( int argt )
{
    type = argt;
    switch( type )
    {
    case 0:
        entity.setFillColor(sf::Color::Black);
        entity.setOutlineColor(sf::Color(60,60,60));
        entity.setOutlineThickness(1);
        break;
    case 1:
        entity.setFillColor(sf::Color::Yellow);
        break;
    }
}

void Tile::create( int argx, int argy, int argt = 0 )
{
    xt = argx;
    yt = argy;
    entity.setSize(sf::Vector2f(tsize,tsize));
    entity.setPosition((xt+1)*tsize, (yt+1)*tsize);
    this->settype(argt);
}
