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

int main()
{
    Graph graph;
    initGraph(&graph, MAX_VERTICES);
    readInput(&graph);
    printTransferStations(&graph);
    freeGraph(&graph);
    return 0;
}