#include <stdio.h>
#include <stdlib.h>
#include <cstdbool>

struct Edge {
	int start;//시작정점
	int end;//끝정점
	int weight;//가중치
	bool visit;//선택되었는가
};

#define edge struct Edge

edge* arr;//간선배열
int* Set;//Set배열
int Edgesize = 0;//간선개수
int Versize = 0;//정점개수

void kruskalAlgorithm();
int FindSet(int u);
void sort();
void makeSet(int i, int j);


void kruskalAlgorithm() {
	Set = (int*)malloc(sizeof(int)*Versize);
	for (int i = 0; i < Versize; i++)//set을 자기자신만을 포함한 정점집합 set으로 만든다
		Set[i] = -1;//자기자신만
	sort();//오름차순으로 삽입정렬 weightSort
	for (int i = 0; i < Edgesize; i++) {//가중치작은것부터 선택한게
		if (FindSet(arr[i].start) != FindSet(arr[i].end)) {//두정점의 set이 다르면
			makeSet(arr[i].start, arr[i].end);//Union
			arr[i].visit = true;//selected
		}
	}
	int totalcost = 0;
	printf("선택 간선목록\n");
	for (int i = 0; i < Edgesize; i++)
		if (arr[i].visit) {//selected라면
			printf("start:%d end:%d weight:%d\n", arr[i].start, arr[i].end, arr[i].weight);//그 간선 출력
			totalcost += arr[i].weight;//토탈코스트 누적
		}
	printf("\nTotalCost=>%d", totalcost);
}


void makeSet(int i,int j) {
	int x = FindSet(i);//i의 root 붕괴법칙
	int y = FindSet(j);//j의 root 붕괴법칙
	int newsize = Set[x] + Set[y];//newsize변수에 둘의 사이즈를 더함
	if (Set[x] >= Set[y]) { //-Set[y]가  -Set[x]보다크면 Set[y]를 부모로만듬 
		Set[x] = y;
		Set[y] = newsize;
	}
	else { // 아니면 Set[i]를 부모로만듬
		Set[y] = x;
		Set[x] = newsize;
	}
}

int FindSet(int i) {//붕괴 법칙을 이용한 CollapsingFind
	if (Set[i]<0)
		return i;
	return Set[i] =FindSet(Set[i]);
}


void sort(){
	for (int i = 1; i < Edgesize; i++) {//정렬할 인덱스 다음인덱스부터 마지막 인덱스까지 돈다
		edge key = arr[i];//key를 i인덱스로 정하고
		int j = i;
		for (j = i; j > 0 && arr[j - 1].weight > key.weight; j--) {//작은거 찾으면
			arr[j]= arr[j - 1];
		}
		arr[j] = key;//삽입
	}
}

// main function
int main(void){
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\신하람\\Desktop\\graph_sample.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			if (Edgesize == 0) {
				fscanf(f, "%d", &Versize);//정점개수
			}
			arr = (edge*)realloc(arr, sizeof(edge)*(Edgesize+1));//간선개수만큼 realloc
			int q, w, e;
			fscanf(f, "%d", &q);
			fscanf(f, "%d", &w);
			fscanf(f, "%d", &e);
			arr[Edgesize].start = q;//간선 노드를 만들어주고
			arr[Edgesize].end=w;
			arr[Edgesize].weight = e;
			arr[Edgesize].visit = false;//선택안되었다고 초기화
			Edgesize++;//엣지의 개수
		}
		fclose(f);
	}
	else
		printf("파일 읽기 실패");
		kruskalAlgorithm();
		return 0;
}