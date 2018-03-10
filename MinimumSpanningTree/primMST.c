#include <stdio.h>
#include <stdlib.h>
#include <cstdbool>

struct Vertex {//���� Struct
	int now;//�ε��� �� �����ΰ�
	int key;//value
	struct Vertex* PA;//parent
};

#define Ver struct Vertex
#define INF 2000000000//���Ѵ�

Ver* vertices;//�����迭
int* index;//������� �迭
int** arr;//�����迭
bool* visit;//�湮�ߴ��� �迭

int Edgesize = 0;//��������
int Versize = 0;//��������
int Heapsize = 0;//��������

Ver* BuildMinHeap();
void primAlgorithm(int** graph, int startVertex);
Ver* Vswap(Ver* input, int i, int j);
Ver* MinHeapify(Ver* A, int i, int heapsize);
int* IndexUpdate(int*A, int x, int y);
Ver extractMinHeap(Ver* A);

void primAlgorithm(int** graph, int startVertex) {
	for (int i = 1; i <= Versize; i++) {//������� �ʱ�ȭ���ش�.
		vertices[i].now = i - 1;
		vertices[i].key = INF ;
		vertices[i].PA = NULL;
	}
	vertices[startVertex + 1].key = 0;//���� ���� +1���� �����ؾ��� heap�� 1���ͽ����̹Ƿ�
	
	Vswap(vertices, 1, startVertex + 1);//���������� key�� 0�̵Ǿ��� ������ �� ���Ѵ��̹Ƿ� �׳ɽ���
	IndexUpdate(index, 1, startVertex+1);//�ε���������Ʈ
	printf("Path:");
	while (Heapsize != 0) {
		Ver u = extractMinHeap(vertices);//���� ���� ����ġ ���� ��
		printf("%d ", u.now);
		visit[u.now] = true;//�湮�ߴٰ� ��ũ
		for (int i = 0; i <Versize; i++) {//index[i]�� i�� u.now�� ������ vertices[i]�� �ε�����
			if (!visit[i] && arr[u.now][i]<vertices[index[i]].key&&arr[u.now][i] != 0){//�湮���� �ʾҰ� �� �۰� ����Ǿ��ִٸ�
				vertices[index[i]].key = arr[u.now][i];//������Ʈ
				vertices[index[i]].PA = &u;
			}
		}
		BuildMinHeap(vertices);//������Ʈ�� ������ �� �� �����Ƿ� BuildMinHeap���
	}
	int totalcost = 0;
	for (int i = Versize; i >= 1; i--) {//���
		if (visit[i]) {
			printf("\n����%d�� key��=>%d", vertices[i].now, vertices[i].key);
			totalcost += vertices[i].key;
		}
	}
	printf("\nTotalCost=>%d", totalcost);
}

Ver* BuildMinHeap() {//������Ʈ�� ������ �� �� �����Ƿ� BuildMinHeap�� ���ش�.
	for (int i = floor(Heapsize / 2); i >= 1; i--)
		vertices = MinHeapify(vertices,i, Heapsize);
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
	index=IndexUpdate(index,1,i);//index���� ������Ʈ ���ش�
	Heapsize--;//�������� ���δ�
	return temp;//���� ������ ����
}

int main(void) {
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\���϶�\\Desktop\\graph_sample.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			if (Edgesize == 0) {
				fscanf(f, "%d", &Versize);
				Heapsize = Versize;//��������,��������
				vertices = (Ver*)malloc(sizeof(Ver)*(Versize + 1));//�����迭
				arr = (int **)calloc(Versize, sizeof(int*));//������ �����迭
				index = (int*)calloc(Versize, sizeof(int));//index[i]�� u.now==i�� vertices[x]�� x���� value�� ���´�
				visit = (bool*)malloc(sizeof(bool)*(Versize));//�湮�ߴ��� �迭
				for (int k = 0; k <Versize; k++) {
					arr[k] = (int *)calloc(Versize, sizeof(int));//�� 0�ʱ�ȭ
					visit[k] = false;//No �湮 �ʱ�ȭ
					index[k] = k + 1;//���� �ε����� 1�����̹Ƿ�
				}
			}
			int q, w, e;
			fscanf(f, "%d", &q);
			fscanf(f, "%d", &w);
			fscanf(f, "%d", &e);
			arr[q][w] = e;//undirected�� ��������� ����
			arr[w][q] = e;
			Edgesize++;//������ ����
		}
		fclose(f);
	}
	else
		printf("���� �б� ����");
	primAlgorithm(arr, 0);//�����˰��� ����
	return 0;
}