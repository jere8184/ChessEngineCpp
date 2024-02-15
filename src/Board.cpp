#include "Board.hpp"
#include "Queen.hpp"
#include "King.hpp"
#include "Pawn.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "GameStateParser.hpp"
#include <iostream>


bool operator==(Square lhs, Square* const rhs)
{
    if(lhs.file == rhs->file && lhs.rank == rhs->rank)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Board::Board()
{
    m_white_pieces.reserve(16);
    m_black_pieces.reserve(16);
    for(unsigned short file = 0; file < 8; file++)
    {
        for(unsigned short rank = 0; rank < 8; rank++)
        {
            board[file][rank].file = static_cast<eFile>(file);
            board[file][rank].rank = static_cast<eRank>(rank);
        }
    }
}

void Board::DrawBoard()
{
    //std::string turn = m_whites_turn ? "White's" : "Black's";
    //std::cout << turn << " turn" <<  std::endl;

    for(short rank = 7; rank > -1; rank--)
    {
        std::cout << rank + 1 << "|";
        for(short file = 0; file < 8; file++)
        {
            Piece* piece = board[file][rank].occupier;
            const char* symbol = piece != nullptr && !piece->m_captured ?  piece->m_symbol : " ";
            std::cout << symbol << "|";
        }
        std::cout << std::endl;
    }
    std::cout << "  a b c d e f g h" <<  std::endl << std::endl;

}

void Board::LoadGameFen(std::string FEN)
{
    unsigned short rank = eRank::Eight;
    unsigned short file = eFile::A;

    int space = FEN.find(' ');
    std::string postions = FEN.substr(0, space);


    std::string turn = FEN.substr(space+1, 1);
    m_whites_turn = turn == "w";

    for(const char c : postions)
    {
        if(c > '0' && c < '9')
        {
            int i = c - '0';
            file += (i - 1);
            continue;
        }

        switch (c)
        {
        case 'P':
            new Pawn(&board[file][rank], *this, true, "P");
            file++;
            break;
        case 'p':
            new Pawn(&board[file][rank], *this, false, "p");
            file++;
            break;
        case 'Q':
            new Queen(&board[file][rank], *this, true, "Q");
            file++;
            break;
        case 'q':
            new Queen(&board[file][rank], *this, false, "q");
            file++;
            break;
        case 'K':
            new King(&board[file][rank], *this, true, "K");
            file++;
            break;
        case 'k':
            new King(&board[file][rank], *this, false, "k");
            file++;
            break;
        case 'R':
            new Rook(&board[file][rank], *this, true, "R");
            file++;
            break;
        case 'r':
            new Rook(&board[file][rank], *this, false, "r");
            file++;
            break;
        case 'B':
            new Bishop(&board[file][rank], *this, true, "B");
            file++;
            break;
        case 'b':
            new Bishop(&board[file][rank], *this, false, "b");
            file++;
            break;
        case 'N':
            new Knight(&board[file][rank], *this, true, "N");
            file++;
            break;
        case 'n':
            new Knight(&board[file][rank], *this, false, "n");
            file++;
            break;
        case '/':
            rank--;
            file = eFile::A;
        }
    } 
}


std::vector<std::string> splitString(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    size_t start = 0;
    size_t end = input.find(delimiter);

    while (end != std::string::npos) {
        token = input.substr(start, end - start);
        tokens.push_back(token);
        start = end + 1;
        end = input.find(delimiter, start);
    }

    token = input.substr(start);
    tokens.push_back(token);

    return tokens;
}


Square* Board::GetSquareFromMove(const std::string& move)
{
    char file = move[move.length() - 2];
    char rank = move[move.length() -1];
    eFile e_file =(eFile)(file - 'a');
    eRank e_rank = (eRank)(rank - '1');

    return &board[e_file][e_rank];
}

void Board::PlayGame(const std::string& algebraic_notation, const std::string& FEN_game_state)
{
    LoadGameFen(FEN_game_state);
    std::vector<Turn> turns = GameStateParser::ParseTurns(algebraic_notation, this);
    DrawBoard();

    for(Turn turn : turns)
    {
        std::cout << "white plays " << turn.white_move.algebraic_notation << std::endl;
        Piece* white_piece =  GameStateParser::GetPieceFromMove(this, turn.white_move, true);
        white_piece->Move(turn.white_move.dest);
        if(turn.white_move.king_side_castle)
        {
            board[eFile::H][eRank::One].occupier->Move_No_checks(&board[eFile::F][eRank::One]);
        }
        else if(turn.white_move.king_side_castle)
        {
            board[eFile::A][eRank::One].occupier->Move_No_checks(&board[eFile::C][eRank::One]);
        }

        DrawBoard();

        std::cout << "black plays " << turn.black_move.algebraic_notation << std::endl;
        Piece* black_piece =  GameStateParser::GetPieceFromMove(this, turn.black_move, false);
        black_piece->Move(turn.black_move.dest);
        if(turn.black_move.king_side_castle)
        {
            board[eFile::H][eRank::Eight].occupier->Move_No_checks(&board[eFile::F][eRank::Eight]);
        }
        else if(turn.black_move.king_side_castle)
        {
            board[eFile::A][eRank::Eight].occupier->Move_No_checks(&board[eFile::C][eRank::Eight]);
        }
        DrawBoard();
    }
}

//returns all squares from upto and including the first occupied square or "end"
std::vector<Square> Board::GetSquares(const Square& begin, const Square& end)
{
    std::vector<Square> squares;

    short file_delta = end.file - begin.file;
    short rank_delta = end.rank - begin.rank;
    short delta = abs(file_delta) > abs(rank_delta) ? abs(file_delta) : abs(rank_delta);

    short file_direction = (file_delta > 0) - (file_delta < 0);
    short rank_direction = (rank_delta > 0) - (rank_delta < 0);

    short file = begin.file;
    short rank = begin.rank;

    for(int i = 0; i < delta; i++)
    {
        file += file_direction;
        rank += rank_direction;
        Square& square = board[file][rank];
        squares.emplace_back(square);
        if(square.occupier != nullptr)
        {
            break;
        }
    }

    return squares;
}

//returns all squares from "begin" upto and including the first occupied square or "end"
std::vector<Square> Board::GetSquares(const Square* begin, short file_direction, short rank_direction, short limit)
{
    std::vector<Square> squares;

    short file_limit = 8;
    if(file_direction == 1)
    {
        file_limit = 7 - begin->file;
    }
    else if(file_direction == -1)
    {
        file_limit = begin->file;
    }

    short rank_limit = 8;
    if(rank_direction == 1)
    {
        rank_limit = 7 - begin->rank;
    }
    else if(rank_direction == -1)
    {
        rank_limit = begin->rank;
    }

    float bound_limit = file_limit < rank_limit ? file_limit : rank_limit;
    limit = limit < bound_limit ? limit : bound_limit;

    short file = begin->file;
    short rank = begin->rank;
    for(int i = 0; i < limit; i++)
    {
        file += file_direction;
        rank += rank_direction;
        Square& square = board[file][rank];
        squares.emplace_back(square);
        if(square.occupier != nullptr)
        {
            break;
        }
    }

    return squares;
}

int main()
{
    std::cout << "hello world" << std::endl;
    /*Board b;
    King wq(&b.board[eFile::A][eRank::One], b, true, "Q");
    b.DrawBoard();
    wq.Move(&b.board[eFile::B][eRank::Two]);
    b.DrawBoard();
    wq.Move(&b.board[eFile::H][eRank::Two]);
    b.DrawBoard();*/
    /*Board b;
    b.LoadGameFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w");
    b.DrawBoard();
    Knight* n = (Knight*)b.board[eFile::B][eRank::One].occupier;
    n->GetPotentialMoves();
    for(auto square : n->m_potentialMoves)
    {
        std::cout << square.file << " " << square.rank << std::endl;
    }*/

    Board b;
    b.PlayGame("1. Nf3 Nf6 2. c4 g6 3. Nc3 Bg7 4. d4 O-O 5. Bf4 d5 6. Qb3 dxc4 7. Qxc4 c6 8. e4 Nbd7 9. Rd1 Nb6 10. Qc5 Bg4 11. Bg5 Na4 12. Qa3 Nxc3 13. bxc3 Nxe4 14. Bxe7 Qb6 15. Bc4 Nxc3");
    std::cout << "bye world" << std::endl;

}