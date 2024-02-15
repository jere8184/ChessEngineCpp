#include "GameStateParser.hpp"
#include "Piece.hpp"
#include <algorithm>


std::vector<Piece*>& GetPiecesFromSymbol(Board* board, char symbol, bool white)
{
    switch(symbol)
    {
    case 'N':
        if(white)
        {
            return board->m_white_knights;
        }
        else
        {
            return board->m_black_knights;
        }
    case 'B':
        if(white)
        {
            return board->m_white_bishops;
        }
        else
        {
            return board->m_black_bishops;
        }
    case 'R':
        if(white)
        {
            return board->m_white_rooks;
        }
        else
        {
            return board->m_black_rooks;
        }
    case 'Q':
        if(white)
        {
            return board->m_white_queens;
        }
        else
        {
            return board->m_black_queens;
        }
    case '0':
    case 'O':
    case 'K':
        if(white)
        {
            return board->m_white_kings;
        }
        else
        {
            return board->m_black_kings;
        }
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'P':
        if(white)
        {
            return board->m_white_pawns;
        }
        else
        {
            return board->m_black_pawns;
        }
    }
    
}

Square* GetSquareFromAlgebraic(const std::string& algebraic_move, Board* board)
{
    char file = algebraic_move[algebraic_move.length() - 2];
    char rank = algebraic_move[algebraic_move.length() -1];
    eFile e_file =(eFile)(file - 'a');
    eRank e_rank = (eRank)(rank - '1');

    return &board->board[e_file][e_rank];
}

Move GetMoveFromAlgebraic(const std::string& algebraic_move, Board* board, bool white)
{
    Move move;
    std::vector<Piece*> pieces;

    move.algebraic_notation = algebraic_move;

    if(algebraic_move[0] == '0' || algebraic_move[0] == 'O')
    {
        if(algebraic_move.length() == 3)
        {
            move.king_side_castle = true;
            move.dest = white ? &board->board[eFile::G][eRank::One] : &board->board[eFile::G][eRank::Eight];
        }
        else
        {
            move.queen_side_castle = true;
            move.dest = white ? &board->board[eFile::B][eRank::One] : &board->board[eFile::B][eRank::Eight];
        }
        move.symbol = 'K';
        return move;
    }
    else
    {
        move.symbol = algebraic_move[0];
    }

    if(algebraic_move.length() == 4 && algebraic_move[1] != 'x')
    {
        move.file_specifier = CharToEfile(algebraic_move[1]);
    }

    move.dest = GetSquareFromAlgebraic(algebraic_move, board);

    return move;
}

Piece* GameStateParser::GetPieceFromMove(Board* board, Move& move, bool white)
{
    std::vector<Piece*> pieces =  GetPiecesFromSymbol(board, move.symbol, white);
    
    for(Piece* piece : pieces)
    {
        if(piece->m_captured)
        {
            continue;
        }
        piece->GetPotentialMoves();
        if(std::find(piece->m_potentialMoves.begin(), piece->m_potentialMoves.end(), move.dest) != piece->m_potentialMoves.end())
        {
            if(move.file_specifier != eFile::F_OUT_OF_BOUNDS)
            {
                if(piece->m_postion->file != move.file_specifier)
                {
                    continue;
                }
            }
            return piece;   
        }
    }
}



std::vector<std::string> SplitString(std::string input_string ,std::string delimiter)
{
    std::vector<std::string> tokens;
    int delimiter_index;

    while(true)
    {
        delimiter_index = input_string.find(delimiter);
        if(delimiter_index == std::string::npos)
        {
            tokens.push_back(input_string.substr(0));
            break;
        }
        tokens.push_back(input_string.substr(0,delimiter_index));
        input_string = input_string.substr(delimiter_index + 1);
    }
    return tokens;
}


std::vector<Turn> GameStateParser::ParseTurns(std::string algebraic_notation, Board* board)
{
    std::vector<Turn> turns; 
    std::vector<std::string> tokens = SplitString(algebraic_notation, " ");
    int turn_number = 0;
    for(int i = 0; i < tokens.size(); i += 3)
    {
        turn_number++;
        Turn turn;
        turn.turn = turn_number;
        turn.white_move = GetMoveFromAlgebraic(tokens[i+1], board, true);
        turn.black_move = GetMoveFromAlgebraic(tokens[i+2], board, false);
        turns.push_back(turn);
    }
    return turns;
}