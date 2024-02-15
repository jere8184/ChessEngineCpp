#include "Piece.hpp"
#include <algorithm>
#include <iostream>

const Square* Piece::GetPostion()
{
    return m_postion;
}

void Piece::GetPotentialCaptures()
{
    m_potentialCaptures.clear();
    for(Square square : m_potentialMoves)
    {
        if(square.occupier != nullptr && square.occupier->m_white != m_white)
        {
            m_potentialCaptures.push_back(square);
        }
    }
}

void Piece::Move(Square* square)
{
    GetPotentialMoves();
    if(std::find(m_potentialMoves.begin(), m_potentialMoves.end(), square) != m_potentialMoves.end())
    {
        

        if(square->occupier != nullptr)
        {
            if(square->occupier->m_white != m_white)
            {
                square->occupier->m_captured = true;
            }
            else
            {
                std::cout << "cant take on your own color" << std::endl;
                return;
            }
        }
        m_postion->occupier = nullptr;
        m_postion = square;
        m_postion->occupier = this;
        m_moved = true;
    }
    else
    {
        std::cout << "invalid move" << std::endl;
    }
}

void Piece::Move_No_checks(Square* square)
{
    m_postion->occupier = nullptr;
    m_postion = square;
    m_postion->occupier = this;
    m_moved = true;   
}



Piece::Piece(Square* square, Board& board, bool isWhite, const char* symbol):  m_postion(square), m_board(board), m_white(isWhite), m_symbol(symbol) 
{
    std::cout << &square << std::endl;
    
    if(m_white)
    {
        m_board.m_white_pieces.push_back(this);
    }
    else
    {
        m_board.m_black_pieces.push_back(this);
    }

    m_postion->occupier = this;
    m_potentialMoves.reserve(27);
    m_potentialCaptures.reserve(8);
}
