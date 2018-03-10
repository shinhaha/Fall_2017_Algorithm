#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
using namespace std;

#define INF 2000000000

int Edgesize = 0;//간선개수
int Versize = 0;//정점개수
int** arr;
int** ExtendShortestPaths(int** A,int** B);
int** newArr();
void SlowAllPairsShortestPaths();
void print(int** A,int i);

void SlowAllPairsShortestPaths() {
	printf("SlowAllPairsShortestPaths\n");
	int** first = newArr();//n*n배열 생성 L1
	for (int i = 0; i < Versize; i++)
		for (int j = 0; j < Versize; j++)
			first[i][j] = arr[i][j];//first배열에 복사
	print(first,0);//L0출력
	for (int i = 1; i <Versize-1; i++) {
		first = ExtendShortestPaths(first,arr);//first배열을 arr에 대해 더 짧은경로 업데이트한 것을 first에 넣어줌
		print(first,i);//first출력 Li
	}
}

void FasterAllPairsShortestPaths() {
	printf("FasterAllPairsShortestPaths\n");
	int** first = newArr();//n*n배열 생성 L1
	for (int i = 0; i < Versize; i++)
		for (int j = 0; j < Versize; j++)
			first[i][j] = arr[i][j];//frst에 배열에 복사
	int m = 1;
	print(first,0);//L0 출력
	while (m <Versize-1) {//다이나믹 프로그램을 이용하여
		first= ExtendShortestPaths(first,first);//first배열에 대하여 fisrt배열로 업데이트 한것을 first에 넣어준다
		print(first,m);//Lm을 출력한다
		m *= 2;//m을 2배로 해준다
	}
}

int** ExtendShortestPaths(int** A,int** B) {//B배열에 대하여 A배열을 더 짧은 경로로 업데이트하는 함수다
	int** newArrays = newArr();
	for (int i = 0; i < Versize; i++)
		for (int j = 0; j < Versize; j++) {
			newArrays[i][j] = INF;//가장 큰 값으로 초기화
			for (int k = 0; k < Versize; k++)
				if(B[k][j]!=INF&&A[i][k]!=INF)//오버플로우 방지
				newArrays[i][j] = min(newArrays[i][j], A[i][k] + B[k][j]);
		}
	return newArrays;
}

int** newArr() {//n*n배열 생성
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
			if (A[i][j] == INF)//무한대면 경로가 없다
				printf("    X");
			else
				printf("%5d", A[i][j]);
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
			int q, w, e;//시작정점,도착정점,cost
			fscanf(f, "%d", &q);
			fscanf(f, "%d", &w);
			fscanf(f, "%d", &e);
			arr[q][w] = e;
			Edgesize++;//간선개수 ++
		}
		fclose(f);
	}
	else
		printf("파일 읽기 실패");

	SlowAllPairsShortestPaths();//Slow
	FasterAllPairsShortestPaths();//Faster
}
