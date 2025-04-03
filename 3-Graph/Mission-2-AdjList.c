#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define MAX_STATION_NAME_LEN 50

typedef struct AdjNode
{
    int destination;
    float distance;
    struct AdjNode *next;
} AdjNode;

typedef struct Vertex
{
    char stationName[MAX_STATION_NAME_LEN];
    AdjNode *head;
} Vertex;

typedef struct Graph
{
    int verticesNum;
    Vertex *vertices;
} Graph;

int getOrAddVertex(Graph *graph, const char *stationName)
{
    for (int i = 0; i < graph->verticesNum; i++)
    {
        if (strcmp(graph->vertices[i].stationName, stationName) == 0)
        {
            return i;
        }
    }

    strcpy(graph->vertices[graph->verticesNum].stationName, stationName);
    graph->vertices[graph->verticesNum].head = NULL;
    return graph->verticesNum++;
}

void freeGraph(Graph *graph)
{
    for (int i = 0; i < graph->verticesNum; ++i)
    {
        AdjNode *curr = graph->vertices[i].head;
        while (curr)
        {
            AdjNode *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph->vertices);
    graph->vertices = NULL;
    graph->verticesNum = 0;
}

Graph * initGraph(Graph *graph, int maxVertices)
{
    graph->verticesNum = 0;
    graph->vertices = (Vertex *)malloc(sizeof(Vertex) * maxVertices);
    return graph;
}

void addEdge(Graph * graph, int src, int dest, float distance)
{
    AdjNode * newNode = (AdjNode*)malloc(sizeof(AdjNode));
    newNode->destination = dest;
    newNode->distance = distance;
    newNode->next = graph->vertices[src].head;
    graph->vertices[src].head = newNode;
}

void readInput(Graph * graph)
{
    char src[MAX_STATION_NAME_LEN];
    char dest[MAX_STATION_NAME_LEN];
    float dist = 0;
    int siteSrc = 0, siteDest = 0;

    while (true)
    {
        scanf("%s", src);
        if (strcmp(src, "END!") == 0)
        {
            return;
        }
        scanf("%s %f", dest, &dist);

        siteSrc = getOrAddVertex(graph, src);
        siteDest = getOrAddVertex(graph, dest);

        addEdge(graph, siteSrc, siteDest, dist);
        addEdge(graph, siteDest, siteSrc, dist);
    }
}

void printTransferStations(const Graph * graph)
{
    for (int i=0; i<graph->verticesNum; i++)
    {
        int connectingCount = 0;
        AdjNode * curr = graph->vertices[i].head;

        while(curr != NULL)
        {
            curr = curr->next;
            connectingCount++;
        }

        if (connectingCount > 2)
        {
            printf("%s %d\n", graph->vertices[i].stationName, connectingCount);
        }
    }
}

int findVertexIndex(const Graph * graph, const char * stationName)
{
    for (int i=0; i<graph->verticesNum; i++)
    {
        if (strcmp(graph->vertices[i].stationName, stationName) == 0)
        {
            return i;
        }
    }
    return -1;
}

void dijkstrea(const Graph * graph)
{
    char srcStationName[MAX_STATION_NAME_LEN];
    char destStationName[MAX_STATION_NAME_LEN];

    scanf("%s %s", srcStationName, destStationName);
    int src = findVertexIndex(graph, srcStationName);
    int dest = findVertexIndex(graph, destStationName);

    float * shortestDistance = (float *)malloc(sizeof(float) * graph->verticesNum);
    bool * stationVisited = (bool *)malloc(sizeof(bool) * graph->verticesNum);
    int * previousStation = (int *)malloc(sizeof(int) * graph->verticesNum);

    for (int i=0; i<graph->verticesNum; i++)
    {
        shortestDistance[i] = 1e9;
        stationVisited[i] = false;
        previousStation[i] = -1;
    }

    shortestDistance[src] = 0;

    for (int count=0; count<graph->verticesNum; count++)
    {
        int currentStation = -1;
        float minDistance = 1e9;

        for (int i=0; i<graph->verticesNum; i++)
        {
            if ((stationVisited[i] == false) && (shortestDistance[i] < minDistance))
            {
                minDistance = shortestDistance[i];
                currentStation = i;
            }
        }

        if (currentStation == -1)
        {
            break;
        }

        stationVisited[currentStation] = true;

        AdjNode * neightbor  = graph->vertices[currentStation].head;
        while (neightbor != NULL)
        {
            int adjacentStation = neightbor->destination;
            float weight = neightbor->distance;

            if ((stationVisited[adjacentStation] == false) && (shortestDistance[currentStation] + weight < shortestDistance[adjacentStation]))
            {
                shortestDistance[adjacentStation] = shortestDistance[currentStation] + weight;
                previousStation[adjacentStation] = currentStation;
            }

            neightbor = neightbor->next;
        }
    }

    int * path = (int *)malloc(sizeof(int) * graph->verticesNum);
    int pathLength = 0;
    int current = dest;

    while (current != -1)
    {
        path[pathLength++] = current;
        current = previousStation[current];
    }

    for (int i = pathLength - 1; i >= 0; --i)
    {
        printf("%s ", graph->vertices[path[i]].stationName);
    }
    printf("%.2f", shortestDistance[dest]);

    free(path);
    free(shortestDistance);
    free(stationVisited);
    free(previousStation);
}

int main()
{
    Graph graph;
    initGraph(&graph, MAX_VERTICES);
    readInput(&graph);
    // printTransferStations(&graph);
    dijkstrea(&graph);
    freeGraph(&graph);
    return 0;
}