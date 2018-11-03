#pragma once

#include <cstdio>

class SplayTree {
	int root, last, size;

	struct {
		int l, r, p;
		int key;
		int cnt;
	} nodes[200000 + 1];
	
	void Update(int x);
	void Rotate(int x);
	void Splay(int x);

public:
	int GetRoot();
	int GetSize();
	bool Insert(int key);
	bool Find(int key);
	bool Delete(int key);
	int NthNode(int k);
	void InOrder(int cur, int level = 0);
};
