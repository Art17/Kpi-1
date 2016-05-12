#ifndef CHESSENGINE_H
#define CHESSENGINE_H

#include <stack>

using namespace std;

typedef char byte;

enum Figures {Rook = 1, Knight = 2, Bishop = 4, Queen = 8, King = 16, Pawn = 32};

struct Move
{
    byte from;
    byte to;
    Figures extra;
};

class ChessEngine
{
    public:
        ChessEngine();

        void newGame ();

        bool isValidMove (const Move&) const;

        byte* getValidMoves (int from, byte moves[], int* lPtr) const;

        void engineMove (Move* );
        bool makeMove (const Move& );

        void getBoard (byte* );
        void setBoard (byte* );

        bool isBeaten (int, bool) const;
    private:
        inline bool isDifferentColor (int, int) const;
        inline bool isWhite (int) const;
        int cti (int, int) const;

        byte* getRookMoves (int , byte [], int* ) const;
        byte* getKnightMoves (int , byte [], int* ) const;
        byte* getBishopMoves (int , byte [], int* ) const;
        byte* getQueenMoves (int , byte [], int* ) const;
        byte* getKingMoves (int, byte [], int* ) const;
        byte* getPawnMoves (int, byte [], int* ) const;

        void reload ();

        byte board[8][8];
        const byte colorWhite;

        bool bWhiteKingMoved, bWhiteLeftRookMoved, bWhiteRightRookMoved;
        bool bBlackKingMoved, bBlackLeftRookMoved, bBlackRightRookMoved;

        int whiteKingPos, blackKingPos;

        bool whiteTurn;

        stack<Move> lastMoves;

};

#endif // CHESSENGINE_H
