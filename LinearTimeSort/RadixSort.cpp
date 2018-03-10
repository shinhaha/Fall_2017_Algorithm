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
	for (int i = 0; i < 4; i++) {//32/8�� 4�̹Ƿ� 4���Ѵ�
	B = countingSort(A, B, n, 8*i);//ī���� �����ѹ迭�� B�� ����
	for (int i = 0; i < n; i++)
		A[i] = B[i];//A�� B�� ����
}
	printing(A, n);
}

unsigned int* countingSort(unsigned int *A,unsigned int* B,int n, int shift) {
	int max = -1, mask = 511;   //8��Ʈ 11111111 ����ũ
	for (int i = 0; i < n; i++) { 
		int s = (A[i] >> shift) & mask;
		if (s> max)//8��Ʈ�� �������� max���� ���Ѵ�.
			max = s;
	}
	int* C = (int*)calloc(max+1,sizeof(int));   // �ִ밪 +1�迭 0�ʱ�ȭ
	for (int i = 0; i <n; i++)  
		C[(A[i] >> shift) & mask] += 1;   //���ڿ� shift�� �� ���� mask�� &���� �Ѱ� count�Ѵ�.
	for (int i = 1; i <=max; i++)  //����
		C[i] = C[i] + C[i - 1];
	for (int i = n - 1; i >= 0; i--) {
		B[C[(A[i] >> shift) & mask] - 1] = A[i];
		C[(A[i] >> shift) & mask] -= 1;   //�ε��� �̵���Ų��=>�ϳ��� �׾ư���
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
fopen_s(&f, "C:\\Users\\���϶�\\Desktop\\input500.txt", "r");
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
printf("���� �б� ����");
unsigned int* B = (unsigned int *)malloc(i * sizeof(int));
RadixSort(arr,B,i);
free(B);
}