#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<time.h>
#include<iostream>
using namespace std;
void TopDownMergeSort(int* A,int n);
void TopDownSplitMerge(int* A, int iBegin, int iEnd);
void TopDownMerge(int* A, int iBegin, int iMiddle, int iEnd);
void copyArray(int* A, int Astart, int* B, int Bstart, int length);
void printing(int* A, int n);
void insertionSort(int* A, int start,int end);
int* arr;

int visit[100001] = { 0 };

void insertionSort(int* A,int start,int end) {
	for (int i = start+1; i < end; i++) {
		int key = A[i];
		int j = i;
		for (j = i; j > start && A[j - 1] > key; j--)
			A[j] = A[j - 1];
		A[j] = key;
	}
}

void TopDownMergeSort(int* A,int n) {
	TopDownSplitMerge(A, 0, n);
}

void TopDownSplitMerge(int* A, int iBegin, int iEnd) {//iEnd-iBegin은 사이즈
	//if(visit[iEnd-iBegin]==0){//실제로 사이즈 가능한경우 출력
	//printf("%d\n",iEnd-iBegin);
	//visit[iEnd-iBegin]=1;}
	//if (iEnd - iBegin < 2)
		//return;
	if (iEnd - iBegin <=39){//사이즈가 39이하면 insertionsort
		insertionSort(A, iBegin, iEnd);
	}
else {//아니라면 mergesplit한다
	int iMiddle = (iEnd + iBegin) / 2;
	TopDownSplitMerge(A, iBegin, iMiddle);
	TopDownSplitMerge(A, iMiddle, iEnd);
	TopDownMerge(A, iBegin, iMiddle, iEnd);//insertion을 하든 split을 하든 여기서 합쳐진다.
	}
}
void TopDownMerge(int* A, int iBegin, int iMiddle, int iEnd) {
	if (A[iMiddle - 1] <= A[iMiddle]) return;
	int i = iBegin, j = iMiddle, k = 0;
	int* aa = (int*)malloc(sizeof(int)*(iEnd - iBegin));
	while (i < iMiddle&&j < iEnd)
		if (A[i] < A[j])aa[k++] = A[i++];
		else aa[k++] = A[j++];
		if (i <iMiddle)copyArray(A,i,A,iBegin+k,iMiddle-i);
		copyArray(aa,0,A,iBegin, k);
		free(aa);
}
void copyArray(int* A,int Astart,int* B,int Bstart, int length) {
	int x = Astart;
	int y = Bstart;
	for (int i = 0; i < length; i++)
		 B[y++]= A[x++];
}

void printing(int* A,int n) {
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
	fscanf(f,"%d",(arr+i));
	i++;
}
	fclose(f);
}
else
	printf("파일 읽기 실패");
float start = clock();
TopDownMergeSort(arr,i);
float end = clock();
float finish = end - start;
printf("%.12f\n", finish /CLOCKS_PER_SEC);
printing(arr, i);
}