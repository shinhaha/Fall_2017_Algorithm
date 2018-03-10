#include <stdio.h>
#include <stdlib.h>
#include <cstdbool>

struct Edge {
	int start;//��������
	int end;//������
	int weight;//����ġ
	bool visit;//���õǾ��°�
};

#define edge struct Edge

edge* arr;//�����迭
int* Set;//Set�迭
int Edgesize = 0;//��������
int Versize = 0;//��������

void kruskalAlgorithm();
int FindSet(int u);
void sort();
void makeSet(int i, int j);


void kruskalAlgorithm() {
	Set = (int*)malloc(sizeof(int)*Versize);
	for (int i = 0; i < Versize; i++)//set�� �ڱ��ڽŸ��� ������ �������� set���� �����
		Set[i] = -1;//�ڱ��ڽŸ�
	sort();//������������ �������� weightSort
	for (int i = 0; i < Edgesize; i++) {//����ġ�����ͺ��� �����Ѱ�
		if (FindSet(arr[i].start) != FindSet(arr[i].end)) {//�������� set�� �ٸ���
			makeSet(arr[i].start, arr[i].end);//Union
			arr[i].visit = true;//selected
		}
	}
	int totalcost = 0;
	printf("���� �������\n");
	for (int i = 0; i < Edgesize; i++)
		if (arr[i].visit) {//selected���
			printf("start:%d end:%d weight:%d\n", arr[i].start, arr[i].end, arr[i].weight);//�� ���� ���
			totalcost += arr[i].weight;//��Ż�ڽ�Ʈ ����
		}
	printf("\nTotalCost=>%d", totalcost);
}


void makeSet(int i,int j) {
	int x = FindSet(i);//i�� root �ر���Ģ
	int y = FindSet(j);//j�� root �ر���Ģ
	int newsize = Set[x] + Set[y];//newsize������ ���� ����� ����
	if (Set[x] >= Set[y]) { //-Set[y]��  -Set[x]����ũ�� Set[y]�� �θ�θ��� 
		Set[x] = y;
		Set[y] = newsize;
	}
	else { // �ƴϸ� Set[i]�� �θ�θ���
		Set[y] = x;
		Set[x] = newsize;
	}
}

int FindSet(int i) {//�ر� ��Ģ�� �̿��� CollapsingFind
	if (Set[i]<0)
		return i;
	return Set[i] =FindSet(Set[i]);
}


void sort(){
	for (int i = 1; i < Edgesize; i++) {//������ �ε��� �����ε������� ������ �ε������� ����
		edge key = arr[i];//key�� i�ε����� ���ϰ�
		int j = i;
		for (j = i; j > 0 && arr[j - 1].weight > key.weight; j--) {//������ ã����
			arr[j]= arr[j - 1];
		}
		arr[j] = key;//����
	}
}

// main function
int main(void){
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\���϶�\\Desktop\\graph_sample.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			if (Edgesize == 0) {
				fscanf(f, "%d", &Versize);//��������
			}
			arr = (edge*)realloc(arr, sizeof(edge)*(Edgesize+1));//����������ŭ realloc
			int q, w, e;
			fscanf(f, "%d", &q);
			fscanf(f, "%d", &w);
			fscanf(f, "%d", &e);
			arr[Edgesize].start = q;//���� ��带 ������ְ�
			arr[Edgesize].end=w;
			arr[Edgesize].weight = e;
			arr[Edgesize].visit = false;//���þȵǾ��ٰ� �ʱ�ȭ
			Edgesize++;//������ ����
		}
		fclose(f);
	}
	else
		printf("���� �б� ����");
		kruskalAlgorithm();
		return 0;
}