#pragma once


//maybe I should make enums signed shorts and set the first value to defaulut

//should i make enums class enums and add implicit conversions to bas type

enum eFile : unsigned short {A, B, C, D, E, F, G, H, F_OUT_OF_BOUNDS};

template<typename T>
eFile operator+(eFile file, T size)
{
    short file_val = (short)file + size;

    if(file_val > 7 || file_val < 0 )
    {
        return eFile::F_OUT_OF_BOUNDS;
    }
    return (eFile)file_val;
}

template<typename T>
eFile operator-(eFile file, T size)
{
    short file_val = (short)file - size;

    if(file_val > 7 || file_val < 0 )
    {
        return eFile::F_OUT_OF_BOUNDS;
    }
    return (eFile)file_val;
}

eFile CharToEfile(char c);

/*eFile operator++(eFile file)
{
    if(file == eFile::H)
    {
        return eFile::H;
    }
    unsigned short s = ++file;
    return (eFile)s;
}

eFile operator--(eFile file)
{
    if(file == eFile::A)
    {
        return eFile::A;
    }
    unsigned short s = --file;
    return (eFile)s;
}
*/

enum eRank : unsigned short {One, Two, Three, Four, Five, Six, Seven, Eight, R_OUT_OF_BOUNDS};

template<typename T>
eRank operator+(eRank rank, T size)
{
    short rank_val = (short)rank + size;

    if(rank_val > 7 || rank_val < 0)
    {
        return eRank::R_OUT_OF_BOUNDS;
    }
    return (eRank)rank_val;
}

template<typename T>
eRank operator-(eRank rank, T size)
{
    short rank_val = (short)rank - size;

    if(rank_val > 7 || rank_val < 0)
    {
        return eRank::R_OUT_OF_BOUNDS;
    }
    return (eRank)rank_val;
}

/*
eRank operator++(eRank file)
{
    if(file == eRank::Eight)
    {
        return eRank::Eight;
    }
    unsigned short s = ++file;
    return (eRank)s;
}

eRank operator--(eRank file)
{
    if(file == eRank::One)
    {
        return eRank::One;
    }
    unsigned short s = --file;
    return (eRank)s;
}
*/
