#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int x = -1;//첫번째 문장 글자수
int y = -1;//두번째 문장 글자수
char* arrx;//첫 문장 배열
char* arry;//두번째 문장 배열
int** c;//공통 글자수 저장 배열
char** b;//방향 배열
int** newArri(int m,int n);
char** newArrc(int m, int n);
void LcsLength();//dp로 공통된 문자를 뽑는 함수
void LcsPrint(int i, int j);//공통된거 출력하는 함수

void LcsLength(){//공통 문자 뽑기
	int m = x;//첫번째 문장의 길이
	int n = y;//두번째 문장의 길이
	c = newArri(m+1, n+1);//m+1 by n+1 int 배열 생성
	b = newArrc(m+1, n+1);//m+1 by n+1 char 배열 생성
	for (int i = 1; i <= m; i++)//초기화
		c[i][0] = 0;
	for (int j = 0; j <= n; j++)//초기화
		c[0][j] = 0;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (arrx[i] == arry[j]) {//문자가 같으면
				c[i][j] = c[i - 1][j - 1] + 1;//전거에서 +1
				b[i][j] = 'q';//대각선
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {//전중에 더 큰것을
				c[i][j] = c[i - 1][j];//업데이트
				b[i][j] = 'u';//up
			}
			else {
				c[i][j] = c[i][j - 1];//전중에 더 큰것을 업데이트
				b[i][j] = 'l';//left
			}
		}
	}
}

void LcsPrint(int i, int j) {//프린트 하는 함수
	if (i == 0 || j == 0)//종료 조건
		return;
	if (b[i][j] == 'q') {//대각이면
		LcsPrint(i - 1, j - 1);//대각으로 내려감
		printf("%c", arrx[i]);//출력
	}
	else if (b[i][j] == 'u')//위면
		LcsPrint(i - 1, j);//아래로
	else//왼쪽이면
		LcsPrint(i, j - 1);//오른쪽으로
}

int** newArri(int m,int n) {//m*n int배열 리턴
	int** temp;
	temp = (int**)malloc(sizeof(int*)*m);
	for (int i = 0; i < m; i++)
		temp[i] = (int*)malloc(sizeof(int)*n);
	return temp;
}

char** newArrc(int m, int n) {//m*n char배열 리턴
	char** temp;
	temp = (char**)malloc(sizeof(char*)*m);
	for (int i = 0; i < m; i++)
		temp[i] = (char*)malloc(sizeof(char)*n);
	return temp;
}

int main(void) {
	char* str1=NULL;//첫번째 sentence
	char* str2 = NULL;//두번째 sentence
	FILE *f = NULL;
	fopen_s(&f, "C:\\Users\\신하람\\Desktop\\sample_lcs1.txt", "r");
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
		printf("파일 읽기 실패");
	LcsLength();//공통된 문자수 세는 dp 함수
	printf("LCS=> ");
	LcsPrint(x,y);//공통된 문자 print 함수
	return 0;
}