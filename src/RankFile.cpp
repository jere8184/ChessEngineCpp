#include "RankFile.hpp"


eFile CharToEfile(char c)
{
    short file_val = c - 'a';

    if(file_val > 7 || file_val < 0 )
    {
        return eFile::F_OUT_OF_BOUNDS;
    }

    return (eFile)file_val;
}