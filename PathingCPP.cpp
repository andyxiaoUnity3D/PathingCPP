#include <iostream>
#include <format>
#include <queue>
#include "PathingCPP.h"
#include <conio.h>
using namespace std;

graph::graph()
{
    this->connections = new int*[0];
    this->rowCount = 0;
    this->columnCount = 0;
    this->startPoint = -1;
    this->endPoint = -1;
}

void graph::Init(int* row, int* column)
{
    rowCount = row;
    columnCount = column;
    connections = new int* [*rowCount];

    for (int i = 0; i < *rowCount; i++)
    {
        connections[i] = new int[*columnCount];
        for (int k = 0; k < *columnCount; k++)
        {
            connections[i][k] = 0;
        }
    }

    srand(time(NULL));
    for (int j = 0; j < 5; j++)
    {
        int randomRow = rand() % *rowCount;
        int randomCol = rand() % *columnCount;
        connections[randomRow][randomCol] = -1;
    }
}

graph::~graph()
{
    for (int i = 0; i < *rowCount; i++)
    {
        delete[] connections[i];
    }
    delete[] connections;
}

tile::tile(int* r, int* c)
{
    row = r;
    col = c;
};

int test = 0;

graph* g = new graph();
int moveCount = 0;
int nodesLeftInLayer = 1;
int NodesInNextLayer = 0;
queue<int> rQueue;
queue<int> cQueue;
int* directionRow = new int[] {-1, 1, 0, 0};
int* directionCol = new int[] {0, 0, 1, -1};
bool reachedEnd = false;
bool** visited;


void DrawGrid(bool* query)
{
    cout << format("end point set to {} \n", g->endPoint);
    cout << format("start point is set to {} \n", g->startPoint);
    int counter = 0;
    for (int i = 0; i < *g->rowCount; i++)
    {
        for (int j = 0; j < *g->columnCount; j++)
        {
            counter++;
            if (g->connections[i][j] == -1)
            {
                if (counter < 10)
                {
                    cout << format("|{} [X] |", counter);
                }
                else
                {
                    cout << format("|{}[X] |", counter);
                }
                
            }
            else if (g->connections[i][j] == 1 && counter != g->startPoint && counter != g->endPoint)
            {
                if (counter < 10)
                {
                    cout << format("|{} [O] |", counter);
                }
                else
                {
                    cout << format("|{}[O] |", counter);
                }
                
            }
            else
            {
                if (counter == g->endPoint)
                {
                    if (counter < 10)
                    {
                        cout << format("|{} [E] |", counter);
                    }
                    else
                    {
                        cout << format("|{}[E] |", counter);
                    }
                    
                }
                else if (counter == g->startPoint)
                {
                    if (counter < 10)
                    {
                        cout << format("|{} [S] |", counter);
                    }
                    else
                    {
                        cout << format("|{}[S] |", counter);
                    }
                    
                }
                else
                {
                    if (counter < 10)
                    {
                        cout << format("|{} [ ] |", counter);
                    }
                    else
                    {
                        cout << format("|{}[ ] |", counter);
                    }
                    
                }
            }
        }
        cout << "\n";
    }

    if (*query)
    {
        int find;
        cin >> find;

        cout << format("Query is :{} \n", find);
        tile* test = FindTile(g, &find);
        int* item = GetTileValue(&find, g);
        cout << format("array item is {}, adjacency matrix id r: {} d:{} \n", *item, *test->row, *test->col);
    }

}

bool** InitVisited(bool** visited, graph* g)
{
    visited = new bool* [*g->rowCount];
    for (int c = 0; c < *g->columnCount; c++)
    {
        visited[c] = new bool [*g->columnCount];
    }
    for (int i = 0; i < *g->rowCount; i++)
    {
        for (int j = 0; j < *g->columnCount; j++)
        {
            visited[i][j] = false;
        }
    }
    return visited;
}

tile* FindTile(graph* graph, int* id)
{
    int count = 0;
    for (int i = 0; i < *graph->rowCount; i++)
    {
        for (int j = 0; j < *graph->columnCount; j++)
        {
            count++;
            if (count == *id)
            {
                tile* result = new tile(&i, &j);
                return result;
            }
        }
    }
    return NULL;
}

int* SetStartPoint(graph* g)
{
    int rChoice = 0;
    int cChoice = 0;
    rChoice = rand() % *g->rowCount;
    cChoice = rand() % *g->columnCount;
    if (g->connections[rChoice][cChoice] == -1 || g->connections[rChoice][cChoice] == g->endPoint)
    {
        SetStartPoint(g);
    }
    else
    {
        g->startPoint = *GetTileIndex(&rChoice, &cChoice, g);
        return &g->startPoint;
    }
}

int* SetEndPoint(graph* g)
{
    int rChoice = 0;
    int cChoice = 0;
    rChoice = rand() % *g->rowCount;
    cChoice = rand() % *g->columnCount;
    if (g->connections[rChoice][cChoice] == -1)
    {
        SetEndPoint(g);
    }
    else
    {
        g->endPoint = *GetTileIndex(&rChoice, &cChoice, g);
        return &g->endPoint;
    }
}

int* GetTileIndex(int* row, int* col, graph* g)
{
    int result = ((*row * *g->rowCount) + *col);
    return &result;
}

int* GetTileValue(int* arg, graph* g)
{
    int counter = 0;
    int* result = nullptr;
    for (int i = 0; i < *g->rowCount; i++)
    {
        for (int j = 0; j < *g->columnCount; j++)
        {
            counter++;
            if ((i * *g->columnCount) + j + 1 == *arg)
            {
                result = &g->connections[i][j];
            }
        }
    }
    return result;
}

int* GetIndex(int* a, int* b)
{
    int count = -1;
    for (int i = 0; i < *g->rowCount; i++)
    {
        for (int j = 0; j < *g->columnCount; j++)
        {
            count++;
            int index = (*a * *g->rowCount) + *b;
            if (count == index)
            {
                return &count;
            }
        }
    }
    count = -1;
    return &count;
}

int* Solve(int* start, int* end, graph* g)
{
    tile* startTile = FindTile(g, start);
    rQueue.push(*startTile->row);
    cQueue.push(*startTile->col);
    visited[*startTile->row][*startTile->col] = true;

    while (!rQueue.empty())
    {
        int r = rQueue.front();
        int c = cQueue.front();

        int* currentIndex = GetIndex(&r, &c);
        if (currentIndex == end)
        {
            cout << "found \n";
            reachedEnd = true;
            break;
        }

        ExploreNeighbors(&r, &c);
        nodesLeftInLayer--;
        if (nodesLeftInLayer == 0)
        {
            nodesLeftInLayer = NodesInNextLayer;
            NodesInNextLayer = 0;
            moveCount++;
        }

        rQueue.pop();
        cQueue.pop();
    }
    if (reachedEnd)
    {
        return &moveCount;
    }
    int result = -1;
    return &result;
}

void ExploreNeighbors(int* r, int* c)
{
    for (int i = 0; i < 4; i++)
    {
        int rr = *r + directionRow[i];
        int cc = *c + directionCol[i];
        
        // adjacency matrix bound
        if (rr < 0 || cc < 0)
        {
            continue;
        }
        if (rr >= *g->rowCount || cc >= *g->columnCount)
        {
            continue;
        }

        int* targetIndex = GetIndex(&rr, &cc);
        bool targetVisited = visited[rr][cc];
        if (targetVisited == true)
        {
            g->connections[rr][cc] = 1;
            if (*targetIndex == g->endPoint)
            {
                reachedEnd = true;
                break;
            }
            continue;
        }

        // avoid obstacles
        if (g->connections[rr][cc] == -1)
        {
            continue;
        }

        rQueue.push(rr);
        cQueue.push(cc);
        visited[rr][cc] = true;
        NodesInNextLayer++;
    }
}

int main()
{
    int row = 8;
    int col = 8;
    g->Init(&row, &col);

    SetEndPoint(g);
    SetStartPoint(g);

    visited = InitVisited(visited, g);

    cout << format("{} \n", visited[2][5]);

    bool drawGrid = true;
    DrawGrid(&drawGrid);
    int* result = Solve(&g->startPoint, &g->endPoint, g);
    drawGrid = false;
    DrawGrid(&drawGrid);
    cout << format("moves to solve: {}", *result);
    // int* result = GetIndex(&testRow, &testCol, &g);
    // cout << format("row {} col {} is id {}", testRow, testCol, *result);
    return 0;
}