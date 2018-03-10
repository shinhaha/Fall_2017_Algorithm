
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define INF 1000000000

struct Ver {
	int i;//input에서의 인덱스
	int s;//시작시간
	int f;//종료시간
	int v;//value
};

#define ver struct Ver

ver* act;//Ver node배열
int number = 0;//개수

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

void Iterative_Greedy_algorithm(int i) {
	int n = i;
	int k = 1;
	number++;
	printf("선택된 Activity의 input에서의 index=> %d\n", act[k].i);
	for (int m = 1; m <= n; m++)//앞에서부터 돌면서(종료시간 빠른거부터 돌면서)
		if (act[m].s >= act[k].f) {//시작시간이 종료시간보다 느린걸 찾으면
			number++;//개수 ++
			k = m;//고른다
			printf("선택된 Activity의 input에서의 index=> %d\n",act[k].i);
		}
}

int main(void) {
	FILE *file = NULL;
	fopen_s(&file, "C:\\Users\\신하람\\Desktop\\activity_input.txt", "r");
	int size;//막대길이
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
			act[i + 1].i = i + 1;//input에서의 index저장
			fscanf(file, "%d", &act[i + 1].s);//input받음
			fscanf(file, "%d", &act[i + 1].f);
			fscanf(file, "%d", &act[i + 1].v);
			i++;
		}
		act[i + 1].s = INF;
		fclose(file);
	}
	else
		printf("파일 읽기 실패");
	insertionSort(act, 1, i + 1);//종료시간 기준 정렬
	cout << "Homework1_3\n" << endl;
	Iterative_Greedy_algorithm(i);//Activity selection
	cout << "총 개수: " << number;

	return 0;
}