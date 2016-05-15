#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <SFML/Graphics.hpp>
#include <qsfmlcanvas.h>

#include <QMouseEvent>
#include <QStack>

#include <chessengine.h>
#include <figures.h>
#include <selectfiguredialog.h>

using namespace sf;


struct FigureMovedInfo
{
    Sprite* s_Figure;
    int figure;
    int figureIndex;
    QRect figureMove;
    bool bPromoted;

    Sprite* s_ExtraFigure;
    int extraFigure;
    int extraFigureIndex;
    QRect extraFigureMove;
};

class ChessBoard : public QSFMLCanvas
{
    Q_OBJECT
public :

    ChessBoard(QWidget* , const QPoint& , const QSize& );

    void newGameAgainstComputer ();
    void newGameAgainstHuman ();

    void undo ();

private :

    virtual void mousePressEvent (QMouseEvent* );
    virtual void mouseMoveEvent (QMouseEvent* );

    void unselect ();

    inline bool isWhite (int figure)
    {
        return (figure & colorWhite) == colorWhite;
    }

    void OnInit();
    void OnUpdate();

    void loadFigures ();
    void loadBoard ();
    void loadRectangles ();
    void loadChessEngine ();
    void resetVariables ();
    void clearJournal ();
    void initFigureRects ();

    void fillTable ();
    void setSpritesPositionAndRects ();

    void setSpriteRect (Sprite* , int);

    int indexTable[8][8];
    int figuresTable[8][8];

    const int colorWhite;

    Texture t_Figures;
    Sprite s_Figures[32];

    float boardWidth, boardHeight;
    float boardTileWidth, boardTileHeight;

    float figureWidth, figureHeight;
    float figureOriginalWidth, figureOriginalHeight;

    int iSelectedFigure;
    int iSelectedTileX, iSelectedTileY;

    bool bWhiteCheck, bBlackCheck;
    bool bAgainstComputer;

    QStack<FigureMovedInfo> journal;

    RectangleShape rs_Selected;
    RectangleShape rs_Moving;
    RectangleShape rs_ValidMoveHighlight[8][8];
    bool bValid[8][8];
    RectangleShape rs_Check;

    IntRect figureRects[6][2];

    ChessEngine* chessEng;

    int movingTileX, movingTileY;

    Texture  t_Board;
    Sprite s_Board;

    SelectFigureDialog* selectDialog;

};

#endif // CHESSBOARD_H
