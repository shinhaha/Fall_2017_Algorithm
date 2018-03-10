#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
using namespace std;

#define INF 2000000000

int Edgesize = 0;//��������
int Versize = 0;//��������
int** arr;
int** ExtendShortestPaths(int** A,int** B);
int** newArr();
void SlowAllPairsShortestPaths();
void print(int** A,int i);

void SlowAllPairsShortestPaths() {
	printf("SlowAllPairsShortestPaths\n");
	int** first = newArr();//n*n�迭 ���� L1
	for (int i = 0; i < Versize; i++)
		for (int j = 0; j < Versize; j++)
			first[i][j] = arr[i][j];//first�迭�� ����
	print(first,0);//L0���
	for (int i = 1; i <Versize-1; i++) {
		first = ExtendShortestPaths(first,arr);//first�迭�� arr�� ���� �� ª����� ������Ʈ�� ���� first�� �־���
		print(first,i);//first��� Li
	}
}

void FasterAllPairsShortestPaths() {
	printf("FasterAllPairsShortestPaths\n");
	int** first = newArr();//n*n�迭 ���� L1
	for (int i = 0; i < Versize; i++)
		for (int j = 0; j < Versize; j++)
			first[i][j] = arr[i][j];//frst�� �迭�� ����
	int m = 1;
	print(first,0);//L0 ���
	while (m <Versize-1) {//���̳��� ���α׷��� �̿��Ͽ�
		first= ExtendShortestPaths(first,first);//first�迭�� ���Ͽ� fisrt�迭�� ������Ʈ �Ѱ��� first�� �־��ش�
		print(first,m);//Lm�� ����Ѵ�
		m *= 2;//m�� 2��� ���ش�
	}
}

int** ExtendShortestPaths(int** A,int** B) {//B�迭�� ���Ͽ� A�迭�� �� ª�� ��η� ������Ʈ�ϴ� �Լ���
	int** newArrays = newArr();
	for (int i = 0; i < Versize; i++)
		for (int j = 0; j < Versize; j++) {
			newArrays[i][j] = INF;//���� ū ������ �ʱ�ȭ
			for (int k = 0; k < Versize; k++)
				if(B[k][j]!=INF&&A[i][k]!=INF)//�����÷ο� ����
				newArrays[i][j] = min(newArrays[i][j], A[i][k] + B[k][j]);
		}
	return newArrays;
}

int** newArr() {//n*n�迭 ����
	int** arrtemp = (int**)malloc(sizeof(int*)*Versize);
	for (int q = 0; q < Versize; q++)
		arrtemp[q] = (int*)malloc(sizeof(int)*Versize);
	return arrtemp;
}

void print(int** A,int i) {//����ϴ� �Լ�
	printf("(%d)\n", i);
	for (int i = 0; i < Versize; i++) {
		printf("\n");
		for (int j = 0; j < Versize; j++)
			if (A[i][j] == INF)//���Ѵ�� ��ΰ� ����
				printf("    X");
			else
				printf("%5d", A[i][j]);
	}
	printf("\n");
}

int main(void) {
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\���϶�\\Desktop\\graph_sample_directed.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			if (Edgesize == 0) {
				fscanf(f, "%d", &Versize);
				arr = (int**)malloc(sizeof(int*)*Versize);
				for (int i = 0; i < Versize; i++)
					arr[i] = (int*)malloc(sizeof(int)*Versize);
				for (int i = 0; i < Versize; i++)
					for (int j = 0; j < Versize; j++)
						if (i == j)
							arr[i][j] = 0;
						else
							arr[i][j] = INF;
			}
			int q, w, e;//��������,��������,cost
			fscanf(f, "%d", &q);
			fscanf(f, "%d", &w);
			fscanf(f, "%d", &e);
			arr[q][w] = e;
			Edgesize++;//�������� ++
		}
		fclose(f);
	}
	else
		printf("���� �б� ����");

	SlowAllPairsShortestPaths();//Slow
	FasterAllPairsShortestPaths();//Faster
}
