#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
using namespace std;

#define INF 2000000000//���Ѵ�

int Edgesize = 0;//��������
int Versize = 0;//��������
int** arr;//����ġ �迭
void FloydWarshall();
void print(int** A,int i);
int** newArr();

void FloydWarshall() {
	printf("FloydWarshall\n");
	int** first = newArr();//D0����
		for (int i = 0; i < Versize; i++)
			for (int j = 0; j < Versize; j++)
				first[i][j] = arr[i][j];//����ġ �迭�� �����ؼ� D0�� ����
		print(first,0);//D0���
		for (int k = 0; k < Versize; k++) {
			int** newArrays = newArr();//n*n newArray ����
			for (int i = 0; i < Versize; i++) {
				for (int j = 0; j < Versize; j++) {
					if (first[i][k] != INF&&first[k][j] != INF)//�����÷ο� ����
						newArrays[i][j] = min(first[i][j], first[i][k] + first[k][j]);//i-j��κ��� i-k-j��ΰ� �� ������
					else
						newArrays[i][j] = first[i][j];//���� D(i-1)���� ����
				}
			}	
			first = newArrays;//first�� ����
			print(first,k+1);//Di���
		}
}

int** newArr() {//n*n �迭 ����
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
			if (A[i][j] == INF)//���Ѵ�� ���ٰ� X���
				printf("    X");
			else
				printf("%5d", A[i][j]);//���Ѵ밡 �ƴ϶�� ����ġ ���
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
			int q, w, e;//���� ����,���� ����,cost
			fscanf(f, "%d", &q);
			fscanf(f, "%d", &w);
			fscanf(f, "%d", &e);
			arr[q][w] = e;
			Edgesize++;//��������++
		}
		fclose(f);
	}
	else
		printf("���� �б� ����");
	FloydWarshall();//�÷��̵� ���� �˰��� ����
}