#include <stdio.h>
#include <stdbool.h>

#define V 6

int graph[V][V] = {
    {0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0},
    {0, 1, 0, 1, 0, 0},
    {0, 0, 1, 0, 1, 0},
    {0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0}
};

bool visited[V];
int path[V];
int path_index;
int min_cycle = V + 1;
int max_cycle = -1;

void checkCycle(int start, int v) {
    for (int i = 0; i < path_index; i++) {
        if (path[i] == v) {
            int cycle_length = path_index - i;
            if (cycle_length > 2) {
                if (cycle_length < min_cycle) min_cycle = cycle_length;
                if (cycle_length > max_cycle) max_cycle = cycle_length;
            }
            return;
        }
    }
}

void DFS(int u, int parent) {
    visited[u] = true;
    path[path_index++] = u;

    for (int v = 0; v < V; v++) {
        if (graph[u][v]) {
            if (!visited[v]) {
                DFS(v, u);
            } else if (v != parent) {
                checkCycle(u, v);
            }
        }
    }

    path_index--;
    visited[u] = false;
}

void findCycles() {
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }
    path_index = 0;

    for (int i = 0; i < V; i++) {
        DFS(i, -1);
    }

    if (min_cycle == V + 1) {
        printf("No cycles found.\n");
    } else {
        printf("Smallest Cycle Length: %d\n", min_cycle);
        printf("Largest Cycle Length: %d\n", max_cycle);
    }
}

int main() {
    findCycles();
    return 0;
}

