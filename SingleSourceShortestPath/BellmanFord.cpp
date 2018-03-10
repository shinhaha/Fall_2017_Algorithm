#include <stdio.h>
#include <stdlib.h>

struct Vertex {//���� Struct
int key;//value
int PA;//parent
};

struct Edge {
	int u;//��������
	int v;//��������
	int w;//����ġ
};

#define edge struct Edge
#define Ver struct Vertex
#define INF 2000000000//���Ѵ�

Ver* vertices;//�����迭
edge* arr;//�����迭

int Edgesize = 0;//��������
int Versize = 0;//��������
int BellmanFordAlgorithm(edge* graph);//�������� �Լ�
void Print();//����ϴ� �Լ�
void PrintPath(int index);//��������� ����ϴ� �Լ�
void Relax(int u, int v,int w);//shortest path�� ã�� ������Ʈ �ϴ� �Լ�


int BellmanFordAlgorithm(edge* graph) {
	for (int i = 0; i < Versize; i++) {//�ʱ�ȭ
		vertices[i].key = INF;
		vertices[i].PA = NULL;
	}
	vertices[0].key = 0;//Initialize Single Source

	for (int i = 0; i < Versize - 1; i++) //��������-1
		for (int j = 0; j <Edgesize; j++) //�� ���������Ͽ�
			Relax(arr[j].u,arr[j].v,arr[j].w);//������Ʈ

	for (int j = 0; j < Edgesize; j++)//���� ����Ŭ �ִ��� Ȯ��
		if (vertices[arr[j].v].key > vertices[arr[j].u].key + arr[j].w)
			return 0;
	return 1;
}

void Relax(int u, int v,int w) {//shortest path�� ������Ʈ �ϴ� �Լ���. �θ� ������Ʈ�Ѵ�.
	if (vertices[v].key > vertices[u].key +w ) {//�� ª�� �Ÿ��� ã����
		vertices[v].key = vertices[u].key + w;//������Ʈ
		vertices[v].PA = u;
	}
}

void Print() {//����ϴ� �Լ���.
	for (int i = 0; i < Versize; i++) {//��� ����������
		printf("%d=>Path: 0 ", i);
		PrintPath(i);
		printf(" Cost:%d\n",vertices[i].key);
	}
}

void PrintPath(int index) {//��������� PA�� NULL�϶����� ����ϴ� �Լ���.
	if (vertices[index].PA != NULL) //���϶����� ���
		PrintPath(vertices[index].PA);
	if(index!=0)
		printf("%d ", index);

}

int main(void) {
FILE *f = NULL;
fopen_s(&f, "C:\\Users\\���϶�\\Desktop\\graph_sample_bellman.txt", "r");
if (f != NULL) {
while (!feof(f)) {
	if (Edgesize == 0) {
		fscanf(f, "%d", &Versize);
		vertices = (Ver*)malloc(sizeof(Ver)*(Versize + 1));//�����迭
		arr = (edge*)malloc((Edgesize+1)*sizeof(edge));//�����迭
	}
	fscanf(f, "%d", &arr[Edgesize].u);//�����迭�� �־��ݴϴ�
	fscanf(f, "%d", &arr[Edgesize].v);
	fscanf(f, "%d", &arr[Edgesize].w);
	Edgesize++;//������ ����
				}
	fclose(f);
}
	else
		printf("���� �б� ����");
printf("�������� �˰���\n");
if (BellmanFordAlgorithm(arr))//�������� �˰��� ����
Print();//���ǻ���Ŭ �� ������ ���
else
printf("���� ����Ŭ �����ϴ�\n");//���� ����Ŭ ������
	return 0;
}