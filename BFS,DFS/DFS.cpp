#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;

#define WHITE 0//not discoverd
#define GRAY 1//are discovered but not fully explored
#define BLACK 2//are discovered and fully explored

struct Node {
int color=WHITE;//color
int d;//time when first discovered
int f;//time when u is finished
struct Node* PI=NULL;//parent
};

#define node struct Node

void DFSVisit(int** A, int size, node* vertex, int index,int time);
void DFS(int** A, int size);
int time;

void DFS(int** A,int size){
node* vertex = (node*)malloc(size*sizeof(node));
for (int i = 0; i < size; i++) {//node sturct 배열을 초기화 합니다
	vertex[i].color = WHITE;
	vertex[i].d = 0;
	vertex[i].f = 0;
	vertex[i].PI = NULL;
}
cout << "DFS" << endl;
for (int i = 0; i < size; i++) {
	time = 0;//처음시간은 0
if (vertex[i].color == WHITE)//아직 미방문 정점이라면 
DFSVisit(A, size, vertex,i,time);//방문 합니다
}
}

void DFSVisit(int** A, int size, node* vertex,int index,int hamsutime) {
cout <<"방문 정점=>"<<index << endl;
time++;
vertex[index].d = hamsutime;//시간을 셋해주고
vertex[index].color = GRAY;//방문했다고 마크합니다
for(int i=0; i<size; i++)
if (A[index][i] != 0) {//인접하고
if (vertex[i].color == WHITE) {//방문하지 않은 정점에대하여
vertex[i].PI =&vertex[index];//prev로 마크하고
DFSVisit(A, size, vertex, i,hamsutime+1);//미방문 정점을 방문합니다.
	}
}
vertex[index].color = BLACK;//이 함수를 호출한 정점에 대하여 모든경로를 다 돌았다고 마크
time++;
vertex[index].f =time;
}

int main() {
FILE *f = NULL;
fopen_s(&f, "C:\\Users\\신하람\\Desktop\\graph.txt", "r");
int i = 0;
int** arr;
int size;//정점의 개수
if (f != NULL) {
while (!feof(f)) {
if (i == 0) {
fscanf(f, "%d", &size);
arr= (int**)malloc(sizeof(int*)*(size));//연결 정보 저장할 2차원 배열
for (int i = 0; i < size; i++)
(arr[i]) = (int*)malloc(sizeof(int)*size);
i++;
}
else{
int value;
for(int x=0; x<size; x++)
for(int y=0; y<size; y++){
fscanf(f, "%d", &value);//배열에 연결정보를 저장합니다.
arr[x][y] = value;
}
}
}
fclose(f);
}
else
printf("파일 읽기 실패");
DFS(arr, size);//DFS함수 실행합니다
}
