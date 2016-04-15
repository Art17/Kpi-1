#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <SFML/Graphics.hpp>
#include <qsfmlcanvas.h>

using namespace sf;

enum Figures {Pawn = 1, Knight, Bishop, Rook, Queen, King};

class ChessBoard : public QSFMLCanvas
{
public :

    ChessBoard(QWidget* , const QPoint& , const QSize& );

private :

    void OnInit();
    void OnUpdate();

    void loadFigures ();

    Texture t_Figures;
    Sprite s_Figures[32];

    Texture  t_Board;
    Sprite s_Board;
};

#endif // CHESSBOARD_H
