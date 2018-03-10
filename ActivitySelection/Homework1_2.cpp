
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define INF 1000000000

int** c;
int** rem;

struct Ver {
	int i;
	int s;
	int f;
	int v;
};

#define ver struct Ver

ver* act;
int total = 0;//총 value

void DynamicSelection(int n) {
	for (int l = 2; l <= n + 1; l++)//bottom up을 위한 chain length
		for (int i = 0; i <= n - l + 1; i++) {//렝스를 고려한 i범위
			int j = i + l;//length만큼 본다
			c[i][j] = 0;//초기화
			int k = j - 1;//k의 범위는 i<k<j
			while (i < k) {
				//i의 종료시간이 k보다 작거나 같고 j의 시작시간이 k의 종료시간보다 크거나 같으며
				//더 큰 값을 찾았다면
				if (act[i].f <= act[k].s&&act[k].f <= act[j].s&&c[i][k] + c[k][j] + act[k].v > c[i][j]) {
					c[i][j] = c[i][k] + c[k][j] + act[k].v;//값 업데이트
					rem[i][j] = k;//어떻게 잘랐나 기억
				}
				k--;
			}
		}
}

void PrintActivities(int i, int j) {
	if (c[i][j] > 0) {
		int k = rem[i][j];//i,j를 어떻게 어떻게 잘랐나 k
		total+=act[k].v;
		cout <<"선택된 Activity의 input에서의 index는=> "<<act[k].i<<endl;//원래 input에서의 인덱스를 출력
		PrintActivities(i, k);//k 왼쪽부분 어떻게 잘랐나
		PrintActivities(k, j);//k 오른쪽 부분 어떻게 잘랐나
	}
}

void insertionSort(ver* A, int start, int end) {//종료시간 기준 삽입정렬
	for (int i = start + 1; i < end; i++) {//정렬할 인덱스 다음인덱스부터 마지막 인덱스까지 돈다
		ver key = act[i];
		int j = i;
		for (j = i; j > start && A[j - 1].f > key.f; j--) {//작은거 찾으면
			act[j] = act[j - 1];
		}
		A[j] = key;//값 스왑
	}
}

int main(void) {
	FILE *file = NULL;
	fopen_s(&file, "C:\\Users\\신하람\\Desktop\\activity_input.txt", "r");
	int i = 0;
	if (file != NULL) {
		while (!feof(file)) {
			act = (ver*)realloc(act, sizeof(ver)*(i + 2));
			if (i == 0) {
				act[0].i = 0;
				act[0].s = 0;
				act[0].f = 0;
				act[0].v = 0;
			}
			act[i + 1].i = i + 1;//input에서의 인덱스 기억
			fscanf(file, "%d", &act[i + 1].s);//input을 1부터 받는다.
			fscanf(file, "%d", &act[i + 1].f);
			fscanf(file, "%d", &act[i + 1].v);
			i++;
		}
		act[i + 1].s = INF;

		c = (int**)calloc(i + 2, sizeof(int*));//0으로 초기화된 dp 2차원배열 생성
		for (int k = 0; k <i + 2; k++)
			c[k] = (int*)calloc(i + 2, sizeof(int));

		rem = (int**)calloc(i + 2, sizeof(int*));//0으로 초기화된 rem 기억 2차원배열 생성
		for (int k = 0; k<i + 2; k++)
			rem[k] = (int*)calloc(i + 2, sizeof(int));

		fclose(file);
	}
	else
		printf("파일 읽기 실패");

	insertionSort(act, 1, i + 1);//종료시간순 정렬
	cout << "Homework1_2\n" << endl;
	DynamicSelection(i);//max value dp
	PrintActivities(0, i + 1);//출력
	cout << "Sum of values of selected activities: " << total;
	return 0;
}