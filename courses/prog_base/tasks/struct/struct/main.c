#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define len(k) sizeof(k)/sizeof(k[0])

#define maxGenre 16
#define maxName 32
#define maxKey 64

typedef struct Game
{
    char genre[maxGenre];
    char name[maxName];
    char key[maxKey];
} Game_t;

int count (int size, Game_t games[size])
{
    int c = 0;

    for (int i = 0; i < size; i++)
        if (strcmp (games[i].genre, "RPG") == 0)
            c++;
    return c;
}

void change (Game_t* pGame, const char* newValue )
{
    strcpy ( (*pGame).name, newValue );
}

void print (Game_t* game)
{
    printf ("%-15s %-15s %-15s\n", ((*game).genre), ((*game).name), ((*game).key));
}

int main()
{
    srand (time (NULL));

    const char* names[] = {"Uliria", "Agrirash", "Hean", "Araorid", "Larirandra",
                    "Fidus", "Glerramma", "Eowerrawin", "Aberralith", "Glogan", "Gleaniel",
                    "Frigof", "Sauweth", "Cralif", "Thoredda", "Afirawyr", "Onoendra"};
    const char* keys[] = {"A6732:877", "A4234:033", "A4327:222", "A0001:499", "A3232:055", "A3333:221", "A4444:101", "A5454:056"};

    const char* genres[] = {"RPG", "STRATEGY", "ACTION", "RACING"};

    const int n = 10;
    Game_t games[n];

    for (int i = 0; i < n; i++)
    {
        strcpy (games[i].genre, genres [rand () % len(genres) ]);
        strcpy (games[i].name, names[ rand() % len(names) ]);
        strcpy (games[i].key, keys[ rand() % len(keys) ]);
    }

    for (int i = 0; i < n; i++)
    {
        printf ("%2d   ", i);
        print (&games[i]);
    }

    printf ("count: %d\n", count (n, games));

    int ind;
    char name[maxName];

    printf ("write zero-based index and new name(d s): ");
    scanf ("%d %s", &ind, name);

    change (&games[ind], name);

    print (&games[ind]);

    return 0;
}
