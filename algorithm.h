#ifndef ALGORITHM_H
#define ALGORITHM_H

#define INF 0x7FFFFFFF

namespace lys {

	template <typename T>
	void swap(T &a, T &b) {

		T t = a;
		a = b;
		b = t;
	}

	int partition(int *arr, int left, int right);
	void quicksort(int *arr, int left, int right);

	void dijkstra(int v, int src, int e);

	struct DisjointSet {
	private:
		int *parent, *rank;

	public:
		DisjointSet(int n);
		~DisjointSet();

		int find(int u);
		void merge(int u, int v);
	};
}

#endif