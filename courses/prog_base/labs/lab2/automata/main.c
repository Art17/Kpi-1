#include <stdio.h>
#include <stdlib.h>

enum Move {POP = -4, REPEAT = -3, CONTINUE = -2, BREAK = -1};

struct Pair
{
    int op;
    int state;
};

struct Pair Table[4][210];

void fillTable ()
{
    struct Pair p;
    p.op = 9;
    p.state = 1;
    Table[0][6] = p;

    p.op = BREAK;
    p.state = -1;
    Table[0][14] = p;

    p.op = 7;
    p.state = 2;
    Table[0][24] = p;

    p.op = 5;
    p.state = 3;
    Table[0][204] = p;

    p.op = 3;
    p.state = 2;
    Table[1][6] = p;

    p.op = BREAK;
    p.state = -1;
    Table[1][14] = p;

    p.op = 1;
    p.state = 2;
    Table[1][24] = p;

    p.op = POP;
    p.state = 0;
    Table[1][204] = p;

    p.op = REPEAT;
    p.state = 0;
    Table[2][6] = p;

    p.op = BREAK;
    p.state = -1;
    Table[2][14] = p;

    p.op = CONTINUE;
    p.state = 0;
    Table[2][24] = p;

    p.op = BREAK;
    p.state = -1;
    Table[2][204] = p;

    p.op = 19;
    p.state = 0;
    Table[3][6] = p;

    p.op = POP;
    p.state = 0;
    Table[3][14] = p;

    p.op = BREAK;
    p.state = -1;
    Table[3][24] = p;

    p.op = 14;
    p.state = 1;
    Table[3][204] = p;

}

int run (int moves[], int movesLen, int res[], int resLen)
{
    fillTable ();
    for (int i = 0; i < resLen; i++)
        res[i] = 0;

    int state = 0;
    int cur = 0;

    for (int i = 0; i < movesLen; i++)
    {
        switch (Table[state][ moves[i] ].op)
        {
        case POP:
            res[cur--] = 0;
            if (cur < 0)
                return 0;
            state = Table[state][ moves[i] ].state;
            break;
        case REPEAT:
            state = Table[state][ moves[i] ].state;
            i--;
            break;
        case CONTINUE:
            state = Table[state][ moves[i] ].state;
            continue;
        case BREAK:
            return cur;
            break;
        default:
            res[cur++] = Table[state][ moves[i] ].op;
            state = Table[state][ moves[i] ].state;
            if (cur >= resLen)
                return cur;
            break;
        }
    }
    return cur;
}

int main()
{
    int moves[] = {6, 204, 24, 6, 24, 24, 6};
    int movesLen = sizeof (moves) / sizeof (moves[0]);

    int resLen = 10;
    int res[resLen];

    printf ("Result: %d\n", run (moves, movesLen, res, resLen));
    for (int i = 0; i < resLen; i++)
        printf ("%d ", res[i]);

    return 0;
}
