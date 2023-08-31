
class graph
{
    int** connections;
    int* rowCount;
    int* columnCount;
    int* startPoint;
    int* endPoint;
public:
    graph();
    virtual ~graph();
    void Init(int* row, int* column);
    int** GetConnections();
    int* GetRowCount();
    int* GetColumnCount();
    void SetStartPoint(int* arg);
    void SetEndPoint(int* arg);
    int* GetEndPoint();
    int* GetStartPoint();
};

struct tile
{
    int* row;
    int* col;
    tile(int* r, int* c);
};

int* SetEndPoint(graph* g);
int* SetStartPoint(graph* g);
int* GetTileIndex(int* row, int* col, graph* g);
int* GetTileValue(int* arg, graph* g);
int* Solve(int* start, int* end, graph* g);
int* GetIndex(int* a, int* b);
tile* FindTile(graph* graph, int* id);
bool** InitVisited(bool** arg, graph* g);
void ExploreNeighbors(int* r, int* c);
void DrawGrid(bool* query);