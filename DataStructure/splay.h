#pragma once

#include <cstdio>

struct node {
	int l, r, p;
	int key;
	int cnt;
};

void Update(int x);
void Rotate(int x);
void Splay(int x);
void Insert(int key);
bool Find(int key);
void Delete(int key);
void Find_Kth(int k);
void InOrder(int root, int level = 0);
