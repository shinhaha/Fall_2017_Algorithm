#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
void RecursiveBinarySearch(int* A, int start, int end,int find);
void printing(int* A, int n);
int* arr;

void printing(int* A, int n) {
	for (int i = 0; i < n; i++) 
			printf("%d ", A[i]);
}

void RecursiveBinarySearch(int* A,int start,int end,int find) {
	if (start <= end) {
		int i = (start + end) / 2;
		if (A[i] == find)
			printf("start:%d end:%d find:%d", start, end, find);
		else if (A[i] < find)
			RecursiveBinarySearch(A, i + 1, end, find);
		else if (A[i] > find)
			RecursiveBinarySearch(A, start, i - 1, find);
	}
	else 
		printf("없습니다.\n");
}

int main() {
	FILE *f = NULL;
	fopen_s(&f,"C:\\test_recursive.txt", "r");
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
		printf("Read Fail");
	RecursiveBinarySearch(arr, 0,i-1,1050);
}