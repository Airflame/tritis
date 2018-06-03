#ifndef BLOCK_H
#define BLOCK_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#define R_T 0.2
//#define F_T 0.2
#define M_T 0.1
#define C_T 0.3

class Block
{
public:
    const int tsize = 32;
    bool wholemap[10][20];
    sf::RectangleShape entity[3][3];
    sf::Vector2i abspos;
    std::vector<std::vector<bool>> collidermap;
    std::vector<std::vector<bool>> nextcollidermap;
    int currcollider;
    int nextcollider;
    float F_T = 0.3;
    float rtimer = R_T;
    float ftimer = F_T;
    float mtimer = M_T;
    float ctimer = C_T;
    bool physical = true;
    bool instantfall = false;
    bool lose = false;
    int points = 0;

    Block();
    void refresh( float/*, bool (&argmap)[10][20]*/);
    void movement( float );
    void rotation();
    bool mcollision();
    bool fcollision();
    void newcollider();
    void eraserow( int );
    void restart();
    std::vector<std::vector<bool>> getnextcollider( int );
};

#endif // BLOCK_H
