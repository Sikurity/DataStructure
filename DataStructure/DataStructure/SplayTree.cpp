#include <iostream>
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
    int g = nodes[p].p;
    int c;
    if (x == nodes[p].l) {
        c = nodes[x].r;
        nodes[p].l = c;
        nodes[x].r = p;
    }
    else {
        c = nodes[x].l;
        nodes[p].r = c;
        nodes[x].l = p;
    }
    nodes[x].p = g;
    nodes[p].p = x;
    
    if (c)
        nodes[c].p = p;
    
//    (g ? p == nodes[g].l ? nodes[g].l : nodes[g].r : root) = x;
    if (g) {
        if(p == nodes[g].l)
            nodes[g].l = x;
        else
            nodes[g].r = x;
    }
    else
        root = x;
    
    Update(p);
    Update(x);
}

// zig-zig, zig-zag
void SplayTree::Splay(int x) {
    while (nodes[x].p) { // when x is not root
        int p = nodes[x].p;
        int g = nodes[p].p;
        if (g) // zigzig then p, zigzag then x
            Rotate((x == nodes[p].l) == (p == nodes[g].l) ? p : x);
        Rotate(x); 
    }
}

bool SplayTree::Insert(int key) {
    int p = root;

    if (p) {
        int lr = 0;
        while (!lr) {
            if (nodes[p].key == key)
				return false; 
			else if (nodes[p].key < key) {
                if (!nodes[p].r)
                    lr = 1;
				else
					p = nodes[p].r;
            }
            else {
                if (!nodes[p].l)
                    lr = -1;
				else
					p = nodes[p].l;
            }
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
		Update(x);
    }
    
    ++size;
    return true;
}

bool SplayTree::Find(int key) {
    int p = root;
    if (!p)
        return false;
    
    while (p) {
        if (key == nodes[p].key) 
			break;
        if (key < nodes[p].key) {
            if (!nodes[p].l) 
				break;
            p = nodes[p].l;
        }
        else {
            if (!nodes[p].r) 
				break;
            p = nodes[p].r;
        }
    }
    Splay(p);
    
    return key == nodes[p].key;
}

bool SplayTree::Delete(int key) {
    if (!Find(key)) 
        return false;
    
    int p = root;
    int l = nodes[p].l;
    int r = nodes[p].r;
	if (l) {
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
        
        while (l && nodes[l].cnt > k) {
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

void SplayTree::InOrder(int x) {
    if (x) {
		x = x < 0 ? root : x;
        InOrder(nodes[x].l);
		// cout << nodes[x].key << endl;
        InOrder(nodes[x].r);
    }
}