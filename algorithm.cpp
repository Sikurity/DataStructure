#include "stdafx.h"

#define INF 0x7FFFFFFF

namespace lys {

	int partition(int *arr, int left, int right) {

		int low, high, pivot;
		int idx = left + rand() % (right - left + 1);

		swap(arr[left], arr[idx]);
		pivot = arr[left];

		low = left;
		high = right + 1;

		do {
			do {
				low++;
			} while (arr[low] < pivot);

			do {
				high--;
			} while (pivot < arr[high]);

			if (low < high)
				swap(arr[low], arr[high]);
		} while (low < high);

		swap(arr[left], arr[high]);

		return high;
	}

	void quicksort(int *arr, int left, int right) {

		if (left < right) {
			int pivot = partition(arr, left, right);
			quicksort(arr, left, pivot - 1);
			quicksort(arr, pivot + 1, right);
		}
	}

	DisjointSet::DisjointSet(int n) {
		this->parent = new int[n];
		this->rank = new int[n];

		for (int i = 0; i < n; i++) {
			this->parent[i] = i;
			this->rank[i] = 1;
		}
	}

	DisjointSet::~DisjointSet() {
		delete[] this->parent;
		delete[] this->rank;
	}

	int DisjointSet::find(int u) {

		if (u != parent[u])
			parent[u] = find(parent[u]);

		return parent[u];
	}

	void DisjointSet::merge(int u, int v) {

		u = find(u);
		v = find(v);

		if (u == v)
			return;

		if (rank[u] > rank[v])
			swap(u, v);

		parent[u] = v;

		if (rank[u] == rank[v])
			rank[v]++;
	}

	struct Pair {
	public:

		int dist;
		int vertex;

		inline Pair() {
			this->dist = -1;
			this->vertex = -1;
		}

		inline Pair(int dist, int vertex) {
			this->dist = dist;
			this->vertex = vertex;
		}

		bool operator<(const Pair &p) const {
			return this->dist < p.dist;
		}

		bool operator>(const Pair &p) const {
			return this->dist > p.dist;
		}
	};

	template <typename T>
	struct Heap {

	private:
		
		T *nodes;
		int max;
		int count;

	public:

		Heap(int size) {
			max = size;
			nodes = new T[max + 1];
			count = 0;
		}

		~Heap() {
			delete[] nodes;
		}

		void insert(T value) throw(...) {

			if (count == max)
				throw - 1;

			nodes[++count] = value;

			int pos = count;
			int parent = pos / 2;
			while (0 < pos && nodes[pos] < nodes[parent]) {
				swap(nodes[pos], nodes[parent]);

				pos = parent;
				parent = pos / 2;
			}
		}

		T pop() throw(...) {

			if (count < 1)
				throw - 1;
			else {
				T root = nodes[1];

				if (count == 1)
					count = 0;
				else {
					swap(nodes[1], nodes[count]);
					count--;

					int current = 1;
					int leftChild = current << 1;
					int rightChild = leftChild + 1;

					while (leftChild <= count) {
						int selected = leftChild;

						if (rightChild <= count && nodes[leftChild] > nodes[rightChild])
							selected = rightChild;

						swap(nodes[current], nodes[selected]);

						current = selected;
						leftChild = current << 1;
						rightChild = leftChild + 1;
					}
				}

				return root;
			}
		}

		bool isEmpty() {
			return count == 0;
		}
	};

	void dijkstra(int v, int src, int e) {

		int **adj = new int *[v];
		int *dist = new int[v];
		bool *visit = new bool[v];

		for (int i = 0; i < v; i++) {
			adj[i] = new int[v];
			dist[i] = INF;
			visit[i] = false;
			for (int j = 0; j < v; j++)
				adj[i][j] = INF;
		}

		dist[src] = 0;

		int from, to, weight;
		for (int i = 0; i < e; i++) {
			scanf("%d %d %d", &from, &to, &weight);
			adj[from][to] = weight;
		}

		/*int min, next;*/

		Heap<Pair> heap = Heap<Pair>(100);
		heap.insert(Pair(src, 0));
		while (!heap.isEmpty()) {

			Pair cur = heap.pop();

			int index = cur.vertex;

			if (dist[index] < cur.dist)
				continue;

			for (int j = 0; j < v; j++) {
				if (dist[j] > dist[index] + adj[index][j]) {
					dist[j] = dist[index] + adj[index][j];
					heap.insert(Pair(dist[j], j));
				}
			}
		}
		
		//for (int i = 0; i < v; i++) {

		//	min = INF;
		//	for (int j = 0; j < v; j++) {

		//		if (visit[j] == false && min > dist[j])    // 갈수 있는 정점중에 가장 가까운 정점 선택
		//		{
		//			min = dist[j];
		//			next = j;
		//		}
		//	}

		//	visit[next] = true;

		//	for (int j = 0; j < v; j++) {
		//		if (dist[j] > dist[next] + adj[next][j])
		//			dist[j] = dist[next] + adj[next][j];
		//	}
		//}
	}
}