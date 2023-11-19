#include <stdio.h>
#include <limits.h>

int main() {
    int count, src_router, i, j, k, w, v, min;
    int cost_matrix[100][100], dist[100], last[100];
    int flag[100];

    printf("\n Enter the number of routers: ");
    scanf("%d", &count);

    printf("\n Enter the cost matrix values:\n");
    for (i = 0; i < count; i++) {
        for (j = 0; j < count; j++) {
            printf("%d->%d: ", i, j);
            scanf("%d", &cost_matrix[i][j]);

            if (cost_matrix[i][j] < 0) {
                cost_matrix[i][j] = INT_MAX;
            }
        }
    }

    printf("\n Enter the source router: ");
    scanf("%d", &src_router);

    for (v = 0; v < count; v++) {
        flag[v] = 0;
        last[v] = src_router;
        dist[v] = cost_matrix[src_router][v];
    }

    flag[src_router] = 1;

    for (i = 0; i < count; i++) {
        min = INT_MAX;
        for (w = 0; w < count; w++) {
            if (!flag[w] && dist[w] < min) {
                v = w;
                min = dist[w];
            }
        }

        flag[v] = 1;

        for (w = 0; w < count; w++) {
            if (!flag[w] && (min + cost_matrix[v][w] < dist[w])) {
                dist[w] = min + cost_matrix[v][w];
                last[w] = v;
            }
        }
    }

    for (i = 0; i < count; i++) {
        if (i != src_router) {
            printf("\n%d ==> %d: Path taken: %d", src_router, i, i);
            w = i;
            while (w != src_router) {
                printf(" <-- %d", last[w]);
                w = last[w];
            }
            printf("\n Shortest path cost: %d\n", dist[i]);
        }
    }

    return 0;
}
