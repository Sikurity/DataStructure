#include <cstdio>
#include "SplayTree.h"

using namespace std;

void SplayTree::Update(int x) {
	nodes[x].cnt = 1;
    // if (nodes[x].l)
		nodes[x].cnt += nodes[nodes[x].l].cnt;
    // if (nodes[x].r)
		nodes[x].cnt += nodes[nodes[x].r].cnt;
}

void SplayTree::Rotate(int x) {
	int p = nodes[x].p;
	int g = nodes[p].p;;
    
	int c;
    if (x == nodes[p].l) {
		c = nodes[x].r;
		nodes[x].r = p;
        nodes[p].l = c;
    }
    else {
        c = nodes[x].l;
		nodes[x].l = p;
		nodes[p].r = c;
    }

	if (g)
		((p == nodes[g].l) ? nodes[g].l : nodes[g].r) = x;
	else
		root = x;

	nodes[x].p = g;
    nodes[p].p = x;
    
    if (c)
        nodes[c].p = p;
    
    Update(p);
    Update(x);
}

// zig-zig, zig-zag
void SplayTree::Splay(int x) {
    while (nodes[x].p) { // when x is not root
        int p = nodes[x].p;
        int g = nodes[p].p;
        if (g) // zigzig then p, zigzag then x
            Rotate(((x == nodes[p].l) == (p == nodes[g].l)) ? p : x);
        Rotate(x); 
    }
}

bool SplayTree::Insert(int key) {

    if (root) {
		int x = root;
        while (key != nodes[x].key) {
			if (key < nodes[x].key) {
				if (!nodes[x].l)
					break;
				x = nodes[x].l;
            }
            else {
				if (!nodes[x].r)
					break;
				x = nodes[x].r;
            }
        }

		if (key == nodes[x].key)
			return false;
		
		(key < nodes[x].key ? nodes[x].l : nodes[x].r) = ++last;

		nodes[last] = { NULL, NULL, x, key, 0 };
        Splay(last);
    }
    else {
        root = ++last;

		nodes[root] = { NULL, NULL, NULL, key, 1 };
    }
    
    ++size;
    return true;
}

bool SplayTree::Find(int key) {
    
    if (!root)
        return false;
    
	int x = root;
    while (key != nodes[x].key) {
        if (key < nodes[x].key) {
            if (!nodes[x].l) 
				break;
            x = nodes[x].l;
        }
        else {
            if (!nodes[x].r) 
				break;
            x = nodes[x].r;
        }
    }
    Splay(x);
    
    return key == nodes[x].key;
}

bool SplayTree::Delete(int key) {
	if (!Find(key))
		return false;
    
	int l = nodes[root].l;
	int r = nodes[root].r;
	if(l) {
		root = l;
		nodes[root].p = NULL;
		if (r) {
			int x = root;
			while (nodes[x].r)
				x = nodes[x].r;

			nodes[x].r = r;
			nodes[r].p = x;

			Splay(x);
		}
	}
	else if (r) { // only right child
		root = r;
		nodes[root].p = NULL;
	}
    else    // delete p;
        root = NULL;

    --size;
    return true;
}

int SplayTree::NthNode(int k) {

	if (k < 0 || size <= k)
		return -1;

    int x = root;
    while (true) {
        int l = nodes[x].l;
        while (l && k < nodes[l].cnt) {
            x = l;
			l = nodes[x].l;
		}
        
        if (l)
            k -= nodes[l].cnt;
        if (!k--) 
            break;
        
        x = nodes[x].r;
    }
    Splay(x);

    return x;
}

int tt;
void SplayTree::InOrder(int x) {
    if (x) {
		x = x < 0 ? root : x;
        InOrder(nodes[x].l);
		tt = nodes[x].key; // printf("%d ", key);
        InOrder(nodes[x].r);
    }
}