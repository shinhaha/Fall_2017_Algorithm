#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
using namespace std;

#define INF 2000000000//무한대

int Edgesize = 0;//간선개수
int Versize = 0;//정점개수
int** arr;//가중치 배열
void FloydWarshall();
void print(int** A,int i);
int** newArr();

void FloydWarshall() {
	printf("FloydWarshall\n");
	int** first = newArr();//D0생성
		for (int i = 0; i < Versize; i++)
			for (int j = 0; j < Versize; j++)
				first[i][j] = arr[i][j];//가중치 배열을 복사해서 D0을 만듬
		print(first,0);//D0출력
		for (int k = 0; k < Versize; k++) {
			int** newArrays = newArr();//n*n newArray 생성
			for (int i = 0; i < Versize; i++) {
				for (int j = 0; j < Versize; j++) {
					if (first[i][k] != INF&&first[k][j] != INF)//오버플로우 방지
						newArrays[i][j] = min(first[i][j], first[i][k] + first[k][j]);//i-j경로보다 i-k-j경로가 더 작은가
					else
						newArrays[i][j] = first[i][j];//그전 D(i-1)값을 복사
				}
			}	
			first = newArrays;//first에 복사
			print(first,k+1);//Di출력
		}
}

int** newArr() {//n*n 배열 생성
	int** arrtemp = (int**)malloc(sizeof(int*)*Versize);
	for (int q = 0; q < Versize; q++)
		arrtemp[q] = (int*)malloc(sizeof(int)*Versize);
	return arrtemp;
}

void print(int** A,int i) {//출력하는 함수
	printf("(%d)\n", i);
	for (int i = 0; i < Versize; i++) {
		printf("\n");
		for (int j = 0; j < Versize; j++)
			if (A[i][j] == INF)//무한대면 없다고 X출력
				printf("    X");
			else
				printf("%5d", A[i][j]);//무한대가 아니라면 가중치 출력
	}
	printf("\n");
}

int main(void) {
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\신하람\\Desktop\\graph_sample_directed.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			if (Edgesize == 0) {
				fscanf(f, "%d", &Versize);
				arr = (int**)malloc(sizeof(int*)*Versize);
				for (int i = 0; i < Versize; i++)
					arr[i] = (int*)malloc(sizeof(int)*Versize);
				for (int i = 0; i < Versize; i++)
					for (int j = 0; j < Versize; j++)
						if (i == j)
							arr[i][j] = 0;
						else
							arr[i][j] = INF;
			}
			int q, w, e;//시작 정점,도착 정점,cost
			fscanf(f, "%d", &q);
			fscanf(f, "%d", &w);
			fscanf(f, "%d", &e);
			arr[q][w] = e;
			Edgesize++;//간선개수++
		}
		fclose(f);
	}
	else
		printf("파일 읽기 실패");
	FloydWarshall();//플로이드 워셜 알고리즘 실행
}