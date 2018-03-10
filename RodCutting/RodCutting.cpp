#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define INF 1000000000


int* arr;//���ڹ��� �迭
int RecursiveCutRod(int n);
int BottomupCutRod(int n);
void PrintCutRod(int* s, int n);

int* rem;//recursive ��� �߶����� �˱����� ����迭

int RecursiveCutRod(int n) {//����� CutRod
	if (n == 0)//��������
		return 0;
	int q = -INF;//�ʱ�ȭ
	for (int i = 1; i <= n; i++) {
		if (q < arr[i] + RecursiveCutRod(n - i)) {//n�� i�� n-i�� �ڸ��� �� ��θ�
			q = arr[i] + RecursiveCutRod(n - i);//������Ʈ recursive�� n-i�� ��� �ڸ��ΰ��� ȣ��
			rem[n] = i;//����
		}
	}
	return q;//max ����
}

int BottomupCutRod(int n) {//Bottomup Cutrod
	int *r = (int*)malloc(sizeof(int)*(n + 1));//dp
	int *s = (int*)malloc(sizeof(int)*(n + 1));//��� �߶����� ���迭
	r[0] = 0;
	for (int j = 1; j <= n; j++) {
		int q = -INF;//�ʱ�ȭ
		for (int i = 1; i <= j; i++)
			if (q < arr[i] +r[j-i]) {//j���̸� i�� j-i�� �ڸ��� �� ��θ�
				q=arr[i] + r[j-i];//������Ʈ
				s[j] = i;//���
			}
		r[j] = q;//�ִ밪 ����
	}
	PrintCutRod(s,n);//How bottom Cut ���
	cout << "<=Bottomup CutRod";
	return r[n];//�ִ밪 ����
}


void PrintCutRod(int* s,int n) {//��� �߶����� ���
	int temp = n;
	cout << "( ";
	while (temp> 0){
		cout << s[n]<<" ";//��� �߶��� ����ϰ�
		temp = temp - s[n];//��ü���� ���� ���
	}
	cout << ")�� �߸�";
	cout << "cost��";
	temp = n;
	cout << "( ";
	while (temp> 0) {//���� ������� cost ���
		cout << arr[s[temp]] << " ";
		temp =temp - s[temp];
	}
	cout << " )";
}

int main(void) {
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\���϶�\\Desktop\\rod_cutting.txt", "r");
	int size;//�������
	if (f != NULL) {
		while (!feof(f)) {
			fscanf(f, "%d",&size);//�־��� �������
			int index = -1;
			for (int k = 1; k<=size; k++) {
				fscanf(f, "%d",&index);
				arr = (int*)realloc(arr, sizeof(int)*(index + 1));
				fscanf(f, "%d", &arr[index]);//���ҿ� ���� �ִ´�
			}
		}
		fclose(f);
	}
	else
		printf("���� �б� ����");

	rem= (int*)malloc(sizeof(int)*(size + 1));
	cout <<"RecursiveCutRod=>"<<RecursiveCutRod(size)<< endl;
	PrintCutRod(rem, size);//How recursive Cut ���
	cout <<"<=recursive CutRod"<<endl;
	cout << endl<<"BottomupCutRod=>" <<BottomupCutRod(size) << endl;
	return 0;
}