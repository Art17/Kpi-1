#ifndef PAWN_H_INCLUDED
#define PAWN_H_INCLUDED

#include "abstractfigure.h"

class Pawn : public AbstractFigure
{
    public:
        Pawn (Color, const char*);

        void draw ();

    private:
        Color color;
        int xPos;
        int yPos;

};

#endif // PAWN_H_INCLUDED
