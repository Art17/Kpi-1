#include "ChessEngine.h"
#include <memory.h>
#include <iostream>

void ChessEngine::reload ()
{
    whiteTurn = true;
    canCastling = 0;
    canCastling = WHITE_LEFT_CASTLING | WHITE_RIGHT_CASTLING | BLACK_RIGHT_CASTLING | BLACK_LEFT_CASTLING;

    bTestMode = false;

    while (lastMoves.size() != 0)
        lastMoves.pop ();
    whiteKingPos = cti (4, 7);
    blackKingPos = cti (4, 0);
}

void ChessEngine::fillBoard()
{
    memset (board, 0, sizeof(byte)*8*8);

    board[0][0] = Rook;
    board[0][1] = Knight;
    board[0][2] = Bishop;
    board[0][3] = Queen;
    board[0][4] = King;
    board[0][5] = Bishop;
    board[0][6] = Knight;
    board[0][7] = Rook;

    for (int i = 0; i < 8; i++)
        board[1][i] = Pawn;

    board[7][0] = Rook | colorWhite;
    board[7][1] = Knight | colorWhite;
    board[7][2] = Bishop | colorWhite;
    board[7][3] = Queen | colorWhite;
    board[7][4] = King | colorWhite;
    board[7][5] = Bishop | colorWhite;
    board[7][6] = Knight | colorWhite;
    board[7][7] = Rook | colorWhite;

    for (int i = 0; i < 8; i++)
        board[6][i] = Pawn | colorWhite;
}
