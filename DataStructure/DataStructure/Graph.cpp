#define _CRT_SECURE_NO_WARNINGS

#include <cstdio> 

const int INF	= 0x7FFFFFFF;
const int N		= 465;

int DP[N][N];

void init() {

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			DP[i][j] = (i == j) ? 0 : INF;

	int a, b, cost;
	for (int i = 0; i < N; i++) {
		scanf("%d %d %d", &a, &b, &cost);
		DP[a][b] = cost;
		// d[b][a] = cost; /* 양방향 그래프 */
	}
}

void floyd_warshall() {
	for (int k = 0; k < N; ++k)
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				if (DP[i][j] > DP[i][k] + DP[k][j])
					DP[i][j] = DP[i][k] + DP[k][j];
}