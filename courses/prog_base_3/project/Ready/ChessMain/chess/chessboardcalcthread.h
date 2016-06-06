#ifndef CHESSBOARD_CALCTHREAD_H
#define CHESSBOARD_CALCTHREAD_H

#include <QThread>
#include <ChessEngine.h>

class ChessBoardCalcThread : public QThread
{
    Q_OBJECT
public:
    ChessBoardCalcThread(ChessEngine*);

    void run();

signals:
    void moveReady (Move);
private:
    ChessEngine* chessEng;
};

#endif // CHESSBOARD_CALCTHREAD_H
