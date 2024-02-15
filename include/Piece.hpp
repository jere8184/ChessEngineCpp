#pragma once

#include <vector>
#include "Board.hpp"

class Piece
{
    public:
    const Square* GetPostion();
    virtual void GetPotentialMoves() = 0;
    virtual void GetPotentialCaptures();
    void Move_No_checks(Square* square);
    void Move(Square* square);
    void Capture(const Square& square);

    const char* m_symbol = "Z";
    Piece(Square* square, Board& board, bool isWhite, const char* symbol);
    Square* m_postion = nullptr;
    Board& m_board;
    std::vector<Square> m_potentialMoves;
    std::vector<Square> m_potentialCaptures;
    bool m_captured = false;
    bool m_white;
    bool m_moved = false;

};