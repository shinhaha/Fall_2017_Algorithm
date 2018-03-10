
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define INF 1000000000

int** c;
int** rem;

struct Ver {
	int i;
	int s;
	int f;
	int v;
};

#define ver struct Ver

ver* act;
int total = 0;//�� value

void DynamicSelection(int n) {
	for (int l = 2; l <= n + 1; l++)//bottom up�� ���� chain length
		for (int i = 0; i <= n - l + 1; i++) {//������ ����� i����
			int j = i + l;//length��ŭ ����
			c[i][j] = 0;//�ʱ�ȭ
			int k = j - 1;//k�� ������ i<k<j
			while (i < k) {
				//i�� ����ð��� k���� �۰ų� ���� j�� ���۽ð��� k�� ����ð����� ũ�ų� ������
				//�� ū ���� ã�Ҵٸ�
				if (act[i].f <= act[k].s&&act[k].f <= act[j].s&&c[i][k] + c[k][j] + act[k].v > c[i][j]) {
					c[i][j] = c[i][k] + c[k][j] + act[k].v;//�� ������Ʈ
					rem[i][j] = k;//��� �߶��� ���
				}
				k--;
			}
		}
}

void PrintActivities(int i, int j) {
	if (c[i][j] > 0) {
		int k = rem[i][j];//i,j�� ��� ��� �߶��� k
		total+=act[k].v;
		cout <<"���õ� Activity�� input������ index��=> "<<act[k].i<<endl;//���� input������ �ε����� ���
		PrintActivities(i, k);//k ���ʺκ� ��� �߶���
		PrintActivities(k, j);//k ������ �κ� ��� �߶���
	}
}

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

int main(void) {
	FILE *file = NULL;
	fopen_s(&file, "C:\\Users\\���϶�\\Desktop\\activity_input.txt", "r");
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
			act[i + 1].i = i + 1;//input������ �ε��� ���
			fscanf(file, "%d", &act[i + 1].s);//input�� 1���� �޴´�.
			fscanf(file, "%d", &act[i + 1].f);
			fscanf(file, "%d", &act[i + 1].v);
			i++;
		}
		act[i + 1].s = INF;

		c = (int**)calloc(i + 2, sizeof(int*));//0���� �ʱ�ȭ�� dp 2�����迭 ����
		for (int k = 0; k <i + 2; k++)
			c[k] = (int*)calloc(i + 2, sizeof(int));

		rem = (int**)calloc(i + 2, sizeof(int*));//0���� �ʱ�ȭ�� rem ��� 2�����迭 ����
		for (int k = 0; k<i + 2; k++)
			rem[k] = (int*)calloc(i + 2, sizeof(int));

		fclose(file);
	}
	else
		printf("���� �б� ����");

	insertionSort(act, 1, i + 1);//����ð��� ����
	cout << "Homework1_2\n" << endl;
	DynamicSelection(i);//max value dp
	PrintActivities(0, i + 1);//���
	cout << "Sum of values of selected activities: " << total;
	return 0;
}