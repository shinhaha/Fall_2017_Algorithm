#include <stdio.h>
#include <stdlib.h>


int size;//원소개수
int A;//출력할 숫자
int* arr;//인자받을 배열
int** newArr(int n);//새로운 n*n배열 리턴
void MatrixChainOrder();//dp함수
void PrintOptimalParens(int** s, int i, int j);//recursion 출력 함수

#define INF 200000000

void MatrixChainOrder() {
	int n = size;//원소개수
	int** m = newArr(n + 1);//n+1크기의 2차원 매트릭스 생성 값 저장
	int** s = newArr(n + 1);

	for (int i = 1; i <= n; i++)//i,i 자기자신 하나만 쓰는경우 0으로 초기화
		m[i][i] = 0;

	for (int l = 2; l <= n; l++) {//chain length
		for (int i = 1; i <= n - l + 1; i++) {//i를 1부터 보는데 chain length만큼 감해서 확인한다
			int j = i + l - 1;//i시작점에서 chain length l만큼 더함
			m[i][j] = INF;//초기화
			for (int k = i; k <= j - 1; k++) {
				int q = m[i][k] + m[k + 1][j] + (arr[i - 1] * arr[k] * arr[j]);//i~k의 최소값 k+1~j 의 최소값을 더하고 2개의행렬 곱 더한게(combine)
				if (q < m[i][j]) {//원래 값보다 작으면
					m[i][j] = q;//업데이트
					s[i][j] = k;//업데이트
				}
			}
		}
	}
	A = 1;//print함수에서 i==j일때 출력 할 숫자
	PrintOptimalParens(s, 1, n );//어떻게 계산해야되는지 출력
	printf("\nCost:%d", m[1][n]);//최대값이 저장되어 있는 인덱스
}


void PrintOptimalParens(int** s, int i, int j) {//재귀적으로 출력하는 함수
	if (i == j)//같으면 출력
		printf("%d ",A++);//출력 숫자 ++
	else {
		printf("( ");
		PrintOptimalParens(s, i, s[i][j]);//재귀적 호출
		PrintOptimalParens(s, s[i][j] + 1, j);
		printf(") ");
	}
}

int** newArr(int n) {//n을 넣으면 새로운 n*n 매트릭스를 내뱉는다.
	int** temp;//리턴할 2차원 배열
	temp = (int**)malloc(sizeof(int*)*n);//할당
	for (int i = 0; i < n; i++)
		temp[i] = (int*)malloc(sizeof(int)*n);
	return temp;
}

int main(void) {
	int i = 0;
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\신하람\\Desktop\\sample_mat1.txt", "r");
	if (f != NULL) {
		while (!feof(f)) {
			if (i == 0) {
				fscanf(f, "%d", &size);//원소 개수 받고
				arr = (int*)malloc(sizeof(int)*size);//원소 개수만큼 할당
			}
			fscanf(f, "%d", &arr[i]);//원소에 값을 넣는다
			i++;
		}
		fclose(f);
	}
	else
		printf("파일 읽기 실패");
	MatrixChainOrder();//함수 실행
	return 0;
}