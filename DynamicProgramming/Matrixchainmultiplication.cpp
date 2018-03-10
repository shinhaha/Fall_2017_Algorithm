#include <stdio.h>
#include <stdlib.h>


int size;//���Ұ���
int A;//����� ����
int* arr;//���ڹ��� �迭
int** newArr(int n);//���ο� n*n�迭 ����
void MatrixChainOrder();//dp�Լ�
void PrintOptimalParens(int** s, int i, int j);//recursion ��� �Լ�

#define INF 200000000

void MatrixChainOrder() {
	int n = size;//���Ұ���
	int** m = newArr(n + 1);//n+1ũ���� 2���� ��Ʈ���� ���� �� ����
	int** s = newArr(n + 1);

	for (int i = 1; i <= n; i++)//i,i �ڱ��ڽ� �ϳ��� ���°�� 0���� �ʱ�ȭ
		m[i][i] = 0;

	for (int l = 2; l <= n; l++) {//chain length
		for (int i = 1; i <= n - l + 1; i++) {//i�� 1���� ���µ� chain length��ŭ ���ؼ� Ȯ���Ѵ�
			int j = i + l - 1;//i���������� chain length l��ŭ ����
			m[i][j] = INF;//�ʱ�ȭ
			for (int k = i; k <= j - 1; k++) {
				int q = m[i][k] + m[k + 1][j] + (arr[i - 1] * arr[k] * arr[j]);//i~k�� �ּҰ� k+1~j �� �ּҰ��� ���ϰ� 2������� �� ���Ѱ�(combine)
				if (q < m[i][j]) {//���� ������ ������
					m[i][j] = q;//������Ʈ
					s[i][j] = k;//������Ʈ
				}
			}
		}
	}
	A = 1;//print�Լ����� i==j�϶� ��� �� ����
	PrintOptimalParens(s, 1, n );//��� ����ؾߵǴ��� ���
	printf("\nCost:%d", m[1][n]);//�ִ밪�� ����Ǿ� �ִ� �ε���
}


void PrintOptimalParens(int** s, int i, int j) {//��������� ����ϴ� �Լ�
	if (i == j)//������ ���
		printf("%d ",A++);//��� ���� ++
	else {
		printf("( ");
		PrintOptimalParens(s, i, s[i][j]);//����� ȣ��
		PrintOptimalParens(s, s[i][j] + 1, j);
		printf(") ");
	}
}

int** newArr(int n) {//n�� ������ ���ο� n*n ��Ʈ������ ����´�.
	int** temp;//������ 2���� �迭
	temp = (int**)malloc(sizeof(int*)*n);//�Ҵ�
	for (int i = 0; i < n; i++)
		temp[i] = (int*)malloc(sizeof(int)*n);
	return temp;
}

int main(void) {
	int i = 0;
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\���϶�\\Desktop\\sample_mat1.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			if (i == 0) {
				fscanf(f, "%d", &size);//���� ���� �ް�
				arr = (int*)malloc(sizeof(int)*size);//���� ������ŭ �Ҵ�
			}
			fscanf(f, "%d", &arr[i]);//���ҿ� ���� �ִ´�
			i++;
		}
		fclose(f);
	}
	else
		printf("���� �б� ����");
	MatrixChainOrder();//�Լ� ����
	return 0;
}