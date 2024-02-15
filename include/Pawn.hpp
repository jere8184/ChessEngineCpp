#pragma once

#include "Piece.hpp"


class Pawn : public Piece
{
    public:
    void GetPotentialMoves();
    void GetPotentialAttacks();
    std::vector<Square> m_potentialCaptures;
    Pawn(Square* square, Board& board, bool isWhite, const char* symbol);
};