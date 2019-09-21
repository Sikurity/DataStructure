#pragma once

#define MAX_NODES_NUM 1000000

class SplayTree {
    void Update(int x);
    void Rotate(int x);
    void Splay(int x);

public:
    int root, last, size;

    struct {
        int l, r, p;
        int key;
        int cnt;
    } nodes[MAX_NODES_NUM + 1];

    bool Insert(int key);
    bool Find(int key);
    bool Delete(int key);
    int NthNode(int k);
    void InOrder(int x = -1);
};
