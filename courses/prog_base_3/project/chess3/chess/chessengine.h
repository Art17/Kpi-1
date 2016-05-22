#ifndef CHESSENGINE_H
#define CHESSENGINE_H

#include <stack>
#include <cstdio>
#include <list>
#include <vector>
#include <QList>

#include "figures.h"

#define MAKEWORD(a,b)   ((short)(((char)(a))|(((short)((char)(b)))<<8)))
#define LOBYTE(w)	((char)(w))
#define HIBYTE(w)	((char)(((short)(w)>>8)&0xFF))

#define WHITE_LEFT_CASTLING 1
#define WHITE_RIGHT_CASTLING 2
#define BLACK_LEFT_CASTLING 4
#define BLACK_RIGHT_CASTLING 8

using namespace std;

typedef char byte;
typedef short dbyte;

enum Status {ACTIVE_GAME=0, WHITE_WON, BLACK_WON, DRAW};

struct Move
{
    byte from;
    byte to;
    byte extra;
};

struct ExtraMove
{
    byte from;
    byte to;

    byte extraFigure;  // pawn promotion

    byte beatenFigure; // include passant
    byte beatenFigurePos;

    byte castlingFigureFrom;
    byte castlingFigureTo;

    int canCastling;  // doesnt take care about beaten rooks, getKingMoves checks it
};

class ChessEngine
{
    public:
        ChessEngine();

        void newGame ();
        void setTestMode (bool);

        bool isValidMove (const Move&);

        byte* getValidMoves (int from, byte moves[], int* lPtr);

        void getBestMove (Move* );
        int makeMove (const Move& );

        bool getBoard (byte* );
        void setBoard (byte*, bool);

        int getKingPos (bool) const;
        bool isCheck (bool) const;

        bool undo ();

        bool isBeaten (int, bool) const;
        int isEnd ();

        dbyte* getAllMoves (dbyte*, int*, bool);
    private:

        int minmax (Move* pRes, int depth);
        int getOptimalDepth ();
        int EvaluatePlayerPosition (bool bWhite);
        int AlphaBetaPruning (int alpha, int beta, int depth, bool curPlayer, Move* pRes, int, int);
        byte* getRookMoves (int , byte [], int* ) ;
        byte* getKnightMoves (int , byte [], int* ) ;
        byte* getBishopMoves (int , byte [], int* ) ;
        byte* getQueenMoves (int , byte [], int* ) ;
        byte* getKingMoves (int, byte [], int* ) ;
        byte* getPawnMoves (int, byte [], int* ) ;

        byte* getValidMovesLow (int, byte [], int*);

        bool isFigurePinned (int from, int to) ;
        int makeMoveLow (const Move& );
        void makeMoveLL (const Move& );

        void getRandomMove (Move* );
        void getRandomBeatMove (Move* pRes);

        void reload ();
        void fillBoard ();

        byte board[8][8];
        const byte colorWhite;

        int canCastling, whiteKingPos, blackKingPos;

        bool whiteTurn;

        bool bTestMode;

        stack<ExtraMove> lastMoves;

        inline bool isDifferentColor (int f1, int f2) const
        {
            return (((f1 & colorWhite) ^ (f2 & colorWhite)) == colorWhite);
        }
        inline bool isWhite (int figure) const
        {
            return (figure & colorWhite) == colorWhite;
        }
        inline int cti (int x, int y) const
        {
            return y*8 + x;
        }
        inline int getFigurePower (int figure)
        {
            if (figure & Pawn)
                return 1000;
            else if (figure & Knight || figure & Bishop)
                return 3000;
            else if (figure & Rook)
                return 5000;
            else if (figure & Queen)
                return 9000;
            else if (figure & King)
                return 0;

            return 0;
        }

};

#endif // CHESSENGINE_H
