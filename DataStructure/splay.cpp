#include <iostream>
#include "splay.h"

using namespace std;

node nodes[200000 + 1];
int tree, last;

void Update(int x) {
	nodes[x].cnt = 1;
	if (nodes[x].l) 
		nodes[x].cnt += nodes[nodes[x].l].cnt;
	if (nodes[x].r) 
		nodes[x].cnt += nodes[nodes[x].r].cnt;
}

void Rotate(int x) {
	int p = nodes[x].p;
	int b;
	if (x == nodes[p].l) {
		nodes[p].l = b = nodes[x].r;
		nodes[x].r = p;
	}
	else {
		nodes[p].r = b = nodes[x].l;
		nodes[x].l = p;
	}
	nodes[x].p = nodes[p].p;
	nodes[p].p = x;
	if (b) 
		nodes[b].p = p;
	(nodes[x].p ? p == nodes[nodes[x].p].l ? nodes[nodes[x].p].l : nodes[nodes[x].p].r : tree) = x;
	
	Update(p);
	Update(x);
}

void Splay(int x) {
	while (nodes[x].p) {
		int p = nodes[x].p;
		int g = nodes[p].p;
		if (g) Rotate((x == nodes[p].l) == (p == nodes[g].l) ? p : x);
		Rotate(x);
	}
}

void Insert(int key) {
	int p = tree, lr = 0;
	if (!p) {
		int x = ++last;
		tree = x;
		nodes[x].l = nodes[x].r = nodes[x].p = NULL;
		nodes[x].key = key;
		return;
	}
	while (1) {
		if (key == nodes[p].key) return;
		if (key < nodes[p].key) {
			if (!nodes[p].l) {
				lr = -1;
				break;
			}
			p = nodes[p].l;
		}
		else {
			if (!nodes[p].r) {
				lr = 1;
				break;
			}
			p = nodes[p].r;
		}
	}
	int x = ++last;
	(lr < 0 ? nodes[p].l : nodes[p].r) = x;
	nodes[x].l = nodes[x].r = NULL;
	nodes[x].p = p;
	nodes[x].key = key;
	Splay(x);
}

bool Find(int key) {
	int p = tree;
	if (!p) return false;
	while (p) {
		if (key == nodes[p].key) break;
		if (key < nodes[p].key) {
			if (!nodes[p].l) break;
			p = nodes[p].l;
		}
		else {
			if (!nodes[p].r) break;
			p = nodes[p].r;
		}
	}
	Splay(p);
	return key == nodes[p].key;
}

void Delete(int key) {
	if (!Find(key)) 
		return;
	int p = tree;
	if (nodes[p].l) {
		if (nodes[p].r) {
			tree = nodes[p].l;
			nodes[tree].p = NULL;
			int x = tree;
			while (nodes[x].r) x = nodes[x].r;
			nodes[x].r = nodes[p].r;
			nodes[nodes[p].r].p = x;
			Splay(x);
			// delete p;
			return;
		}
		tree = nodes[p].l;
		nodes[tree].p = NULL;
		// delete p;
		return;
	}
	if (nodes[p].r) {
		tree = nodes[p].r;
		nodes[tree].p = NULL;
		// delete p;
		return;
	}
	// delete p;
	tree = NULL;
}

void Find_Kth(int k) {
	int x = tree;
	while (1) {
		while (nodes[x].l && nodes[nodes[x].l].cnt > k) x = nodes[x].l;
		if (nodes[x].l) k -= nodes[nodes[x].l].cnt;
		if (!k--) break;
		x = nodes[x].r;
	}
	Splay(x);
}

int max = 0;
void InOrder(int root, int level) {
	if (max < level)
		max = level;
	if (root) {
		InOrder(nodes[root].l, level + 1);
		int buf = nodes[root].key;
		InOrder(nodes[root].r, level + 1);
	}
	if (level == 0)
		cout << max << endl;
}