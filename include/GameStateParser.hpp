#pragma once
#include <string>
#include <vector>
#include "Board.hpp"

struct Move
{
    Square* dest = nullptr;
    char symbol;
    std::string algebraic_notation;
    bool king_side_castle = false;
    bool queen_side_castle = false;
    eFile file_specifier = eFile::F_OUT_OF_BOUNDS;
};


struct Turn
{
    int turn;
    Move white_move;
    Move black_move;
};


class GameStateParser
{
    public:
    //static std::vector<std::string> SplitString(std::string input_string ,std::string delimiter);
    static std::vector<Turn> ParseTurns(std::string algebraic_notation, Board* board);
    static Piece* GetPieceFromMove(Board* board, Move& move, bool white);
    //static Square* GetSquareFromAlgebraic(const std::string& algebraic_move, Board& Board);
    //static Move GetMoveFromAlgebraic(const std::string& algebraic_move, Board& Board, bool white);
};