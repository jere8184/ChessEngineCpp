#pragma once

#include "Square.hpp"
#include <vector>
#include <string>

bool operator==(Square lhs, Square* const rhs);

class Board
{
    public:
    Square board[8][8];
    bool m_whites_turn = true;
    Board();
    void DrawBoard();
    void LoadGameFen(std::string FEN);
    void PlayGame(const std::string& algebraic_notation, const std::string& FEN_game_state = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w");
    std::vector<Square> GetSquares(const Square& begin, const Square& end);
    std::vector<Square> GetSquares(const Square* begin, short file_direction, short rank_direction, short limit);
    std::vector<Piece*> m_white_pieces;
    std::vector<Piece*> m_black_pieces;
    std::vector<Piece*> m_white_pawns;
    std::vector<Piece*> m_black_pawns;
    std::vector<Piece*> m_white_knights;
    std::vector<Piece*> m_black_knights;
    std::vector<Piece*> m_white_bishops;
    std::vector<Piece*> m_black_bishops;
    std::vector<Piece*> m_white_rooks;
    std::vector<Piece*> m_black_rooks;
    std::vector<Piece*> m_white_queens;
    std::vector<Piece*> m_black_queens;
    std::vector<Piece*> m_white_kings;
    std::vector<Piece*> m_black_kings;

    Square* GetSquareFromMove(const std::string& move);
    friend class GameStateParser;

};