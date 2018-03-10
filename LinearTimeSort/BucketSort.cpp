#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define PI vector<float>
float* arr;
void printing(PI A);
PI insertionSort(PI A);

PI insertionSort(PI A) {
	for (int i = 1; i <A.size(); i++) {
		float key = A[i];
		int j = i - 1;
		for (j = i; j >0 && A[j - 1] > key; j--)
			A[j] = A[j - 1];
		A[j] = key;
	}
	return A;
}

void printing(PI A) {
	for (int i = 0; i < A.size(); i++)
		cout << A[i] << " ";
}

void BucketSort(float* A, int n) {
	PI* v = new PI[n];//���� ������ŭ ���͸����
	for (int i = 0; i < n; i++) {
		int temp = floor(n*A[i]);//����
		v[temp].push_back(A[i]);//���Ϳ� �ִ´�
	}
	for (int i = 0; i < n; i++)
		if (v[i].size() != 0)//0�̸� ��Ʈ����
		v[i]=insertionSort(v[i]);//�� ���͸� ��������
	for (int i = 0; i < n; i++)
		if (v[i].size() != 0)
		printing(v[i]);//���
}

int main() {
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\���϶�\\Desktop\\bucket.txt", "r");
	int i = 0;
	if (f != NULL) {
		while (!feof(f)) {
			arr = (float*)realloc(arr, sizeof(float)*(i + 1));
			fscanf(f, "%f", (arr + i));
			i++;
		}
		fclose(f);
	}
	else
		printf("���� �б� ����");
	BucketSort(arr, i);
}