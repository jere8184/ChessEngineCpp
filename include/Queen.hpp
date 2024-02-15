#pragma once

#include "Piece.hpp"


class Queen : public Piece
{
    public:
    void GetPotentialMoves();
    Queen(Square* square, Board& board, bool isWhite, const char* symbol);
};