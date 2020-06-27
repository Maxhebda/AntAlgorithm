#include "ant.h"

Ant::Ant()
{
    direction = 0;  //up
    Color = 11;     //white
}

Ant::Ant(unsigned short int Color)
{
    direction = 0;  //up
    this->Color = Color;
}

Ant::Ant(unsigned short int Color, unsigned short int newDirection)
{
    direction = newDirection;
    this->Color = Color;
}

unsigned short int Ant::getColor()
{
    return Color;
}

unsigned short int Ant::getDirection()
{
    return direction;
}

void Ant::setDirection(unsigned short int newDirection)
{
    direction = newDirection;
}

void Ant::setColor(unsigned short newColor)
{
    Color = newColor;
}

unsigned short int Ant::getX()
{
    return x;
}

unsigned short int Ant::getY()
{
    return y;
}

void Ant::setX(unsigned short newX)
{
    x = newX;
}

void Ant::setY(unsigned short newY)
{
    y = newY;
}

void Ant::turnRight()
{
    if (direction<3)
    {
       direction++;
    }
    else
    {
       direction=0;
    }
}

void Ant::turnLeft()
{
    if (direction<1)
    {
        direction=3;
    }
    else
    {
        direction--;
    }
}

void Ant::go(bool floorColor)
{
    if (floorColor==0)
    {
        turnRight();
    }
    else
    {
        turnLeft();
    }
    goForward();
}

void Ant::goForward()
{
    switch (direction) {
        case 0 : {  //up
            if (y>0)
                y--;
            else
                y=349;
            break;
        }
        case 1 : {  //rigth
            if (x<449)
                x++;
            else
                x=0;
            break;
        }
        case 2 : {  //down
            if (y<349)
                y++;
            else
                y=0;
            break;
        }
        case 3 : {  //left
            if (x>0)
                x--;
            else
                x=449;
            break;
        }
    }
}

