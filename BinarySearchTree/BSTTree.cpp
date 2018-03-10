#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
#include <iostream>
using namespace std;

typedef struct Tree {
	int key;
	struct Tree* left;
	struct Tree* right;
	struct Tree* p;
}tree;
tree* TreeInsert(tree *A, tree *z);
int* arr;
tree* T = NULL;

tree* TreeInsert(tree *A, tree *z) {
	tree *y = NULL;
	tree *x = A;
	while (x!= NULL) {
		(y) = (x);
		if ((z)->key <(x)->key)
			x = (x)->left;
		else
			x = (x)->right;
	}
	(z)->p = (y);
	if (y == NULL)
		A = z;
	else if ((z)->key < (y)->key)
		((y)->left) = z;
	else (y)->right = z;
	return A;
}

tree* IterativeSearch(tree *x, int key) {   //iterative
	while (x != NULL && key != x->key) {
		if (key < x->key)
			x = x->left;
		else 
			x = x->right;
	}
	if (x== NULL) 
		return NULL;
	return x;
}

tree* TreeSearch(tree* x,int* A, int k) {
	while (x != NULL&&k != x->key)
		if (k < x->key)
			x = x->left;
		else
			x = x->right;
	return x;
}

tree* TreeMinimum(tree* x) {
	while (x->left != NULL)
		x = x->left;
	return x;
}

tree* TreeMaximum(tree* x) {
	while (x->right != NULL)
		x = x->right;
	return x;
}

tree* TreeSuccessor(tree* x) {
	if (x->right != NULL)
		return TreeMinimum(x->right);
	tree* y = x->p;
	while (y != NULL&&x == y->right) {
		x = y;
		y = y->p;
	}
	return y;
}

tree* TreePredecessor(tree* x) {
	if (x->left != nullptr) 
		return TreeMaximum(x->left);
	tree* y = x->p;
	while (y != NULL && x == y->left) {
		x = y;
		y = y->p;
	}
	return y;
}

tree* Delete(tree* x, int k) {
	tree* temp;
	if (x == NULL) {
		return NULL;
	}
	else if (k < x->key) {
		x->left = Delete(x->left, k);
	}
	else if (k > x->key) {
		x->right = Delete(x->right, k);
	}
	else {
		if (x->right && x->left) {
			temp = TreeMinimum(x->right);
			x->key = temp->key;
			x->right = Delete(x->right, temp->key);
		}
		else {
			temp =x;
			if( x->left == NULL)
				x = x->right;
			else if (x->right = NULL)
				x =x->left;
			free(temp);
		}
	}
	return x;
}

void inordertreewalk(tree* x) {
	if (x != NULL) {
		inordertreewalk(x->left);
		printf("%d ", x->key);
		inordertreewalk(x->right);
	}
}

int main() {
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\신하람\\Desktop\\데이터.txt", "r");
	int i = 0;
	int maxValue = -1;
	if (f != NULL) {
		while (!feof(f)) {
			arr = (int*)realloc(arr, sizeof(int)*(i + 1));
			fscanf(f, "%d", (arr + i));
			maxValue = max(maxValue, arr[i]);
			i++;
		}
		fclose(f);
	}
	else
		printf("파일 읽기 실패");

	for (int q = 0; q < i; q++) {
		tree *temp=(tree*)malloc(sizeof(tree));
		temp->key = arr[q];
		temp->p = temp->left = temp->right = NULL;
		T=TreeInsert(T,temp);
	}
	
	printf("그냥 삽입\nTreeSuccessor:");
	cout << TreeSuccessor(T)->key << endl;
	printf("TreePredecessor:");
	cout << TreePredecessor(T)->key << endl;
	
}

