#ifndef ALGORITHM_H
#define ALGORITHM_H

#define INF 0x7FFFFFFF

namespace lys {

	struct DisjointSet {
		static const int MAX_SET_SIZE;
	private:
		int parent[1000], size[1000], rank[1000];

	public:
		DisjointSet();
		~DisjointSet();

		int find(int u);
		void unify(int u, int v);
	};
}

#endif