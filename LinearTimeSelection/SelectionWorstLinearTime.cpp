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

int Select(int *A, int p, int r, int i) {//i��° �� ã�� �Լ�
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
	int k = ceil((double)r / 5.0);//�׷� �
	int* temp = (int*)malloc(k * sizeof(int));//�߰��� ������ �迭
	for (int i = 0; i < k; i++) {
		int end= 5*(i + 1)>=r?r:5*(i + 1);
		insertionSort(A, 5*i,end);//5���׷� ��������
	    temp[i]=Select(A, 5*i,end-1,((5*i+end)/2)-5*i+1);//5�������� �߰���
	}
	int median=Select(temp,0, k-1,k/2);//�߰����� �߰��� ����
	cout << "�߰�����:" << median<<endl<<"�ε�����:";
	return MedianPartition(A,p,r,median);//�� �߰����� pivot����
	}

	int MedianPartition(int*A, int p, int r,int median) {
	int x = median;//�Ǻ��� ��
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

void printing(int* A, int start,int n) {
	for (int i = start; i < n; i++) {
			printf("%d ", A[i]);
	}
}

void insertionSort(int* A, int start, int end) {//��������
for (int i = start + 1; i < end; i++) {//������ �ε��� �����ε������� ������ �ε������� ����
	int key = A[i];//key�� i�ε����� ���ϰ�
	int j = i - 1;
	for (j = i; j > start && A[j - 1] > key; j--)//������ ã����
		A[j] = A[j - 1];//�����
		A[j] = key;//�� ����
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
	cout<<hamsu(arr, 0,i)<<endl;
}
