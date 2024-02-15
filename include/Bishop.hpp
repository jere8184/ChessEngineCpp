#pragma once

#include "Piece.hpp"


class Bishop : public Piece
{
    public:
    void GetPotentialMoves();
    Bishop(Square* square, Board& board, bool isWhite, const char* symbol);
};