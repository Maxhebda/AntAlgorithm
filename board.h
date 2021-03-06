#ifndef BOARD_H
#define BOARD_H
#include <QVector>
#include <ant.h>

class Board
{
public:
    Board();
    void clear();
    unsigned short int get(unsigned short int y, unsigned short int x);
    void set(unsigned short int y, unsigned short int x, unsigned short int floorColor);
    QVector <Ant> getAnts();
    Ant getAnt(unsigned short int index);
    void setAnt(unsigned short int index, Ant newAnt);
    void addAnt(Ant newAnt);
    void deleteAnt(unsigned short int index);
    void goNextStep();

private:
    unsigned short int board[350][450];
    QVector <Ant> ants;
};

#endif // BOARD_H
