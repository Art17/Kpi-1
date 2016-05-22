#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <SFML/Graphics.hpp>
#include <qsfmlcanvas.h>

#include <QMouseEvent>
#include <QStack>

#include <chessengine.h>
#include <figures.h>
#include <selectfiguredialog.h>
#include <infodialog.h>

#include <qmessagebox.h>
#include <selectcolordialog.h>

#include <chessboardcalcthread.h>
#include <chessboard_movethread.h>

#include <QMutex>

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
    bool undoLow ();

    int makeMove (const Move& );

private slots:
    void moveReady(Move);
    void onFlipView (int);

private :
    virtual void mousePressEvent (QMouseEvent* );
    void OnInit();
    void OnUpdate();

    void unselect ();

    inline bool isWhite (int figure)
    {
        return (figure & colorWhite) == colorWhite;
    }

    void endGame (int);

    void loadFigures ();
    void loadBoard ();
    void loadRectangles ();
    void loadChessEngine ();
    void resetVariables ();
    void clearJournal ();
    void initFigureRects ();

    void flipView ();
    void select(int, int);

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
    bool bAgainstComputer, bAsWhite, bLocked;

    int lastMoveFrom, lastMoveTo;

    QStack<FigureMovedInfo> journal;

    RectangleShape rs_Selected;
    RectangleShape rs_Moving;
    RectangleShape rs_ValidMoveHighlight[8][8];
    bool bValid[8][8];
    RectangleShape rs_Check;

    IntRect figureRects[6][2];

    ChessEngine* chessEng;

    Texture  t_Board;
    Sprite s_Board;

    SelectFigureDialog* selectDialog;
    InfoDialog* infoDialog;
    SelectColorDialog* scd;

    MoveThread* figureMoveThread;
    MoveThread* extraFigureMoveThread;

    ChessBoardCalcThread* cbct;

};

#endif // CHESSBOARD_H
