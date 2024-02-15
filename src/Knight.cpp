#include "Knight.hpp"
#include <iostream>

void Knight::GetPotentialMoves()
{
    int moves[8][2] = {{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1},{-1,2}};

    for(int i = 0; i < 8 ;i++)
    {
        eFile file = m_postion->file + moves[i][0];
        eRank rank = m_postion->rank + moves[i][1];
        if(file != eFile::F_OUT_OF_BOUNDS && rank != eRank::R_OUT_OF_BOUNDS)
        {
            m_potentialMoves.emplace_back(m_board.board[file][rank]);
        }
    }

    
}


Knight::Knight(Square* square, Board& board, bool isWhite, const char* symbol) : Piece(square, board, isWhite, symbol) 
{
    if(isWhite)
    {
        board.m_white_knights.emplace_back(this);
    }
    else
    {
        board.m_black_knights.emplace_back(this);
    }
}
