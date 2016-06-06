#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>

#include <stack>
#include <cstdio>
#include <list>
#include <vector>

#include "figures.h"

#define MAKEWORD(a,b)   ((short)(((char)(a))|(((short)((char)(b)))<<8)))
#define LOBYTE(w)	((char)(w))
#define HIBYTE(w)	((char)(((short)(w)>>8)&0xFF))

#define WHITE_LEFT_CASTLING 1
#define WHITE_RIGHT_CASTLING 2
#define BLACK_LEFT_CASTLING 4
#define BLACK_RIGHT_CASTLING 8

using namespace std;

typedef short dbyte;

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

enum DLL_EXPORT Status {ACTIVE_GAME=0, WHITE_WON, BLACK_WON, DRAW};

struct DLL_EXPORT Move
{
    byte from;
    byte to;
    byte extra;
};

struct DLL_EXPORT ExtraMove
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

class DLL_EXPORT ChessEngine
{
    public:
        ChessEngine();

        void newGame ();
        void setTestMode (bool);

        bool isValidMove (const Move&);

        byte* getValidMoves (int from, byte moves[], int* lPtr);

        void getBestMove (Move* );
        bool makeMove (const Move& );

        bool getBoard (byte* );
        void setBoard (byte*, bool);

        int getKingPos (bool) const;
        bool isCheck (bool) const;

        bool undo ();

        bool isBeaten (int, bool) const;
        int isEnd ();

        dbyte* getAllMoves (dbyte*, int, int*, bool);
    private:

        int minmax (Move* pRes, int depth);
        int minmaxLow (int depth);
        int getPlayerPower (bool bWhite);

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

        int evaluateMove (const Move&);

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
                return 100;
            else if (figure & Knight || figure & Bishop)
                return 300;
            else if (figure & Rook)
                return 500;
            else if (figure & Queen)
                return 900;
            else if (figure & King)
                return 0;

            return 0;
        }

};


#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
