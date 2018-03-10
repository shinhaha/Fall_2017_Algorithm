#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
#include <iostream>
using namespace std;
int* arr;
void insertionSort(int* A, int start, int end);
int Select(int *A, int p, int r, int i);
void Swap(int* A, int x, int y);
int Partition(int*A, int p, int r);
void printing(int* A, int start,int n);
int MedianPartition(int*A, int p, int r,int median);

int Select(int *A, int p, int r, int i) {//i번째 값 찾는 함수
if (p == r)
	return A[p];
int q = Partition(A, p, r);
int k = q - p + 1;
if (i == k)
	return A[q];
if (i < k)
	return Select(A, p, q - 1, i);
else
	return Select(A, q + 1, r, i - k);
}

int hamsu(int *A, int p, int r) {
	int k = ceil((double)r / 5.0);//그룹 몇개
	int* temp = (int*)malloc(k * sizeof(int));//중간값 저장할 배열
	for (int i = 0; i < k; i++) {
		int end= 5*(i + 1)>=r?r:5*(i + 1);
		insertionSort(A, 5*i,end);//5개그룹 삽입정렬
	    temp[i]=Select(A, 5*i,end-1,((5*i+end)/2)-5*i+1);//5개마다의 중간값
	}
	int median=Select(temp,0, k-1,k/2);//중간값중 중간값 리턴
	cout << "중간값은:" << median<<endl<<"인덱스는:";
	return MedianPartition(A,p,r,median);//그 중간값을 pivot으로
	}

	int MedianPartition(int*A, int p, int r,int median) {
	int x = median;//피봇의 값
	int i = p - 1;//시작점
	for (int j = p; j < r; j++) {//서브배열을 돌면서
	if (A[j] <= x) {//피봇보다 작으면
	i++;
	Swap(A, i, j);//swap
	}
	}
	Swap(A, i + 1, r);//피봇을 피봇보다 작은거 뒤에놓는다
	return i + 1;//피봇의 인덱스 리턴
	}

int Partition(int*A, int p, int r) {
	int x = A[r];//피봇의 값
	int i = p - 1;//시작점
	for (int j = p; j < r; j++) {//서브배열을 돌면서
		if (A[j] <= x) {//피봇보다 작으면
		i++;
		Swap(A, i, j);//swap
	}
	}
	Swap(A, i + 1, r);//피봇을 피봇보다 작은거 뒤에놓는다
	return i + 1;//피봇의 인덱스 리턴
}

void Swap(int* A, int x, int y) {
	int temp = A[x];
	A[x] = A[y];
	A[y] = temp;
}

void printing(int* A, int start,int n) {
	for (int i = start; i < n; i++) {
			printf("%d ", A[i]);
	}
}

void insertionSort(int* A, int start, int end) {//삽입정렬
for (int i = start + 1; i < end; i++) {//정렬할 인덱스 다음인덱스부터 마지막 인덱스까지 돈다
	int key = A[i];//key를 i인덱스로 정하고
	int j = i - 1;
	for (j = i; j > start && A[j - 1] > key; j--)//작은거 찾으면
		A[j] = A[j - 1];//땡기고
		A[j] = key;//값 스왑
	}
}

int main() {
FILE *f = NULL;
fopen_s(&f, "C:\\Users\\신하람\\Desktop\\input500.txt", "r");
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
	cout<<hamsu(arr, 0,i)<<endl;
}
