#include "King.hpp"
#include <iostream>

void King::GetPotentialMoves()
{
    m_potentialMoves.clear(); 
    std::vector<Square> squares = m_board.GetSquares(m_postion, 0, 1, 1);
    m_potentialMoves.insert(m_potentialMoves.end(), squares.begin(), squares.end());
    squares = m_board.GetSquares(m_postion, 1, 1, 1);
    m_potentialMoves.insert(m_potentialMoves.end(), squares.begin(), squares.end());
    squares = m_board.GetSquares(m_postion, 1, 0, 1);
    m_potentialMoves.insert(m_potentialMoves.end(), squares.begin(), squares.end());
    squares = m_board.GetSquares(m_postion, 1, -1, 1);
    m_potentialMoves.insert(m_potentialMoves.end(), squares.begin(), squares.end());
    squares = m_board.GetSquares(m_postion, 0, -1, 1);
    m_potentialMoves.insert(m_potentialMoves.end(), squares.begin(), squares.end());
    squares = m_board.GetSquares(m_postion, -1, -1, 1);
    m_potentialMoves.insert(m_potentialMoves.end(), squares.begin(), squares.end());
    squares = m_board.GetSquares(m_postion, -1, 0, 1);
    m_potentialMoves.insert(m_potentialMoves.end(), squares.begin(), squares.end());
    squares = m_board.GetSquares(m_postion, -1, 1, 1);
    m_potentialMoves.insert(m_potentialMoves.end(), squares.begin(), squares.end());

    if(CanCastle(true))
    {
        m_potentialMoves.emplace_back(m_board.board[eFile::B][m_postion->rank]);
    }

    if(CanCastle(false))
    {
        m_potentialMoves.emplace_back(m_board.board[eFile::G][m_postion->rank]);
    }
}





bool King::CanCastle(bool QueenSide)
{

    if(!m_moved)
    {
        std::vector<Square> squares;
        if(QueenSide && !m_board.board[eFile::A][m_postion->rank].occupier->m_moved)
        {
            squares = m_board.GetSquares(m_postion, -1, 0, 4);
            if(squares.size() == 4)
            {
                return true;
            }
        }
        else if(!QueenSide && !m_board.board[eFile::H][m_postion->rank].occupier->m_moved)
        {
            squares = m_board.GetSquares(m_postion, 1, 0, 3);
            if(squares.size() == 3)
            {
               return true;
            }
        }
    }
    return false;
}


King::King(Square* square, Board& board, bool isWhite, const char* symbol) : Piece(square, board, isWhite, symbol) 
{
    if(isWhite)
    {
        board.m_white_kings.emplace_back(this);
    }
    else
    {
        board.m_black_kings.emplace_back(this);
    }
}


