#ifndef FIGURE_H_INCLUDED
#define FIGURE_H_INCLUDED

enum FigureType {PAWN = 1, ROOK, BISHOP, KNIGHT, KING, QUEEN};
enum Color {WHITE = 1, BLACK};

class AbstractFigure
{
    public:
        virtual void draw ();
        virtual FigureType getType ();
};

#endif // FIGURE_H_INCLUDED
