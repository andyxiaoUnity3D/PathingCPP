
class graph
{
public:
    int** connections;
    int* rowCount;
    int* columnCount;
    int startPoint;
    int endPoint;
    ~graph();
    graph();
    void Init(int* row, int* column);
};

struct tile
{
public:
    int* row;
    int* col;
    tile(int* r, int* c);
};
int* SetEndPoint(graph* g);
int* SetStartPoint(graph* g);
int* GetTileIndex(int* row, int* col, graph* g);
int* GetTileValue(int* arg, graph* g);
int* Solve(int* start, int* end, graph* g);
tile* FindTile(graph* graph, int* id);
int* GetIndex(int* a, int* b);
void ExploreNeighbors(int* r, int* c);
void DrawGrid(bool* query);

bool** InitVisited(bool** arg, graph* g);