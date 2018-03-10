#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
void IterativeMergeSort(int length);
void merge(int k, int length);
void printing(int* A, int n);
void copyArray(int* B, int iBegin, int iEnd, int* A);
int* arr;
int* workarr;

void IterativeMergeSort(int length) {
	for (int i = 1; i<length; i *= 2)
		merge(i, length);
}

void merge(int k,int length) {
	int mid,end,i,j,stack;
	for (int start = 0; start + k < length; start += k * 2) {
		mid = start + k;
		end = mid + k;
		if (end > length) end = length;
		stack= start; i = start; j = mid;
		for (stack = start; stack <end; stack++) {
			if (i < mid&& (j >= end|| arr[i] <= arr[j])) {
				workarr[stack] = arr[i]; i ++;
			}
			else {
				workarr[stack] = arr[j]; j ++;
			}
		}
		copyArray(workarr, start,end, arr);
	}}

void copyArray(int* B, int iBegin, int iEnd, int* A) {
	for (int k = iBegin; k < iEnd; k++)
		A[k] = B[k];
}

void printing(int* A, int n) {
	for (int i = 0; i < n; i++)
			printf("%d ", A[i]);
}

int main() {
	FILE *f = NULL;
	fopen_s(&f, "C:\\test_10000.txt", "r");
	int i = 0;
	if (f != NULL) {
		while (!feof(f)) {
			arr = (int*)realloc(arr, sizeof(int)*(i + 1));
			workarr = (int*)realloc(workarr, sizeof(int)*(i + 1));
			fscanf(f, "%d", (arr + i));
			i++;
		}
		fclose(f);
	}
	else
		printf("Read Fail");
	IterativeMergeSort(i);
	printing(arr, i);
} 