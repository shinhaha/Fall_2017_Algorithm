#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define INF 1000000000

int** c;//dp�� ���� �迭
int** rem;//��� �߶��� ����ϱ� ���� �迭

struct Ver {
	int i;//��ǲ������ �ε���
	int s;//���۽ð�
	int f;//����ð�
	int v;//value
};

#define ver struct Ver

ver* act;//input node�迭
int number = 0;

void DynamicSelection(int n) {

	for(int l=2; l<=n+1; l++)//Bottom-up ������� chain-length 2���� �׾ư�
		for (int i = 0; i <= n - l + 1; i++) {//i�� ü�η����� ������ ���� ���̸�ŭ Ȯ��
			int j = i+l;//j-i=chain length
			c[i][j] = 0;//�ʱ�ȭ
			int k = j - 1;//i<k<j�� k�ǹ����̹Ƿ�
			while (i<k) {
			//i�� ����ð��� k���� �۰ų� ���� j�� ���۽ð��� k�� ����ð����� ũ�ų� ������
			//�� ū ���� ã�Ҵٸ�
				if (act[i].f <= act[k].s&&act[k].f <= act[j].s&&c[i][k] + c[k][j] + 1 >= c[i][j]) {
					c[i][j] = c[i][k] + c[k][j] + 1;//�� ������Ʈ
					rem[i][j] = k;//��� �߶��� ���
				}
				k--;
			}
		}	
}

void PrintActivities(int i, int j) {
	if (c[i][j] > 0) {
	int k = rem[i][j];
		number++;
		cout <<"���õ� Activity�� input������ index��=> "<<act[k].i<<endl;//���� input������ �ε����� ���
		PrintActivities(i, k);//k ���ʺκ� ��� �߶���
		PrintActivities(k, j);//k �����ʺκ� ��� �߶���
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
			act[i + 1].i = i + 1;//input������ �ε��� ���
			fscanf(file, "%d", &act[i + 1].s);//��ǲ�� 1���� �޴´�
			fscanf(file, "%d", &act[i + 1].f);
			fscanf(file, "%d", &act[i + 1].v);
			i++;
		}
		act[i + 1].s = INF;

		c = (int**)calloc(i + 2, sizeof(int*));
		for (int k = 0; k <i+2; k++)
			c[k] = (int*)calloc(i + 2, sizeof(int));//0���� �ʱ�ȭ�� dp 2�����迭 ����
		
		rem= (int**)calloc(i + 2, sizeof(int*));//0���� �ʱ�ȭ�� rem ���迭 ����
		for (int k = 0; k<i+2; k++)
			rem[k] = (int*)calloc(i + 2, sizeof(int));

		fclose(file);
	}
	else
		printf("���� �б� ����");

	insertionSort(act, 1, i + 1);//����ð��� ����
	cout << "Homework1_1\n" << endl;
	DynamicSelection(i);//number of select dp
	PrintActivities(0, i+1);//���
	cout << "�� ����: " << number;

	return 0;
}