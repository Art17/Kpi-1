#include "chessboard.h"

ChessBoard::ChessBoard(RenderWindow* pWindow)
{
    t_Board.loadFromFile (szField);
    s_Board.setTexture (t_Board);

    boardWidth = s_Board.getLocalBounds().width;
    boardHeight = s_Board.getLocalBounds().height;

    this->pWindow = pWindow;
}

ChessBoard::~ChessBoard ()
{

}

void ChessBoard::draw ()
{
    pWindow->draw (s_Board);
}

void ChessBoard::setPosition (Vector2f v2f_Pos)
{
    s_Board.setPosition (v2f_Pos);
}

FloatRect ChessBoard::getLocalBounds()
{
    return s_Board.getLocalBounds();
}
