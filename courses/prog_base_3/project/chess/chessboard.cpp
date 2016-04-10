#include "chessboard.h"

ChessBoard::ChessBoard(RenderWindow* windowPtr)
{
    t_Board.loadFromFile (szField);
    s_Board.setTexture (t_Board);

    boardWidth = s_Board.getLocalBounds().width;
    boardHeight = s_Board.getLocalBounds().height;

    this->windowPtr = windowPtr;
}

ChessBoard::~ChessBoard ()
{

}

void ChessBoard::draw ()
{
    (*windowPtr).draw (s_Board);
}

void ChessBoard::setPosition (Vector2f v)
{
    s_Board.setPosition (v);
}

FloatRect ChessBoard::getLocalBounds()
{
    return s_Board.getLocalBounds();
}
