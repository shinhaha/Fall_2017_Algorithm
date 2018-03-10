
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define INF 1000000000

struct Ver {
	int i;//input������ index
	int s;//���۽ð�
	int f;//����ð�
	int v;//value
};

#define ver struct Ver

ver* act;//input Ver ��� �迭
int number = 0;//�Ѱ���

void insertionSort(ver* A, int start, int end) {//���۽ð� ���� ��������
	for (int i = start + 1; i < end; i++) {//������ �ε��� �����ε������� ������ �ε������� ����
		ver key= act[i];
		int j = i;
		for (j = i; j > start && A[j - 1].s > key.s; j--) {//������ ã����
			act[j] = act[j - 1];
		}
		A[j] = key;//�� ����
	}
}

void Iterative_Greedy_algorithm(int i) {
	int n = i;//�Ѱ���
	int k = n;
	printf("���õ� Activity�� input������ index=> %d\n", act[k].i);//���
	number++;//���� ++
	for (int m = n; m>0; m--)//�ڿ������� ���鼭(���۽ð��� �����ͺ��� ���鼭)
		if (act[m].f<=act[k].s) {//����ð��� ���۽ð����� ������ ã����
			k = m;//����
			printf("���õ� Activity�� input������ index=> %d\n",act[k].i);
			number++;//����++
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
			act[i + 1].i = i + 1;
			fscanf(file,"%d", &act[i+1].s);//input index 1���� �޴´�
			fscanf(file, "%d",&act[i+1].f);
			fscanf(file, "%d",&act[i+1].v);
			i++;
		}
		act[i+1].s = INF;
		fclose(file);
	}
	else
		printf("���� �б� ����");

	insertionSort(act, 1, i + 1);//���۽ð��� ����
	cout << "Homework1_4\n" << endl;
	Iterative_Greedy_algorithm(i);//���۽ð� ���� activity select �׸��� �˰���
	cout << "�� ����: " << number;

	return 0;
}