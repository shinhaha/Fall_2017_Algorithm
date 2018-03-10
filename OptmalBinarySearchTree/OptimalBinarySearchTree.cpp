#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define INF 1000000000

typedef struct OBST {//OST Build를 위한 struct OBST
	int KEY;
	struct OBST *left, *right;
}OBST;
OBST *ROOT;

double* p;//node받을 배열
double* q;//dummy 받을 배열

void TablePrint(int** arr, int n);
void OptimalBST(int n);
double** DoublenewArr(int n, int m);
int** IntnewArr(int n, int m);
OBST *Build_OBST(int** root, int i, int j,int index,int h);
void DISPLAY(int* A,int n);

int* MarkArr;//트리구조 출력을 위한 배열
int Maxh = 0;//최대 높이
int NumberOfParameter = 0;//node원소 개수
int dummy = 1;//dummy 인덱스

void OptimalBST(int n) {//공간들을 잡아준다
	double** e = DoublenewArr(n + 1, n);//i번째부터 j번까지 최적트리의 검색시간 정보
	double** w = DoublenewArr(n + 1, n);//선택 확률
	int** root = IntnewArr(n, n);//최적트리를 구축할수있는 2차원 배열

	for (int i = 0; i <= n; i++) {//초기화
		e[i + 1][i] = q[i];
		w[i + 1][i] = q[i];
	}

	for (int l = 1; l <= n; l++)//노드 개수만큼
		for (int i = 1; i <= n - l + 1; i++) {//chain length
			int j = i + l - 1;
			e[i][j] = INF;//초기화
			w[i][j] = w[i][j - 1] + p[j] + q[j];//누적
			for (int r = i; r <= j; r++) {
				double t = e[i][r - 1] + e[r + 1][j] + w[i][j];//key index r이 있을때 subtree 1부터 r-1    subtree r+1부터 n까지 평균검색시간
				if (t < e[i][j]) {//더 작으면
					e[i][j] = t;//업데이트
					root[i][j] = r;//조상
				}
			}
		}

	cout << "ROOT table:";
	TablePrint(root, n);//root table 출력
	cout << endl << endl;
	MarkArr = (int*)calloc(pow(2, NumberOfParameter), sizeof(int));//트리구조 출력을 위한 배열할당
	ROOT = Build_OBST(root, 1,n,0,1);//OBST Build
	cout << endl;
	cout <<"\nOBST Tree:"<< endl;
	DISPLAY(MarkArr,Maxh);//OBST 출력
}

OBST *Build_OBST(int** root, int i, int j,int index,int h) {//OBST Tree 빌드함수 i,j는 root 테이블의 인덱스 
	//index는 트리구조 출력을 위한 배열에서의 인덱스 h는 높이
	OBST *ptr;
	if(i!=0&&j!=0&&root[i][j]!=0)//원하는 출력만 함
		cout << i << "," << j << "조상은=>" << root[i][j] << endl;
	if (root[i][j] == 0) {
		ptr = NULL;//NULL이면
		MarkArr[index] = -(dummy++);//dummy null과 구분을 위해 음수로 넣음
	}
	else {
		ptr = new OBST;
		Maxh = max(h, Maxh);//최대 높이값을 업데이트
		ptr->KEY = root[i][j];//ptr에 값을 넣는다
		MarkArr[index] = ptr->KEY;//배열에도 값 저장
		ptr->left = Build_OBST(root, i, root[i][j] - 1,2*index+1,h+1);//index 0 부터 시작이라 left는 2*i+1
		if (root[i][j] + 1 <= NumberOfParameter)
			ptr->right = Build_OBST(root, root[i][j] + 1, j,2*index+2,h+1); //index 0 부터 시작이라 right는 2*i+2
		else {//오른쪽 자식이 NULL이면
			ptr->right = NULL;
			MarkArr[2 * index + 2]=-(dummy++);//dummy null과 구분을 위해 음수로 넣음
		}
	}
	return ptr;
}

void DISPLAY(int* A,int h) {// 이진트리 출력하는 함수
	int gap = 16;//빈칸
	int level = 0;//높이
	int levelNum = 1;//레벨 원소수
	int index = 0;//A배열의 index
	while (level<=(h+1)){//리프 높이의 +1 만큼 출력
		cout << "D" << level << ": ";
		for (int ln = 0; ln < levelNum; ln++) {//레벨 원소수만큼 출력
			for (int i = 0; i <gap; i++)//gap 만큼 띄우고
				cout << " ";
			if (A[index] < 0)//dummy면 음수
				cout << "d" <<-(A[index]+1);//-1부터 시작인데 출력은 0부터이므로 1더해서 음수로 처리
			else if (A[index] == 0)//NULL이면 0
				cout << "X";
			else 
				cout << "k" << A[index]<<" ";//node면 값 출력
			index++;
		}
		cout << endl;//띄움
		levelNum *= 2;//원소수 2배
		gap /= 2;//빈칸 반으로
		level++;//높이 ++
	}
}

void TablePrint(int** arr, int n) {//root table 출력
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
	fopen_s(&f, "C:\\Users\\신하람\\Desktop\\OBST.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			fscanf(f, "%d", &NumberOfParameter);//원소개수
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
		printf("파일 읽기 실패");
	OptimalBST(NumberOfParameter);
	return 0;
}