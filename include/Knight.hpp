#pragma once

#include "Piece.hpp"


class Knight : public Piece
{
    public:
    void GetPotentialMoves();
    Knight(Square* square, Board& board, bool isWhite, const char* symbol);
};