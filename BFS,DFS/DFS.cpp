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
for (int i = 0; i < size; i++) {//node sturct �迭�� �ʱ�ȭ �մϴ�
	vertex[i].color = WHITE;
	vertex[i].d = 0;
	vertex[i].f = 0;
	vertex[i].PI = NULL;
}
cout << "DFS" << endl;
for (int i = 0; i < size; i++) {
	time = 0;//ó���ð��� 0
if (vertex[i].color == WHITE)//���� �̹湮 �����̶�� 
DFSVisit(A, size, vertex,i,time);//�湮 �մϴ�
}
}

void DFSVisit(int** A, int size, node* vertex,int index,int hamsutime) {
cout <<"�湮 ����=>"<<index << endl;
time++;
vertex[index].d = hamsutime;//�ð��� �����ְ�
vertex[index].color = GRAY;//�湮�ߴٰ� ��ũ�մϴ�
for(int i=0; i<size; i++)
if (A[index][i] != 0) {//�����ϰ�
if (vertex[i].color == WHITE) {//�湮���� ���� ���������Ͽ�
vertex[i].PI =&vertex[index];//prev�� ��ũ�ϰ�
DFSVisit(A, size, vertex, i,hamsutime+1);//�̹湮 ������ �湮�մϴ�.
	}
}
vertex[index].color = BLACK;//�� �Լ��� ȣ���� ������ ���Ͽ� ����θ� �� ���Ҵٰ� ��ũ
time++;
vertex[index].f =time;
}

int main() {
FILE *f = NULL;
fopen_s(&f, "C:\\Users\\���϶�\\Desktop\\graph.txt", "r");
int i = 0;
int** arr;
int size;//������ ����
if (f != NULL) {
while (!feof(f)) {
if (i == 0) {
fscanf(f, "%d", &size);
arr= (int**)malloc(sizeof(int*)*(size));//���� ���� ������ 2���� �迭
for (int i = 0; i < size; i++)
(arr[i]) = (int*)malloc(sizeof(int)*size);
i++;
}
else{
int value;
for(int x=0; x<size; x++)
for(int y=0; y<size; y++){
fscanf(f, "%d", &value);//�迭�� ���������� �����մϴ�.
arr[x][y] = value;
}
}
}
fclose(f);
}
else
printf("���� �б� ����");
DFS(arr, size);//DFS�Լ� �����մϴ�
}
