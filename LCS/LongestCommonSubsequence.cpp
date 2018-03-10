#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int x = -1;//ù��° ���� ���ڼ�
int y = -1;//�ι�° ���� ���ڼ�
char* arrx;//ù ���� �迭
char* arry;//�ι�° ���� �迭
int** c;//���� ���ڼ� ���� �迭
char** b;//���� �迭
int** newArri(int m,int n);
char** newArrc(int m, int n);
void LcsLength();//dp�� ����� ���ڸ� �̴� �Լ�
void LcsPrint(int i, int j);//����Ȱ� ����ϴ� �Լ�

void LcsLength(){//���� ���� �̱�
	int m = x;//ù��° ������ ����
	int n = y;//�ι�° ������ ����
	c = newArri(m+1, n+1);//m+1 by n+1 int �迭 ����
	b = newArrc(m+1, n+1);//m+1 by n+1 char �迭 ����
	for (int i = 1; i <= m; i++)//�ʱ�ȭ
		c[i][0] = 0;
	for (int j = 0; j <= n; j++)//�ʱ�ȭ
		c[0][j] = 0;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (arrx[i] == arry[j]) {//���ڰ� ������
				c[i][j] = c[i - 1][j - 1] + 1;//���ſ��� +1
				b[i][j] = 'q';//�밢��
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {//���߿� �� ū����
				c[i][j] = c[i - 1][j];//������Ʈ
				b[i][j] = 'u';//up
			}
			else {
				c[i][j] = c[i][j - 1];//���߿� �� ū���� ������Ʈ
				b[i][j] = 'l';//left
			}
		}
	}
}

void LcsPrint(int i, int j) {//����Ʈ �ϴ� �Լ�
	if (i == 0 || j == 0)//���� ����
		return;
	if (b[i][j] == 'q') {//�밢�̸�
		LcsPrint(i - 1, j - 1);//�밢���� ������
		printf("%c", arrx[i]);//���
	}
	else if (b[i][j] == 'u')//����
		LcsPrint(i - 1, j);//�Ʒ���
	else//�����̸�
		LcsPrint(i, j - 1);//����������
}

int** newArri(int m,int n) {//m*n int�迭 ����
	int** temp;
	temp = (int**)malloc(sizeof(int*)*m);
	for (int i = 0; i < m; i++)
		temp[i] = (int*)malloc(sizeof(int)*n);
	return temp;
}

char** newArrc(int m, int n) {//m*n char�迭 ����
	char** temp;
	temp = (char**)malloc(sizeof(char*)*m);
	for (int i = 0; i < m; i++)
		temp[i] = (char*)malloc(sizeof(char)*n);
	return temp;
}

int main(void) {
	char* str1=NULL;//ù��° sentence
	char* str2 = NULL;//�ι�° sentence
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\���϶�\\Desktop\\sample_lcs1.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
				fscanf(f, "%d", &x);
				arrx = (char*)malloc(sizeof(char)*(x+1));
				fscanf(f,"%s",arrx+1);
				fscanf(f, "%d", &y);
				arry = (char*)malloc(sizeof(char)*(y+1));
				fscanf(f, "%s",arry+1);
			}
		fclose(f);
	}
	else
		printf("���� �б� ����");
	LcsLength();//����� ���ڼ� ���� dp �Լ�
	printf("LCS=> ");
	LcsPrint(x,y);//����� ���� print �Լ�
	return 0;
}