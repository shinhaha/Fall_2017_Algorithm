#include <stdio.h>
#include <stdlib.h>

struct Vertex {//정점 Struct
int key;//value
int PA;//parent
};

struct Edge {
	int u;//시작정점
	int v;//도착정점
	int w;//가중치
};

#define edge struct Edge
#define Ver struct Vertex
#define INF 2000000000//무한대

Ver* vertices;//정점배열
edge* arr;//간선배열

int Edgesize = 0;//간선개수
int Versize = 0;//정점개수
int BellmanFordAlgorithm(edge* graph);//벨만포드 함수
void Print();//출력하는 함수
void PrintPath(int index);//재귀적으로 출력하는 함수
void Relax(int u, int v,int w);//shortest path를 찾고 업데이트 하는 함수


int BellmanFordAlgorithm(edge* graph) {
	for (int i = 0; i < Versize; i++) {//초기화
		vertices[i].key = INF;
		vertices[i].PA = NULL;
	}
	vertices[0].key = 0;//Initialize Single Source

	for (int i = 0; i < Versize - 1; i++) //정점개수-1
		for (int j = 0; j <Edgesize; j++) //각 간선에대하여
			Relax(arr[j].u,arr[j].v,arr[j].w);//업데이트

	for (int j = 0; j < Edgesize; j++)//음의 사이클 있는지 확인
		if (vertices[arr[j].v].key > vertices[arr[j].u].key + arr[j].w)
			return 0;
	return 1;
}

void Relax(int u, int v,int w) {//shortest path를 업데이트 하는 함수다. 부모도 업데이트한다.
	if (vertices[v].key > vertices[u].key +w ) {//더 짧은 거리를 찾으면
		vertices[v].key = vertices[u].key + w;//업데이트
		vertices[v].PA = u;
	}
}

void Print() {//출력하는 함수다.
	for (int i = 0; i < Versize; i++) {//모든 정점에대해
		printf("%d=>Path: 0 ", i);
		PrintPath(i);
		printf(" Cost:%d\n",vertices[i].key);
	}
}

void PrintPath(int index) {//재귀적으로 PA가 NULL일때까지 출력하는 함수다.
	if (vertices[index].PA != NULL) //널일때까지 출력
		PrintPath(vertices[index].PA);
	if(index!=0)
		printf("%d ", index);

}

int main(void) {
FILE *f = NULL;
fopen_s(&f, "C:\\Users\\신하람\\Desktop\\graph_sample_bellman.txt", "r");
if (f != NULL) {
while (!feof(f)) {
	if (Edgesize == 0) {
		fscanf(f, "%d", &Versize);
		vertices = (Ver*)malloc(sizeof(Ver)*(Versize + 1));//정점배열
		arr = (edge*)malloc((Edgesize+1)*sizeof(edge));//간선배열
	}
	fscanf(f, "%d", &arr[Edgesize].u);//간선배열에 넣어줍니다
	fscanf(f, "%d", &arr[Edgesize].v);
	fscanf(f, "%d", &arr[Edgesize].w);
	Edgesize++;//엣지의 개수
				}
	fclose(f);
}
	else
		printf("파일 읽기 실패");
printf("벨만포드 알고리즘\n");
if (BellmanFordAlgorithm(arr))//벨만포드 알고리즘 실행
Print();//음의사이클 안 가지면 출력
else
printf("음의 사이클 가집니다\n");//음의 사이클 가지면
	return 0;
}