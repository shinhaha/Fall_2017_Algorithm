#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
void TopDownMergeSort(int* A, int* B, int n);
void TopDownSplitMerge(int* A, int iBegin, int iEnd, int* B);
void TopDownMerge(int* A, int iBegin, int iMiddle, int iEnd, int* B);
void copyArray(int* B, int iBegin, int iEnd, int* A);
void printing(int* A, int n);
int* arr;
int* workarr;

void TopDownMergeSort(int* A, int* B,int n) {
	TopDownSplitMerge(A, 0, n, B);
}

void TopDownSplitMerge(int* A, int iBegin, int iEnd, int* B) {
	if (iEnd - iBegin < 2) return;
	int iMiddle = (iEnd + iBegin) / 2;
	TopDownSplitMerge(A, iBegin, iMiddle, B);
	TopDownSplitMerge(A, iMiddle, iEnd, B);
	TopDownMerge(A, iBegin, iMiddle, iEnd, B);
	copyArray(B, iBegin, iEnd, A);
}

void TopDownMerge(int* A, int iBegin, int iMiddle, int iEnd, int* B) {
	int i = iBegin;
	int j = iMiddle;
	for (int k = iBegin; k < iEnd; k++) {
		if (i < iMiddle && (j >= iEnd || A[i] <= A[j])) {
			B[k] = A[i]; i = i + 1;
		}
		else {
			B[k] = A[j]; j = j + 1;
		}
	}
}

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
	fopen_s(&f,"C:\\test_10000.txt", "r");
	int i = 0;
	if (f != NULL) {
		while (!feof(f)) {
			arr = (int*)realloc(arr, sizeof(int)*(i + 1));
			workarr= (int*)realloc(workarr, sizeof(int)*(i + 1));
			fscanf(f,"%d",(arr+i));
			i++;
		}
		fclose(f);
	}
	else
		printf("Read Fail");
	TopDownMergeSort(arr, workarr, i);
	printing(arr, i);
}