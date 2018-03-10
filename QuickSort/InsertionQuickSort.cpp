#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>

int* arr;
void Quicksort(int* A, int p, int r);
void Swap(int* A, int x, int y);
int Partition(int*A, int p, int r);
void printing(int* A, int n);
void insertionSort(int* A, int start, int end);

void Quicksort(int* A, int p, int r) {
	if (p < r) {
		if ((r - p) <100)//크기가 어느정도 이하면
			insertionSort(A, p, r + 1);//삽입정렬
		else {
			int q = Partition(A, p, r);//피봇을 정하고
			Quicksort(A, p, q - 1);////재귀적으로 호출
			Quicksort(A, q + 1, r);
		}
	}
}

int Partition(int*A, int p, int r) {
	int x = A[r];
	int i = p - 1;
	for (int j = p; j < r; j++) {
		if (A[j] <= x) {
			i++;
			Swap(A, i, j);
		}
	}
	Swap(A, i + 1, r);
	return i + 1;
}

void insertionSort(int* A, int start, int end) {
	for (int i = start + 1; i < end; i++) {
		int key = A[i];
		int j = i;
		for (j = i; j > start && A[j - 1] > key; j--)
			A[j] = A[j - 1];
		A[j] = key;
	}
}

void Swap(int* A, int x, int y) {
	int temp = A[x];
	A[x] = A[y];
	A[y] = temp;
}

void printing(int* A, int n) {
	for (int i = 0; i < n; i++)
		printf("%d ", A[i]);
}

int main() {
	FILE *f = NULL;
	fopen_s(&f, "C:\\test2.txt", "r");
	int i = 0;
	if (f != NULL) {
		while (!feof(f)) {
			arr = (int*)realloc(arr, sizeof(int)*(i + 1));
			fscanf(f, "%d", (arr + i));
			i++;
		}
		fclose(f);
	}
	else
		printf("파일 읽기 실패");
	srand((unsigned)time(NULL));
	float start = clock();
	Quicksort(arr, 0, i - 1);
	float end = clock();
	float finish = end - start;
	//printf("InsertionQuickSort : %.12f\n", finish / CLOCKS_PER_SEC);
	printing(arr, i);
}
