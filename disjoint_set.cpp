#include "stdafx.h"

int parent[1000], size[1000], rank[1000]; 

void init() { 
	for (int i = 0; i < 1000; i++) { 
		parent[i] = i; size[i] = 1; rank[i] = 0; 
	} 
} 

int find(int p) { 
	if (parent[p] == p) 
		return p; 
	else 
		return parent[p] = find(parent[p]); 
}

void uni(int p, int q) { 

	p = find(p); 
	q = find(q); 

	if (rank[p] < rank[q]) 
		parent[p] = q, size[q] += size[p]; 
	else 
		parent[q] = p, size[p] += size[q]; 

	if (rank[p] == rank[q]) 
		rank[p]++; 
}