#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define INF 1000000000

int* w;//weight input arr
int* b;//benefit input arr
int **B;//dp����迭

int W;//����ũ��


void knapsackPrint(int n, int** B) {
	int i = n;
	int weight = W;
	int maxbenefit = B[i][weight + 1];//�ִ� benefit
	while (i > 0 && maxbenefit>=0) {//input������ŭ Ȯ���ϰų� �ִ� benefit�� 0�� Ŭ����
		if (B[i][weight+1] != B[i - 1][weight+1]) {//�״�� ������ �ű�� �ƴϿ��ٸ�
			cout << "���õ� item:" << i << endl;
			maxbenefit = maxbenefit - b[i];//benefit���� ���ش�
			weight = weight - w[i];//���� ���Կ��� ���ش�
			i--;
		}
		else
			i--;//�״�� �����οű��
	}
}

void Knapsack(int n) {

	for (int i = 1; i <= n; i++){//input ������
		for (int j = 1;j <= W+1; j++){//���� ũ�⸸ŭ ����
			if (w[i] < j)//���� ũ�⸦ ���󰡴� ���� j���� ũ�� ������ ������
				if (b[i] + B[i - 1][j - w[i]] > B[i - 1][j])//���ؼ�
					B[i][j] = b[i] + B[i - 1][j - w[i]];//ū�� �־��ش�
				else
					B[i][j] = B[i - 1][j];
			else B[i][j] = B[i - 1][j];//�ƴϸ� ������ �ű��
		}
	}

	cout << "max->" <<B[n][W+1]<<endl;//max����� ��ġ ���
	knapsackPrint(n, B);//��� �־��� ���
	
}



int main(void) {
	FILE *file = NULL;
	fopen_s(&file, "C:\\Users\\���϶�\\Desktop\\knapsack_input_1.txt", "r");
	int size;//�������
	int i = 0;
	if (file != NULL) {
		while (!feof(file)) {
			w= (int*)realloc(w, sizeof(int)*(i + 2));
			b= (int*)realloc(b, sizeof(int)*(i + 2));
			if (i == 0) {
				w[0] = 0;
				b[0] = 0;
			}
			fscanf(file,"%d", &w[i+1]);
			fscanf(file, "%d",&b[i+1]);
			i++;
		}
		W = 10;//����ũ��
		B = (int**)calloc(i+1, sizeof(int*));
		for (int k = 0; k <i+1; k++)
			B[k] = (int*)calloc(W+2,sizeof(int));//W+1���� ����
		fclose(file);
	}
	else
		printf("���� �б� ����");
	
	cout << "Homework2_1\n" << endl;
	Knapsack(i);//knapsack 0-1 problem

	return 0;
}