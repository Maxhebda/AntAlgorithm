#ifndef ANT_H
#define ANT_H


class Ant
{
public:
    Ant();
    Ant(unsigned short int color);
    Ant(unsigned short int color, unsigned short int direction);
    unsigned short int getColor();
    unsigned short int getDirection();
    void setDirection(unsigned short int newDirection);
    unsigned short int getX();
    unsigned short int getY();
    void setX(unsigned short int newX);
    void setY(unsigned short int newY);

    // ------ skrecanie i robienie kroku ------
    void turnRight();
    void turnLeft();
    void go(bool floorColor);       // floorColor - kolor na którym znajduje się mrówka 0-czarny 1-bialy(mrowki)

private:
    unsigned short int color;       // - gatunek (color ant)
    unsigned short int x,y;         // - współrzedne mrówki
    unsigned short int direction;   // - zwrot mówrki 0-gora 1-prawo 2-lewo 3-dol
    void goForward();               // - idź do przodu, zmiana wspolrzednych w odpowiednim kierunku i nic wiecej
};

#endif // ANT_H
