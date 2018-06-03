#include "../include/Block.h"

Block::Block()
{
    for( int i = 0; i < 3; i++ )
    {
        for( int j = 0; j < 3; j++ )
        {
            entity[i][j].setSize(sf::Vector2f(tsize, tsize));
        }
    }
    currcollider = rand() % 7;
    collidermap = getnextcollider(currcollider);
    nextcollider = rand() % 7;
    nextcollidermap = getnextcollider(nextcollider);
    abspos.x = 6;
    abspos.y = -1;
}

void Block::refresh( float dt )
{
    for( int i = 0; i < 3; i++ )
    {
        for( int j = 0; j < 3; j++ )
        {
            entity[i][j].setPosition( (i+abspos.x-1)*tsize-1, (j+abspos.y-1)*tsize-1 );
            if( collidermap[j][i] )
                entity[i][j].setFillColor(sf::Color::Blue);
            else
                entity[i][j].setFillColor(sf::Color(0,0,0,0));
        }
    }
    rtimer += dt;
    ftimer += dt;
    mtimer += dt;
}

void Block::rotation()
{
    if( physical and currcollider != 6 )
    {
        if( rtimer >= R_T )
        {
            std::vector<std::vector<bool>> argmap;
            argmap = collidermap;
            for( int i = 0; i < 3; i++ )
            {
                for( int j = 0; j < 3; j++ )
                {
                    collidermap[j][i] = 0;
                }
            }
            /*for( int i = 0; i < 3; i++ )
            {
                for( int j = 0; j < 3; j++ )
                {
                    if( argmap[j][i] )
                        collidermap[2-i][j] = 1;
                }
            }*/
            for( int i = 0; i < 3; i++ )
            {
                for( int j = 0; j < 3; j++ )
                {
                    if( argmap[j][i] )
                        collidermap[i][2-j] = 1;
                }
            }
            rtimer = 0;
            if( mcollision() )
            {
                abspos.x -= 1;
                if( !mcollision() )
                    return;
                abspos.x += 2;
                if( !mcollision() )
                    return;
                abspos.x -= 1;
                collidermap = argmap;
            }
        }

    }
}

void Block::movement( float dt )
{
    if( !lose )
    {
        if( physical )
        {
            sf::Vector2i oldpos = abspos;
            if( ftimer >= F_T or instantfall )
            {
                abspos.y += 1;
                ftimer = 0;
            }
            if( abspos.y > 1 )
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    rotation();
                }
                if( mtimer >= M_T )
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    {
                        abspos.x -= 1;
                        mtimer = 0;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    {
                        abspos.x += 1;
                        mtimer = 0;
                    }
                }

                if( mcollision() )
                    abspos = oldpos;
                if( fcollision() )
                {
                    if( abspos.y == 1 )
                        lose = true;
                    if( ctimer <= 0 or instantfall )
                    {
                        physical = false;
                        ctimer = C_T;
                    }
                    ctimer -= dt;
                }
            }
        }
        else
        {
            for( int i = 0; i < 3; i++ )
            {
                for( int j = 0; j < 3; j++ )
                {
                    if( collidermap[j][i] )
                    {
                        int x = abspos.x - 1 + i;
                        int y = abspos.y - 1 + j;
                        wholemap[x-1][y-1] = true;
                    }
                }
            }
            instantfall = false;
            abspos.x = 6;
            abspos.y = -1;
            int newpoints = 0;
            for( int j = 0; j < 20; j++ )
            {
                bool fullrow = true;
                for( int i = 0; i < 10; i++ )
                {
                    if( !wholemap[i][j] )
                    {
                        fullrow = false;
                        break;
                    }
                }
                if( fullrow )
                {
                    newpoints++;
                    eraserow( j );
                }
            }
            points += newpoints*newpoints;
            newcollider();
            if( !lose )
                physical = true;
        }
    }
}

bool Block::mcollision()
{
    for( int i = 0; i < 3; i++ )
    {
        for( int j = 0; j < 3; j++ )
        {
            if( collidermap[j][i] == 1 and (abspos.y + j - 1 > 20 or abspos.x - 1 + i < 1 or abspos.x - 1 + i > 10 or wholemap[(int)(abspos.x + i - 2)][(int)(abspos.y + j - 2)]) )
            {
                return true;
            }
        }
    }
    return false;
}

bool Block::fcollision()
{
    for( int i = 0; i < 3; i++ )
    {
        for( int j = 0; j < 3; j++ )
        {
            if( collidermap[j][i] == 1 and ( abspos.y + j > 20 or ( (abspos.x+i-2 < 10 and abspos.x+i-2 >= 0) ? wholemap[(int)(abspos.x + i - 2)][(int)(abspos.y + j - 1)] : false ) )  )
            {
                return true;
            }
        }
    }
    return false;
}

void Block::newcollider()
{
    collidermap.clear();
    collidermap = nextcollidermap;
    currcollider = nextcollider;
    nextcollider = rand() % 7;
    nextcollidermap = getnextcollider(nextcollider);
}

void Block::eraserow( int argrow )
{
    for( int i = argrow; i > 0; i-- )
    {
        for( int j = 0; j < 10; j++ )
        {
            wholemap[j][i] = wholemap[j][i-1];
        }
    }
    for( int j = 0; j < 10; j++ )
    {
        wholemap[j][0] = false;
    }
}

std::vector<std::vector<bool>> Block::getnextcollider( int i )
{
    std::vector<std::vector<bool>> argmap;
    switch( i )
    {
    case 0:
        argmap =
        {
            {0,1,0},
            {0,1,0},
            {0,1,0},
        };
        break;
    case 1:
        argmap =
        {
            {0,1,0},
            {0,1,0},
            {1,1,0},
        };
        break;
    case 2:
        argmap =
        {
            {1,1,0},
            {0,1,0},
            {0,1,0},
        };
        break;
    case 3:
        argmap =
        {
            {1,0,0},
            {1,1,0},
            {0,1,0},
        };
        break;
    case 4:
        argmap =
        {
            {0,1,0},
            {1,1,0},
            {1,0,0},
        };
        break;
    case 5:
        argmap =
        {
            {0,1,0},
            {1,1,0},
            {0,1,0},
        };
        break;
    case 6:
        argmap =
        {
            {1,1,0},
            {1,1,0},
            {0,0,0},
        };
        break;
    }
    return argmap;
}

void Block::restart()
{
    lose = false;
    points = 0;
    abspos.x = 6;
    abspos.y = -4;
    for( int i = 0; i < 10; i++ )
    {
        for( int j = 0; j < 20; j++ )
        {
            wholemap[i][j] = 0;
        }
    }
    currcollider = rand() % 7;
    collidermap = getnextcollider(currcollider);
    nextcollider = rand() % 7;
    nextcollidermap = getnextcollider(nextcollider);
    physical = true;
    rtimer = R_T;
    ftimer = F_T;
    mtimer = M_T;
    instantfall = false;
    return;
}
