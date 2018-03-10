#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define INF 1000000000

int* w;//weight input arr
int* b;//benefit input arr
int* index;//input에서의 index 배열
double* value;//정렬할 기준 b/w

int W;//가방 크기
double total = 0.0;//총 benefit

void ISwap(int* A, int x, int y) {//int배열 스왑
	int temp = A[x];
	A[x] = A[y];
	A[y] = temp;
}

void DSwap(double* A, int x, int y) {//double 배열 스왑
	double temp = A[x];
	A[x] = A[y];
	A[y] = temp;
}

int Partition(double *A, int p, int r) {
	double x = A[r];//피봇의 값
	int i = p - 1;//시작점
	for (int j = p; j < r; j++) {//서브배열을 돌면서
		if (A[j] > x) {//피봇보다 작으면
			i++;
			DSwap(A, i, j);//swap
			ISwap(b, i, j);
			ISwap(w, i, j);
			ISwap(index, i, j);
		}
	}
	DSwap(A, i + 1, r);//피봇을 피봇보다 작은거 뒤에놓는다
	ISwap(b, i + 1, r);
	ISwap(w, i + 1, r);
	ISwap(index, i + 1, r);
	return i + 1;//피봇의 인덱스 리턴
}

void Quicksort(double* A, int p, int r) {
	if (p < r) {
		int q = Partition(A, p, r);//랜덤피봇을 정하고
		Quicksort(A, p, q - 1);//재귀적으로 호출
		Quicksort(A, q + 1, r);
	}
}

void Knapsack(int n) {
	Quicksort(value, 1, n);// b/w로 Quick 정렬
	int weight = W;
	for (int i = 1; i <= n; i++) {
		if (weight == 0)
			break;
		if (weight - w[i] >= 0) {//남은 가방 크기보다 작으면
			weight -= w[i];//그대로 넣는다
			total += b[i];//이익을 통째로 더한다
			cout << "선택된 item" << index[i] << "의 fraction은 " << w[i]<<endl;
		}
		else {//남은 가방 크기보다 크면
			cout << "선택된 item" << index[i] << "의 fraction은 " <<((double)w[i]*(double)weight/(double)w[i])<<endl;
			total += ((double)b[i]*(double)weight / (double)w[i]);//잘라서 넣는다
			weight = 0;//가방이 비워졌다
		}
	}
}

int main(void) {
	FILE *file = NULL;
	fopen_s(&file, "C:\\Users\\신하람\\Desktop\\knapsack_input_1.txt", "r");
	int i = 0;
	if (file != NULL) {
		while (!feof(file)) {
			w= (int*)realloc(w, sizeof(int)*(i + 2));//input 받는다
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
		printf("파일 읽기 실패");
	
	cout << "Homework2_3\n" << endl;
	Knapsack(i);//knapsack problem fraction
	cout << "total benifit=> " << total;

	return 0;
}