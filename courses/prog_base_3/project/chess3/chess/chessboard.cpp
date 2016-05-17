#include "chessboard.h"
#include "resources.h"

#include <movethread.h>
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
    selectDialog = new SelectFigureDialog (this);
    egd = new EndGameDialog (this);
    scd = new SelectColorDialog (this);

    resetVariables();
    bAgainstComputer = true;

    loadBoard ();
    loadFigures ();
    loadRectangles ();
    loadChessEngine ();

    fillTable ();
    setSpritesPositionAndRects ();
}


void ChessBoard::newGameAgainstHuman()
{
    resetVariables ();
    clearJournal ();
    fillTable ();
    setSpritesPositionAndRects();

    bAgainstComputer = false;

    chessEng->newGame();
}

void ChessBoard::newGameAgainstComputer()
{
    resetVariables ();
    clearJournal ();
    fillTable ();
    setSpritesPositionAndRects();

    bAgainstComputer = true;

    if (scd->exec())
    {
        bAsWhite = scd->isWhite();
    }

    chessEng->newGame();

    /*dbyte allMoves[64];
    int l = 0;
    chessEng->getAllMoves(allMoves, &l, true);
    for (int i = 0; i < l; i++)
        cout << "h " << (int)LOBYTE(allMoves[i])%8 << " " << (int)LOBYTE(allMoves[i])/8 << " "
             << (int)HIBYTE (allMoves[i])%8 << " " << (int)HIBYTE (allMoves[i])/8 << endl;*/
}


void ChessBoard::OnUpdate()
{
    this->clear(sf::Color(0, 0, 0));
    this->draw (s_Board);
    if (iSelectedFigure >= 0)
    {
        rs_Selected.setPosition(boardTileWidth*iSelectedTileX,
                                 boardTileHeight*iSelectedTileY);

        this->draw (rs_Selected);
    }

    rs_Moving.setPosition( boardTileWidth*movingTileX, movingTileY*boardTileHeight );
    this->draw(rs_Moving);

    if (bWhiteCheck)
    {
        int whitePos = chessEng->getKingPos(true);
        rs_Check.setPosition((whitePos%8)*boardTileWidth, (whitePos/8)*boardTileHeight);
        this->draw (rs_Check);
    }
    else if (bBlackCheck)
    {
        int blackPos = chessEng->getKingPos(false);
        rs_Check.setPosition((blackPos%8)*boardTileWidth, (blackPos/8)*boardTileHeight);
        this->draw (rs_Check);
    }

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (bValid[i][j])
                this->draw(rs_ValidMoveHighlight[i][j]);

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
    egd->setText( QString (messages[res-1]) );
    egd->exec();
}
