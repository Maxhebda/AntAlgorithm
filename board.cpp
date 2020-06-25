#include "board.h"

Board::Board()
{
    clear();
    ants.clear();
}

void Board::clear()
{
    for (unsigned short int y=0;y<700; y++)
    {
        for(unsigned short int x=0;x<900;x++)
        {
            board[y][x] = 0;        //black
        }
    }
}

unsigned short int Board::get(unsigned short int y, unsigned short int x)
{
    return board[y][x];
}

void Board::set(unsigned short y, unsigned short x, unsigned short floorColour)
{
    board[y][x] = floorColour;
}

QVector <Ant> Board::getAnts()
{
    return ants;
}

Ant Board::getAnt(unsigned short index)
{
    return ants[index];
}

void Board::setAnt(unsigned short index, Ant newAnt)
{
    ants[index] = newAnt;
}

void Board::addAnt(Ant newAnt)
{
    ants.push_back(newAnt);
}

void Board::goNextStep()
{
    unsigned short int antCoun = ants.size();
    unsigned short int floorColour;
    for (unsigned short int index=0;index<antCoun; index++)
    {
        // --- dynamiczna kopia mrówki ---
        Ant * ant = new Ant(getAnt(index).getColour(),getAnt(index).getDirection());
        ant ->setX(getAnt(index).getX());
        ant ->setY(getAnt(index).getY());

        // kolor na ktorym stoi mrowka
        floorColour = board[ant->getY()][ant->getX()];
        //ustawiamy nowy kolor
        board[ant->getY()][ant->getX()] = floorColour==0?ant->getColour():0;
        //przesuwamy tymczasową mrowkę na podstawie podloza na ktorym stoi
        ant->go(floorColour);
        //aktualizujemy mrowkę na planszy
        setAnt(index,*ant);

        delete ant;
    }
}
