#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

#define WHITE 0//not discoverd
#define GRAY 1//are discovered but not fully explored
#define BLACK 2//are discovered and fully explored

struct Node {
int color=WHITE;//color
int vertice;
int d;//time when first discovered
struct Node* PI;//parent
};

#define node struct Node

void BFS(int** A, int size,int s);
int time;

void BFS(int** A,int size,int s){
node* vertex = (node*)malloc(size*sizeof(node));
for (int i = 0; i < size; i++) {//node struct 배열을 초기화 합니다.
	vertex[i].vertice = i;
	vertex[i].color = WHITE;
	vertex[i].d = 0;
	vertex[i].PI = NULL;
}
vertex[s].color = GRAY;//처음 방문 정점의 인덱스 s일때 s를 방문했다고 마크
vertex[s].d = 0;
vertex[s].PI = NULL;
queue<node> q;
q.push(vertex[s]);//시작 정점을 큐에 넣는다
cout << "BFS" << endl;
while (!q.empty()) {
	node u = q.front();//큐에서 나온 정점
	q.pop();
	cout <<"방문 정점=>"<< u.vertice<<endl;
	for(int i=0; i<size; i++)
		if(A[i][u.vertice]!=0)//인접하고
			if (vertex[i].color == WHITE){//방문하지 않은 정점이 있다면
				vertex[i].color = GRAY;//방문했다고 마크하고
				vertex[i].d = u.d + 1;//방문 시간은 그 전 정점 +1
				vertex[i].PI = &u;//prev로 넣는다
				q.push(vertex[i]);//큐에 넣는다
			}
	u.color = BLACK;//pop된 정점에 대하여 모든경로를 탐색했다고 마크한다.
	}
}

int main() {
FILE *f = NULL;
fopen_s(&f, "C:\\Users\\신하람\\Desktop\\graph.txt", "r");
int i = 0;
int** arr;//연결 정보 저장할 이차원 배열
int size;//정점의 개수
if (f != NULL) {
while (!feof(f)) {
if (i == 0) {
fscanf(f, "%d", &size);
arr= (int**)malloc(sizeof(int*)*(size));
for (int i = 0; i < size; i++)
(arr[i]) = (int*)malloc(sizeof(int)*size);
i++;
}
else{
int value;
for(int x=0; x<size; x++)
for(int y=0; y<size; y++){//배열에 연결정보를 넣는다
fscanf(f, "%d", &value);
arr[x][y] = value;
}
}
}
fclose(f);
}
else
printf("파일 읽기 실패");
BFS(arr, size,0);//BFS실행
}
