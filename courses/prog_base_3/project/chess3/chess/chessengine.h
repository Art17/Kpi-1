#ifndef CHESSENGINE_H
#define CHESSENGINE_H

#include <stack>
#include <cstdio>

using namespace std;

typedef char byte;

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
};

class ChessEngine
{
    public:
        ChessEngine();

        void newGame ();

        bool isValidMove (const Move&) ;

        byte* getValidMoves (int from, byte moves[], int* lPtr);

        void engineMove (Move* );
        bool makeMove (const Move& );

        bool getBoard (byte* );
        void setBoard (byte*, bool);

        bool undo ();

        bool isBeaten (int, bool) const;
    private:
        inline bool isDifferentColor (int, int) const;
        inline bool isWhite (int) const;
        int cti (int, int) const;

        byte* getRookMoves (int , byte [], int* ) ;
        byte* getKnightMoves (int , byte [], int* ) ;
        byte* getBishopMoves (int , byte [], int* ) ;
        byte* getQueenMoves (int , byte [], int* ) ;
        byte* getKingMoves (int, byte [], int* ) ;
        byte* getPawnMoves (int, byte [], int* ) ;

        bool isFigurePinned (int from, int to) ;

        void reload ();

        byte board[8][8];
        const byte colorWhite;

        bool bWhiteKingMoved, bWhiteLeftRookMoved, bWhiteRightRookMoved;
        bool bBlackKingMoved, bBlackLeftRookMoved, bBlackRightRookMoved;

        int whiteKingPos, blackKingPos;

        bool whiteTurn;

        stack<ExtraMove> lastMoves;

};

#endif // CHESSENGINE_H
