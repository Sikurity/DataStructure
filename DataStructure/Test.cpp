#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include <random>
#include <set>
#include <vector>
#include <algorithm>
#include "DataStructure\SplayTree.h"

using namespace std;

set<int> s;
SplayTree st;

const int MAX_ITER = 1000000;
const int MAX_RANGE = 2000000;

void RandomTest() {
	std::random_device rd;
	std::mt19937 mersenne(rd()); // Create a mersenne twister, seeded using the random device

	// Create a reusable random number generator that generates uniform numbers between 1 and 6 
	std::uniform_int_distribution<int> rndg(0, 0x7FFFFFFF);

	vector<int> v, half;
	printf("CREATE RANDOM DATA: ");
	for (int i = 0; i < MAX_ITER; i++) {
		int num = rndg(mersenne);
		v.push_back(num);
		if (i < MAX_ITER >> 1)
			half.push_back(num);
		// printf("%d ", num);
	}
	puts("");

	printf("Set RANDOM INSERT START\n");
	clock_t start = clock();
	for (auto &key : v) {
		s.insert(key);
		//for (auto &key : s)
		//	printf("%d ", key);// int buf = key;
		//puts("");
	}
	printf("Set RANDOM INSERT: %.3lfs\n", (clock() - start) / 1000.0);
	puts("");

	printf("SplayT RANDOM INSERT START\n");
	start = clock();
	for (auto &key : v) {
		st.Insert(key);
		// st.InOrder(); // Stack Overflow!!!
		// puts("");
	}
	printf("SplayT RANDOM INSERT: %.3lfs\n", (clock() - start) / 1000.0);
	puts("");

	printf("SET RANDOM TRAVERSE START\n");
	start = clock();
	for (auto &key : s) {
		int buf = key;
		// printf("%d ", key);
	}
	printf("SET RANDOM TRAVERSE: %.3lfs\n", (clock() - start) / 1000.0);
	puts("");

	printf("SplayT RANDOM TRAVERSE START\n");
	start = clock();
	// st.InOrder(); // Stack Overflow!!!
	for (int i = 0; i < st.size; ++i)
		int buf = st.nodes[st.NthNode(i)].key;
	printf("SplayT RANDOM Traverse: %.3lfs\n", (clock() - start) / 1000.0);
	puts("");

	printf("SET RANDOM FIND START\n");
	start = clock();
	for (auto &key : v)
		s.find(key);
	printf("SET RANDOM FIND: %.3lfs\n", (clock() - start) / 1000.0);
	puts("");

	printf("SplayT RANDOM FIND START\n");
	start = clock();
	for (auto &key : v)
		st.Find(key);
	printf("SplayT RANDOM FIND: %.3lfs\n", (clock() - start) / 1000.0);

	puts("");
	printf("SIZE(Set, Splay) : %lu %ld\n", s.size(), st.size);

	puts("");
	printf("BEGIN SET, SplayT: %d %d\n", *(s.begin()), st.nodes[st.NthNode(0)].key);
	printf("END   SET, SplayT: %d %d\n", *(--s.end()), st.nodes[st.NthNode(st.size - 1)].key);

	puts("");

	printf("Set RANDOM DELETE START\n");
	start = clock();
	for (auto &key : v)
		s.erase(key);
	printf("Set RANDOM Delete: %.3lfs\n", (clock() - start) / 1000.0);

	printf("SplayT RANDOM DELETE START\n");
	start = clock();
	for (auto &key : v)
		st.Delete(key);
	printf("Splay RANDOM Delete: %.3lfs\n", (clock() - start) / 1000.0);

	puts("");
	printf("SIZE(Set, Splay) : %d %d\n", s.size(), st.size);

	vector<int> a;
	for (auto &key : s)
		a.push_back(key);

	vector<int> b;
	for (int i = 0; i < st.size; ++i)
		b.push_back(st.nodes[st.NthNode(i)].key);

	if (a.size() == b.size()) {
		printf("Compare Set & Splay values\n");
		int size = a.size();
		for (int i = 0; i < size; i++)
			if (a[i] != b[i])
				printf("#%d MISS (%d, %d)\n", i, a[i], b[i]);
		printf("Compare End\n");
	}
	else
		printf("Error: Diffrent Size\n");
}

void SequentialTest() {
	std::random_device rd;
	std::mt19937 mersenne(rd()); // Create a mersenne twister, seeded using the random device

	// Create a reusable random number generator that generates uniform numbers between 1 and 6 
	std::uniform_int_distribution<int> rndg(0, 0x7FFFFFFF);

	vector<int> v, half;
	printf("CREATE SEQUNTTIAL DATA: ");
	for (int i = 0; i < MAX_ITER; i++) {
		int num = rndg(mersenne);
		v.push_back(num);
		if (i < MAX_ITER >> 1)
			half.push_back(num);
		// printf("%d ", num);
	}
	puts("");

	sort(v.begin(), v.end());
	sort(half.begin(), half.end());

	printf("Set SEQUENTIAL INSERT START\n");
	clock_t start = clock();
	for (auto &key : v) {
		s.insert(key);
		//for (auto &key : s)
		//	printf("%d ", key);// int buf = key;
		//puts("");
	}
	printf("Set SEQUENTIAL INSERT: %.3lfs\n", (clock() - start) / 1000.0);
	puts("");

	printf("SplayT SEQUENTIAL INSERT START\n");
	start = clock();
	for (auto &key : v) {
		st.Insert(key);
		// st.InOrder();  // Stack Overflow!!!
		// puts("");
	}
	printf("SplayT SEQUENTIAL INSERT: %.3lfs\n", (clock() - start) / 1000.0);
	puts("");

	printf("SET SEQUENTIAL TRAVERSE START\n");
	start = clock();
	for (auto &key : s) {
		int buf = key;
		// printf("%d ", key);
	}
	printf("SET SEQUENTIAL TRAVERSE: %.3lfs\n", (clock() - start) / 1000.0);
	puts("");

	printf("SplayT SEQUENTIAL TRAVERSE START\n");
	start = clock();
	// st.InOrder();  // Stack Overflow!!!
	for (int i = 0; i < st.size; ++i)
		int buf = st.nodes[st.NthNode(i)].key;
	printf("SplayT SEQUENTIAL Traverse: %.3lfs\n", (clock() - start) / 1000.0);
	puts("");

	printf("SET SEQUENTIAL FIND START\n");
	start = clock();
	for (auto &key : v)
		s.find(key);
	printf("SET SEQUENTIAL FIND: %.3lfs\n", (clock() - start) / 1000.0);
	puts("");

	printf("SplayT SEQUENTIAL FIND START\n");
	start = clock();
	for (auto &key : v)
		st.Find(key);
	printf("SplayT SEQUENTIAL FIND: %.3lfs\n", (clock() - start) / 1000.0);

	puts("");
	printf("SIZE(Set, Splay) : %lu %ld\n", s.size(), st.size);

	puts("");
	printf("BEGIN SET, SplayT: %d %d\n", *(s.begin()), st.nodes[st.NthNode(0)].key);
	printf("END   SET, SplayT: %d %d\n", *(--s.end()), st.nodes[st.NthNode(st.size - 1)].key);

	vector<int> a;
	for (auto &key : s)
		a.push_back(key);

	vector<int> b;
	for (int i = 0; i < st.size; ++i)
		b.push_back(st.nodes[st.NthNode(i)].key);

	if (a.size() == b.size()) {
		printf("Compare Set & Splay values\n");
		int size = a.size();
		for (int i = 0; i < size; i++)
			if (a[i] != b[i])
				printf("#%d MISS (%d, %d)\n", i, a[i], b[i]);
		printf("Compare End\n");
	}
	else
		printf("Error: Diffrent Size\n");

	puts("");

	printf("Set SEQUENTIAL DELETE START\n");
	start = clock();
	for (auto &key : v)
		s.erase(key);
	printf("Set SEQUENTIAL Delete: %.3lfs\n", (clock() - start) / 1000.0);

	printf("SplayT SEQUENTIAL DELETE START\n");
	start = clock();
	for (auto &key : v)
		st.Delete(key);
	printf("Splay SEQUENTIAL Delete: %.3lfs\n", (clock() - start) / 1000.0);

	puts("");
	printf("SIZE(Set, Splay) : %d %d\n", s.size(), st.size);
}

int main() {
	RandomTest();

	s.clear();
	st.root = st.size = st.last = NULL;

	puts("=============================================================");

	SequentialTest();

	/*v.clear();

	for (int i = 0; i < MAX_ITER; i++)
		v.push_back(i);
	std::random_shuffle(v.begin(), v.end());

	for (auto &key : v)
		st.Insert(key);

	std::uniform_int_distribution<int> rndg2(0, MAX_ITER);

	for (int i = 0; i < 3; i++) {
		int d = rndg2(mersenne);
		st.Delete(d);
		printf("%d deleted\n", d);
	}

	for (int i = 0; i < 100; i++) {
		int m = rndg2(mersenne);
		int n = st.nodes[st.NthNode(m)].key;
		if(m != n)
			printf("%d, %d\n", m, n);
	}*/

	return 0;
}