#include <stdio.h>

#define V 6

int time_counter;

void DFSUtil(int u, int graph[V][V], int visited[], int entry[], int exit[]) {
    visited[u] = 1;
    entry[u] = ++time_counter;

    for (int v = 0; v < V; v++) {
        if (graph[u][v]) {
            if (visited[v] == 0) {
                printf("Tree Edge: %d -> %d\n", u, v);
                DFSUtil(v, graph, visited, entry, exit);
            }
            else if (visited[v] == 1) {
                printf("Back Edge: %d -> %d\n", u, v);
            }
            else {
                if (entry[u] < entry[v])
                    printf("Forward Edge: %d -> %d\n", u, v);
                else
                    printf("Cross Edge: %d -> %d\n", u, v);
            }
        }
    }
    visited[u] = 2;
    exit[u] = ++time_counter;
}

void DFS(int graph[V][V]) {
    int visited[V], entry[V], exit[V];
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
        entry[i] = 0;
        exit[i] = 0;
    }
    time_counter = 0;
    for (int i = 0; i < V; i++) {
        if (visited[i] == 0)
            DFSUtil(i, graph, visited, entry, exit);
    }
}

int main() {
    int graph[V][V] = {
        {0, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0}
    };

    DFS(graph);
    return 0;
}

