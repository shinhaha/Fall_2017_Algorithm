#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
void MinHeapify(int* A, int i, int heapsize);
void BuildMinHeap(int* A);
void HeapExtractMin(int* A, int tempsize);
void MinHeapSort(int* A);
void MinHeapDecreaseKey(int* A, int x, int key);
void MinHeapInsert(int* A, int key);
void Min_Heap_Increase_Key_No_Constraint(int *A, int index, int key);
int *arr;
int heapsize;
void MinHeapify(int* A, int i, int heapsize) {
	int l = 2 * i;
	int r = 2 * i + 1;
	int smallest;
	if (l <= heapsize&&A[l] < A[i])
		smallest = l;
	else
		smallest = i;
	if (r <= heapsize&&A[r]<A[smallest])
		smallest = r;
	if (smallest != i) {
		int temp = A[i];
		A[i] = A[smallest];
		A[smallest] = temp;
		MinHeapify(A, smallest, heapsize);
	}
}
void BuildMinHeap(int* A) {
	for (int i = floor(heapsize / 2); i >= 1; i--)
		MinHeapify(arr, i, heapsize);
}
void HeapExtractMin(int* A,int tempsize) {
	int i = tempsize;
	int temp = A[1];
	A[1] = A[i];
	A[i] = temp;
}

void MinHeapSort(int* A) {
	BuildMinHeap(A);
	int tempsize = heapsize;
	for (int i = heapsize; i >= 2; i--) {
		HeapExtractMin(A, tempsize);
		tempsize --;
		MinHeapify(A, 1, tempsize);
	}
}

void MinHeapInsert(int* A, int key) {
	heapsize++;
	arr = (int*)realloc(arr, sizeof(int)*(heapsize + 1));
	A[heapsize] = INT_MAX;
	MinHeapDecreaseKey(A, heapsize, key);
}

void MinHeapDecreaseKey(int* A, int x, int key) {
	if (key > A[x])
		printf("new key is larger than current key");
	else {
		A[x] = key;
		while (x > 1 && A[(int)floor(x / 2)] > A[x]) {
			int temp = A[x];
			A[x] = A[(int)floor(x / 2)];
			A[(int)floor(x / 2)] = temp;
			x = (int)floor(x / 2);
		}
	}
}

void Min_Heap_Increase_Key_No_Constraint(int *A, int index, int key) {
	A[index] = key;
	BuildMinHeap(A);
}

void printing(int* A, int n) {
	for (int i = 1; i <= n; i++)
		printf("%d ", A[i]);
}
int main() {
	FILE *f = NULL;
	fopen_s(&f, "C:\\test.txt", "r");
	int i = 1;
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

	heapsize = i - 1;
	
	BuildMinHeap(arr);
	printf("Build Min Heap=>");
	printing(arr, heapsize);
	printf("\n");
	printf("Min Heap Insert 300=>");
	MinHeapInsert(arr, 300);
	printing(arr, heapsize);
	printf("\n");
	printf("Min Heap Insert 1000=>");
	MinHeapInsert(arr, 1000);
	printing(arr, heapsize);
	printf("\n");
	MinHeapSort(arr);
	printf("Min Heap Sort=>");
	printing(arr, heapsize);
	printf("\n");
	Min_Heap_Increase_Key_No_Constraint(arr, 3, 44);
	printf("Min_Heap_Decrease_Key_No_Constraint(arr, 3, 44) =>");
	printing(arr, heapsize);
	printf("\n");

}


