#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

struct Vertex {//정점 Struct
	int now;//자신이 무슨 정점인가,인덱스 몇 정점인가
	int key;//value
	int PA;//parent
};

struct Edge {//간선 Struct
	int u;//시작정점
	int v;//도착정점
	int w;//가중치
};

#define Ver struct Vertex
#define edge struct Edge
#define PI vector<edge>
#define INF 2000000000//무한대

Ver* vertices;//정점배열
PI* Vectors;//edge저장할 간선 vector
int* index;//인덱스 저장할 배열

int StartVertex = -1;//입력받을 출방 정점
int Edgesize = 0;//간선개수
int Versize = 0;//정점개수
int Heapsize = 0;//힙사이즈

void Print();//출력하는 함수다
void PrintPath(int index);//재귀적으로 PA가 NULL일때까지 출력한다
void DijkstraAlgorithm(PI* Vecarr, int startVertex);//다이스트라 함수다
Ver* BuildMinHeap();
Ver* Vswap(Ver* input, int i, int j);//vertices Swap함수다
int* IndexUpdate(int*A, int x, int y);//Vswap할때 index배열을 스왑하는 함수다
Ver* MinHeapify(Ver* A, int i, int heapsize);
Ver extractMinHeap(Ver* A);
void Relax(int u, int v, int w);//shortest path를 업데이트하는 함수다

void DijkstraAlgorithm(PI* Vecarr,int startVertex) {
	for (int i = 1; i <= Versize; i++) {//모든정점 초기화해준다.
		vertices[i].now = i - 1;//자신이 무슨정점인가
		vertices[i].key = INF;
		vertices[i].PA = NULL;
	}
	vertices[startVertex + 1].key = 0;//시작 정점 +1에서 시작해야함 heap은 1부터시작이므로
	vertices=Vswap(vertices, 1, startVertex + 1);//시작정점만 key가 0이되었고 나머진 다 무한대이므로 그냥스왑
	index=IndexUpdate(index, 1, startVertex + 1);//인덱스업데이트
	while (Heapsize != 0) {//큐에 아무것도 없을때까지
		Ver u = extractMinHeap(vertices);//가장 작은 가중치의 정점을 뽑는다
		for (int i = 0; i < Vectors[u.now].size(); i++) {//뽑은 정점에 연결되어있는 벡터 리스트를 돌면서 Relax한다
			edge temp = Vectors[u.now].at(i);
			Relax(temp.u, temp.v, temp.w);//업데이트
		}
	}
}

void Relax(int u, int v, int w) {//shortest path를 업데이트 하는 함수다. 부모도 업데이트한다.
	if (vertices[index[v]].key > vertices[index[u]].key+w) {
		vertices[index[v]].key = vertices[index[u]].key+w;
		vertices[index[v]].PA = u;
	}
	vertices=MinHeapify(vertices, 1,Heapsize);//값이 업데이트 될때마다 hapify를 해준다.
}

void Print() {//출력하는 함수다.
	for (int i = 0; i <Versize; i++) {
		printf("%d=>Path: %d ", vertices[index[i]].now,StartVertex);
		PrintPath(vertices[index[i]].now);
		printf(" Cost:%d\n", vertices[index[i]].key);
	}
}

void PrintPath(int i){//재귀적으로 PA가 NULL일때까지 출력하는 함수다.
	if (vertices[index[i]].PA != NULL)
		PrintPath(vertices[index[i]].PA);
	if(vertices[index[i]].now!=StartVertex)
		printf("%d ", vertices[index[i]].now);
}

Ver* BuildMinHeap() {//업데이트가 여러개 될 수 있으므로 BuildMinHeap을 해준다.
	for (int i = floor(Heapsize / 2); i >= 1; i--)
		vertices = MinHeapify(vertices, i, Heapsize);
	return vertices;
}

Ver* MinHeapify(Ver* A, int i, int heapsize) {//작은값으로 힙어파이 해준다
	int l = 2 * i;
	int r = 2 * i + 1;
	int smallest;
	if (l <= heapsize&&A[l].key < A[i].key)//왼쪽자식과 비교
		smallest = l;
	else
		smallest = i;
	if (r <= heapsize&&A[r].key<A[smallest].key)//오른쪽 자식과 비교
		smallest = r;
	if (smallest != i) {//같지 않으면 자식과 바꿔주고 재귀적으로 실행
		vertices = Vswap(vertices, i, smallest);
		index = IndexUpdate(index, i, smallest);
		vertices = MinHeapify(vertices, smallest, heapsize);
	}
	return vertices;
}

Ver* Vswap(Ver* input, int i, int j) {//두개의 정점의 인자들을 스왑해준다
	Ver *tmp = (Ver *)malloc(sizeof(Ver));//임시 할당
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

int* IndexUpdate(int*A, int x, int y) {//스왑한 값 업데이트
	A[vertices[x].now] = x;//vertices[x]가 정점인덱스 x.now를 갖고 index[x.now]는 x이다. 
	A[vertices[y].now] = y;
	return A;
}

Ver extractMinHeap(Ver* A) {//가장작은값을 뽑는다
	int i = Heapsize;//i는 힙사이즈
	Ver temp = A[1];//리턴할 가장 작은 값 정점
	vertices = Vswap(A, 1, i);//Vertices 배열을 스왑한다 
	index = IndexUpdate(index, 1, i);//index값을 업데이트 해준다
	Heapsize--;//힙사이즈 줄인다
	return temp;//가장 작은값 리턴
}

int main(void) {
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\신하람\\Desktop\\graph_sample_dijkstra.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			if (Edgesize == 0) {
				fscanf(f, "%d", &Versize);
				Heapsize = Versize;//힙사이즈,정점개수
				vertices = (Ver*)malloc(sizeof(Ver)*(Versize + 1));//힙에 사용할 정점배열
				index = (int*)malloc(sizeof(int)*(Versize));//힙의 정점 인덱스 저장할 배열
				Vectors = new PI[Versize];//각 정점마다 Vector를 만든다
				for (int i = 0; i < Versize; i++) 
					index[i] = i + 1;//index[i]는 u.now==i인 vertices[x]의 x값을 value로 갖는다
			}
			int q, w, e;
			fscanf(f, "%d", &q);
			fscanf(f, "%d", &w);
			fscanf(f, "%d", &e);
			edge temp;
			temp.u = q; temp.v = w; temp.w = e;//연결
			Vectors[q].push_back(temp);//vector에 넣는다
			Edgesize++;//엣지의 개수
		}
		fclose(f);
	}
	else
		printf("파일 읽기 실패");
	printf("다이스트라 시작 정점 입력하시오.\n");
	scanf("%d", &StartVertex);
	DijkstraAlgorithm(Vectors,StartVertex);//다이스트라 함수 실행
	Print();//출력
	return 0;
}