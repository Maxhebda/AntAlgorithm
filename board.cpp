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
