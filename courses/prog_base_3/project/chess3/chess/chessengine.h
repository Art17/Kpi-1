#ifndef CHESSENGINE_H
#define CHESSENGINE_H

#include <stack>
#include <cstdio>
#include <list>

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
    byte extraFigure;
    byte beatenFigure; // exclude passant
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
        inline bool isDifferentColor (int, int) const;
        inline bool isWhite (int) const;
        bool isWhiteTile (int);
        int cti (int, int) const;

        byte* getRookMoves (int , byte [], int* ) ;
        byte* getKnightMoves (int , byte [], int* ) ;
        byte* getBishopMoves (int , byte [], int* ) ;
        byte* getQueenMoves (int , byte [], int* ) ;
        byte* getKingMoves (int, byte [], int* ) ;
        byte* getPawnMoves (int, byte [], int* ) ;

        bool isFigurePinned (int from, int to) ;
        int makeMoveLow (const Move& );

        int getFigurePower (int);

        void getRandomMove (Move* );
        void getRandomBeatMove (Move* pRes);

        void reload ();
        void fillBoard ();

        byte board[8][8];
        const byte colorWhite;

        list<byte> whitePositions;
        list<byte> blackPositions;

        int canCastling;
        int whiteKingPos, blackKingPos;
        bool whiteTurn;

        bool bTestMode;

        stack<ExtraMove> lastMoves;

};

#endif // CHESSENGINE_H
