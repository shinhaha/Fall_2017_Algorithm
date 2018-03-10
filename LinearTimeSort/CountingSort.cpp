#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
#include <iostream>
using namespace std;

int* arr;
void printing(int* A, int n);
void insertionSort(int* A, int start, int end);

void CountingSort(int* A, int* B,int n,int k) {//n은 데이터 개수,k는 데이터 최대값
	//A는 숫자저장 배열
	//C는 숫자의 개수 배열
	//B는 저장배열
	int* C = (int*)malloc((k+1)*sizeof(int));
	for (int i = 0; i <= k; i++)
		C[i] = 0;//카운트 배열을 초기화
	for (int j = 0; j <n; j++)
		C[A[j]] += 1;//카운트해줌
	for (int i = 1; i <= k; i++)
		C[i] += C[i - 1];//누적함
	for (int j = n-1 ; j >=0; j--){
		B[C[A[j]]-1] = A[j];//뒤에서부터 값을 쌓아감
		C[A[j]] -= 1;
	}
	printing(B,n);//출력
	free(C);
}

void printing(int* A, int n) {
	for (int i = 0; i < n; i++) 
			printf("%d ", A[i]);
}

int main() {
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\신하람\\Desktop\\counting.txt", "r");
	int i = 0;
	int maxValue= -1;
	if (f != NULL) {
		while (!feof(f)) {
			arr = (int*)realloc(arr, sizeof(int)*(i + 1));
			fscanf(f, "%d", (arr + i));
			maxValue = max(maxValue, arr[i]);
			i++;
		}
		fclose(f);
	}
	else
		printf("파일 읽기 실패");
	int* B = (int *)malloc(i*sizeof(int));
	CountingSort(arr,B,i,maxValue);
}
