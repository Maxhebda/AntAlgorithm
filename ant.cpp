#include "ant.h"

Ant::Ant()
{
    direction = 0;  //up
    colour = 255;    //white
}

Ant::Ant(unsigned short int colour)
{
    direction = 0;  //up
    this->colour = colour;
}

Ant::Ant(unsigned short int colour, unsigned short int newDirection)
{
    direction = newDirection;
    this->colour = colour;
}

unsigned short int Ant::getColour()
{
    return colour;
}

unsigned short int Ant::getDirection()
{
    return direction;
}

void Ant::setDirection(unsigned short int newDirection)
{
    direction = newDirection;
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
    direction++;
    if (direction>3)
        direction = 0;
}

void Ant::turnLeft()
{
    direction--;
    if (direction<0)
        direction = 3;
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
            y--;
            if (y<0)
                y=699;
        }
        case 1 : {  //rigth
            x++;
            if (x>899)
                x=0;
        }
        case 2 : {  //down
            y++;
            if (y>699)
                y=0;
        }
        case 3 : {  //left
            x--;
            if (x<0)
                x=899;
        }
    }
}

