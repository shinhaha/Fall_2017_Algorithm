#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
void MaxHeapify(int* A, int i, int heapsize);
void BuildMaxHeap(int* A);
void HeapExtractMax(int* A,int tempsize);
void MaxHeapSort(int* A);
void MaxHeapIncreaseKey(int* A, int x, int key);
void MaxHeapInsert(int* A, int key);
void Max_Heap_Increase_Key_No_Constraint(int *A, int index, int key);
int *arr;
int heapsize;

void MaxHeapify(int* A, int i,int heapsize) {
	int l = 2*i;
	int r = 2*i+1;
	int largest;
	if (l <= heapsize&&A[l] > A[i])
		largest = l;
	else
		largest = i;
	if (r <= heapsize&&A[r] > A[largest])
		largest = r;
	if (largest != i) {
		int temp = A[i];
		A[i]=A[largest];
		A[largest] =temp;
		MaxHeapify(A, largest, heapsize);
	}

}
void BuildMaxHeap(int* A) {//전체 인자에 대하여 heapify
	for (int i = floor(heapsize/2); i >= 1; i--)
		MaxHeapify(arr, i,heapsize);
}

void HeapExtractMax(int* A,int tempsize) {
	int i = tempsize;
	int temp = A[1];
	A[1] = A[i];
	A[i] = temp;
}

void MaxHeapSort(int* A) {
	BuildMaxHeap(A);
	int tempsize = heapsize;
	for (int i = heapsize; i >= 2; i--) {
		HeapExtractMax(A, tempsize);
		tempsize --;
		MaxHeapify(A, 1,tempsize);
	}
}

void MaxHeapInsert(int* A, int key) {
	heapsize++;
	arr = (int*)realloc(arr, sizeof(int)*(heapsize+1));
	A[heapsize] =INT_MIN;
	MaxHeapIncreaseKey(A, heapsize, key);
}

void MaxHeapIncreaseKey(int* A, int x, int key) {
	if (key < A[x])
		printf("new key is smaller than current key");
	else {
		A[x] = key;
		while (x > 1 && A[(int)floor(x/ 2)] < A[x]){
			int temp = A[x];
			A[x] = A[(int)floor(x / 2)];
			A[(int)floor(x / 2)] = temp;
			x = (int)floor(x / 2);
		}
	}
}

void Max_Heap_Increase_Key_No_Constraint(int *A, int index, int key) {
	A[index] = key;
	BuildMaxHeap(A);
}
void printing(int* A, int n) {
	for (int i = 1; i <=n; i++)
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
	heapsize = i-1;

	BuildMaxHeap(arr);
	printf("Build Max Heap=>");
	printing(arr,heapsize);
	printf("\n");
	printf("Max Heap Insert 300=>");
	MaxHeapInsert(arr, 300);
	printing(arr, heapsize);
	printf("\n");
	printf("Max Heap Insert 1000=>");
	MaxHeapInsert(arr, 1000);
	printing(arr, heapsize);
	printf("\n");
	MaxHeapSort(arr);
	printf("Max Heap Sort=>");
	printing(arr, heapsize);
	printf("\n");
	Max_Heap_Increase_Key_No_Constraint(arr, 3, 44);
	printf("Max_Heap_Increase_Key_No_Constraint(arr, 3, 44) =>");
	printing(arr, heapsize);
	printf("\n");
}


