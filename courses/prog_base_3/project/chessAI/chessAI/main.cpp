#include "ChessEngine.h"
#include <memory.h>
#include <cstdio>

typedef char byte;

using namespace std;

void printBoard (byte board[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printf ("%2d ", board[i][j]);
        }
        printf ("\n");
    }
}

void printArray (byte array[], int l)
{
    printf ("Array: ");
    for (int i = 0; i < l; i++)
        printf ("(%d,%d) ", array[i]%8+1,array[i]/8+1);
    printf ("\n");
}

int main()
{
    ChessEngine* chessEng = new ChessEngine ();
    chessEng->newGame ();

    byte board[8][8];
    memset (&board, 0, sizeof(byte)*8*8);

    board[0][0] = 66;
    board[1][2] = 2;
    byte moves[32];
    int length = 0;

    chessEng->setBoard((byte*)board);

    printf ("%d\n", chessEng->isBeaten(17, true));

    printArray (moves, length);
    printBoard (board);

    return 0;
}
