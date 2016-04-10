#ifndef PAWN_H_INCLUDED
#define PAWN_H_INCLUDED

#include "abstractfigure.h"

class Pawn : public AbstractFigure
{
    public:
        Pawn ();

    private:
        Color color;

};

#endif // PAWN_H_INCLUDED
