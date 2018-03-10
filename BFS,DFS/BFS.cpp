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
for (int i = 0; i < size; i++) {//node struct �迭�� �ʱ�ȭ �մϴ�.
	vertex[i].vertice = i;
	vertex[i].color = WHITE;
	vertex[i].d = 0;
	vertex[i].PI = NULL;
}
vertex[s].color = GRAY;//ó�� �湮 ������ �ε��� s�϶� s�� �湮�ߴٰ� ��ũ
vertex[s].d = 0;
vertex[s].PI = NULL;
queue<node> q;
q.push(vertex[s]);//���� ������ ť�� �ִ´�
cout << "BFS" << endl;
while (!q.empty()) {
	node u = q.front();//ť���� ���� ����
	q.pop();
	cout <<"�湮 ����=>"<< u.vertice<<endl;
	for(int i=0; i<size; i++)
		if(A[i][u.vertice]!=0)//�����ϰ�
			if (vertex[i].color == WHITE){//�湮���� ���� ������ �ִٸ�
				vertex[i].color = GRAY;//�湮�ߴٰ� ��ũ�ϰ�
				vertex[i].d = u.d + 1;//�湮 �ð��� �� �� ���� +1
				vertex[i].PI = &u;//prev�� �ִ´�
				q.push(vertex[i]);//ť�� �ִ´�
			}
	u.color = BLACK;//pop�� ������ ���Ͽ� ����θ� Ž���ߴٰ� ��ũ�Ѵ�.
	}
}

int main() {
FILE *f = NULL;
fopen_s(&f, "C:\\Users\\���϶�\\Desktop\\graph.txt", "r");
int i = 0;
int** arr;//���� ���� ������ ������ �迭
int size;//������ ����
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
for(int y=0; y<size; y++){//�迭�� ���������� �ִ´�
fscanf(f, "%d", &value);
arr[x][y] = value;
}
}
}
fclose(f);
}
else
printf("���� �б� ����");
BFS(arr, size,0);//BFS����
}
