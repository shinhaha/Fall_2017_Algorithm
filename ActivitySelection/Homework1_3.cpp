
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define INF 1000000000

struct Ver {
	int i;//input������ �ε���
	int s;//���۽ð�
	int f;//����ð�
	int v;//value
};

#define ver struct Ver

ver* act;//Ver node�迭
int number = 0;//����

void insertionSort(ver* A, int start, int end) {//����ð� ���� ��������
	for (int i = start + 1; i < end; i++) {//������ �ε��� �����ε������� ������ �ε������� ����
		ver key = act[i];
		int j = i;
		for (j = i; j > start && A[j - 1].f > key.f; j--) {//������ ã����
			act[j] = act[j - 1];
		}
		A[j] = key;//�� ����
	}
}

void Iterative_Greedy_algorithm(int i) {
	int n = i;
	int k = 1;
	number++;
	printf("���õ� Activity�� input������ index=> %d\n", act[k].i);
	for (int m = 1; m <= n; m++)//�տ������� ���鼭(����ð� �����ź��� ���鼭)
		if (act[m].s >= act[k].f) {//���۽ð��� ����ð����� ������ ã����
			number++;//���� ++
			k = m;//����
			printf("���õ� Activity�� input������ index=> %d\n",act[k].i);
		}
}

int main(void) {
	FILE *file = NULL;
	fopen_s(&file, "C:\\Users\\���϶�\\Desktop\\activity_input.txt", "r");
	int size;//�������
	int i = 0;
	if (file != NULL) {
		while (!feof(file)) {
			act = (ver*)realloc(act, sizeof(ver)*(i + 2));
			if (i == 0) {
				act[0].i = 0;
				act[0].s = 0;
				act[0].f = 0;
				act[0].v = 0;
			}
			act[i + 1].i = i + 1;//input������ index����
			fscanf(file, "%d", &act[i + 1].s);//input����
			fscanf(file, "%d", &act[i + 1].f);
			fscanf(file, "%d", &act[i + 1].v);
			i++;
		}
		act[i + 1].s = INF;
		fclose(file);
	}
	else
		printf("���� �б� ����");
	insertionSort(act, 1, i + 1);//����ð� ���� ����
	cout << "Homework1_3\n" << endl;
	Iterative_Greedy_algorithm(i);//Activity selection
	cout << "�� ����: " << number;

	return 0;
}