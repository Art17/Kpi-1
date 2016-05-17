#include "ChessEngine.h"
#include <vector>

struct Chain;
struct Node;

struct Node
{
    int from;
    int to;
    Chain* nextChain;
};

struct Chain
{
    vector<Node> nodes;
};

void ChessEngine::buildDebut ()
{
    Chain root;
    Chain currentChain = root;

}
