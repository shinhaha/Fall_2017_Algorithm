#include <stdio.h>
#include <stdlib.h>
#include <cstdbool>

struct Vertex {//정점 Struct
	int now;//인덱스 몇 정점인가
	int key;//value
	struct Vertex* PA;//parent
};

#define Ver struct Vertex
#define INF 2000000000//무한대

Ver* vertices;//정점배열
int* index;//정점기억 배열
int** arr;//간선배열
bool* visit;//방문했는지 배열

int Edgesize = 0;//간선개수
int Versize = 0;//정점개수
int Heapsize = 0;//힙사이즈

Ver* BuildMinHeap();
void primAlgorithm(int** graph, int startVertex);
Ver* Vswap(Ver* input, int i, int j);
Ver* MinHeapify(Ver* A, int i, int heapsize);
int* IndexUpdate(int*A, int x, int y);
Ver extractMinHeap(Ver* A);

void primAlgorithm(int** graph, int startVertex) {
	for (int i = 1; i <= Versize; i++) {//모든정점 초기화해준다.
		vertices[i].now = i - 1;
		vertices[i].key = INF ;
		vertices[i].PA = NULL;
	}
	vertices[startVertex + 1].key = 0;//시작 정점 +1에서 시작해야함 heap은 1부터시작이므로
	
	Vswap(vertices, 1, startVertex + 1);//시작정점만 key가 0이되었고 나머진 다 무한대이므로 그냥스왑
	IndexUpdate(index, 1, startVertex+1);//인덱스업데이트
	printf("Path:");
	while (Heapsize != 0) {
		Ver u = extractMinHeap(vertices);//가장 작은 가중치 정점 팝
		printf("%d ", u.now);
		visit[u.now] = true;//방문했다고 마크
		for (int i = 0; i <Versize; i++) {//index[i]는 i를 u.now로 가지는 vertices[i]의 인덱스다
			if (!visit[i] && arr[u.now][i]<vertices[index[i]].key&&arr[u.now][i] != 0){//방문하지 않았고 더 작고 연결되어있다면
				vertices[index[i]].key = arr[u.now][i];//업데이트
				vertices[index[i]].PA = &u;
			}
		}
		BuildMinHeap(vertices);//업데이트가 여러개 될 수 있으므로 BuildMinHeap사용
	}
	int totalcost = 0;
	for (int i = Versize; i >= 1; i--) {//출력
		if (visit[i]) {
			printf("\n정점%d의 key는=>%d", vertices[i].now, vertices[i].key);
			totalcost += vertices[i].key;
		}
	}
	printf("\nTotalCost=>%d", totalcost);
}

Ver* BuildMinHeap() {//업데이트가 여러개 될 수 있으므로 BuildMinHeap을 해준다.
	for (int i = floor(Heapsize / 2); i >= 1; i--)
		vertices = MinHeapify(vertices,i, Heapsize);
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
	index=IndexUpdate(index,1,i);//index값을 업데이트 해준다
	Heapsize--;//힙사이즈 줄인다
	return temp;//가장 작은값 리턴
}

int main(void) {
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\신하람\\Desktop\\graph_sample.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			if (Edgesize == 0) {
				fscanf(f, "%d", &Versize);
				Heapsize = Versize;//힙사이즈,정점개수
				vertices = (Ver*)malloc(sizeof(Ver)*(Versize + 1));//정점배열
				arr = (int **)calloc(Versize, sizeof(int*));//이차원 간선배열
				index = (int*)calloc(Versize, sizeof(int));//index[i]는 u.now==i인 vertices[x]의 x값을 value로 갖는다
				visit = (bool*)malloc(sizeof(bool)*(Versize));//방문했는지 배열
				for (int k = 0; k <Versize; k++) {
					arr[k] = (int *)calloc(Versize, sizeof(int));//다 0초기화
					visit[k] = false;//No 방문 초기화
					index[k] = k + 1;//힙은 인덱스가 1부터이므로
				}
			}
			int q, w, e;
			fscanf(f, "%d", &q);
			fscanf(f, "%d", &w);
			fscanf(f, "%d", &e);
			arr[q][w] = e;//undirected라 양방향으로 연결
			arr[w][q] = e;
			Edgesize++;//엣지의 개수
		}
		fclose(f);
	}
	else
		printf("파일 읽기 실패");
	primAlgorithm(arr, 0);//프림알고리즘 실행
	return 0;
}