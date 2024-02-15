#include "Pawn.hpp"
#include <iostream>

void Pawn::GetPotentialMoves()
{
    m_potentialMoves.clear(); 
    std::vector<Square> move_squares;
    short rank_direction = m_white ? 1 : -1;
    short range = m_moved ? 1 : 2;

    move_squares = m_board.GetSquares(m_postion, 0, rank_direction, range);
    m_potentialMoves.insert(m_potentialMoves.end(), move_squares.begin(), move_squares.end());


    std::vector<Square> attack_squares;
    auto left = m_board.GetSquares(m_postion, -1, rank_direction, 1);
    auto right = m_board.GetSquares(m_postion, 1, rank_direction, 1);

    if(!left.empty())
    {
        attack_squares.push_back(left[0]);
    }
    if(!right.empty())
    {
        attack_squares.push_back(right[0]);
    }

    for(auto square : attack_squares)
    {
        if(square.occupier != nullptr && square.occupier->m_white != m_white)
        {
            m_potentialMoves.push_back(square);
        }
    }

}


Pawn::Pawn(Square* square, Board& board, bool isWhite, const char* symbol) : Piece(square, board, isWhite, symbol)
{
    if(isWhite)
    {
        m_board.m_white_pawns.emplace_back(this);
    }
    else
    {
        m_board.m_black_pawns.emplace_back(this);
    }
}
