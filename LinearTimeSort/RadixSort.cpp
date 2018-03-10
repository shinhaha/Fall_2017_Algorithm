#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
#include <iostream>
using namespace std;

unsigned int* arr;
void printing(unsigned int* A, int n);
unsigned int* countingSort(unsigned int *A,unsigned int *B,int count, int shift);
void RadixSort(unsigned int *A, unsigned int*B, int count);

void RadixSort(unsigned int *A, unsigned int*B, int n) {//32 8
	for (int i = 0; i < 4; i++) {//32/8은 4이므로 4번한다
	B = countingSort(A, B, n, 8*i);//카운팅 소팅한배열을 B에 리턴
	for (int i = 0; i < n; i++)
		A[i] = B[i];//A에 B를 복사
}
	printing(A, n);
}

unsigned int* countingSort(unsigned int *A,unsigned int* B,int n, int shift) {
	int max = -1, mask = 511;   //8비트 11111111 마스크
	for (int i = 0; i < n; i++) { 
		int s = (A[i] >> shift) & mask;
		if (s> max)//8비트만 봤을때의 max값을 구한다.
			max = s;
	}
	int* C = (int*)calloc(max+1,sizeof(int));   // 최대값 +1배열 0초기화
	for (int i = 0; i <n; i++)  
		C[(A[i] >> shift) & mask] += 1;   //인자에 shift를 한 값에 mask와 &연산 한것 count한다.
	for (int i = 1; i <=max; i++)  //누적
		C[i] = C[i] + C[i - 1];
	for (int i = n - 1; i >= 0; i--) {
		B[C[(A[i] >> shift) & mask] - 1] = A[i];
		C[(A[i] >> shift) & mask] -= 1;   //인덱스 이동시킨다=>하나씩 쌓아간다
	}
	free(C);
	return B;
}


void printing(unsigned int* A, int n) {
for (int i = 0; i < n; i++) 
printf("%d ", A[i]);
}

int main() {
FILE *f = NULL;
fopen_s(&f, "C:\\Users\\신하람\\Desktop\\input500.txt", "r");
int i = 0;
if (f != NULL) {
while (!feof(f)) {
arr = (unsigned int*)realloc(arr, sizeof(int)*(i + 1));
fscanf(f, "%d", (arr + i));
i++;
}
fclose(f);
}
else
printf("파일 읽기 실패");
unsigned int* B = (unsigned int *)malloc(i * sizeof(int));
RadixSort(arr,B,i);
free(B);
}