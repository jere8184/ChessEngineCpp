#pragma once

#include "Piece.hpp"


class Rook : public Piece
{
    public:
    void GetPotentialMoves();
    Rook(Square* square, Board& board, bool isWhite, const char* symbol);
};