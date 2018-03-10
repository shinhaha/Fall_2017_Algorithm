#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
#include <iostream>
using namespace std;
int* arr;
int RandomizedPartition(int*A, int p, int r);
int RandomizedSelect(int *A, int p, int r, int i);
void Swap(int* A, int x, int y);
int Partition(int*A, int p, int r);
void printing(int* A, int n);

int RandomizedSelect(int *A, int p, int r, int i) {
	if (p == r)//인덱스가 하나면
		return A[p];
	int q = RandomizedPartition(A, p, r);//랜덤으로 뽑고 파티션
	int k = q - p + 1;//몇번째 숫자인가
	if (i == k)//i번째 찾았으면
		return A[q];//리턴
	if (i < k)//아니면 divide and conquer
		return RandomizedSelect(A, p, q - 1, i);
	else
		return RandomizedSelect(A, q + 1, r, i - k);
}

int RandomizedPartition(int*A, int p, int r) {
	int i = rand() % (r - p + 1) + p;//p와 r까지의 랜덤값을 정하고
	Swap(A, r, i);//맨오른쪽 값과 바꿔준다
	return Partition(A, p, r);//그 후 원래의 partition 실행
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
void printing(int* A, int n) {
	for (int i = 0; i < n; i++) 
			printf("%d ", A[i]);
}
void insertionSort(int* A, int start, int end) {//삽입정렬
	for (int i = start + 1; i < end; i++) {
		int key = A[i];
		int j = i - 1;
		for (j = i; j > start && A[j - 1] > key; j--)
			A[j] = A[j - 1];
		A[j] = key;
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
	srand((unsigned)time(NULL));

	cout<<RandomizedSelect(arr, 0, i - 1,10)<<endl;	
	printing(arr, i);
}