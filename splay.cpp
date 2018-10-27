#include <iostream>
#include "splay.h"

using namespace std;

void SplayTree::Update(int x) {
	nodes[x].cnt = 1;
	if (nodes[x].l) 
		nodes[x].cnt += nodes[nodes[x].l].cnt;
	if (nodes[x].r) 
		nodes[x].cnt += nodes[nodes[x].r].cnt;
}

void SplayTree::Rotate(int x) {
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
	(nodes[x].p ? p == nodes[nodes[x].p].l ? nodes[nodes[x].p].l : nodes[nodes[x].p].r : root) = x;
	
	Update(p);
	Update(x);
}

void SplayTree::Splay(int x) {
	while (nodes[x].p) {
		int p = nodes[x].p;
		int g = nodes[p].p;
		if (g) Rotate((x == nodes[p].l) == (p == nodes[g].l) ? p : x);
		Rotate(x);
	}
}

void SplayTree::Insert(int key) {
	int p = root;

	if (p) {
		int lr = 0;
		while (true) {
			if (nodes[p].key < key) {
				if (!nodes[p].r) {
					lr = 1;
					break;
				}
				p = nodes[p].r;
			}
			else if (key < nodes[p].key) {
				if (!nodes[p].l) {
					lr = -1;
					break;
				}
				p = nodes[p].l;
			}
			else
				return;
		}
		int x = ++last;
		(lr < 0 ? nodes[p].l : nodes[p].r) = x;
		nodes[x].l = nodes[x].r = NULL;
		nodes[x].p = p;
		nodes[x].key = key;
		Splay(x);
	}
	else {
		int x = ++last;
		root = x;
		nodes[x].l = nodes[x].r = nodes[x].p = NULL;
		nodes[x].key = key;
	}
	
	++size;
}

bool SplayTree::Find(int key) {
	int p = root;
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

void SplayTree::Delete(int key) {
	if (!Find(key)) 
		return;
	
	int p = root;
	if (nodes[p].l || nodes[p].r) {
		if (nodes[p].l == 0) {		// only right child
			root = nodes[p].l;
			nodes[root].p = NULL;
			// delete p;
		}
		else if (nodes[p].r == 0) { // only left child
			root = nodes[p].r;
			nodes[root].p = NULL;
			// delete p;
		}
		else {						// both children
			root = nodes[p].l;
			nodes[root].p = NULL;
			
			int x = root;
			while (nodes[x].r) 
				x = nodes[x].r;
			
			nodes[x].r = nodes[p].r;
			nodes[nodes[p].r].p = x;
			
			Splay(x);
			// delete p;
		}
	}
	else {
		// delete p;
		root = NULL;
	}

	--size;
}

int SplayTree::NthNode(int k) {
	int x = root;
	while (1) {
		while (nodes[x].l && nodes[nodes[x].l].cnt > k) 
			x = nodes[x].l;
		
		
		if (nodes[x].l) 
			k -= nodes[nodes[x].l].cnt;
		if (!k--) 
			break;
		
		x = nodes[x].r;
	}
	Splay(x);

	return nodes[x].key;
}

int max = -1;
void SplayTree::InOrder(int root, int level) {
	/*if (max < level)
		max = level;*/
	if (root) {
		InOrder(nodes[root].l, level + 1);
		if (max < nodes[root].key)
			max = nodes[root].key;
		else {
			cout << max << " > " << nodes[root].key << endl;
			return;
		}
		InOrder(nodes[root].r, level + 1);
	}
	/*if (level == 0)
		cout << max << endl;*/
}

int SplayTree::GetRoot() {
	return root;
}

int SplayTree::GetSize() {
	return size;
}