#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define INF 1000000000

int* w;//weight input arr
int* b;//benefit input arr
int* index;//input������ index �迭
double* value;//������ ���� b/w

int W;//���� ũ��
double total = 0.0;//�� benefit

void ISwap(int* A, int x, int y) {//int�迭 ����
	int temp = A[x];
	A[x] = A[y];
	A[y] = temp;
}

void DSwap(double* A, int x, int y) {//double �迭 ����
	double temp = A[x];
	A[x] = A[y];
	A[y] = temp;
}

int Partition(double *A, int p, int r) {
	double x = A[r];//�Ǻ��� ��
	int i = p - 1;//������
	for (int j = p; j < r; j++) {//����迭�� ���鼭
		if (A[j] > x) {//�Ǻ����� ������
			i++;
			DSwap(A, i, j);//swap
			ISwap(b, i, j);
			ISwap(w, i, j);
			ISwap(index, i, j);
		}
	}
	DSwap(A, i + 1, r);//�Ǻ��� �Ǻ����� ������ �ڿ����´�
	ISwap(b, i + 1, r);
	ISwap(w, i + 1, r);
	ISwap(index, i + 1, r);
	return i + 1;//�Ǻ��� �ε��� ����
}

void Quicksort(double* A, int p, int r) {
	if (p < r) {
		int q = Partition(A, p, r);//�����Ǻ��� ���ϰ�
		Quicksort(A, p, q - 1);//��������� ȣ��
		Quicksort(A, q + 1, r);
	}
}

void Knapsack(int n) {
	Quicksort(value, 1, n);// b/w�� Quick ����
	int weight = W;
	for (int i = 1; i <= n; i++) {
		if (weight == 0)
			break;
		if (weight - w[i] >= 0) {//���� ���� ũ�⺸�� ������
			weight -= w[i];//�״�� �ִ´�
			total += b[i];//������ ��°�� ���Ѵ�
			cout << "���õ� item" << index[i] << "�� fraction�� " << w[i]<<endl;
		}
		else {//���� ���� ũ�⺸�� ũ��
			cout << "���õ� item" << index[i] << "�� fraction�� " <<((double)w[i]*(double)weight/(double)w[i])<<endl;
			total += ((double)b[i]*(double)weight / (double)w[i]);//�߶� �ִ´�
			weight = 0;//������ �������
		}
	}
}

int main(void) {
	FILE *file = NULL;
	fopen_s(&file, "C:\\Users\\���϶�\\Desktop\\knapsack_input_1.txt", "r");
	int i = 0;
	if (file != NULL) {
		while (!feof(file)) {
			w= (int*)realloc(w, sizeof(int)*(i + 2));//input �޴´�
			b= (int*)realloc(b, sizeof(int)*(i + 2));
			index = (int*)realloc(index, sizeof(int)*(i + 2));
			value= (double*)realloc(value, sizeof(double)*(i + 2));
			if (i == 0) {
				w[0] = 0;
				b[0] = 0;
				value[0] = 0;
			}
			fscanf(file,"%d", &w[i+1]);
			fscanf(file,"%d",&b[i+1]);
			index[i + 1] = i + 1;
			value[i + 1] = (double)b[i + 1] / (double)w[i + 1];
			i++;
		}
		W = 10;

		fclose(file);
	}
	else
		printf("���� �б� ����");
	
	cout << "Homework2_3\n" << endl;
	Knapsack(i);//knapsack problem fraction
	cout << "total benifit=> " << total;

	return 0;
}