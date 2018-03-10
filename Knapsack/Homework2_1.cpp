#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define INF 1000000000

int* w;//weight input arr
int* b;//benefit input arr
int **B;//dp저장배열

int W;//가방크기


void knapsackPrint(int n, int** B) {
	int i = n;
	int weight = W;
	int maxbenefit = B[i][weight + 1];//최대 benefit
	while (i > 0 && maxbenefit>=0) {//input개수만큼 확인하거나 최대 benefit이 0이 클동안
		if (B[i][weight+1] != B[i - 1][weight+1]) {//그대로 옆으로 옮긴게 아니였다면
			cout << "선택된 item:" << i << endl;
			maxbenefit = maxbenefit - b[i];//benefit에서 빼준다
			weight = weight - w[i];//가방 무게에서 빼준다
			i--;
		}
		else
			i--;//그대로 옆으로옮긴다
	}
}

void Knapsack(int n) {

	for (int i = 1; i <= n; i++){//input 개수와
		for (int j = 1;j <= W+1; j++){//가방 크기만큼 본다
			if (w[i] < j)//가방 크기를 따라가는 변수 j보다 크면 넣을수 있으니
				if (b[i] + B[i - 1][j - w[i]] > B[i - 1][j])//비교해서
					B[i][j] = b[i] + B[i - 1][j - w[i]];//큰걸 넣어준다
				else
					B[i][j] = B[i - 1][j];
			else B[i][j] = B[i - 1][j];//아니면 옆으로 옮긴다
		}
	}

	cout << "max->" <<B[n][W+1]<<endl;//max저장된 위치 출력
	knapsackPrint(n, B);//어떻게 넣었나 출력
	
}



int main(void) {
	FILE *file = NULL;
	fopen_s(&file, "C:\\Users\\신하람\\Desktop\\knapsack_input_1.txt", "r");
	int size;//막대길이
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
		W = 10;//가방크기
		B = (int**)calloc(i+1, sizeof(int*));
		for (int k = 0; k <i+1; k++)
			B[k] = (int*)calloc(W+2,sizeof(int));//W+1까지 쓴다
		fclose(file);
	}
	else
		printf("파일 읽기 실패");
	
	cout << "Homework2_1\n" << endl;
	Knapsack(i);//knapsack 0-1 problem

	return 0;
}