#include "Rook.hpp"
#include <iostream>

void Rook::GetPotentialMoves()
{
    m_potentialMoves.clear();
    std::vector<Square> squares = m_board.GetSquares(m_postion, 0, 1, 7);
    m_potentialMoves.insert(m_potentialMoves.end(), squares.begin(), squares.end());
    squares = m_board.GetSquares(m_postion, 1, 0, 7);
    m_potentialMoves.insert(m_potentialMoves.end(), squares.begin(), squares.end());
    squares = m_board.GetSquares(m_postion, 0, -1, 7);
    m_potentialMoves.insert(m_potentialMoves.end(), squares.begin(), squares.end());
    squares = m_board.GetSquares(m_postion, -1, 0, 7);
    m_potentialMoves.insert(m_potentialMoves.end(), squares.begin(), squares.end());
}


Rook::Rook(Square* square, Board& board, bool isWhite, const char* symbol) : Piece(square, board, isWhite, symbol) 
{
    if(isWhite)
    {
        board.m_white_rooks.emplace_back(this);
    }
    else
    {
        board.m_black_rooks.emplace_back(this);
    }
}
