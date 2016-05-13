#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <SFML/Graphics.hpp>
#include <qsfmlcanvas.h>

#include <QMouseEvent>
#include <QStack>

#include <chessengine.h>

using namespace sf;

enum Figures {Rook = 1, Knight = 2, Bishop = 4, Queen = 8, King = 16, Pawn = 32};

struct FigureMovedInfo
{
    Sprite* s_Figure;
    int figure;
    int figureIndex;
    QRect figureMove;

    Sprite* s_ExtraFigure;
    int extraFigure;
    int extraFigureIndex;
    QRect extraFigureMove;
};

class ChessBoard : public QSFMLCanvas
{
public :

    ChessBoard(QWidget* , const QPoint& , const QSize& );

    void undo ();

private :

    virtual void mousePressEvent (QMouseEvent* );
    virtual void mouseMoveEvent (QMouseEvent* );

    void unselect ();

    inline bool isWhite (int);

    void OnInit();
    void OnUpdate();

    void loadFigures ();
    void loadBoard ();

    int indexTable[8][8];
    int figuresTable[8][8];

    const int colorWhite;

    Texture t_Figures;
    Sprite s_Figures[32];

    float boardWidth, boardHeight;
    float boardTileWidth, boardTileHeight;

    float figureWidth, figureHeight;

    int iSelectedFigure;
    int iSelectedTileX, iSelectedTileY;

    int qWhiteDestroyed, qBlackDestroyed;

    QStack<FigureMovedInfo> journal;

    RectangleShape rs_Selected;
    RectangleShape rs_Moving;
    RectangleShape rs_ValidMoveHighlight[8][8];
    bool bValid[8][8];

    ChessEngine* chessEng;

    int movingTileX, movingTileY;

    Texture  t_Board;
    Sprite s_Board;

};

#endif // CHESSBOARD_H
