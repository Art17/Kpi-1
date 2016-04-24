#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <SFML/Graphics.hpp>
#include <qsfmlcanvas.h>

#include <QMouseEvent>

using namespace sf;

enum Figures {Pawn = 1, Knight, Bishop, Rook, Queen, King};

class ChessBoard : public QSFMLCanvas
{
public :

    ChessBoard(QWidget* , const QPoint& , const QSize& );

private :

    virtual void mousePressEvent (QMouseEvent* );
    /*virtual void mouseMoveEvent (QMouseEvent*);
    virtual void mouseReleaseEvent (QMouseEvent*);*/

    void OnInit();
    void OnUpdate();

    void loadFigures ();
    void loadBoard ();

    int indexTable[8][8];

    Texture t_Figures;
    Sprite s_Figures[32];

    float boardWidth, boardHeight;
    float boardTileWidth, boardTileHeight;

    float figureWidth, figureHeight;

    int boardMarginTop, boardMarginBottom, boardMarginLeft, boardMarginRight;
    int figureMarginX, figureMarginY;

    int iSelectedFigure;
    int iSelectedTileX, iSelectedTileY;

    Texture  t_Board;
    Sprite s_Board;

};

#endif // CHESSBOARD_H
