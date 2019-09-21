//
//  SegmentTree.cpp
//  DataStructure
//
//  Created by YeongsikLee on 2018. 9. 9..
//  Copyright © 2018년 Hanyang Osori. All rights reserved.
//

#include "SegmentTree.hpp"

int tree[1 << 18];
bool lazy[1 << 18];

void propagation(int node, int s, int e) {
    if (lazy[node]) {
        tree[node] = (e - s + 1) * lazy[node];
        if (s != e) {
            lazy[node << 1] += lazy[node << 1];
            lazy[node << 1 | 1] += lazy[node << 1 | 1];
        }
        lazy[node] = 0;
    }
}

void update(int node, int value, int s, int e, int l, int r) {
    propagation(node, s, e);
    
    if (e < l || r < s)
        return;
    
    if (l <= s && e <= r) {
        lazy[node] = value;
        propagation(node, s, e);
        return;
    }
    
    int m = (s + e) >> 1;
    
    update(node << 1, value, s, m, l, r);
    update(node << 1 | 1, value, m + 1, e, l, r);
    
    tree[node] = tree[node << 1] + tree[node << 1 | 1];
}

int query(int node, int s, int e, int l, int r) {
    propagation(node, s, e);
    
    if (e < l || r < s)
        return 0;
    
    if (l <= s && e <= r)
        return tree[node];
    
    int m = (s + e) >> 1;
    
    return query(node << 1, s, m, l, r) + query(node << 1 | 1, m + 1, e, l, r);
}
