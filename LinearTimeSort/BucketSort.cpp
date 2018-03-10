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
	PI* v = new PI[n];//원소 개수만큼 벡터만든다
	for (int i = 0; i < n; i++) {
		int temp = floor(n*A[i]);//내림
		v[temp].push_back(A[i]);//벡터에 넣는다
	}
	for (int i = 0; i < n; i++)
		if (v[i].size() != 0)//0이면 소트안함
		v[i]=insertionSort(v[i]);//각 벡터를 삽입정렬
	for (int i = 0; i < n; i++)
		if (v[i].size() != 0)
		printing(v[i]);//출력
}

int main() {
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\신하람\\Desktop\\bucket.txt", "r");
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
		printf("파일 읽기 실패");
	BucketSort(arr, i);
}