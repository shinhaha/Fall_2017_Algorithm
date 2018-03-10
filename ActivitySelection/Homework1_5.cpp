#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <cstdbool>
using namespace std;
#define INF 1000000000

struct Ver {
	int i;//input에서의 인덱스
	int s;//시작시간
	int f;//종료시간
	int v;//value
	bool visit;//방문 여부
};

#define ver struct Ver

ver* act;//Ver node 배열
int number = 0;//총개수

void Iterative_Greedy_algorithm(int i) {
	
	int n = i;//총 개수
	int minf = INF;//고를수 있는 가장작은 f
	int minfIndex = -1;//고를수 있는 가장작은 f의 인덱스

	for (int x = 1; x <= n; x++) {
		if (minf >= act[x].f && !act[x].visit) {//방문안한거고 가장작은거면
			minf = act[x].f;//값이랑 인덱스 업데이트
			minfIndex = act[x].i;
		}
	}

	act[minfIndex].visit = true;//방문했다고 마크하고
	printf("선택된 Activity의 input에서의 index = > %d\n", minfIndex);//출력
	number++;//숫자 더함

	while (true) {
		int thanminfs = INF + 1;//초기화
		int thanminff = INF + 1;
		int thanminfsIndex = -1;

		for (int x = 1; x <= n; x++) {//원소개수만큼 돌면서
			if (thanminfs >=act[x].s&&thanminff>=act[x].f &&!act[x].visit&&act[x].s >=minf) {//작은거고 방문안한거고 가장작은 종료 시점보다 크거나같고 thanminfs를 인덱스로 갖는 act배열의 f가 더 작으면
				thanminfs = act[x].s;//업데이트
				thanminff = act[x].f;
				thanminfsIndex = x;//k를 m으로 하는 인덱스를 찾는다와 같다.
			}
		}

		if (thanminfsIndex == -1)//종료조건=>업데이트 안됐을때
			break;

		minf = act[thanminfsIndex].f;//가장작은것으로 업데이트한다
		act[thanminfsIndex].visit = true;//방문했다고 마크한다

		printf("선택된 Activity의 input에서의 index = > %d\n",thanminfsIndex);//출력
		number++;//개수 ++
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
				act[0].visit = false;
			}
			act[i + 1].i = i + 1;//input에서의 index를 기억
			act[i + 1].visit = false;//방문안함
			fscanf(file,"%d", &act[i+1].s);//input 받는다
			fscanf(file, "%d",&act[i+1].f);
			fscanf(file, "%d",&act[i+1].v);
			i++;
		}
		act[i+1].s = INF;
		fclose(file);
	}
	else
		printf("파일 읽기 실패");
	cout << "Homework1_5\n" << endl;
	Iterative_Greedy_algorithm(i);//정렬안된 activity select 그리디 알고리즘
	cout << "총 개수: " << number;
	
	return 0;
}