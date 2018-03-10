#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define INF 1000000000

double* w;//weight input arr
int* b;//benefit input arr
double **B;//dp ���� �迭

double W;//���� ũ��


void knapsackPrint(int n, double** B) {//����ϴ� �Լ�
	int i = n;
	double weight = W;
	int maxbenefit = B[i][(int)((weight)*100.0) + 1];//���� ���� �ִ� benefit
	while (i > 0 && maxbenefit>=0) {//i��ŭ �ϴµ� max�� 0�̻��� ����
		if (B[i][(int)((weight)*100.0) +1] != B[i - 1][(int)((weight)*100.0) + 1]){//�Ҽ��� 2° �ڸ��̹Ƿ� 100���ϰ� �տ����� ������ �״�� �ű���̹Ƿ� �״�� �ű�� �ƴ϶��
			cout << "���õ� item:" << i << endl;//���
			maxbenefit = maxbenefit - b[i];//benefit���� ���ش�
			weight = weight - (w[i]);//���� ���Ը� �ٿ��ش�
			i--;
		}
		else
			i--;//�׳� �������� �̵�
	}
}

void Knapsack(int n) {
	for (int i = 1; i <= n; i++){//���� ������ �����ϰ� �ذ������� �Ҽ����� �ذ��ϱ����� *100�� ó�����ش�
		for (int j = 1;j <= W*100.0+1; j++){
			if ((w[i] * 100.0) < (double)(j))//-���� �ƴ϶��
				if (b[i] + B[i - 1][(int)((j - w[i] * 100.0))] >B[i-1][j])//ū�� ���ؼ� �־��ش�
					B[i][j] = b[i] + B[i - 1][(int)((j - w[i] * 100.0))];
				else
					B[i][j] = B[i - 1][j];
			else B[i][j] = B[i - 1][j];//�ƴϸ� ������ �ű�
		}
	}


	cout << "max->" <<B[n][(int)((W)*100.0)+1]<<endl;//�ִ� benefit ����� ��ġ ���
	knapsackPrint(n, B);//���
}



int main(void) {
	FILE *file = NULL;
	fopen_s(&file, "C:\\Users\\���϶�\\Desktop\\knapsack_input_2.txt", "r");
	int i = 0;
	if (file != NULL) {
		while (!feof(file)) {
			w= (double*)realloc(w, sizeof(double)*(i + 2));
			b= (int*)realloc(b, sizeof(int)*(i + 2));
			if (i == 0) {
				w[0] = 0;
				b[0] = 0;
			}
			fscanf(file,"%lf", &w[i+1]);//index 1���� weight�� benefit�� �Է¹޴´�
			fscanf(file,"%d",&b[i+1]);
			i++;
		}
		W = 1.00;//���� ũ��

		B = (double**)calloc((i+1),sizeof(double*));
		for (int k = 0; k <(i+1); k++)
			B[k] = (double*)calloc((W*100+2),sizeof(double));//�Ҽ��Ʒ� 2°¥�� �����̹Ƿ� 100�� �����ش� �׸��� �ʿ��� ���� 1�� �����ش�->W+1���� ���� ������
		
		fclose(file);
	}
	else
		printf("���� �б� ����");
	cout << "Homework2_2\n" << endl;
	Knapsack(i);//knapsack 0-1 problem

	return 0;
}