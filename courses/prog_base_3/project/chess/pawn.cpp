#include "pawn.h"

Pawn::Pawn (Color color, const char* pos)
{
    xPos = pos[0] - 'A';
    yPos = pos[1] - '0';
    this->color = color;
}

void Pawn::draw ()
