#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
#include <iostream>
using namespace std;

int* arr;
void printing(int* A, int n);
void insertionSort(int* A, int start, int end);

void CountingSort(int* A, int* B,int n,int k) {//n�� ������ ����,k�� ������ �ִ밪
	//A�� �������� �迭
	//C�� ������ ���� �迭
	//B�� ����迭
	int* C = (int*)malloc((k+1)*sizeof(int));
	for (int i = 0; i <= k; i++)
		C[i] = 0;//ī��Ʈ �迭�� �ʱ�ȭ
	for (int j = 0; j <n; j++)
		C[A[j]] += 1;//ī��Ʈ����
	for (int i = 1; i <= k; i++)
		C[i] += C[i - 1];//������
	for (int j = n-1 ; j >=0; j--){
		B[C[A[j]]-1] = A[j];//�ڿ������� ���� �׾ư�
		C[A[j]] -= 1;
	}
	printing(B,n);//���
	free(C);
}

void printing(int* A, int n) {
	for (int i = 0; i < n; i++) 
			printf("%d ", A[i]);
}

int main() {
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\���϶�\\Desktop\\counting.txt", "r");
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
		printf("���� �б� ����");
	int* B = (int *)malloc(i*sizeof(int));
	CountingSort(arr,B,i,maxValue);
}
