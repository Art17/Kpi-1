#include "chessboard.h"
#include "resources.h"

#include <chessboard_movethread.h>
#include <selectfiguredialog.h>

#include <iostream>

using namespace std;

ChessBoard::ChessBoard(QWidget* Parent, const QPoint& Position, const QSize& Size) :
QSFMLCanvas(Parent, Position, Size), colorWhite (64)
{
    setMouseTracking(true);
}

void ChessBoard::OnInit()
{
    qRegisterMetaType<Move> ("Move");

    selectDialog = new SelectFigureDialog (this);
    infoDialog = new InfoDialog (this);
    scd = new SelectColorDialog (this);

    resetVariables();
    bAgainstComputer = true;

    loadBoard ();
    loadFigures ();
    loadRectangles ();
    loadChessEngine ();

    cbct = new ChessBoardCalcThread (chessEng);
    QObject::connect(cbct, SIGNAL(moveReady(Move)),
                     this, SLOT(moveReady(Move)));
    figureMoveThread = new MoveThread ();
    extraFigureMoveThread = new MoveThread ();

    QObject::connect(figureMoveThread, SIGNAL (resultReady(int)), this, SLOT (onFlipView(int)));

    fillTable ();
    setSpritesPositionAndRects ();
}


void ChessBoard::newGameAgainstHuman()
{
    infoDialog->setText("Playing new game against human");
    infoDialog->exec();
    resetVariables ();
    clearJournal ();
    fillTable ();
    setSpritesPositionAndRects();

    bAgainstComputer = false;

    chessEng->newGame();
    chessEng->setTestMode(false);

}

void ChessBoard::newGameAgainstComputer()
{
    resetVariables ();
    clearJournal ();
    fillTable ();
    setSpritesPositionAndRects();

    bAgainstComputer = true;
    chessEng->newGame();

    if (scd->exec())
    {
        bAsWhite = scd->isWhite();
    }

    if (bAsWhite)
    {
        bLocked = false;
    }
    else
    {
        //flipView ();

        bLocked = true;
        cbct->start();
    }

    /*dbyte allMoves[64];
    int l = 0;
    chessEng->getAllMoves(allMoves, &l, true);
    for (int i = 0; i < l; i++)
        cout << "h " << (int)LOBYTE(allMoves[i])%8 << " " << (int)LOBYTE(allMoves[i])/8 << " "
             << (int)HIBYTE (allMoves[i])%8 << " " << (int)HIBYTE (allMoves[i])/8 << endl;*/
}

void ChessBoard::onFlipView(int i)
{
    /*if (!bAgainstComputer)
    {
        QThread::msleep(100);
        flipView ();
    }*/
}

void ChessBoard::OnUpdate()
{
    this->clear(sf::Color(0, 0, 0));
    this->draw (s_Board);
    if (iSelectedFigure >= 0)
    {
        this->draw (rs_Selected);
    }
    QPoint cursorPoint = mapFromGlobal(QCursor::pos());
    int cx = cursorPoint.x();
    int cy = cursorPoint.y();
    if (cx >= 0 && cx < boardWidth && cy >= 0 & cy < boardHeight)
    {
        int movingTileX = cx / boardTileWidth;
        int movingTileY = cy / boardTileHeight;
        rs_Moving.setPosition( boardTileWidth*movingTileX, movingTileY*boardTileHeight );
        this->draw(rs_Moving);
    }

    if (bWhiteCheck)
    {
        this->draw (rs_Check);
    }
    else if (bBlackCheck)
    {
        this->draw (rs_Check);
    }

    if (lastMoveFrom != -1)
    {
        int lastXFrom = lastMoveFrom % 8;
        int lastYFrom = lastMoveFrom / 8;
        int lastXTo = lastMoveTo % 8;
        int lastYTo = lastMoveTo / 8;

        if ( !bValid[lastYFrom][lastXFrom] )
        {
            this->draw(rs_lastMoveFrom);
        }
        if ( !bValid[lastYTo][lastXTo] )
        {
            this->draw(rs_lastMoveTo);
        }
    }

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (bValid[i][j])
            {
                this->draw(rs_ValidMoveHighlight[i][j]);
            }

    for (int i = 0; i < 32; i++)
    {
        this->draw (s_Figures[i]);
    }
}

void ChessBoard::endGame(int res)
{
    const char* messages[] = {"White won by checkmate",
                             "Black won by checkmate",
                             "Game ended in a draw"};
    infoDialog->setText( QString (messages[res-1]) );
    infoDialog->exec();
}
