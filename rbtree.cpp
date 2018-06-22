#include "stdafx.h"

int BLACK = 0;
int RED = 1;

struct node {
	struct node *left;
	struct node *right;
	struct node *parent;
	int value;
	int color; //0 is black, 1 is red
};

struct rbtree {
	struct node *root;
};

void print(struct rbtree *t);

struct rbtree *create();

void insert_node(struct rbtree *t, int value);
void delete_node(struct rbtree *t, int value);

static void replace_node(struct rbtree *t, struct node *o, struct node *n);
static void insert_case1(struct rbtree *t, struct node *n);
static void insert_case2(struct rbtree *t, struct node *n);
static void insert_case3(struct rbtree *t, struct node *n);
static void insert_case4(struct rbtree *t, struct node *n);
static void insert_case5(struct rbtree *t, struct node *n);
static void delete_case1(struct rbtree *t, struct node *n);
static void delete_case2(struct rbtree *t, struct node *n);
static void delete_case3(struct rbtree *t, struct node *n);
static void delete_case4(struct rbtree *t, struct node *n);
static void delete_case5(struct rbtree *t, struct node *n);
static void delete_case6(struct rbtree *t, struct node *n);

/*
helper tools
*/

void _print_node(struct node *n) {
	if (n->parent) {
		printf(" parent=%d ", n->parent->value);
	}
	else {
		printf(" parent=nil ");
	}
	if (n->left) {
		printf(" left=%d ", n->left->value);
	}
	else {
		printf(" left=nil ");
	}
	if (n->right) {
		printf(" right=%d ", n->right->value);
	}
	else {
		printf(" right=nil ");
	}
}


void _print(struct node *n) {
	if (!n) {
		return;
	}
	if (n->color == RED) {
		printf("%d(red)", n->value);
		_print_node(n);
	}
	else {
		printf("%d(black)", n->value);
		_print_node(n);
	}
	printf("\n");
	_print(n->left);
	_print(n->right);
}

void print(struct rbtree *t) {
	struct node *r = t->root;
	printf("root is %d\n", r->value);
	_print(r);
}

struct node *grandparent(struct node *n) {
	return n->parent->parent;
}

struct node *sibling(struct node *n) {
	if (n == n->parent->left)
		return n->parent->right;
	else
		return n->parent->left;
}

struct node *uncle(struct node *n) {
	return sibling(n->parent);
}

int node_color(struct node *n) {
	return n == NULL ? BLACK : n->color;
}

struct rbtree *create() {
	struct rbtree *t = (struct rbtree*)malloc(sizeof(struct rbtree));
	t->root = NULL;
	return t;
}

struct node *new_node(int value, int color, struct node *left, struct node *right) {
	struct node *n = (struct node*)malloc(sizeof(struct node));
	n->color = color;
	n->left = left;
	n->right = right;
	n->value = value;

	if (left != NULL)
	{
		left->parent = n;
	}

	if (right != NULL) {
		right->parent = n;
	}
	n->parent = NULL;

	return n;
}

struct node *search(struct rbtree *t, int value) {
	struct node *n = t->root;
	while (n != NULL) {
		if (value == n->value) {
			return n;
		}
		else if (value < n->value) {
			n = n->left;
		}
		else if (value > n->value) {
			n = n->right;
		}
	}
	return NULL;
}

void replace_node(struct rbtree *t, struct node *o, struct node *n) {
	if (o->parent == NULL) {
		t->root = n;
	}
	else {
		if (o == o->parent->left)
			o->parent->left = n;
		else
			o->parent->right = n;
	}
	if (n != NULL) {
		n->parent = o->parent;
	}
}

void rotate_left(struct rbtree *t, struct node *n) {
	struct node *r = n->right;
	replace_node(t, n, r);
	n->right = r->left;
	if (r->left != NULL) {
		r->left->parent = n;
	}
	r->left = n;
	n->parent = r;
}

void rotate_right(struct rbtree *t, struct node *n) {
	struct node *l = n->left;
	replace_node(t, n, l);
	n->left = l->right;
	if (l->right != NULL) {
		l->right->parent = n;
	}
	l->right = n;
	n->parent = l;
}

/*
insert function start
*/

void insert_case1(struct rbtree *t, struct node *n) {
	if (n->parent == NULL)
		n->color = BLACK;
	else
		insert_case2(t, n);
}

void insert_case2(struct rbtree *t, struct node *n) {
	if (node_color(n->parent) == BLACK)
		return; /* Tree is still valid */
	else
		insert_case3(t, n);
}

void insert_case3(struct rbtree *t, struct node *n) {
	if (node_color(uncle(n)) == RED) {
		n->parent->color = BLACK;
		uncle(n)->color = BLACK;
		grandparent(n)->color = RED;
		insert_case1(t, grandparent(n));
	}
	else {
		insert_case4(t, n);
	}
}

void insert_case4(struct rbtree *t, struct node *n) {
	if (n == n->parent->right && n->parent == grandparent(n)->left) {
		rotate_left(t, n->parent);
		n = n->left;
	}
	else if (n == n->parent->left && n->parent == grandparent(n)->right) {
		rotate_right(t, n->parent);
		n = n->right;
	}
	insert_case5(t, n);
}

void insert_case5(struct rbtree *t, struct node *n) {
	n->parent->color = BLACK;
	grandparent(n)->color = RED;
	if (n == n->parent->left && n->parent == grandparent(n)->left) {
		rotate_right(t, grandparent(n));
	}
	else {
		rotate_left(t, grandparent(n));
	}
}

void insert_node(struct rbtree *t, int value) {
	struct node *n = new_node(value, RED, NULL, NULL);
	if (t->root == NULL) {
		t->root = n;
	}
	else {
		struct node *r = t->root;
		while (1) {
			if (value == r->value) {
				//value is root value
				return;
			}
			else if (value > r->value) {
				if (r->right == NULL) {
					r->right = n;
					break;
				}
				else {
					r = r->right;
				}
			}
			else if (value < r->value) {
				if (n->left == NULL) {
					if (r->left == NULL) {
						r->left = n;
						break;
					}
					else {
						r = r->left;
					}
				}
			}
		}
		n->parent = r;
	}
	insert_case1(t, n);
}

/*
insert function end
*/

void delete_case1(struct rbtree *t, struct node *n) {
	if (n->parent == NULL)
		return;
	else
		delete_case2(t, n);
}

void delete_case2(struct rbtree *t, struct node *n) {
	if (node_color(sibling(n)) == RED) {
		n->parent->color = RED;
		sibling(n)->color = BLACK;
		if (n == n->parent->left)
			rotate_left(t, n->parent);
		else
			rotate_right(t, n->parent);
	}
	delete_case3(t, n);
}

void delete_case3(struct rbtree *t, struct node *n) {
	if (node_color(n->parent) == BLACK &&
		node_color(sibling(n)) == BLACK &&
		node_color(sibling(n)->left) == BLACK &&
		node_color(sibling(n)->right) == BLACK)
	{
		sibling(n)->color = RED;
		delete_case1(t, n->parent);
	}
	else
		delete_case4(t, n);
}

void delete_case4(struct rbtree *t, struct node *n) {
	if (node_color(n->parent) == RED &&
		node_color(sibling(n)) == BLACK &&
		node_color(sibling(n)->left) == BLACK &&
		node_color(sibling(n)->right) == BLACK)
	{
		sibling(n)->color = RED;
		n->parent->color = BLACK;
	}
	else
		delete_case5(t, n);
}

void delete_case5(struct rbtree *t, struct node *n) {
	if (n == n->parent->left &&
		node_color(sibling(n)) == BLACK &&
		node_color(sibling(n)->left) == RED &&
		node_color(sibling(n)->right) == BLACK)
	{
		sibling(n)->color = RED;
		sibling(n)->left->color = BLACK;
		rotate_right(t, sibling(n));
	}
	else if (n == n->parent->right &&
		node_color(sibling(n)) == BLACK &&
		node_color(sibling(n)->right) == RED &&
		node_color(sibling(n)->left) == BLACK)
	{
		sibling(n)->color = RED;
		sibling(n)->right->color = BLACK;
		rotate_left(t, sibling(n));
	}
	delete_case6(t, n);
}

void delete_case6(struct rbtree *t, struct node *n) {
	sibling(n)->color = node_color(n->parent);
	n->parent->color = BLACK;
	if (n == n->parent->left) {
		sibling(n)->right->color = BLACK;
		rotate_left(t, n->parent);
	}
	else
	{
		sibling(n)->left->color = BLACK;
		rotate_right(t, n->parent);
	}
}

struct node *maximum_node(struct node *n) {
	while (n->right != NULL) {
		n = n->right;
	}
	return n;
}

void delete_node(struct rbtree *t, int value) {
	struct node *child;
	struct node *n = search(t, value);
	if (n == NULL) {
		return;
	}
	if (n->left != NULL && n->right != NULL) {
		struct node *pred = maximum_node(n->left);
		n->value = pred->value;
		n = pred;
	}

	child = n->right == NULL ? n->left : n->right;
	if (node_color(n) == BLACK) {
		n->color = node_color(child);
		delete_case1(t, n);
	}
	replace_node(t, n, child);
	if (n->parent == NULL && child != NULL) {
		child->color = BLACK;
	}
	free(n);
}