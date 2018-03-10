
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define INF 1000000000

struct Ver {
	int i;//input에서의 index
	int s;//시작시간
	int f;//종료시간
	int v;//value
};

#define ver struct Ver

ver* act;//input Ver 노드 배열
int number = 0;//총개수

void insertionSort(ver* A, int start, int end) {//시작시간 기준 삽입정렬
	for (int i = start + 1; i < end; i++) {//정렬할 인덱스 다음인덱스부터 마지막 인덱스까지 돈다
		ver key= act[i];
		int j = i;
		for (j = i; j > start && A[j - 1].s > key.s; j--) {//작은거 찾으면
			act[j] = act[j - 1];
		}
		A[j] = key;//값 스왑
	}
}

void Iterative_Greedy_algorithm(int i) {
	int n = i;//총개수
	int k = n;
	printf("선택된 Activity의 input에서의 index=> %d\n", act[k].i);//출력
	number++;//숫자 ++
	for (int m = n; m>0; m--)//뒤에서부터 돌면서(시작시간이 느린것부터 돌면서)
		if (act[m].f<=act[k].s) {//종료시간이 시작시간보다 빠른걸 찾으면
			k = m;//고른다
			printf("선택된 Activity의 input에서의 index=> %d\n",act[k].i);
			number++;//개수++
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
			act[i + 1].i = i + 1;
			fscanf(file,"%d", &act[i+1].s);//input index 1부터 받는다
			fscanf(file, "%d",&act[i+1].f);
			fscanf(file, "%d",&act[i+1].v);
			i++;
		}
		act[i+1].s = INF;
		fclose(file);
	}
	else
		printf("파일 읽기 실패");

	insertionSort(act, 1, i + 1);//시작시간순 정렬
	cout << "Homework1_4\n" << endl;
	Iterative_Greedy_algorithm(i);//시작시간 기준 activity select 그리디 알고리즘
	cout << "총 개수: " << number;

	return 0;
}