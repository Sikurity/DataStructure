//
//  FenwickTree.cpp
//  DataStructure
//
//  Created by YeongsikLee on 2018. 9. 9..
//  Copyright © 2018년 Hanyang Osori. All rights reserved.
//

#include "FenwickTree.hpp"

using LL = long long;

const int MAX_N = 100000;
LL tree[MAX_N + 1];

LL read(LL pos)
{
    LL ret = 0;

    while (pos > 0) {
        ret += tree[pos];
        pos -= (pos & -pos);
    }

    return ret;
}

void update(LL pos, LL value)
{
    while (pos <= MAX_N) {
        tree[pos] += value;
        pos += (pos & -pos);
    }
}

