#pragma once

#include "Piece.hpp"


class King : public Piece
{
    public:
    void GetPotentialMoves();
    bool CanCastle(bool QueenSide);
    King(Square* square, Board& board, bool isWhite, const char* symbol);
};