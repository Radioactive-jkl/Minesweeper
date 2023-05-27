/* * * * * * * * * * * * * * * *
 * Some common settings        *
 *                             *
 * Game basic definitions      *
 * * * * * * * * * * * * * * * */

#ifndef COMMON_H
#define COMMON_H



class COMMON
{
public:

    enum gameLeve
    {
        PRIMARLEVE = 0,
        MIDDLELEVE = 1,
        SENIORLEVE = 2,
        CUSTOMLEVE = 3
    };

    enum primerset
    {
        PRIMARROWANDCOL = 9,
        PRIMARMINNUM    = 10
    };

    enum middleset
    {
        MIDDLEROWANDCOL = 16,
        MIDDLEMINENUM   = 40
    };

    enum seniorset
    {
        SENIORROW     = 16,
        SENIORCOL     = 30,
        SENIORMINENUM = 99
    };

    enum mapset
    {
        MAPWIDTH  = 25,
        MAPHEIGHT = 25
    };

};



#endif // COMMON_H
