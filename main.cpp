#include "include/Tile.h"
#include "include/Block.h"
#define TSIZE 32
#include <SFML/Audio.hpp>
#include <sstream>

int main()
{
    sf::Clock clock;
    float dt = 0;
    sf::RenderWindow window(sf::VideoMode(600, 704), "Tritis");
    window.setFramerateLimit(240);
    srand (time(NULL));

    sf::RectangleShape bgtiles( sf::Vector2f(10*TSIZE, 20*TSIZE) );
    bgtiles.setPosition( TSIZE, TSIZE );
    bgtiles.setFillColor( sf::Color::Black );
    bgtiles.setOutlineColor( sf::Color::White );
    bgtiles.setOutlineThickness( 3 );

    sf::RectangleShape nxtiles( sf::Vector2f(3*TSIZE, 3*TSIZE) );
    nxtiles.setPosition( 13*TSIZE, TSIZE );
    nxtiles.setFillColor( sf::Color::Black );
    nxtiles.setOutlineColor( sf::Color::White );
    nxtiles.setOutlineThickness( 3 );

    sf::Font font;
    font.loadFromFile("res/Square.ttf");

    sf::Text t_headpoints;
    t_headpoints.setFont(font);
    t_headpoints.setString("Points");
    t_headpoints.setCharacterSize(32);
    t_headpoints.setFillColor(sf::Color::White);
    t_headpoints.setPosition( 12.9*TSIZE, 5*TSIZE );

    sf::Text t_points;
    t_points.setFont(font);
    t_points.setString("0");
    t_points.setCharacterSize(32);
    t_points.setFillColor(sf::Color::White);
    t_points.setPosition( 12.9*TSIZE, 6*TSIZE );

    sf::Text t_gameover;
    t_gameover.setFont(font);
    t_gameover.setString("Game over");
    t_gameover.setCharacterSize(64);
    t_gameover.setFillColor(sf::Color::White);
    t_gameover.setPosition( 1.1*TSIZE, 9*TSIZE );

    sf::Text t_pause;
    t_pause.setFont(font);
    t_pause.setString("Paused");
    t_pause.setCharacterSize(64);
    t_pause.setFillColor(sf::Color::White);
    t_pause.setPosition( 2.5*TSIZE, 9*TSIZE );


    Tile tiles[10][20];
    Tile tilesn[3][3];

    bool focused = true;

    Block b;
    for( int i = 0; i < 10; i++ )
    {
        for( int j = 0; j < 20; j++ )
        {
            b.wholemap[i][j] = 0;
            tiles[i][j].create(i, j, 0);
        }
    }
    for( int i = 0; i < 3; i++ )
    {
        for( int j = 0; j < 3; j++ )
        {
            tilesn[i][j].create(i+12, j, 0);
        }
    }

    while (window.isOpen())
    {
        std::stringstream ss;
        std::string s_points;
        ss << b.points;
        s_points = ss.str();
        t_points.setString(s_points);
        ss.clear();

        window.clear(sf::Color::Black);
        window.draw(bgtiles);
        window.draw(nxtiles);
        window.draw(t_headpoints);
        window.draw(t_points);
        for( int i = 0; i < 10; i++ )
        {
            for( int j = 0; j < 20; j++ )
            {
                if( b.wholemap[i][j] == 1 )
                    tiles[i][j].settype(1);
                else
                    tiles[i][j].settype(0);
                window.draw( tiles[i][j].entity );
            }
        }
        for( int i = 0; i < 3; i++ )
        {
            for( int j = 0; j < 3; j++ )
            {
                if( b.nextcollidermap[j][i] == 1 )
                    tilesn[i][j].settype(1);
                else
                    tilesn[i][j].settype(0);
            }
        }
        for( int i = 0; i < 3; i++ )
        {
            for( int j = 0; j < 3; j++ )
            {
                window.draw( b.entity[i][j] );
                window.draw( tilesn[i][j].entity );
            }
        }
        if( b.lose )
            window.draw(t_gameover);

        if( focused )
        {
            b.refresh( dt );
            b.movement( dt );
        }

        if( !focused and !b.lose )
        {
            window.draw(t_pause);
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Down)
                {
                    b.F_T = 0.05;
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    b.instantfall = true;
                }
                else if (event.key.code == sf::Keyboard::R )
                {
                    b.restart();
                }
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Down)
                {
                    b.F_T = 0.3;
                }
            }
            if (event.type == sf::Event::LostFocus)
                focused = false;
            if (event.type == sf::Event::GainedFocus)
                focused = true;
        }
        window.display();

        dt = clock.restart().asSeconds();
    }

    return 0;
}
