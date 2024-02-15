#include "Bishop.hpp"
#include <iostream>

void Bishop::GetPotentialMoves()
{
    m_potentialMoves.clear(); 
    std::vector<Square> squares = m_board.GetSquares(m_postion, 1, 1, 7);
    m_potentialMoves.insert(m_potentialMoves.end(), squares.begin(), squares.end());
    squares = m_board.GetSquares(m_postion, 1, -1, 7);
    m_potentialMoves.insert(m_potentialMoves.end(), squares.begin(), squares.end());
    squares = m_board.GetSquares(m_postion, -1, -1, 7);
    m_potentialMoves.insert(m_potentialMoves.end(), squares.begin(), squares.end());
    squares = m_board.GetSquares(m_postion, -1, 1, 7);
    m_potentialMoves.insert(m_potentialMoves.end(), squares.begin(), squares.end());
}


Bishop::Bishop(Square* square, Board& board, bool isWhite, const char* symbol) : Piece(square, board, isWhite, symbol) 
{
    if(isWhite)
    {
        board.m_white_bishops.emplace_back(this);
    }
    else
    {
        board.m_black_bishops.emplace_back(this);
    }
}
