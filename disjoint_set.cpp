#include "algorithm.h"

namespace lys {;

const int DisjointSet::MAX_SET_SIZE = 1000;

DisjointSet::DisjointSet() {
	for (int i = 0; i < MAX_SET_SIZE; i++)
		parent[i] = i, size[i] = 1, rank[i] = 0;
}

int DisjointSet::find(int u) {

	if (u != parent[u])
		parent[u] = find(parent[u]);

	return parent[u];
}

void DisjointSet::unify(int u, int v) {

	u = find(u);
	v = find(v);

	if (u == v)
		return;

	if (rank[u] > rank[v])
		SWAP(u, v);

	parent[u] = v;

	if (rank[u] == rank[v])
		rank[v]++;
}
}