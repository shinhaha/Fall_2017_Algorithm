#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

struct Vertex {//���� Struct
	int now;//�ڽ��� ���� �����ΰ�,�ε��� �� �����ΰ�
	int key;//value
	int PA;//parent
};

struct Edge {//���� Struct
	int u;//��������
	int v;//��������
	int w;//����ġ
};

#define Ver struct Vertex
#define edge struct Edge
#define PI vector<edge>
#define INF 2000000000//���Ѵ�

Ver* vertices;//�����迭
PI* Vectors;//edge������ ���� vector
int* index;//�ε��� ������ �迭

int StartVertex = -1;//�Է¹��� ��� ����
int Edgesize = 0;//��������
int Versize = 0;//��������
int Heapsize = 0;//��������

void Print();//����ϴ� �Լ���
void PrintPath(int index);//��������� PA�� NULL�϶����� ����Ѵ�
void DijkstraAlgorithm(PI* Vecarr, int startVertex);//���̽�Ʈ�� �Լ���
Ver* BuildMinHeap();
Ver* Vswap(Ver* input, int i, int j);//vertices Swap�Լ���
int* IndexUpdate(int*A, int x, int y);//Vswap�Ҷ� index�迭�� �����ϴ� �Լ���
Ver* MinHeapify(Ver* A, int i, int heapsize);
Ver extractMinHeap(Ver* A);
void Relax(int u, int v, int w);//shortest path�� ������Ʈ�ϴ� �Լ���

void DijkstraAlgorithm(PI* Vecarr,int startVertex) {
	for (int i = 1; i <= Versize; i++) {//������� �ʱ�ȭ���ش�.
		vertices[i].now = i - 1;//�ڽ��� ���������ΰ�
		vertices[i].key = INF;
		vertices[i].PA = NULL;
	}
	vertices[startVertex + 1].key = 0;//���� ���� +1���� �����ؾ��� heap�� 1���ͽ����̹Ƿ�
	vertices=Vswap(vertices, 1, startVertex + 1);//���������� key�� 0�̵Ǿ��� ������ �� ���Ѵ��̹Ƿ� �׳ɽ���
	index=IndexUpdate(index, 1, startVertex + 1);//�ε���������Ʈ
	while (Heapsize != 0) {//ť�� �ƹ��͵� ����������
		Ver u = extractMinHeap(vertices);//���� ���� ����ġ�� ������ �̴´�
		for (int i = 0; i < Vectors[u.now].size(); i++) {//���� ������ ����Ǿ��ִ� ���� ����Ʈ�� ���鼭 Relax�Ѵ�
			edge temp = Vectors[u.now].at(i);
			Relax(temp.u, temp.v, temp.w);//������Ʈ
		}
	}
}

void Relax(int u, int v, int w) {//shortest path�� ������Ʈ �ϴ� �Լ���. �θ� ������Ʈ�Ѵ�.
	if (vertices[index[v]].key > vertices[index[u]].key+w) {
		vertices[index[v]].key = vertices[index[u]].key+w;
		vertices[index[v]].PA = u;
	}
	vertices=MinHeapify(vertices, 1,Heapsize);//���� ������Ʈ �ɶ����� hapify�� ���ش�.
}

void Print() {//����ϴ� �Լ���.
	for (int i = 0; i <Versize; i++) {
		printf("%d=>Path: %d ", vertices[index[i]].now,StartVertex);
		PrintPath(vertices[index[i]].now);
		printf(" Cost:%d\n", vertices[index[i]].key);
	}
}

void PrintPath(int i){//��������� PA�� NULL�϶����� ����ϴ� �Լ���.
	if (vertices[index[i]].PA != NULL)
		PrintPath(vertices[index[i]].PA);
	if(vertices[index[i]].now!=StartVertex)
		printf("%d ", vertices[index[i]].now);
}

Ver* BuildMinHeap() {//������Ʈ�� ������ �� �� �����Ƿ� BuildMinHeap�� ���ش�.
	for (int i = floor(Heapsize / 2); i >= 1; i--)
		vertices = MinHeapify(vertices, i, Heapsize);
	return vertices;
}

Ver* MinHeapify(Ver* A, int i, int heapsize) {//���������� �������� ���ش�
	int l = 2 * i;
	int r = 2 * i + 1;
	int smallest;
	if (l <= heapsize&&A[l].key < A[i].key)//�����ڽİ� ��
		smallest = l;
	else
		smallest = i;
	if (r <= heapsize&&A[r].key<A[smallest].key)//������ �ڽİ� ��
		smallest = r;
	if (smallest != i) {//���� ������ �ڽİ� �ٲ��ְ� ��������� ����
		vertices = Vswap(vertices, i, smallest);
		index = IndexUpdate(index, i, smallest);
		vertices = MinHeapify(vertices, smallest, heapsize);
	}
	return vertices;
}

Ver* Vswap(Ver* input, int i, int j) {//�ΰ��� ������ ���ڵ��� �������ش�
	Ver *tmp = (Ver *)malloc(sizeof(Ver));//�ӽ� �Ҵ�
	tmp->key = (input + i)->key;
	tmp->now = (input + i)->now;
	tmp->PA = (input + i)->PA;
	(input + i)->key = (input + j)->key;
	(input + i)->now = (input + j)->now;
	(input + i)->PA = (input + j)->PA;
	(input + j)->key = tmp->key;
	(input + j)->now = tmp->now;
	(input + j)->PA = tmp->PA;
	free(tmp);//free
	return input;
}

int* IndexUpdate(int*A, int x, int y) {//������ �� ������Ʈ
	A[vertices[x].now] = x;//vertices[x]�� �����ε��� x.now�� ���� index[x.now]�� x�̴�. 
	A[vertices[y].now] = y;
	return A;
}

Ver extractMinHeap(Ver* A) {//������������ �̴´�
	int i = Heapsize;//i�� ��������
	Ver temp = A[1];//������ ���� ���� �� ����
	vertices = Vswap(A, 1, i);//Vertices �迭�� �����Ѵ� 
	index = IndexUpdate(index, 1, i);//index���� ������Ʈ ���ش�
	Heapsize--;//�������� ���δ�
	return temp;//���� ������ ����
}

int main(void) {
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\���϶�\\Desktop\\graph_sample_dijkstra.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			if (Edgesize == 0) {
				fscanf(f, "%d", &Versize);
				Heapsize = Versize;//��������,��������
				vertices = (Ver*)malloc(sizeof(Ver)*(Versize + 1));//���� ����� �����迭
				index = (int*)malloc(sizeof(int)*(Versize));//���� ���� �ε��� ������ �迭
				Vectors = new PI[Versize];//�� �������� Vector�� �����
				for (int i = 0; i < Versize; i++) 
					index[i] = i + 1;//index[i]�� u.now==i�� vertices[x]�� x���� value�� ���´�
			}
			int q, w, e;
			fscanf(f, "%d", &q);
			fscanf(f, "%d", &w);
			fscanf(f, "%d", &e);
			edge temp;
			temp.u = q; temp.v = w; temp.w = e;//����
			Vectors[q].push_back(temp);//vector�� �ִ´�
			Edgesize++;//������ ����
		}
		fclose(f);
	}
	else
		printf("���� �б� ����");
	printf("���̽�Ʈ�� ���� ���� �Է��Ͻÿ�.\n");
	scanf("%d", &StartVertex);
	DijkstraAlgorithm(Vectors,StartVertex);//���̽�Ʈ�� �Լ� ����
	Print();//���
	return 0;
}