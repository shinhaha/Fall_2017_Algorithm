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
	if (p == r)//�ε����� �ϳ���
		return A[p];
	int q = RandomizedPartition(A, p, r);//�������� �̰� ��Ƽ��
	int k = q - p + 1;//���° �����ΰ�
	if (i == k)//i��° ã������
		return A[q];//����
	if (i < k)//�ƴϸ� divide and conquer
		return RandomizedSelect(A, p, q - 1, i);
	else
		return RandomizedSelect(A, q + 1, r, i - k);
}

int RandomizedPartition(int*A, int p, int r) {
	int i = rand() % (r - p + 1) + p;//p�� r������ �������� ���ϰ�
	Swap(A, r, i);//�ǿ����� ���� �ٲ��ش�
	return Partition(A, p, r);//�� �� ������ partition ����
}

int Partition(int*A, int p, int r) {
	int x = A[r];//�Ǻ��� ��
	int i = p - 1;//������
	for (int j = p; j < r; j++) {//����迭�� ���鼭
		if (A[j] <= x) {//�Ǻ����� ������
			i++;
			Swap(A, i, j);//swap
		}
	}
	Swap(A, i + 1, r);//�Ǻ��� �Ǻ����� ������ �ڿ����´�
	return i + 1;//�Ǻ��� �ε��� ����
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
void insertionSort(int* A, int start, int end) {//��������
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
	fopen_s(&f, "C:\\Users\\���϶�\\Desktop\\input500.txt", "r");
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
		printf("���� �б� ����");
	srand((unsigned)time(NULL));

	cout<<RandomizedSelect(arr, 0, i - 1,10)<<endl;	
	printing(arr, i);
}