#include "graph.h"
#include "slotsqueue.h" // Assuming SlotsQueue is available for BFS

Graph::Graph() {
    // Initialize distances to -1 (unreachable or unvisited)
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            dist[i][j] = -1;
        }
    }
}

void Graph::bfs(int startR, int startC) {
    // Reset distances
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            dist[i][j] = -1;
        }
    }

    SlotsQueue q;
    q.enqueue(startR, startC);
    dist[startR][startC] = 0;

    int dr[] = {-1, 1, 0, 0}; // Row movements (Up, Down)
    int dc[] = {0, 0, -1, 1}; // Col movements (Left, Right)

    int currentR, currentC;
    while (!q.isEmpty()) {
        q.dequeue(currentR, currentC);

        // Check all 4 neighbors
        for (int i = 0; i < 4; ++i) {
            int nextR = currentR + dr[i];
            int nextC = currentC + dc[i];

            // Check if the neighbor is within bounds and unvisited
            if (nextR >= 0 && nextR < ROWS && nextC >= 0 && nextC < COLS && dist[nextR][nextC] == -1) {
                dist[nextR][nextC] = dist[currentR][currentC] + 1;
                q.enqueue(nextR, nextC);
            }
        }
    }
}

void Graph::bfsDistance(int startR, int startC) {
    bfs(startR, startC);
}
