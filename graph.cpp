#include "stdafx.h"

const int N = 465;

int dp[N][N];

void init() {

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			dp[i][j] = (i == j) ? 0 : INF;

	int a, b, cost;
	for (int i = 0; i < N; i++) {
		scanf("%d %d %d", &a, &b, &cost);
		dp[a][b] = cost;
		// d[b][a] = cost; /* 양방향 그래프 */
	}
}

void floyd_warshall() {
	for (int k = 0; k < N; ++k)
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				if (dp[i][j] > dp[i][k] + dp[k][j])
					dp[i][j] = dp[i][k] + dp[k][j];
}