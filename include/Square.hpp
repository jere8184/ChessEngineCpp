#pragma once

#include "RankFile.hpp"
#include <vector>
#include <string>

class Piece;

struct Square
{
    eFile file;
    eRank rank;
    Piece* occupier = nullptr;
    std::vector<Piece*> white_attackers;
    std::vector<Piece*> black_attackers;
};