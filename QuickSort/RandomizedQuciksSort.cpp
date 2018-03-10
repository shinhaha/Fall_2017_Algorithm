#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
int* arr;
int RandomizedPartition(int*A, int p, int r);
void Quicksort(int* A, int p, int r);
void Swap(int* A, int x, int y);
int Partition(int*A, int p, int r);
void printing(int* A, int n);

void Quicksort(int* A, int p, int r) {
	if (p < r) {
		int q = RandomizedPartition(A, p, r);
		Quicksort(A, p, q - 1);
		Quicksort(A, q + 1, r);
	}
}

int RandomizedPartition(int*A, int p, int r) {
	int i = rand() % (r-p+1) + p;//p와 r까지의 랜덤값을 정하고
	Swap(A,r,i);//맨오른쪽 값과 Swap
	return Partition(A, p, r);
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
	fopen_s(&f,"C:\\test1.txt", "r");
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
	Quicksort(arr,0,i-1);
	float end = clock();
	float finish = end - start;
	//printf("RandomizedQuickSort : %.12f\n", finish / CLOCKS_PER_SEC);
	printing(arr, i);
}
