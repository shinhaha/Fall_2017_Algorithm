#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define INF 1000000000

typedef struct OBST {//OST Build�� ���� struct OBST
	int KEY;
	struct OBST *left, *right;
}OBST;
OBST *ROOT;

double* p;//node���� �迭
double* q;//dummy ���� �迭

void TablePrint(int** arr, int n);
void OptimalBST(int n);
double** DoublenewArr(int n, int m);
int** IntnewArr(int n, int m);
OBST *Build_OBST(int** root, int i, int j,int index,int h);
void DISPLAY(int* A,int n);

int* MarkArr;//Ʈ������ ����� ���� �迭
int Maxh = 0;//�ִ� ����
int NumberOfParameter = 0;//node���� ����
int dummy = 1;//dummy �ε���

void OptimalBST(int n) {//�������� ����ش�
	double** e = DoublenewArr(n + 1, n);//i��°���� j������ ����Ʈ���� �˻��ð� ����
	double** w = DoublenewArr(n + 1, n);//���� Ȯ��
	int** root = IntnewArr(n, n);//����Ʈ���� �����Ҽ��ִ� 2���� �迭

	for (int i = 0; i <= n; i++) {//�ʱ�ȭ
		e[i + 1][i] = q[i];
		w[i + 1][i] = q[i];
	}

	for (int l = 1; l <= n; l++)//��� ������ŭ
		for (int i = 1; i <= n - l + 1; i++) {//chain length
			int j = i + l - 1;
			e[i][j] = INF;//�ʱ�ȭ
			w[i][j] = w[i][j - 1] + p[j] + q[j];//����
			for (int r = i; r <= j; r++) {
				double t = e[i][r - 1] + e[r + 1][j] + w[i][j];//key index r�� ������ subtree 1���� r-1    subtree r+1���� n���� ��հ˻��ð�
				if (t < e[i][j]) {//�� ������
					e[i][j] = t;//������Ʈ
					root[i][j] = r;//����
				}
			}
		}

	cout << "ROOT table:";
	TablePrint(root, n);//root table ���
	cout << endl << endl;
	MarkArr = (int*)calloc(pow(2, NumberOfParameter), sizeof(int));//Ʈ������ ����� ���� �迭�Ҵ�
	ROOT = Build_OBST(root, 1,n,0,1);//OBST Build
	cout << endl;
	cout <<"\nOBST Tree:"<< endl;
	DISPLAY(MarkArr,Maxh);//OBST ���
}

OBST *Build_OBST(int** root, int i, int j,int index,int h) {//OBST Tree �����Լ� i,j�� root ���̺��� �ε��� 
	//index�� Ʈ������ ����� ���� �迭������ �ε��� h�� ����
	OBST *ptr;
	if(i!=0&&j!=0&&root[i][j]!=0)//���ϴ� ��¸� ��
		cout << i << "," << j << "������=>" << root[i][j] << endl;
	if (root[i][j] == 0) {
		ptr = NULL;//NULL�̸�
		MarkArr[index] = -(dummy++);//dummy null�� ������ ���� ������ ����
	}
	else {
		ptr = new OBST;
		Maxh = max(h, Maxh);//�ִ� ���̰��� ������Ʈ
		ptr->KEY = root[i][j];//ptr�� ���� �ִ´�
		MarkArr[index] = ptr->KEY;//�迭���� �� ����
		ptr->left = Build_OBST(root, i, root[i][j] - 1,2*index+1,h+1);//index 0 ���� �����̶� left�� 2*i+1
		if (root[i][j] + 1 <= NumberOfParameter)
			ptr->right = Build_OBST(root, root[i][j] + 1, j,2*index+2,h+1); //index 0 ���� �����̶� right�� 2*i+2
		else {//������ �ڽ��� NULL�̸�
			ptr->right = NULL;
			MarkArr[2 * index + 2]=-(dummy++);//dummy null�� ������ ���� ������ ����
		}
	}
	return ptr;
}

void DISPLAY(int* A,int h) {// ����Ʈ�� ����ϴ� �Լ�
	int gap = 16;//��ĭ
	int level = 0;//����
	int levelNum = 1;//���� ���Ҽ�
	int index = 0;//A�迭�� index
	while (level<=(h+1)){//���� ������ +1 ��ŭ ���
		cout << "D" << level << ": ";
		for (int ln = 0; ln < levelNum; ln++) {//���� ���Ҽ���ŭ ���
			for (int i = 0; i <gap; i++)//gap ��ŭ ����
				cout << " ";
			if (A[index] < 0)//dummy�� ����
				cout << "d" <<-(A[index]+1);//-1���� �����ε� ����� 0�����̹Ƿ� 1���ؼ� ������ ó��
			else if (A[index] == 0)//NULL�̸� 0
				cout << "X";
			else 
				cout << "k" << A[index]<<" ";//node�� �� ���
			index++;
		}
		cout << endl;//���
		levelNum *= 2;//���Ҽ� 2��
		gap /= 2;//��ĭ ������
		level++;//���� ++
	}
}

void TablePrint(int** arr, int n) {//root table ���
	for (int i = 1; i <= n; i++) {
		cout << endl;
		for (int j = 1; j <= n; j++)
			printf("%d ", arr[i][j]);
	}
}


double** DoublenewArr(int n, int m) {//n*m double matrix returns
	double** temp;
	temp = (double**)calloc((n + 1), sizeof(double*));
	for (int i = 0; i <= n; i++)
		temp[i] = (double*)calloc((m + 1), sizeof(double));
	return temp;
}

int** IntnewArr(int n, int m) {//n*m int matrix returns
	int** temp;
	temp = (int**)calloc((n + 1), sizeof(int*));
	for (int i = 0; i <= n; i++)
		temp[i] = (int*)calloc((m + 1), sizeof(int));
	return temp;
}

int main(void) {
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\���϶�\\Desktop\\OBST.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			fscanf(f, "%d", &NumberOfParameter);//���Ұ���
			p = (double*)malloc(sizeof(double)*(NumberOfParameter + 1));
			q = (double*)malloc(sizeof(double)*(NumberOfParameter + 1));
			for (int i = 1; i <= NumberOfParameter; i++)
				fscanf(f, "%lf", &p[i]);
			for (int i = 0; i <= NumberOfParameter; i++)
				fscanf(f, "%lf", &q[i]);
		}
		fclose(f);
	}
	else
		printf("���� �б� ����");
	OptimalBST(NumberOfParameter);
	return 0;
}